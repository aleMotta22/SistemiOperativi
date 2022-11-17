#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 3333
#define MAXQUEUE 1
#define DIM 1024

char * list(char *buffer, char *history)
{
   if(strcmp(buffer, "SHOW\r\n") != 0)
   {
      strcat(history, ";");
      strcat(history, buffer);
      return "OK\n";
   }
   else
      return history;
}

int main(int argc, char **argv)
{
   if(argc != 1)
   {
      printf("use: %s\n", argv[0]);
      return 0;
   }

   int sockfd = socket(PF_INET, SOCK_STREAM, 0);
   if(sockfd == -1)
   {
      perror("socket()");
      exit(1);
   }

   int reuse = 1;
   if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
   {
      perror("setsockopt()");
      exit(1);
   }

   struct sockaddr_in local;
   socklen_t len = sizeof(local);

   memset(&local, 0, len);
   local.sin_family = AF_INET;
   local.sin_port = htons(PORT);
   local.sin_addr.s_addr = INADDR_ANY;

   if(bind(sockfd, (struct sockaddr *) &local, len) == -1)
   {
      perror("bind()");
      exit(1);
   }

   if(listen(sockfd, MAXQUEUE) == -1)
   {
      perror("listen()");
      exit(1);
   }

   struct sockaddr_in remote;
   char history[DIM] = "";

   while(1)
   {
      printf("Server in ascolto...\n");

      int newsockfd = accept(sockfd, (struct sockaddr *) &remote, &len);
      if(newsockfd == -1)
      {
         perror("accept()");
         exit(1);
      }

      printf("Connessione stabilita con il client\n");

      char buffer[DIM];

      while(1)
      {
         int n = read(newsockfd, buffer, DIM - 1);
         if(n == -1)
         {
            perror("read()");
            exit(1);
         }
         if(n == 0)
         {
            printf("Chiusura connessione con il client\n");
            close(newsockfd);
            break;
         }

         buffer[n] = '\0';

         printf("Messaggio dal client: %s", buffer);

         strcpy(buffer, list(buffer, history));

         write(newsockfd, buffer, strlen(buffer));         
      }
   }

   return 0;
}