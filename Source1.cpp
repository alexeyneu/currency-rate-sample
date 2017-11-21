#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
 #include <unistd.h> 
       #include <netdb.h>
#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char  server_reply[15000];

     struct hostent *host;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
     host = gethostbyname("finance.yahoo.com");

    server.sin_addr.s_addr=*((unsigned long*)host->h_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons( 443 );

	connect(sock , (struct sockaddr *)&server , sizeof(server));


       



SSL_CTX *ctx = NULL;
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
OPENSSL_init_ssl(0, NULL); 



SSL_CTX *sslctx = SSL_CTX_new( SSLv23_client_method());

 
   SSL *cSSL = SSL_new(sslctx);
    SSL_set_fd(cSSL, sock);

//SSL_set_cipher_list(cSSL, "aNULL");


SSL_connect(cSSL);




	char        message[]="GET /quote/BTCUSD%3DX?p=BTCUSD%3DX HTTP/1.1\r\nhost:finance.yahoo.com\r\n\r\n";
      SSL_write(cSSL, message,strlen(message));


    SSL_read(cSSL,server_reply ,3800 );
      puts(server_reply);
SSL_read(cSSL,server_reply ,3400 );
      puts(server_reply);
SSL_read(cSSL,server_reply ,3400 );
      puts(server_reply);


 SSL_shutdown(cSSL);

 
    return 0;
}
