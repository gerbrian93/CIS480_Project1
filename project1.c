#include <stdio.h>
#include <string.h>

int main()
{
   FILE *fp, *outfp;
   char buffer[200];
   char *opcode, *rs, *rt, *rd, *shamt, *funct;

   fp = fopen("students.asm", "r");
   outfp = fopen("students2.out", "wb");

   if (fp == NULL || outfp == NULL)
   {
      perror("error opening file");
      return 1;
   }

   char *token;

   while (fgets(buffer, sizeof(buffer), fp) != NULL) // this loop goes through each line of the program
   {
      // printf(line);
      //   We'll need the first loop to parse the line and convert to machine code
      token = strtok(buffer, " ,\n");
      while (token != NULL)
      {
         if (token == NULL || token[0] == '#')
         {
            printf("%s\n", token);
         }
         token = strtok(NULL, " ,\n");
      }
      // write to out file.
   }
   // content = fread(buffer, sizeof(char), 200, fp);
   fclose(fp);
}
