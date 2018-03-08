/* Sample TCP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>

char key[1000];

typedef struct {
	char mesg[15];
	int number;
	int *ptr_to_n;
} data;

void print_key(struct sockaddr_in cliaddr, int connfd) {
   FILE* keyfile = fopen("./key", "r");
   fscanf(keyfile, "%s", key);
   sendto(connfd, key, strlen(key), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}

int perform_action(struct sockaddr_in cliaddr, int connfd, socklen_t clilen) {
   data data;
   data.number = 1;
   data.ptr_to_n = &data.number;
   char *himsg = "Hi, there! What's your name?\n";
   int n;
   sendto(connfd, himsg, strlen(himsg), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
   n = recvfrom(connfd, data.mesg, 35, 0, (struct sockaddr *)&cliaddr, &clilen);
   if(data.number == 1146570058 && data.ptr_to_n == 0x5a58535948474c4d) {
      print_key(cliaddr, connfd);
   }
   return 0;   
}

int main(int argc, char**argv)
{
   int listenfd,connfd;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t clilen;
   pid_t     childpid;

   listenfd=socket(AF_INET,SOCK_STREAM,0);
   setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(32000);
   bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   listen(listenfd,1024);

   for(;;)
   {
      clilen=sizeof(cliaddr);
      connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

      perform_action(cliaddr, connfd, clilen);

      close(connfd);
   }
   
   close (listenfd);
   
   return 0;
}

