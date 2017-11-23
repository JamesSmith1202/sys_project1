#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int count_delims(char* line, char* delim){
  char* p = line;
  int counter = 0;
  while(p){
    if(*p == *delim){
      counter++;
    }
  }
  return counter;
}

char ** parse_args(char * line, char * delim){
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
  }
  args[counter] = 0;//set last to null for execvp
  return args;
}

int main(){
  char * input_line;//line the user gives
  char ** args_line;//the split lines 
  char ** line_arr;//the array of args_lines
  int i;//index counter
  pid_t child;
  while(1){//infinite loop
    if(fgets(input_line, "%s", stdin) == -1){//get user input
      printf("Error gaining input...\n");
      exit(0);
    }
    line_arr = parse_args(input_line, ";");//parse input line for multiple commands 
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
  }
  return 0;
}
