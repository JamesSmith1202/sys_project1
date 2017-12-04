#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "headers.h"

#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"
#define BUFFER_SIZE 256

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
  int len = strlen(delim);
  char * target = line;
  while(target = strstr(target, delim)){
    counter++;
    target += len;
  }
  return counter + 1;
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
    counter++;
  }
  args[counter] = 0;//set last to null for execvp
  return args;
}

void fix_newline(char * line){
  strsep(&line, "\n");
}

char * strip_spaces(char * line){
  int len = strlen(line);
  char * end = line+len-1;
  while(*line && isspace(*line)){
    line++;
  }
  while(end > line && isspace(*end)){
    *end-- = '\0';
  }
  return line;
}

void redirect_in(char **line_arr, int num_args) {
  int i;
  int in;
  for (i = 0; line_arr[i]; i++) {
    if (!strcmp(line_arr[i], "<")) {
      in = open(line_arr[i+1], O_RDONLY);
      dup2(in, 0);
      close(in);
      memmove(line_arr+i, line_arr+i+2, (num_args-i)*sizeof(char *));
    }
  }
}

void redirect_out(char ** line_arr, int num_args){// >
  int i;
  int out;
  for (i = 0; line_arr[i]; i++) {
    if (!strcmp(line_arr[i],">")) {   
      out = open(line_arr[i+1], O_WRONLY | O_APPEND | O_CREAT, 0664);
      dup2(out, 1);
      close(out);
      memmove(line_arr+i, line_arr+i+2, (num_args-i)*sizeof(char *));
    }
  }
}

void execute_child(char ** line_arr, int num_args){
  redirect_in(line_arr, num_args);
  redirect_out(line_arr, num_args);
  execvp(line_arr[0], line_arr);
  printf("No command found\n");
  exit(0);
}

void execute(int num_commands, char ** commands_arr){
  int counter = 0;
  int num_args;
  int child_info;
  pid_t child;
  char ** line_arr;//the array of commands_arrs
  while(counter < num_commands){//while the program hasnt executed all supplied commands...
      commands_arr[counter] = strip_spaces(commands_arr[counter]);
      num_args = count_delims(commands_arr[counter], " ");
      line_arr = parse_args(commands_arr[counter], " ", num_args);//parse the args into line_arr
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
          execute_child(line_arr, num_args);
        }
        wait(&child_info);
      }
      counter++;
      free(line_arr);
  }
}

void get_input(char ** input){
  char cwd[BUFFER_SIZE];//string for the current working directory
  printf(BLUE "%s$ " RESET, getcwd(cwd, BUFFER_SIZE)); //prompt with the current directory
  if(!fgets(*input, BUFFER_SIZE, stdin)){//get user input and if it fails, exit
    exit(0);
  }
  fix_newline(*input);//set the user newline to null
}