#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



//create a linked list and define it as tnode to save time
typedef struct node
{
    char * data;
    char * type;
    struct node *next;
} tnode;
/*------------------------------------------------------------- void function used to add token to the end of the token list -----------------------------------*/
void addtok(tnode **head, char *dtype, char* instr, int ststr, int len)
{
    tnode *newtok = malloc(sizeof(tnode));
    
    if(newtok == NULL) //check to see if memory was allocated
    {
        printf("unable to allocate memory");
        exit(0);
    }

    newtok->type = dtype;
    newtok->data = malloc((char)(len));
    if(newtok->data == NULL)
    {
        printf("unable to allocate memory"); //check to see if memory was allocated
        exit(0);
    }

    strncpy(newtok->data,(instr + ststr), len);
    //if our token list is empty start the list with the first token
    if(*head == NULL)
        *head = newtok;
    //if it's not empty, just add it to the last token
    else
    {
        tnode *temp = *head;

        while (temp->next !=NULL)
        {
            temp = temp->next;
        }
        temp->next = newtok;

    }
    

}
//creates a temporary pointer pointing to head, iterates and prints data, then stops when the next node is NULL
void printok(tnode *head)
{
    tnode *temp = head;

    while(temp != NULL)
    {
        printf("%s: \"%s\" \n", temp->type, temp->data);
        temp = temp->next;
    }
}

//this is a function that checks for keywords such as sizeof, int, while, etc. it creates a string similar to how addtok works and it compares it with a string passed into the function of the keyword you are looking for
int keywordcheck( char * cstr, char * inpt, int strt)
{
    char * tmpptr;
    int wordlen = strlen(cstr);
    tmpptr = malloc(wordlen);
    strncpy(tmpptr, (inpt+strt), wordlen);  

    return strcmp(cstr,tmpptr);
   
}


/*========================================================================================begin main()=================================================================================================*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv)
{
    if(argv[1] == NULL) //if we have no input string, exit
    {
      exit(0);
    }
    tnode *tokens = NULL;
    char *input = argv[1];
    int i = 0;
    size_t insize = strlen(input);
    //begin tokenizing 
    while(i<insize)
    {
        
    
        if(isspace(input[i])) //if it's a space, iterate by 1
        {
            i++;
        }

        
    /*--------------------------------------------------------------------------this checks for symbols-----------------------------------------------------------------------------------------*/

        if(input[i] == '[' || input[i] == ']') 
        {
            if(input[i] == '[')
            {
                addtok(&tokens,"left bracket", input, i, 1);
                i++;
            }
            else
            {
                addtok(&tokens, "right bracket", input, i, 1);
                i++;
            }
        }
            
        if(input[i] == ',' )
        {
            addtok(&tokens, "comma",input,i,1);
            i++;

        }
        
        if(input[i] == '(' || input[i] == ')') 
        {
            if(input[i] == '(') 
            {
                addtok(&tokens,"left parenthesis", input, i, 1);
                i++;
            }
            else 
            {
                addtok(&tokens,"right parenthesis", input, i, 1);
                i++;
            }
        }
        if(input[i] == '.')
        {
            addtok(&tokens, "structure member", input, i , 1);
            i++;
        }
        if(input[i] == '-')
        {
            if(input[i+1] == '>')
            {
                addtok(&tokens, "structure pointer", input, i , 2);
                i+=2;
            }
            else if(input[i+1] == '-')
            {
                addtok(&tokens, "decrement", input, i, 2);
                i+=2;
            }
            else if(input[i+1] == '=')
            {
                addtok(&tokens, "minus equals", input, i, 2);
                i+=2;
            }
            else
            {
                addtok(&tokens, "minus/subtract operator", input, i, 1);
                i++;
            }
        }

        if(input[i] == '+')
        {
        
            if(input[i+1] == '+')
            {
                addtok(&tokens, "increment", input, i, 2);
                i+=2;
            }
            else if(input[i+1] == '=')
            {
                addtok(&tokens, "plus equals", input, i, 2);
                i+=2;
            }
            else
            {
                addtok(&tokens, "addition", input, i, 1);
                i++;
            }
        }
        if(input[i] == '=')
        {
            if(input[i+1] == '=')
            {
                addtok(&tokens, "equality test", input, i, 2);
                i+=2;
            }
            else
            {
                addtok(&tokens, "assignment", input, i, 1);
                i++;
            }
            
        }

        if(input[i] == '!')
        {
            if(input[i+1] == '=')
            {
                addtok(&tokens, "inequality test", input, i, 2);
                i+=2;
            }
            else
            {
                addtok(&tokens, "negate", input, i, 1);
                i++;
            }
            
        }
        if(input[i] == '~')
        {
            addtok(&tokens, "1s complement", input, i, 1);
            i++;
        }
        if(input[i] == '>')
        {
            if(input[i+1] == '=')
            {
                addtok(&tokens, "greater than or equal test", input, i, 2);
                i+=2;
            }
            else if(input [i+1] == '>')
            {
                if(input[i+2] == '=')
                {
                    addtok(&tokens, "shift right equals", input, i, 3);
                    i+=3;
                }
                else
                {
                    addtok(&tokens, "shift right", input, i, 2);
                    i+=2;
                }
            }
            else
            {
                addtok(&tokens, "greater than test", input, i, 1);
                i++;
            }  
            
        }
        if(input[i] == '<')
        {
            if(input[i+1] == '=')
            {
                addtok(&tokens, "less than or equal test", input, i, 2);
                i+=2;
            }
            else if(input [i+1] == '<')
            {
                if(input[i+2] == '=')
                {
                    addtok(&tokens, "shift left equals", input, i, 3);
                    i+=3;
                }
                else
                {
                    addtok(&tokens, "shift left", input, i, 2);
                    i+=2;
                }
            }
            else
            {
                addtok(&tokens, "less than test", input, i, 1);
                i++;
            }
        }
        if(input[i] == '^')
        {
            if(input[i+1] == '=')
            {
                addtok(&tokens, "bitwise XOR equals", input, i, 2);
                i+=2;
            }
            else
            {
                addtok(&tokens, "bitwise XOR", input, i, 1);
                i++;
            }
            
        }
        if(input[i] == '|')
        {
            if(input[i+1] == '|')
            {
                addtok(&tokens, "logical OR", input, i, 2);
                i+=2;
            }
            else if(input[i+1] == '=')
            {
                addtok(&tokens, "bitwise OR equals", input, i, 2);
                i+=2;
            }
            else
            {
                addtok(&tokens, "bitwise OR", input, i, 1);
                i++;
            }
            
        }
        if(input[i] == '/')
        {
            if(input[i+1] == '=')
            {
                addtok(&tokens, "divide equals", input, i, 2);
                i+=2;
            }
            else
            {
                addtok(&tokens, "division", input, i, 1);
                i++;
            }
            
        }
        if(input[i] == '&')
        {
            if(input[i+1] == '&')
            {
                addtok(&tokens, "logical AND", input, i, 2);
                i+=2;
            }
            else if(input[i+1] == '=')
            {   
                addtok(&tokens, "bitwise AND equals", input, i, 2);
                i+=2;
            }
            else
            {
                addtok(&tokens, "AND/address operator", input, i, 1);
                i++;
            }
            
        }
        if(input[i] == '?')
        {
            addtok(&tokens, "conditional true", input, i, 1);
            i++;
        }
        if(input[i] == ':')
        {
            addtok(&tokens, "conditional false", input, i, 1);
            i++;
        }    
        if(input[i] == '*')
        {
            if(input[i+1] == '=')
            {
                addtok(&tokens, "times equals", input, i, 2);
                i+=2;
            }
            addtok(&tokens, "multiply/dereference operator", input, i, 1);
            i++;
        }
        if(input[i] == '%')
        {
            if(input[i+1] == '=')
            {
                addtok(&tokens, "mod equals", input, i, 2);
                i+=2;
            }
            else
            {
                addtok(&tokens, "mod", input, i, 1);
                i++;
            }
            

        }

  
        

    //end check for symbols 

    /*---------------------------------------------------------------------------this checks for words-----------------------------------------------------------------------------------------*/

        if(isalpha(input[i]))
        {
           // char * temp;
            int start = i;

            int length = 0;


            if(input[i] == 's')
            {
                    if((keywordcheck("sizeof", input, i) == 0))
                    {
                        if((isspace(input[i-1]) || i == 0) && (isspace(input[i+6]) || i+6 == insize))
                        {
                            
                            addtok(&tokens, "sizeof", input, start, 6);
                            i+=6;
                            
                        }
                        else
                        {
                            while(isalnum(input[i]))
                            {
                                length++;
                                i++;
                            }
                            addtok(&tokens, "word", input, start, length);
                        }
                        
                    }
                    else
                    {
                        while(isalnum(input[i]))
                        {
                            length++;
                            i++;
                        }
                        addtok(&tokens, "word", input, start, length);
                    }
                    
                    
            }
            else if(input[i] == 'i')
            {
                if(keywordcheck("int", input, i) == 0)
                {
                    if((isspace(input[i-1]) || i == 0) && (isspace(input[i+3]) || i+3 == insize))
                    {
                        addtok(&tokens, "keyword", input, start, 3);
                        i+=3;
                    }
                    else
                    {
                        while(isalnum(input[i]))
                        {
                            length++;
                            i++;
                        }
                        addtok(&tokens, "word", input, start, length);
                    }
                    
                }
                else
                    {
                        while(isalnum(input[i]))
                        {
                            length++;
                            i++;
                        }
                        addtok(&tokens, "word", input, start, length);
                    }

            }

            else
            {
                while(isalnum(input[i]))
                {    
                    length++;
                    i++;
                } 
                addtok(&tokens, "word", input, start, length);
            }
             
        }
                   
        
    //end check for words

        
/*---------------------------------------------------------------------begin check for hex--------------------------------------------------------------------*/
    if(input[i] == '0')
    {
        int start = i;
        int length = 0;
        
        
        if(input[i+1] == 'x' || input[i+1] == 'X')
        {
            i+=2;
            length+=2;
            
            while((( input[i]>= '0' ) && (input[i] <= '9'))  || (input[i] >= 'a' && input[i] <= 'f') || (input[i]>= 'A' && input[i] <= 'F')) //since 0-0 are sequential numbers on the ascii table, as aree a-f, and A-F, I can just make sure that the values are between these chars
            {
                i++;
                length++;
            }
            
            addtok(&tokens, "hexadecimal integer",input, start, length);
            
        }
        
    }
//end check for hex 

/*------------------------------------------------------------ begin check for integers --------------------------------------------------------------------*/
        if(isdigit(input[i]))
        {
            int start = i;
            int length = 0;
            

  
        
        while(isdigit(input[i]))
        {
            i++;
            length++;
        }
        
            //end check for octals
            
        /*-------------------------------------------------- begin check for float -----------------------------------------*/
        if(input[i] == '.')
        {
            if(isdigit(input[i+1]))
            {
                i++; 
                length++;
                while(isdigit(input[i]))
                {
                    i++;
                    length++;
                }
                //checks for scientific notation
                if(input[i] == 'e')
                {
                    if(input[i+1] == '-')
                    {
                        if(isdigit(input[i+2]))
                        {
                            i+=2;
                            length+=2;
                
                            while(isdigit(input[i]))
                            {
                                i++;
                                length++;
                            }
                
                            addtok(&tokens, "float", input, start, length);
                
                        }
                    }
                    else 
                    {
                        while(isdigit(input[i]))
                        {
                            i++;
                            length++;
                        }
                
                        addtok(&tokens, "float", input, start, length);
                    //end check
                    }
                    
                    
                }
                else
                {
                        addtok(&tokens, "float", input, start, length);
                }
                  
                

            }
            else
            {
                int check = 0;
                if(input[start] == '0')
                {
                    for(int j = start; j<start+length; j++)
                    {
                        if(!(input[j] >= '0' && input[j] <= '7'))
                        {
                            check ++;
                            
                        }
                        
                                
                    }
                    if(check  != 0 )
                    {
                        addtok(&tokens, "decimal integer", input, start, length); //if it starts with 0, but has a number > 7
                    }
                    else
                    {
                        addtok(&tokens, "octal integer", input, start, length); //if it starts with 0, but has no number > 7
                    }

                }
            }         
            
        }
    //end check for float
            
        else 
        {
            /*----------------------------------------------begin check for octal------------------------*/
            
            int check = 0;
            if(input[start] == '0')
            {
                for(int j = start; j<start+length; j++)
                {
                    if(!(input[j] >= '0' && input[j] <= '7'))
                    {
                        check ++;
                       
                    }
                    
                         
                }
                if(check  != 0 )
                {
                    addtok(&tokens, "decimal integer", input, start, length); //if it starts with 0, but has a number > 7
                }
                else
                {
                    addtok(&tokens, "octal integer", input, start, length); //if it starts with 0, but has no number > 7
                }
                

                
            }
            else
            {
                addtok(&tokens, "decimal integer", input, start, length); //if it's not a hexadecimal, an octal, or a float, it's a decimal integer
            }
                    
            
        }
    }

    } 
    printok(tokens);

}
