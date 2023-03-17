#include <stdio.h>
#include <string.h>

int main()
{
   FILE *fp;
   char line[50];
   char j;
   fp = fopen("students.asm", "r");
   if (fp == NULL)
   {
      perror("error opening file");
      return 1;
   }
   // char *opcode, *rs, *rt, *rd, *shamt, *funct;
   // j = 1;
   char *token;
   while (fgets(line, sizeof(line), fp) != NULL) // this loop goes through each line of the program
   {
      // printf(line);
      //   We'll need the first loop to parse the line and convert to machine code
      token = strtok(line, " ");
      // write to out file.
      // while (token != NULL)
      //{
      printf("%s", token);
      token = strtok(NULL, "");
      //}
   }
}