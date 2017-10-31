#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
 #include <unistd.h> 
       #include <netdb.h>
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char  server_reply[5000];

     struct hostent *host;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     host = gethostbyname("finance.yahoo.com");


    server.sin_addr.s_addr=*((unsigned long*)host->h_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");


char        message[]="GET /currency-converter/#from=USD;to=EUR;amt=1 HTTP/1.1\r\nhost:finance.yahoo.com\r\n\r\n";

        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }


        //Receive a reply from the server
        if( recv(sock , server_reply , 3000 , 0) < 0)
        {
            puts("recv failed");

        }

        puts("Server reply :");

        puts(server_reply);



        //Receive a reply from the server
        if( recv(sock , server_reply , 3000 , 0) < 0)
        {
            puts("recv failed");

        }
         puts(server_reply);


    close(sock);
    return 0;
}