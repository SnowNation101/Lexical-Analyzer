#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  int a = 0;
  char* b[100] = {"10", "11", "123", };

  a = 1 + a;

  printf("hello world! \n");

  char* token;
  token = (char *)malloc(10 * sizeof(char));
  strcpy(token, "asdf");
  char t = 'k';
  strcat(token, &t);
  printf("token: %s \n", token);

  FILE *file = fopen("D:/dev/Lexical Analyzer/test.c", "r+");
  char c;
  for (int i = 0; i < 39; i++) {
    c = (char)fgetc(file);
    printf("%c", c);
  }
  fseek(file, 0, SEEK_CUR);

  int abcd = 123.22E99;

  c = '\n';

  c = (char)fgetc(file);
  printf("%c", c);

  // test
  char table[10][100];
  printf("\ntoken= %s =token", table[1]);

  if (table[1][0] == NULL) {
    strcpy(table[1], token);
  }
  printf("\ntoken= %s =token", token);
  printf("\ntoken= %s =token", table[1]);
  return 0;
}

/**asdf
 * asdfasdf
 * asdfasdf
 * asdfasdfasdf
 * asdfasdfasdf
*/


asdf =11;