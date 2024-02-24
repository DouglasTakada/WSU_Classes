#Name: Douglas Takada

from colors import *
from psexpressions import StringValue, DictionaryValue, CodeArrayValue

class PSOperators:
    def __init__(self):
        #stack variables
        self.opstack = []  #assuming top of the stack is the end of the list
        self.dictstack = []  #assuming top of the stack is the end of the list
        # The environment that the REPL evaluates expressions in.
        # Uncomment this dictionary in part2
        self.builtin_operators = {
            "add":self.add,
            "sub":self.sub,
            "mul":self.mul,
            "mod":self.mod,
            "eq":self.eq,
            "lt": self.lt,
            "gt": self.gt,
            "dup": self.dup,
            "exch":self.exch,
            "pop":self.pop,
            "copy":self.copy,
            "count": self.count,
            "clear":self.clear,
            "stack":self.stack,
            "dict":self.psDict,
            "string":self.string,
            "length":self.length,
            "get":self.get,
            "put":self.put,
            "getinterval":self.getinterval,
            "putinterval":self.putinterval,
            "search" : self.search,
            "begin":self.begin,
            "end":self.end,
            "def":self.psDef,
            "if":self.psIf,
            "ifelse":self.psIfelse,
            "for":self.psFor
        }
    #------- Operand Stack Helper Functions --------------
    
    """
        Helper function. Pops the top value from opstack and returns it.
    """
    def opPop(self):
        if len(self.opstack) > 0:
            x = self.opstack[len(self.opstack) - 1]
            self.opstack.pop(len(self.opstack) - 1)
            return x
        else:
            print("Error: opPop - Operand stack is empty")

    """
       Helper function. Pushes the given value to the opstack.
    """
    def opPush(self,value):
        self.opstack.append(value)

    #------- Dict Stack Helper Functions --------------
    """
       Helper function. Pops the top dictionary from dictstack and returns it.
    """  
    def dictPop(self):
        if len(self.dictstack) > 0:
            return self.dictstack.pop(-1)
        else:
            print("Error: dictPop - dictionary stack is empty")

    """
       Helper function. Pushes the given dictionary onto the dictstack. 
    """   
    def dictPush(self,d):
        self.dictstack.append(d)

    """
       Helper function. Adds name:value pair to the top dictionary in the dictstack.
       (Note: If the dictstack is empty, first adds an empty dictionary to the dictstack then adds the name:value to that. 
    """  
    def define(self,name, value):
        if len(self.dictstack) == 0:
            self.dictstack.append({})
        self.dictstack[-1][name] = value
            


    """
       Helper function. Searches the dictstack for a variable or function and returns its value. 
       (Starts searching at the top of the dictstack; if name is not found returns None and prints an error message.
        Make sure to add '/' to the begining of the name.)
    """
    def lookup(self,name):
        for i in range(len(self.dictstack)-1,-1,-1):
            if self.dictstack[i].get("/"+name) is not None:
                return self.dictstack[i].get("/"+name)
        print("Could not find function or variable in dictstack")
        return None
    
    #------- Arithmetic Operators --------------

    """
       Pops 2 values from opstack; checks if they are numerical (int); adds them; then pushes the result back to opstack. 
    """  
    def add(self):
        if len(self.opstack) > 1:
            op1 = self.opPop()
            op2 = self.opPop()
            if (isinstance(op1,int) or isinstance(op1,float))  and (isinstance(op2,int) or isinstance(op2,float)):
                self.opPush(op1 + op2)
            else:
                print("Error: add - one of the operands is not a number value")
                self.opPush(op1)
                self.opPush(op2)             
        else:
            print("Error: add expects 2 operands")

    """
       Pops 2 values from opstack; checks if they are numerical (int); subtracts them; and pushes the result back to opstack. 
    """ 
    def sub(self):
        if len(self.opstack) > 1:
            op1 = self.opPop()
            op2 = self.opPop()
            if (isinstance(op1,int) or isinstance(op1,float))  and (isinstance(op2,int) or isinstance(op2,float)):
                self.opPush(op2 - op1)
            else:
                print("Error: sub - one of the operands is not a number value")
                self.opPush(op1)
                self.opPush(op2)             
        else:
            print("Error: sub expects 2 operands")

    """
        Pops 2 values from opstack; checks if they are numerical (int); multiplies them; and pushes the result back to opstack. 
    """
    def mul(self):
        if len(self.opstack) > 1:
            op1 = self.opPop()
            op2 = self.opPop()
            if (isinstance(op1,int) or isinstance(op1,float))  and (isinstance(op2,int) or isinstance(op2,float)):
                self.opPush(op2 * op1)
            else:
                print("Error: mul - one of the operands is not a number value")
                self.opPush(op1)
                self.opPush(op2)             
        else:
            print("Error: mul expects 2 operands")

    """
        Pops 2 values from stack; checks if they are int values; calculates the remainder of dividing the bottom value by the top one; 
        pushes the result back to opstack.
    """
    def mod(self):
        if len(self.opstack) > 1:
            op1 = self.opPop()
            op2 = self.opPop()
            if isinstance(op1,int)  and isinstance(op2,int):
                self.opPush(op2 % op1)
            else:
                print("Error: mod - one of the operands is not a number value")
                self.opPush(op1)
                self.opPush(op2)             
        else:
            print("Error: mod expects 2 operands")

    """ Pops 2 values from stacks; if they are equal pushes True back onto stack, otherwise it pushes False.
          - if they are integers or booleans, compares their values. 
          - if they are StringValue values, compares the `value` attributes of the StringValue objects;
          - if they are DictionaryValue objects, compares the objects themselves (i.e., ids of the objects).
        """
    def eq(self):
        if len(self.opstack) > 1:
            op1 = self.opPop()
            op2 = self.opPop()
            if isinstance(op1,int) and isinstance(op2,int):
                self.opPush(op1 == op2)

            elif isinstance(op1,bool) and isinstance(op2,bool):
                self.opPush(op1 == op2)

            elif isinstance(op1,StringValue) and isinstance(op2,StringValue):
                self.opPush(op1.value == op2.value)

            elif isinstance(op1, DictionaryValue) and isinstance(op2, DictionaryValue):
                self.opPush(op1 == op2)

            else:
                print("Error: eq - both operands must be of the same type")
                self.opPush(op1)
                self.opPush(op2)
        else:
            print("Error: eq - eq expects two operands")
            

    """ Pops 2 values from stacks; if the bottom value is less than the second, pushes True back onto stack, otherwise it pushes False.
          - if they are integers or booleans, compares their values. 
          - if they are StringValue values, compares the `value` attributes of them;
          - if they are DictionaryValue objects, compares the objects themselves (i.e., ids of the objects).
    """  
    def lt(self):
        if len(self.opstack) > 1:
            op1 = self.opPop()
            op2 = self.opPop()
            if isinstance(op1,int) and isinstance(op2,int):
                self.opPush(op1 > op2)

            elif isinstance(op1,bool) and isinstance(op2,bool):
                self.opPush(op1 > op2)

            elif isinstance(op1,StringValue) and isinstance(op2,StringValue):
                self.opPush(op1.value > op2.value)

            elif isinstance(op1, DictionaryValue) and isinstance(op2, DictionaryValue):
                self.opPush(op1 > op2)

            else:
                print("Error: lt - both operands must be of the same type")
                self.opPush(op1)
                self.opPush(op2)
        else:
            print("Error: lt - lt expects two operands")

    """ Pops 2 values from stacks; if the bottom value is greater than the second, pushes True back onto stack, otherwise it pushes False.
          - if they are integers or booleans, compares their values. 
          - if they are StringValue values, compares the `value` attributes of them;
          - if they are DictionaryValue objects, compares the objects themselves (i.e., ids of the objects).
    """  
    def gt(self):
        if len(self.opstack) > 1:
            op1 = self.opPop()
            op2 = self.opPop()
            if isinstance(op1,int) and isinstance(op2,int):
                self.opPush(op1 < op2)

            elif isinstance(op1,bool) and isinstance(op2,bool):
                self.opPush(op1 < op2)

            elif isinstance(op1,StringValue) and isinstance(op2,StringValue):
                self.opPush(op1.value < op2.value)

            elif isinstance(op1, DictionaryValue) and isinstance(op2, DictionaryValue):
                self.opPush(op1 < op2)

            else:
                print("Error: lt - both operands must be of the same type")
                self.opPush(op1)
                self.opPush(op2)
        else:
            print("Error: lt - lt expects two operands")

    #------- Stack Manipulation and Print Operators --------------
    """
       This function implements the Postscript "pop operator". Calls self.opPop() to pop the top value from the opstack and discards the value. 
    """
    def pop (self):
        if (len(self.opstack) > 0):
            self.opPop()
        else:
            print("Error: pop - not enough arguments")

    """
       Prints the opstack and dictstack. The end of the list is the top of the stack. 
    """
    def stack(self):
        print(OKGREEN+"**opstack**")
        for item in reversed(self.opstack):
            print(item)
        print("-----------------------"+CEND)
        print(RED+"**dictstack**")
        for item in reversed(self.dictstack):
            print(item)
        print("-----------------------"+ CEND)


    """
       Copies the top element in opstack.
    """
    def dup(self):
        op1 = self.opPop()
        self.opPush(op1)
        self.opPush(op1)

    """
       Pops an integer count from opstack, copies count number of values in the opstack. 
    """
    def copy(self):
        if len(self.opstack) > 0:
            size = self.opPop()
            if isinstance(size, int):
                if size <= len(self.opstack):
                    start = len(self.opstack)-size
                    for i in range(start,len(self.opstack)):
                        self.opPush(self.opstack[i])
                else:
                    print("Error: copy - argument cannot be larger than stack size")
            else:
                print("Error: copy - argument must be an integer")
        else:
            print("Error: copy - not enough arguments")


    """
        Counts the number of elements in the opstack and pushes the count onto the top of the opstack.
    """
    def count(self):
        self.opPush(len(self.opstack))

    """
       Clears the opstack.
    """
    def clear(self):
        self.opstack.clear()
        
    """
       swaps the top two elements in opstack
    """
    def exch(self):
        if len(self.opstack) > 1:
            op1 = self.opPop()
            op2 = self.opPop()
            self.opPush(op1)
            self.opPush(op2)
        else:
            print("Error: exch - not enough arguments")
    # ------- String and Dictionary creator operators --------------

    """ Creates a new empty string  pushes it on the opstack.
    Initializes the characters in the new string to \0 , i.e., ascii NUL """
    def string(self):
        if len(self.opstack) > 0:
            size = self.opPop()
            
            if (isinstance(size, int)):
                ans = "("
                for _ in range(size):
                    ans +="\x00"
                ans += ")"
                self.opPush(StringValue(ans))
            else:
                print("Error: string - needs an int argument for its size")
        else:
            print("Error: string - not enough arguments")

        
    
    """Creates a new empty dictionary  pushes it on the opstack """
    def psDict(self):
        if len(self.opstack) > 0:
            self.opPop()
            self.opPush(DictionaryValue({}))
        else:
            print("Error: psDict - not enough arguments")

    # ------- String and Dictionary Operators --------------
    """ Pops a string or dictionary value from the operand stack and calculates the length of it. Pushes the length back onto the stack.
       The `length` method should support both DictionaryValue and StringValue values.
    """
    def length(self):
        if len(self.opstack) > 0:
            val = self.opPop()
            if isinstance(val, StringValue):
                if "("  in val.value and ")" in val.value:
                    self.opPush(val.length() -2 ) 
                else:
                    self.opPush(val.length())
            elif isinstance(val, DictionaryValue):
                self.opPush(val.length())
            else:
                print("Error: length - needs an string or dictionary argument")
        else:
            print("Error: length - needs atleast 1 argument")


    """ Pops either:
         -  "A (zero-based) index and an StringValue value" from opstack OR 
         -  "A `name` (i.e., a key) and DictionaryValue value" from opstack.  
        If the argument is a StringValue, pushes the ascii value of the the character in the string at the index onto the opstack;
        If the argument is an DictionaryValue, gets the value for the given `name` from DictionaryValue's dictionary value and pushes it onto the opstack
    """
    def get(self):
        if len(self.opstack) > 1:
            idx = self.opPop()
            value = self.opPop()
            if isinstance(idx, int) and isinstance(value, StringValue):
                self.opPush(ord(value.value[idx + 1]))
            elif isinstance(value, DictionaryValue):
                self.opPush(value.value[idx])
            else:
                print("arguments can only be A (zero-based) index and an StringValue value \n or A `name` (i.e., a key) and DictionaryValue value")
        else:
            print("Error: get - needs atleast 2 argument")
   
    """
    Pops either:
    - "An `item`, a (zero-based) `index`, and an StringValue value from  opstack", OR
    - "An `item`, a `name`, and a DictionaryValue value from  opstack". 
    If the argument is a StringValue, replaces the character at `index` of the StringValue's string with the character having the ASCII value of `item`.
    If the argument is an DictionaryValue, adds (or updates) "name:item" in DictionaryValue's dictionary `value`.
    """
    def put(self):
        if len(self.opstack) > 2:
            item = self.opPop()
            idx = self.opPop()
            value = self.opPop()
            if isinstance(idx, int) and isinstance(value, StringValue):
                value.value = value.value[:idx+1] + chr(item) + value.value[idx+2:]
            elif isinstance(value, DictionaryValue):
                value.value[idx] = item
            else:
                print("Error: put - loop at function definition for what are legal parameters for this function")
        else:
            print("Error: put - needs atleast 3 argument")

    """
    getinterval is a string only operator, i.e., works only with StringValue values. 
    Pops a `count`, a (zero-based) `index`, and an StringValue value from  opstack, and 
    extracts a substring of length count from the `value` of StringValue starting from `index`,
    pushes the substring back to opstack as a StringValue value. 
    """ 
    def getinterval(self):
        if len(self.opstack) > 2:
            count = self.opPop()
            idx = self.opPop()
            value = self.opPop()
            if isinstance(count, int) and isinstance(idx, int) and isinstance(value, StringValue):
                if idx+count >=value.length():
                    self.opPush("("+value.value[idx+1:]+")")
                else:
                    self.opPush(StringValue("("+value.value[idx+1:idx+count+1]+")"))
        else:
            print("Error getinterval - requires atleast three arguments")

    """
    putinterval is a string only operator, i.e., works only with StringValue values. 
    Pops a StringValue value, a (zero-based) `index`, a `substring` from  opstack, and 
    replaces the slice in StringValue's `value` from `index` to `index`+len(substring)  with the given `substring`s value. 
    """
    def putinterval(self):
        if len(self.opstack) > 2:
            newstr = self.opPop()
            idx = self.opPop()
            value = self.opPop()
            if isinstance(newstr, StringValue) and isinstance(idx, int) and isinstance(value, StringValue):
                if idx+newstr.length() >= value.length():
                    value.value = "("+str(value.value[1:idx+ 1]) + str(newstr.value[1:-1])+")"
                else:
                    value.value = str(value.value[1:idx+1]) + str(newstr.value[1:-1]) + " " +str(value.value[idx+newstr.length():])
        else:
            print("Error putinterval - requires atleast three arguments")

    """
    search is a string only operator, i.e., works only with StringValue values. 
    Pops two StringValue values: delimiter and inputstr
    if delimiter is a sub-string of inputstr then, 
       - splits inputstr at the first occurence of delimeter and pushes the splitted strings to opstack as StringValue values;
       - pushes True 
    else,
        - pushes  the original inputstr back to opstack
        - pushes False
    """
    def search(self):
        if len(self.opstack) > 1:
            delim = self.opPop()
            instr = self.opPop()
            if isinstance(delim, StringValue) and isinstance(instr, StringValue):
                for i in range(1,instr.length()-1):
                    if str(instr.value)[i] == str(delim.value)[1]:
                        self.opPush(StringValue("("+str(instr.value)[i+1:]))
                        self.opPush(StringValue("("+str(instr.value)[i]+")"))
                        self.opPush(StringValue(str(instr.value)[:i]+")"))
                        self.opPush(True)
                        break
                if len(self.opstack) == 0 or self.opPop() != True:
                    self.opPush(instr)
                    self.opPush(False)
                else:
                    self.opPush(True)
            else:
                print("Error search - requires two stringValue types")
        else:
            print("Error search - requires atleast two arguments")

    # ------- Operators that manipulate the dictstact --------------
    """ begin operator
        Pops a DictionaryValue value from opstack and pushes it's `value` to the dictstack."""
    def begin(self):
        if len(self.opstack) > 0:
            value = self.opPop()
            if isinstance(value, DictionaryValue):
                self.dictPush(value.value)
            else:
                 print("Error begin - requires a type Dictionary argument")
        else:
             print("Error begin - requires atleast one argument")

    """ end operator
        Pops the top dictionary from dictstack."""
    def end(self):
        if len(self.dictstack) > 0:
            self.dictPop()
        else:
             print("Error end - requires atleast one argument")
        
    """ Pops a name and a value from stack, adds the definition to the dictionary at the top of the dictstack. """
    def psDef(self):
        value = self.opPop()
        name = self.opPop()
        self.define(name, value)


    # ------- if/ifelse Operators --------------
    """ if operator
        Pops a CodeArrayValue object and a boolean value, if the value is True, executes (applies) the code array by calling apply.
       Will be completed in part-2. 
    """
    def psIf(self):
        if len(self.opstack) > 1:
            v1 = self.opPop()
            v2 = self.opPop()
            if isinstance(v1, CodeArrayValue) and isinstance(v2, bool):
                if v2:
                    v1.apply(self)
            else:
                print("Error psIf - requires a CodeArrayValue value and a boolean value")
        else:
             print("Error psIf - requires atleast two argument")

    """ ifelse operator
        Pops two CodeArrayValue objects and a boolean value, if the value is True, executes (applies) the bottom CodeArrayValue otherwise executes the top CodeArrayValue.
        Will be completed in part-2. 
    """
    def psIfelse(self):
        if len(self.opstack) > 2:
            v1 = self.opPop()
            v2 = self.opPop()
            v3 = self.opPop()
            if isinstance(v1, CodeArrayValue) and isinstance(v2, CodeArrayValue) and isinstance(v3, bool):
                if v3:
                    v2.apply(self)
                else:
                    v1.apply(self)
            else:
                print("Error psIf - requires two CodeArrayValue values and a boolean value")
        else:
             print("Error psIfelse - requires atleast three argument")


    #------- Loop Operators --------------
    """
       Implements for operator.   
       Pops a CodeArrayValue object, the end index (end), the increment (inc), and the begin index (begin) and 
       executes the code array for all loop index values ranging from `begin` to `end`. 
       Pushes the current loop index value to opstack before each execution of the CodeArrayValue. 
       Will be completed in part-2. 
    """ 
    def psFor(self):
        if len(self.opstack) > 3:
            body = self.opPop()
            end = self.opPop()
            inc = self.opPop()
            begin = self.opPop()
            if isinstance(body, CodeArrayValue) and isinstance(end, int) and isinstance(inc, int) and isinstance(begin, int):
                for i in range(begin, end + inc, inc):
                    self.opPush(i)
                    body.apply(self)
            else:
                print("Error For - requires a CodeArrayValue value, and three integer value")
        else:
             print("Error psFor - requires atleast four argument")

    """ Cleans both stacks. """      
    def clearBoth(self):
        self.opstack[:] = []
        self.dictstack[:] = []

    """ Will be needed for part2"""
    def cleanTop(self):
        if len(self.opstack)>1:
            if self.opstack[-1] is None:
                self.opstack.pop()

