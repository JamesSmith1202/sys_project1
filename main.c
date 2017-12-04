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
#define BUFFER_SIZE 256ma

int main(){
  char * input_line = malloc(BUFFER_SIZE);//line the user gives
  char ** commands_arr;//the split lines
  int num_commands;
  while(1){//infinite loop
    get_input(&input_line);
    num_commands = count_delims(input_line, ";");//count the number of commands separated by ; in the input string
    commands_arr = parse_args(input_line, ";", num_commands);//break line into individual commands
    execute(num_commands, commands_arr);
    free(commands_arr);
  }
  return 0;
}
