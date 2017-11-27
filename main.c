#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void print_arr(char ** string_arr) {//prints all strings in an arr of strings
  int counter = 0;
  while (string_arr[counter]) {
    printf("The %d item of the array: %s\n", counter, string_arr[counter]);
    counter++;
  }
  printf("The %d item of the array: %s\n", counter, string_arr[counter]);
}

int count_delims(char* line, char* delim){
  int counter = 0;
  int ctr = 0;
  while(line[counter]){
    if(line[counter] == *delim){
      ctr++;
    }
    counter++;
  }
  return ctr;
}

char ** parse_args(char * line, char * delim, int num_commands){
  char ** args = (char **)calloc(num_commands+1, sizeof(char*));//allocate space for the possible args + ending null for execvp
  char * arg;
  int counter = 0;
  if(!args){//check if memory was allocated
    printf("Memory Allocation Failed\n");
    exit(1);
  }
  while( (arg=strsep(&line, delim)) ){//while you can remove the delim, do so
    args[counter] = arg;//move over the 2d char array and set it equal to the next divided arg
    counter += 1;
  }
  args[counter] = 0;//set last to null for execvp
  return args;
}

void fix_newline(char * line){
  strsep(&line, "\n");
}

int main(){
char * input_line = malloc(256);//line the user gives
char ** commands_arr;//the split lines
char ** line_arr;//the array of commands_arrs
int num_commands;
int num_args;
int counter;
int child_info;
pid_t child;
while(1){//infinite loop
  counter = 0;//reset counter
  num_commands = 0;//extra safety
  num_args = 0;
  if(!fgets(input_line, 256, stdin)){//get user input and if it fails, exit
     exit(0);
  }
  fix_newline(input_line);//set the user newline to null
  int num_commands = count_delims(input_line, ";");//count the number of commands separated by ; in the input string
  commands_arr = parse_args(input_line, ";", num_commands);//break line into individual commands
  while(counter <= num_commands){//while the program hasnt executed all supplied commands...
    num_args = count_delims(commands_arr[counter], " ");
    line_arr = parse_args(input_line, " ", num_args);//parse the args into line_arr
    //COMMAND EXECUTION
    if (!strcmp(line_arr[0], "cd")) {//if cmd is cd
      chdir(line_arr[1]);
    }
    else if (!strcmp(line_arr[0], "exit")) {//if cmd is exit
      exit(0);
    }
    else {//otherwise fork and do it
      child = fork();
      if (!child) {
        execvp(line_arr[0], line_arr);
        printf("No command found\n");
        exit(0);
      }
      wait(&child_info);
    }
    counter++;
    free(line_arr);
  }
free(commands_arr);
}
return 0;
}
