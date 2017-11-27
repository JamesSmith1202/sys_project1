#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int count_delims(char* line, char delim){
  int counter = 0;
  int ctr = 0;
  while(line[counter]){
    if(line[counter] == delim){
      ctr++;
    }
    counter++;
  }
  return ctr;
}

char ** parse_args(char * line, char * delim, int num_args){
  printf("num args given to parse_args: %d\n", num_args);
  char ** args = (char **)calloc(num_args+1, sizeof(char*));//allocate space for the possible args + ending null for execvp
  if(!args){//check if memory was allocated
    printf("Memory Allocation Failed\n");
    exit(1);
  }
  char * arg;
  int counter = 0;
  while( (arg=strsep(&line, delim)) ){//while you can remove the delim, do so
    //printf("arg is %d as an int and %s as a string\n", arg, arg);
    //   if (arg != ' ') {
    args[counter] = arg;//move over the 2d char array and set it equal to the next divided arg
    printf("piece separated by delim %s:%s\n", delim, arg);
    counter += 1;// added the increment james it wasnt here before
    //}
  }
  args[counter] = 0;//set last to null for execvp
  return args;
}

void print_arr(char ** string_arr) {//prints all strings in an arr of strings
  int counter = 0;
  while (string_arr[counter]) {
    printf("The %d item of the array: %s\n", counter, string_arr[counter]);
    counter++;
  }
  printf("The %d item of the array: %s\n", counter, string_arr[counter]);
}

void print_chars_in_arr(char ** string_arr) {//prints all the chars in an arr of strings
  int counter = 0;
  int subctr = 0;
  while (string_arr[counter]) {
    printf("The %d item of the array: %s\n", counter, string_arr[counter]);
    while (string_arr[counter][subctr]) {
      printf("The %d char of the word: %c\n", subctr, string_arr[counter][subctr]);
      subctr++;
    }
    subctr = 0;
    counter++;
  }
  printf("The %d item of the array: %s\n", counter, string_arr[counter]);
}

void fix_newlines(char ** string_arr) {//replaces all newlines with 0's
  int counter = 0;
  int subctr = 0;
  while (string_arr[counter]) {
    //printf("The %d item of the array: %s\n", counter, string_arr[counter]);
    while (string_arr[counter][subctr]) {
      //printf("The %d char of the word: %c\n", subctr, string_arr[counter][subctr]);
      if (string_arr[counter][subctr] == '\n') {
	string_arr[counter][subctr] = 0;
      }
      subctr++;
    }
    subctr = 0;
    counter++;
  }
  //printf("The %d item of the array: %s\n", counter, string_arr[counter]);
}

void fix_newline(char ** string_arr) {//replaces the one buggy newline that appears at the end of all input due to hitting enter
  int counter = 0;
  int subctr = 0;
  while (string_arr[counter]) {//sets counter to last string pos
    //printf("The %d item of the array: %s\n", counter, string_arr[counter]);
    counter++;
  }
  //printf("The %d item of the array: %s\n", counter, string_arr[counter]);
  while (string_arr[counter-1][subctr]) {//one less than final pos is final string
    //printf("The %d letter of the word: %c\n", subctr, string_arr[counter-1][subctr]);
    subctr++;
  }//one less than final pos in final string is the newline char
  if (string_arr[counter-1][subctr-1] == '\n') {
    string_arr[counter-1][subctr-1] = 0;//set it to null to fix
  }
}  
  


int main(){
  char * input_line;//line the user gives
  char ** args_line;//the split lines 
  char ** line_arr;//the array of args_lines
  int i = 0;//index counter
  int num_args = 0;
  int current_arg = 0;
  int num_delims = 0;
  int child_info;
  pid_t child;
  while(1){//infinite loop
    
    printf("Loop Number: %d\n", i);//lets you know how long it been
    i++;

    if (num_args > current_arg) {
      printf("inside the num args else\n");
      input_line = args_line[current_arg];
      current_arg++;
      if (current_arg == num_args) {
	printf("freeing args_line before reallocating\n");
	//free(args_line);
	current_arg = 0;
	num_args = 0;
      }
    }

    else {
      printf("inside the first else\n");
      if(!fgets(input_line, 256, stdin)){//get user input
	printf("Error gaining input...\n");
	exit(0);
      }

      if ((num_delims = count_delims(input_line, ';'))) {
	printf("inside the delims if\n");
	num_args = num_delims + 1;
	printf("num delims: %d\n", num_delims);
	args_line = parse_args(input_line, " ; ", num_args);
	print_arr(args_line);
	input_line = args_line[current_arg];
	printf("the first line: %s\n", input_line);
	current_arg++;
      }
    }
    //printf("%s\n", input_line);
    
    line_arr = parse_args(input_line, " ", count_delims(input_line, ' ') + 1);//parse the args into line_arr
    print_arr(line_arr);
    //print_chars_in_arr(line_arr);
    fix_newline(line_arr);//fix buggy newline
    //print_chars_in_arr(line_arr);
    print_arr(line_arr);

    if (!strcmp(line_arr[0], "cd")) {//if cmd is cd
      chdir(line_arr[1]);//use chdir
    }

    else if (!strcmp(line_arr[0], "exit")) {//if cmd is exit
      exit(0);//use exit
    }

    else {//otherwise fork and do it 
      child = fork();
    
      if (!child) {
	execvp(line_arr[0], line_arr);
	printf("execution of command failed\n");
	exit(0);
      }
    
      wait(&child_info);
    }

  }
  return 0;
}
