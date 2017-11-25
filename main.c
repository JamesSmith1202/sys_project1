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

char ** parse_args(char * line, char delim){
  int num_args = count_delims(line, delim) + 1;
  char ** args = (char **)calloc(num_args, sizeof(char*));//allocate space for the possible args + ending null for execvp
  if(!args){//check if memory was allocated
    printf("Memory Allocation Failed\n");
    exit(1);
  }
  char * arg;
  int counter = 0;
  while( (arg=strsep(&line, delim)) ){//while you can remove the delim, do so
    args[counter] = arg;//move over the 2d char array and set it equal to the next divided arg
    counter += 1;// added the increment james it wasnt here before
  }
  args[counter] = 0;//set last to null for execvp
  return args;
}

char ** parse_args_cruse(char * line){//your code was kinda buggy so this autoseparates on spaces
  char ** args = (char **)calloc(6, sizeof(char*));//allocate space for the 5 possible args + ending null for execvp
  if(!args){//check if memory was allocated
    printf("Memory Allocation Failed\n");
    exit(1);
  }
  char * arg;
  int counter = 0;
  while( (arg=strsep(&line, " ")) ){//while you can remove spaces, do so
    args[counter] = arg;//move over the 2d char array and set it equal to the next divided arg
    //printf("arg[%d]: %s\n", counter, args[counter]);
    counter++;
  }
  args[counter] = 0;//set last to null for execvp
  //printf("arg[%d]: %s\n", counter, args[counter]);
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
  string_arr[counter-1][subctr-1] = 0;//set it to null to fix
}  
  


int main(){
  char * input_line;//line the user gives
  char ** args_line;//the split lines 
  char ** line_arr;//the array of args_lines
  int i = 0;//index counter
  int child_info;
  pid_t child;
  while(1){//infinite loop
    
    printf("Loop Number: %d\n", i);//lets you know how long it been
    i++;

    /*
    //printf("%d\n", scanf("%s", input_line));
    scanf("%s", input_line);
    //printf("%s\n", input_line);
    line_arr = parse_args_cruse(input_line);
    */
    if(!fgets(input_line, 256, stdin)){//get user input
      printf("Error gaining input...\n");
      exit(0);
    }

    //printf("%s\n", input_line);
    
    line_arr = parse_args_cruse(input_line);//parse the args into line_arr
    //print_chars_in_arr(line_arr);
    fix_newline(line_arr);//fix buggy newline
    //print_chars_in_arr(line_arr);

    if (!strcmp(line_arr[0], "cd")) {//if cmd is cd
      chdir(line_arr[1]);//use chdir
    }

    else if (!strcmp(line_arr[0], "exit")) {//if cmd is exit
      exit(0);//use exit
    }

    else {//otherwise fork and do it 
      child = fork();
    
      if (!child) {
	//printf("made it here\n");
	execvp(line_arr[0], line_arr);
	printf("made past it here\n");
	exit(0);
      }
    
      wait(&child_info);
    }

    /*
    if(!fgets(input_line, sizeof(stdin), stdin)){//get user input
      printf("Error gaining input...\n");
      exit(0);
    }
    line_arr = parse_args(input_line, " ");//parse input line for multiple commands
    i = 0;
    while(!line_arr[i]){//while there are more lines of instructions to execute...
      args_line = parse_args(line_arr[i], " ");//split on spaces for execvp
      child = fork();
      if (!child){//if it is the child process
	execvp(args_line[0], args_line);//turn the child into the executed program
      }
      free(args_line);
    }
    free(line_arr);
    */
  }
  return 0;
}
