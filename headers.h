void print_arr(char **);//prints each element of the array
int count_delims(char* , char*);//goes through the array and counts the number of delimeters in the string. Must be single char delimeters 
char ** parse_args(char * , char *, int );//splits a string on the delimeter and returns the char of splits. int is the number of delims for memory allocation. use count_delims()
void fix_newline(char *);//removes the newline from the end of the line on user input
char * strip_spaces(char * );//trims the spaces on the left and right sides of a string
void redirect_in(char **, int);//handles all redirections for standard in given the array of split commands and the length of the array.
void redirect_out(char ** , int );//handles all redirections to standard out given the array of split commands and the length of the array
void execute_child(char **);//function that handles all command executions done by the child
void execute(int , char ** );//General execution function that handles the parent executions(cd and exit) or forks a child and sends it to execute_child
void get_input(char ** );//gets input from the user