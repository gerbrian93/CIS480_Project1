#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

unsigned int Rtype(char opcode, char rs, char rt, char rd, char shamt, char funct)
{
   unsigned int r_type = (opcode << 26);
   r_type |= (rs << 21);
   r_type |= (rt << 16);
   r_type |= (rd << 11);
   r_type |= (shamt << 6);
   r_type |= funct;
   return r_type;
}

unsigned int Itype(char opcode, char rs, char rt, char imm)
{
   unsigned int i_type = opcode << 26;
   i_type |= (rs << 21);
   i_type |= (rt << 16);
   i_type |= (imm & 0xFFFF);
   return i_type;
}

int main()
{
   FILE *fp, *outfp;
   char buffer[50], flag = 0;
   char opcode, rs, rt, rd, shamt, funct;
   short imm;
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
         output = atoi(token);   // convert the value into 32 bit ingteger
         output = htonl(output); // reverse binary string
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
         printf("reading text segment");
      }
      else
      {
         if (strcmp(token, "add") == 0 || strcmp(token, "sll") == 0 || strcmp(token, "slt") == 0 || strcmp(token, "addu") == 0)
         {

            opcode = 0;
            if (strcmp(token, "add") == 0)
            {
               funct = 0x20;
               token = strtok(NULL, " ,$\n");
               rd = atoi(token);
               token = strtok(NULL, " ,$\n");
               rs = atoi(token);
               token = strtok(NULL, " ,$\n");
               rt = atoi(token);
               output = Rtype(opcode, rs, rt, rd, shamt, funct);
               output = htonl(output);
               fwrite(&output, sizeof(int), 1, outfp);
            }
            else if (strcmp(token, "sll") == 0)
            {
               funct = 0x00;
               token = strtok(NULL, " ,$\n");
               rd = atoi(token);
               token = strtok(NULL, " ,$\n");
               rt = atoi(token);
               token = strtok(NULL, " ,$\n");
               shamt = atoi(token);
               rs = 0;
               output = Rtype(opcode, rs, rt, rd, shamt, funct);
               output = htonl(output);
               fwrite(&output, sizeof(int), 1, outfp);
            }
            else if (strcmp(token, "slt") == 0)
            {
               funct = 0x2A;
               token = strtok(NULL, " ,$\n");
               rd = atoi(token);
               token = strtok(NULL, " ,$\n");
               rs = atoi(token);
               token = strtok(NULL, " ,$\n");
               rt = atoi(token);
               shamt = 0;
               output = Rtype(opcode, rs, rt, rd, shamt, funct);
               output = htonl(output);
               fwrite(&output, sizeof(int), 1, outfp);
            }

            else if (strcmp(token, "addu") == 0)
            {
               funct = 0x21;
               token = strtok(NULL, " ,$\n");
               rd = atoi(token);
               token = strtok(NULL, " ,$\n");
               rs = atoi(token);
               token = strtok(NULL, " ,$\n");
               rt = atoi(token);
               shamt = 0;
               output = Rtype(opcode, rs, rt, rd, shamt, funct);
               output = htonl(output);
               fwrite(&output, sizeof(int), 1, outfp);
            }
         }
         else if (strcmp(token, "addi") == 0 || strcmp(token, "lui") == 0)
         {
            if (flag < 1)
            {
               fseek(outfp, 0x200, SEEK_SET);
               flag++;
            }

            if (strcmp(token, "addi") == 0)
            {
               opcode = 0x08;
               token = strtok(NULL, " ,$");
               rt = atoi(token);
               token = strtok(NULL, " ,$");
               rs = atoi(token);
               token = strtok(NULL, " ,$");
               imm = atoi(token);
               output = Itype(opcode, rs, rt, imm);
               output = htonl(output);
               fwrite(&output, sizeof(int), 1, outfp);
            }
            else if (strcmp(token, "lui") == 0)
            {
               opcode = 0xF;
               token = strtok(NULL, " ,$");
               rt = atoi(token);
               token = strtok(NULL, " ,$");
               imm = atoi(token);
               rs = 0;
               output = Itype(opcode, rs, rt, imm);
               output = htonl(output);
               fwrite(&output, sizeof(int), 1, outfp);
            }
         }
      }
   }
   output = 0;
   fseek(outfp, 0x3FC, SEEK_SET);
   fwrite(&output, sizeof(int), 1, outfp);
   fclose(fp);
   fclose(outfp);
}
