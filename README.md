# IssaShell
by James Smith and Jack Cruse

#### Features:
	Forks and executes commands!
	Parses multiple commands on one line!
	Redirection > , <
	Single Pipes
	Displays the current working directory
#### Attempted:
	The following did not end up working, but have been left in the code, commented out.
	Multiple redirections and pipes. The code is there, but the recursive call needs to be flushed out, but due to time restraints we couldn't afford to fix it.

#### Bugs:
	Isolating text with quotation marks does not work (ex. "This sentence would not be isolated")
	Limitation of 256 chars on input and current working directory display
	Tokens must be separated by spaces
	Multiple redirections and pipes fail

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

    /*======== char * combine_strings() ==========
	Inputs: char** line_arr
			int i
	Returns: Void 
    
    Takes all of the string elements and concatenates the first i elements into one string separated by spaces
	====================*/

    /*======== void redirect() ==========
	Inputs: char ** arr
			int source_fd
			int dest_fd
	Returns: Void

   	Handles all redirections given the array of split commands and the source and destination file descriptors
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
