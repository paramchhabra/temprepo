%{
#include <stdio.h>
#include <stdlib.h>

int max_length = 0;
%}

%%

[a-zA-Z0-9]+ {
  int length = yyleng;
  if (length > max_length) {
    max_length = length;
  }
}

\n { }
. { }

%%

int main() {
  FILE *input_file = fopen("input.txt", "r");
  if (!input_file) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }
  
  yyin = input_file;
  yylex();
  fclose(input_file);
  
  printf("Length of the longest word: %d\n", max_length);
  return EXIT_SUCCESS;
}

int yywrap() {
  return 1;
}
