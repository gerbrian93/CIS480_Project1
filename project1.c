#include <stdio.h>

int main()
{
   FILE *fp;
   char line[250];
   fp = fopen("students.asm", "r");
   if (fp == NULL)
   {
      perror("error opening file");
      return 1;
   }
   printf("File opened");
   fread(line, sizeof(char), 25, fp);
   printf("%s", line);
   fclose(fp);
}