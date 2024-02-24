#define LINUX
#include <linux/module.h>
#include <linux/kernel.h>
/*Dep for procfs*/
#include <linux/proc_fs.h> /* Necessary because we use the proc fs */
#include <linux/uaccess.h> /* For copy_from_user */
#include <linux/version.h>
#include <linux/string.h> /* For memset */
/*End of Dep for Procfs*/
#include "kmlab_given.h"

/*Dep for Linked List*/
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/types.h>
/*End of Dep for Linked List*/

/*chardev*/
#include <linux/atomic.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/init.h>
/*chardev*/

/*Timers*/
#include <linux/jiffies.h>
#include <linux/timer.h>
/*Timers*/

/*Queue*/
#include <linux/workqueue.h>
/*Queue*/

/*spinlock*/
#include <linux/spinlock.h>
/*spinlock*/

// Include headers as needed ...


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Takada"); // Change with your lastname
MODULE_DESCRIPTION("CPTS360 Lab 4");

#define DEBUG 1

// Global variables as needed ...

/*Linked List Global Variables*/

struct ll_struct {
		struct list_head list;
		long int value;
        int pid;
};

struct list_head my_list;
struct proc_dir_entry *proc;

/*Linked List Global Variables*/

/*Procfs Global Variables*/
#define PROCFS_DIR "kmlab"
#define PROCFS_NAME "status"

/* This structure hold information about the /proc file */
static struct proc_dir_entry *our_proc_file, *example_dir;
#define KMLAB_MAX_SIZE 1024
static char proc_buffer[KMLAB_MAX_SIZE] = "";
/*ProcFS Global Variables*/

/*chardev Global Variables*/
#define BUF_LEN 80 /* Max length of the message from the device */

/* Global variables are declared as static, so are global within the file. */
static int major; /* major number assigned to our device driver */
enum {
    CDEV_NOT_USED = 0,
    CDEV_EXCLUSIVE_OPEN = 1,
};

/* Is device open? Used to prevent multiple access to device */
static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED);
static struct class *cls;

/*chardev Global Variables*/

/*Timer Global Variables*/
static struct workqueue_struct *queue = NULL;
static struct work_struct work;

static struct timer_list my_timer;
int time_interval = 5000;
/*Timer Global Variables*/

/*Spinlock and work queue global vars*/
static DEFINE_SPINLOCK(sl_static);
/*Spinlock and work queue global vars*/

/*Linked List functions*/

int add_node(int pid)
{
   struct ll_struct *new_node = kmalloc((size_t) (sizeof(struct ll_struct)), GFP_KERNEL);
   if (!new_node) {
      printk(KERN_INFO "Memory allocation failed, this should never fail due to GFP_KERNEL flag\n");
      return 1;
   }
   new_node->pid = pid;
   new_node->value = 0;
   list_add_tail(&(new_node->list), &my_list);
   return 0;
}

int delete_node(int number)
{
   struct ll_struct *entry = NULL, *n;

   list_for_each_entry_safe(entry, n, &my_list, list) {
      if (entry->pid == number) {
         printk(KERN_INFO "Found the element %d\n",
                entry->pid);
         list_del(&(entry->list));
         kfree(entry);
         return 0;
      }
   }
   printk(KERN_INFO "Could not find the element %d\n", number);
   return 1;
}

static void destroy_list(void)
{
    struct list_head *i, *n;
    struct ll_struct *ple;

    list_for_each_safe(i, n, &my_list) {
        ple = list_entry(i, struct ll_struct, list);
        list_del(i);
        kfree(ple);
    }
}


void show_list(void)
{
   struct ll_struct *entry = NULL;

   list_for_each_entry(entry, &my_list, list) {
      printk(KERN_INFO "%d: %ld\n", entry->pid, entry->value);
   }
}

//Updates list by deleting process data that have expired
void update_list(void){

   struct list_head *i, *n;
   struct ll_struct *ple;
      
   list_for_each_safe(i, n, &my_list) {
      ple = list_entry(i, struct ll_struct, list);
      if(get_cpu_use(ple->pid, &(ple->value)) == -1){
         list_del(i);
         kfree(ple);
      }
   }
};

/*End of Linked List functions*/

/*PROCFS functions*/

/* This function is called then the /proc file is read */
static ssize_t procfile_read(struct file *file_pointer, char __user *buffer,
                             size_t buffer_length, loff_t *offset)
{   
    struct ll_struct *entry = NULL;
    char temp[100] = "";
    memset(&proc_buffer[0], 0, sizeof(proc_buffer));
    

    list_for_each_entry(entry, &my_list, list) {
        snprintf(temp, sizeof(proc_buffer), "Process %d: CPU Time %ld\n", entry->pid, entry->value);
        strcat(proc_buffer, temp);
        memset(&temp[0], 0, sizeof(temp));
    }


    if(*offset >= sizeof(proc_buffer)) {
      return -EBUSY;
   }
   
   if(copy_to_user(buffer, proc_buffer, sizeof(proc_buffer))) {
      return -EBUSY;
   } 
   pr_info("procfile read /proc/%s/%s\n%s", PROCFS_DIR, PROCFS_NAME, proc_buffer);
   *offset += sizeof(proc_buffer);

   return sizeof(proc_buffer);
}

/* This function is called with the /proc file is written. */
ssize_t procfile_write(struct file *filp, const char __user * buffer, size_t count, loff_t *pos)
{
   char *str;
   int pid = 0;

   // printk("Calling Proc Write");
   str = kmalloc((size_t) count, GFP_KERNEL);
   if (copy_from_user(str, buffer, count)) {
        kfree(str);
        return -EFAULT;
   }
    sscanf(str, "%d", &pid);
    printk(KERN_INFO "Adding data to linked list %d\n", pid);
    add_node(pid);

   kfree(str);
   return count;
}

static const struct proc_ops proc_file_fops = {
    .proc_read = procfile_read,
    .proc_write = procfile_write,
};

/*End of PROCFS functions */

/*CharDev functions*/

// Called when a process tries to open the device file, "sudo cat /dev/chardev"
static int device_open(struct inode *inode, struct file *file)
{
      printk(KERN_INFO "In the device_open func\n");
   if (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN))
      return -EBUSY;

   try_module_get(THIS_MODULE);

   return 0;
}

// Called when a process closes the device file
static int device_release(struct inode *inode, struct file *file)
{
   /* We're now ready for our next caller */
   atomic_set(&already_open, CDEV_NOT_USED);

   /* Decrement the usage count, or else once you opened the file, you will
   * never get rid of the module.
   */
   module_put(THIS_MODULE);

   return 0;
}

static struct file_operations chardev_fops = {
   .open = device_open,
   .release = device_release,
};

/*end of CharDev functions*/

/*Timer functions*/

void my_timer_callback(struct timer_list *timer) {
   pr_info("This line is printed every %d ms.\n", time_interval);
   schedule_work(&work);
   /* this will make a periodic timer */
   mod_timer(&my_timer, jiffies + msecs_to_jiffies(time_interval));
}
/*end of Timer functions */

/*Queue & spinlock functions */

static void work_handler(struct work_struct *data)
{
   unsigned long flags;
   pr_info("work handler function.\n");
   spin_lock_irqsave(&sl_static, flags);
   pr_info("Locked static spinlock\n");

   update_list();

   spin_unlock_irqrestore(&sl_static, flags);
    pr_info("Unlocked static spinlock\n");
}

/*Queue & spinlock*/



// kmlab_init - Called when module is loaded
int __init kmlab_init(void)
{
   #ifdef DEBUG
   pr_info("KMLAB MODULE LOADING\n");
   #endif
   /*Start PROCFS*/
   example_dir = proc_mkdir(PROCFS_DIR, NULL);
   if(example_dir == NULL) {
      pr_alert("Error:Could not initialize /proc/%s\n", PROCFS_DIR);
      return -ENOMEM;
   }
   pr_info("/proc/%s created\n", PROCFS_DIR);

   our_proc_file = proc_create(PROCFS_NAME, 0666, example_dir, &proc_file_fops);
      if (NULL == our_proc_file) {
         pr_alert("Error:Could not initialize /proc/%s/%s\n", PROCFS_DIR, PROCFS_NAME);
         return -ENOMEM;
      }
   pr_info("/proc/%s%s Created\n", PROCFS_DIR, PROCFS_NAME);
   /*End PROCFS*/

   /*Start Linked List*/
   INIT_LIST_HEAD(&my_list);
   /*End Linked List*/

   /*CharDev*/
   major = register_chrdev(0, PROCFS_NAME, &chardev_fops);
   if (major < 0) {
      pr_alert("Registering char device failed with %d\n", major);
      return major;
   }
   cls = class_create(THIS_MODULE, PROCFS_NAME);
   device_create(cls, NULL, MKDEV(major, 0), NULL, PROCFS_NAME);
   pr_info("Device created on /dev/%s/%s\n", PROCFS_DIR, PROCFS_NAME);
   /*CharDev*/

   /*Timer*/
   /* Setup the timer for initial use. Look in linux/timer.h for this function */
   timer_setup(&my_timer, my_timer_callback, 0);
   mod_timer(&my_timer, jiffies + msecs_to_jiffies(time_interval));
   /*Timer*/

   /*Queue*/
   queue = alloc_workqueue("WORKQUEUE", WQ_UNBOUND, 1);
   INIT_WORK(&work, work_handler);
   /*Queue*/

pr_info("KMLAB MODULE LOADED\n");
return 0;   
}

// kmlab_exit - Called when module is unloaded
void __exit kmlab_exit(void)
{
   #ifdef DEBUG
   pr_info("KMLAB MODULE UNLOADING\n");
   #endif

   /*Start PROCFS*/
   proc_remove(our_proc_file);
   proc_remove(example_dir);
   pr_info("/proc/%s/%s removed\n", PROCFS_DIR, PROCFS_NAME);
   pr_info("/proc/%s removed\n", PROCFS_DIR);
   /*End PROCFS*/

   /*Start Linked List*/
   destroy_list();
   /*End Linked List*/

   /*CharDev*/
   device_destroy(cls, MKDEV(major, 0));
   class_destroy(cls);
   unregister_chrdev(major, PROCFS_NAME);
   /*CharDev*/

   /*Timer*/
   del_timer(&my_timer);
   /*Timer*/

   /*Queue*/
   destroy_workqueue(queue);
   /*Queue*/

   pr_info("KMLAB MODULE UNLOADED\n");
}

// Register init and exit funtions
module_init(kmlab_init);
module_exit(kmlab_exit);
