#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

void Rtype(char opcode, char rs, char rt, char rd, char shamt, char funct)
{
   int r_type = 0;
   r_type |= (atoi(rs) << 21);
   r_type |= (atoi(rt) << 16);
   r_type |= (atoi(rd) << 11);
   r_type |= (atoi(shamt) << 6);
   r_type |= atoi(funct);
   return htonl(r_type);

   printf("rtype\n");
}

void Itype()
{
   printf("itype\n");
}

int main()
{
   FILE *fp, *outfp;
   char buffer[50];
   char *opcode, *rs, *rt, *rd, *shamt, *funct;

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

      if (strcmp(token, ".data") == 0)
      {
         printf("read data");
      }
      else if (strcmp(token, ".integer") == 0) // reads the .integer directive
      {
         token = strtok(NULL, " ,\t"); // goes to next token of line
         // printf("%s\n", token);
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
      }
      else if (strcmp(token, ".text") == 0)
      {
         fseek(outfp, 0x200, SEEK_SET);
      }
      else
      {
         if (strcmp(token, "add") == 0 || strcmp(token, "sll") == 0 || strcmp(token, "slt") == 0 || strcmp(token, "addu") == 0)
         {
            if (strcmp(token, "add") == 0)
            {
            }
            else if (strcmp(token, "sll") == 0)
            {
            }
            else if (strcmp(token, "slt") == 0)
            {
            }
            else if (strcmp(token, "addu"))
            {
            }
            Rtype(opcode, rs, rt, rd, shamt, funct);
            printf("%d", output);
         }
         else if (strcmp(token, "addi") == 0 || strcmp(token, "lui") == 0)
         {
            Itype();
         }
      }
   }
   // content = fread(buffer, sizeof(char), 200, fp);
   fclose(fp);
   fclose(outfp);
}
