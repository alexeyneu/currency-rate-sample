#include<sstream>
#include<string>
#include<cstring>
#include<iostream>
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
 #include <unistd.h> 
       #include <netdb.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
struct triggerblock
{	
	double q;
	long long block[3];
	long long b;
	long long t;
//	tm *c;
//	tm *p;
	unsigned char ptrigger;
	float outofthis;
	double x;
	long double F;
	short finishup;
	double f;
	unsigned char  E;
};

int main(int argc , char *argv[])
{
triggerblock mo={};
    int sock;
    struct sockaddr_in server;
    char  server_reply[5000];

     struct hostent *host;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
     host = gethostbyname("www.coingecko.com");

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




char message[]="GET /en/price_charts/monero/usd HTTP/2.0\r\nhost:www.coingecko.com\r\n\r\n";
      SSL_write(cSSL, message,strlen(message));
static int q;
std::string c;
std::stringstream fr;
do
{
    mo.t=SSL_read(cSSL,server_reply ,4400 );
    fr.write(server_reply,mo.t); 
}
while(q++ < 54);

mo.b=fr.str().find("coin-value");
mo.b=fr.str().find("$",mo.b)+1;
fr.seekg(mo.b);
fr >> mo.F;
std::cout << mo.F<<'\n';
 SSL_shutdown(cSSL);
 SSL_free(cSSL);
close(sock); 
    return 0;
}
