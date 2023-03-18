#include <stdio.h>
#include <string.h>

int main()
{
   FILE *fp, *outfp;
   char buffer[200];
   char *opcode, *rs, *rt, *rd, *shamt, *funct;
   int data = 0, text = 0;
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
      token = strtok(buffer, " ,");
      while (token != NULL)
      {
         if (strcmp(token, ".text") == 0)
         {
            // add code
            text = 0;
            data = 1;
         }
         else if (strcmp(token, ".data") == 0)
         {
            // add code
            data = 1;
            text = 0;
         }
         else if (strcmp(token, ".dbyte") == 0)
         {
            // add code
         }
         else if (strcmp(token, ".integer") == 0)
         {
            // add code
         }
         else
         {
            // R-type rtype(token)
            // I-type
         }
         token = strtok(NULL, " ,");
      }
      // write to out file.
   }
   // content = fread(buffer, sizeof(char), 200, fp);
   fclose(fp);
}
