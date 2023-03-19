#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

int main()
{
   FILE *fp, *outfp;
   char buffer[50];
   // char *opcode, *rs, *rt, *rd, *shamt, *funct;

   fp = fopen("students.asm", "r");
   outfp = fopen("students2.out", "wb");

   if (fp == NULL || outfp == NULL)
   {
      perror("error opening file");
      return 1;
   }

   char *token;
   int output;
   while (fgets(buffer, sizeof(buffer), fp) != NULL) // this loop goes through each line of the program
   {
      // output = 0;
      //    We'll need the first loop to parse the line and convert to machine code
      token = strtok(buffer, " ,\t");
      // printf("%s\n", token);
      if (strcmp(token, ".data") == 0)
      {
         printf("read data");
      }
      else if (strcmp(token, ".integer") == 0) // reads the .integer directive
      {
         token = strtok(NULL, " ,\t"); // goes to next token of line
         printf("%s\n", token);
         output = atoi(token); // convert the value into 32 bit ingteger
         output = htonl(output);
         fwrite(&output, sizeof(int), 1, outfp);
      }
      else if (strcmp(token, ".dbyte") == 0)
      {
         char b, c = 0;
         token = strtok(NULL, " ,\t");
         output = 0;
         b = atoi(token) / 4;
         while (c < b)
         {
            fwrite(&output, sizeof(int), 1, outfp);
            c++;
         }

         // output = atoi(token);
         // fwrite(output, sizeof(int), 1, outfp);
      }
      else if (strcmp(token, ".text") == 0)
      {
         // token = strtok(NULL, " ,");
      }
      else
      {
         // R-type rtype(token)f
         // I-type
      }
      // token = strtok(NULL, " ,");

      // write to out file.
   }
   // content = fread(buffer, sizeof(char), 200, fp);
   fclose(fp);
   fclose(outfp);
}
