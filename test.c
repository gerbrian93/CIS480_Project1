#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h> //disable when using linux -compile with -lws2_32
// #include <netinet/in.h>  //disable when using windows

int main()
{

   FILE *fp, *outfp;
   char buffer[50];
   int value;
   fp = fopen("students.asm", "r");
   outfp = fopen("testout.out", "wb");

   while (fgets(buffer, sizeof(buffer), fp) != NULL)
   {
      char *token = strtok(buffer, " \t");
      // printf("%s", token);
      if (strcmp(token, ".integer") == 0)
      {
         token = strtok(NULL, " \t");
         value = atoi(token);
         value = htonl(value);
         fwrite(&value, sizeof(int), 1, outfp);
         printf("%d\n", value);
      }
      else
      {
         printf("false\n");
         value = 0;
         value = htonl(value);
         fwrite(&value, sizeof(int), 1, outfp);
      }
   }
   fseek(outfp, 0x200, SEEK_SET);
   value = 1;
   fwrite(&value, sizeof(int), 1, outfp);
   fclose(fp);
   fclose(outfp);
   return 0;
}