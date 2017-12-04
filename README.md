# IssaShell
by James Smith and Jack Cruse

#### Features:
	Forks and executes commands!
	Parses multiple commands on one line!

#### Attempted:
	The following did not end up working, but have been left in the code, commented out.
	Could not get pipes to work
    Could not get redirection working. Only works with some commands (works with ls > file.txt but not ls -l > file.txt)

#### Bugs:
	
#### Files & Function Headers:

**functions.c**
	Handles the execution of commands once they are parsed for semicolons
	
    /*======== void print_arr() ==========
	Inputs:  char ** string_arr 
	Returns: Void
    
    Prints each element of the array
	====================*/

    /*======== int count_delims() ==========
	Inputs: char* line
            char* delim
	Returns: Number of instances of delim in the string. 
    
    Goes through the array and counts the number of delimeters in the string. Must be single char delimeters.
	====================*/

    /*======== char ** parse_args(); ==========
	Inputs: char * line
            char * delim
            int num_commands
	Returns: Array of tokens split by delim.
    
    Splits a string on the delimeter. Num_commands is the number of delims for memory allocation. use count_delims()
	====================*/

    /*======== void fix_newline() ==========
	Inputs:  char ** string_arr 
	Returns: Void

    Removes the newline from the end of the line on user input
	====================*/

    /*======== char * strip_spaces() ==========
	Inputs:  char * line
	Returns: Char *

    Trims the spaces on the left and right sides of a string. Returns pointer to new start of string.
	====================*/

    /*======== void redirect_in() ==========
	Inputs: char ** line_arr
            int num_args 
	Returns: Void 
    
    Handles all redirections for standard in given the array of split commands and the length of the array.
	====================*/

    /*======== void redirect_out() ==========
	Inputs: char ** line_arr
            int num_args
	Returns: Void

    Handles all redirections to standard out given the array of split commands and the length of the array
	====================*/

    /*======== void execute_child() ==========
	Inputs: char ** line_arr
            int num_args
	Returns: Void

    Handles all command executions done by the child
	====================*/

    /*======== void execute() ==========
	Inputs: int num_commands
            char ** commands_arr
	Returns: Void

    General execution function that handles the parent executions(cd and exit) or forks a child and sends it to execute_child
	====================*/

    /*======== void get_input() ==========
	Inputs: char ** input
	Returns: Void

    Gets input from the user and writes it to 'input'
	====================*/

**main.c**
	Runs the main loop that gets input from the user, parses by semicolons and then gives the rest to functions.c to execute.