#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// you can use additional headers as needed

typedef struct node {
	char  name[64];       // node's name string
	char  type;
	struct node *child, *sibling, *parent;
} NODE;


NODE *root; 
NODE *cwd;
char *cmd[10] = {"mkdir","rmdir","cd","ls","pwd","creat","rm","save","reload","quit"};  // fill with list of commands
char cwd_filepath[30] = "";

// other global variables

void add_sibling(char *name, char type, NODE *sibling){
	NODE *new_node = (NODE *)malloc(sizeof(NODE));	
	sibling->sibling = new_node;
	strcpy(new_node->name,name);
	new_node->type = type;
	new_node->child = NULL;
	new_node->sibling = NULL;
	new_node->parent = NULL;
	//printf("Added sibling: %s\n",name);
}

void add_child(char *name, char type, NODE *parent){
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	parent->child = new_node;
	strcpy(new_node->name,name);
	new_node->type = type;
	new_node->child = NULL;
	new_node->sibling = NULL;
	new_node->parent = parent;
	//printf("Added child: %s\n",name);
}
void delete(NODE *t){
	t->child = NULL;
	strcpy(t->name,"\0");
	t->parent =NULL;
	t->sibling = NULL;
	t->type = '\0';
	free(t);
}
int initialize() {
	root = (NODE *)malloc(sizeof(NODE));
	strcpy(root->name, "/");
	root->parent = root;
	root->sibling = root;
	root->child = NULL;
	root->type = 'D';
	cwd = root; //Current Working Directory
	printf("Filesystem initialized!\n");
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
}

void find_header(char *param){
	char *token;
	NODE *tmp;
	if(param[0] == '/'){
		tmp = root;
	}else{
		tmp = cwd;
	}
	if (strcmp(param,"") == 0){
		tmp = cwd;
		tmp = tmp->child;
		while(tmp != NULL){
			printf("%c %s\t",tmp->type, tmp->name);
			tmp = tmp->sibling;
		}
		
		
		printf("\n");
		return;
	}
	token = strtok(param,"/\n");// Grabs the 'first element'
	tmp = tmp->child;//skips the '/'

	while(token != NULL){
		
		if (strcmp(tmp->name,token) == 0){// If file names match go down a folder
			token = strtok(NULL,"/\n");
			if (tmp->child == NULL){
				if (token != NULL){
					printf("No such file or directory: %s",param);
					return;
				}
				//print nothing since nothing in tree
				return;
				

			}else{
				if (token == NULL){
					tmp = tmp->child;
					//print out everything in this directory
					while(tmp != NULL){
						printf("%s\t",tmp->name);
						tmp = tmp->sibling;
					}
					printf("\n");
					return;
				}

				tmp = tmp->child;
			}		
		} else if(tmp->sibling != NULL){
			tmp = tmp->sibling;// if not keep going through sibling list until you get to the end
		}
		else if (tmp->sibling == NULL){
			add_sibling(token,'D',tmp);
			return;
		}
			
	}
}

void save_tree(NODE *cur, char *path, FILE *fp){
	if (cur == NULL) {
        return;
    }
    char node_path[64] = "";
    strcpy(node_path, path);
    strcat(node_path, cur->name);
    fprintf(fp,"%s,%c\n", node_path,cur->type);
    if (cur->sibling != NULL) {
        save_tree(cur->sibling, path,fp);
    }
    if (cur->child != NULL) {
        strcat(node_path, "/");
        save_tree(cur->child, node_path,fp);
    }
}



void print_tree(NODE *cur, char *path){
	if (cur == NULL) {
        return;
    }
    char node_path[64] = "";
    strcpy(node_path, path);
    strcat(node_path, cur->name);
    printf("%s,%c\n", node_path,cur->type);
    if (cur->sibling != NULL) {
        print_tree(cur->sibling, path);
    }
    if (cur->child != NULL) {
        strcat(node_path, "/");
        print_tree(cur->child, node_path);
    }
}

int verify(char *CMD){
	for (int i = 0; i < 10;i++){
		if(strcmp(CMD,cmd[i]) == 0){
			return i;
		}
	}
	return -1;
}

void execute(int cmd_num, char *param){
	char *token;
	switch (cmd_num)
	{
	case 0: // mkdir
		NODE *curr;
		// If it an absolute path, start from root
		if(param[0] == '/'){
			curr = root;
		}else{
			curr = cwd;
		}
		token = strtok(param,"/\n");
		if(curr->child == NULL){ //If this is first node add it to tree
			add_child(token, 'D',curr);
			token = strtok(NULL,"/\n");
		}
		//While the file path is not complete yet, keep finding the next token

		curr = curr->child;

		while(token != NULL){
			
			if (strcmp(curr->name,token) == 0){// If file names match go down a folder
				token = strtok(NULL,"/\n");
				if (curr->child == NULL){
					if (token != NULL){
						add_child(token,'D',curr);
						return;
					} else{
						printf("%s pathname already exists!\n",param);
						return;
					}

				}else{
					printf("DIR %s already exists!\n",param);
					return;
				}		
			} else if(curr->sibling != NULL){
				curr = curr->sibling;// if not keep going through sibling list until you get to the end
			}
			else if (curr->sibling == NULL){
				add_sibling(token,'D',curr);
				return;
			}
				
		}
		break;
	case 1: // rmdir
		NODE *temp, *prev;
		// If it an absolute path, start from root
		if(param[0] == '/'){
			temp = root;
		}else{
			temp = cwd;
		}
		token = strtok(param,"/\n");
		if(temp->child == NULL){ //If this is first node add it to tree
			printf("DIR %s Does not exist!\n",token);
			return;
		}else{
		prev= temp;
		temp = temp->child;
		}
		
		while(token != NULL){
			
			if (strcmp(temp->name,token) == 0){// If file names match go down a folder
				token = strtok(NULL,"/\n");
				if (temp->child == NULL){
					if (token != NULL){
						printf("The directory specified does not exist!\n");
						return;
					} else if(token == NULL){
						if(temp->type == 'D'){ //makes sure you don't lose siblings when you delete the subling head list
							if(temp->sibling != NULL){
								prev->child = temp->sibling;
								temp->sibling->parent = prev;
							}
							prev->child = NULL;
							delete(temp);
							return;
						} else{
							printf("Cannot remove file. Must be directory\n");
						}
						
					}

				}else{
					if(token == NULL){
						printf("Cannot remove DIR %s (Not empty)!\n",param);
						return;
					}
					else if(token != NULL){
					prev= temp;
					temp = temp->child;
					}
				}
			} else if(temp->sibling != NULL){
				temp = temp->sibling;// if not keep going through sibling list until you get to the end
			}
			else if (temp->sibling == NULL){
				printf("DIR %s Does not exist!\n",token);
				return;
			}
				
		}
		break;
	case 2: // cd
		NODE *temp2;
		// If it an absolute path, start from root
		if(param[0] == '/'){
			temp2 = root;
		}else{
			temp2 = cwd;
		}
		if(strcmp(param,"")==0){
			cwd = root;
			strcpy(cwd_filepath,"");
			return;
		}
		if(temp2->child == NULL){ //If this is first node add it to tree
			printf("No such file or directory: %s\n",param);
			return;
		}else{
			temp2 = temp2->child;
			token = strtok(param,"/\n");
		}
		
		while(token != NULL){
			if (strcmp(temp2->name,token) == 0){// If file names match go down a folder
				if(temp2->type =='F'){
					printf("%s is a file not a folder.",temp2->name);
					return;
				}
				token = strtok(NULL,"/\n");
				cwd = temp2;
				
				strcat(cwd_filepath,param);
				strcat(cwd_filepath,"/");
				temp2 = temp2->child;
			} else if(temp2->sibling != NULL){

				temp2 = temp2->sibling;// if not keep going through sibling list until you get to the end
			}
			else if (temp2->sibling == NULL){
				printf("No such file or directory: %s\n",param);
				return;
			}
		}
		break;
	case 3: // ls
		find_header(param);
		break;
	case 4: // pwd
		printf("/%s\n",cwd_filepath);
		break;
	case 5: // creat
		// If it an absolute path, start from root
		if(param[0] == '/'){
			curr = root;
		}else{
			curr = cwd;
		}
		token = strtok(param,"/\n");
		if(curr->child == NULL){ //If this is first node add it to tree
			add_child(token, 'F',curr);
			token = strtok(NULL,"/\n");
			return;
		}
		//While the file path is not complete yet, keep finding the next token

		curr = curr->child;

		while(token != NULL){
			
			if (strcmp(curr->name,token) == 0){// If file names match go down a folder
				token = strtok(NULL,"/\n");
				if (curr->child == NULL){
					if (token != NULL){
						if(curr->type != 'F'){
						add_child(token,'F',curr);
						} else{
							printf("Cannot go into a file as a folder.\n");
						}
						return;
					} else{
						printf("DIR %s already exists!\n",param);
						return;
					}

				}else{
					curr = curr->child;
				}		
			} else if(curr->sibling != NULL){
				curr = curr->sibling;// if not keep going through sibling list until you get to the end
			}
			else if (curr->sibling == NULL){
					add_sibling(token,'F',curr);
					return;
			}
		}
		break;
	case 6: // rm
		// If it an absolute path, start from root
		if(param[0] == '/'){
			temp = root;
		}else{
			temp = cwd;
		}
		token = strtok(param,"/\n");
		if(temp->child == NULL){ //If this is first node add it to tree
			printf("DIR %s Does not exist!\n",token);
			return;
		}else{
		prev= temp;
		temp = temp->child;
		}
		
		while(token != NULL){
			
			if (strcmp(temp->name,token) == 0){// If file names match go down a folder
				token = strtok(NULL,"/\n");
				if (temp->child == NULL){
					if (token != NULL){
						printf("The directory specified does not exist!\n");
						return;
					} else if(token == NULL){
						if(temp->type == 'F'){ //makes sure you don't lose siblings when you delete the subling head list
							if(temp->sibling != NULL){
								prev->child = temp->sibling;
								temp->sibling->parent = prev;
							}
							prev->child = NULL;
							delete(temp);
							return;
						} else{
							printf("Cannot remove file. Must be directory\n");
						}
						
					}

				}else{
					if(token == NULL){
						printf("Cannot remove DIR %s (Not empty)!\n",param);
						return;
					}
					else if(token != NULL){
					prev= temp;
					temp = temp->child;
					}
				}
			} else if(temp->sibling != NULL){
				temp = temp->sibling;// if not keep going through sibling list until you get to the end
			}
			else if (temp->sibling == NULL){
				printf("DIR Pathname Does not exist!\n");
				return;
			}
				
		}
		break;
	case 7: // save
		save(param);
		break;
	case 8: // reload
		reload(param);
		break;
	}
}
void save(char *filename){
	FILE *fp;
	char path[100] = "/";
	char ch;
	fp = fopen(filename,"w");
	save_tree(root->child,path,fp);
	fclose(fp);
}

void build_tree(char *in){
	char* path;
	char* type;
	path = strtok(in, ",\n");
	type = strtok(NULL,",\n");
	if(strcmp(type,"F") == 0){
		execute(5,path);
	} else{
		execute(0,path);
	}
}

void reload(char *filename){
	FILE *fp;
	char path[100] = "/";
	char chunk[128] = "";
	fp = fopen(filename,"r");
	if (fp == NULL){
		printf("Cannot openfile\n");
		return;
	}
	while(fgets(chunk,sizeof(chunk),fp) != NULL){
		fputs(chunk,stdin);
		build_tree(chunk);
	}
	fclose(fp);
}

int main() {
	initialize();
	// other initialization as needed
    char param[25] = "";
    char in[35] = "";
    char CMD[10] = "";
	int cmd_num = -1;
	char *token;
	char path[64] = "/";
	while(1) {
		//print_tree(root->child,path);
		printf("Enter Command: ");
		fgets(in,35,stdin);//Grab entire line of string including spaces
		token = strtok(in, " \n");
		cmd_num = verify(token);//verify command

		if(cmd_num == 9){
			save("fssim_Takada");
			break;
		}

		if(cmd_num != -1){ // If valid command
			token = strtok(NULL," ");
			if(token == NULL){
				if(cmd_num > 1 && cmd_num < 6){ //If command is not pwd
					execute(cmd_num, "");//Execute the command
				} else{
					printf("Missing parameters\n");
				}
			}else{
				//strcpy(param,token); // Read parameter
				execute(cmd_num, token);//Execute the command
			}
		} else{
			printf("Command not found!\n");
		}
	}
}
