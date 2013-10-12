#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <jansson.h>
#include "parson/parson.c"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    //Setup json objects
    json_error_t *errors;
    json_t *auth      = json_object();
    json_t *cfg       = json_object();
    json_t *braindata = json_object();
    json_object_set(auth, "appName", json_string("TestFour"));
    //json_object_set(auth, "appKey", json_string("9f54141b4b4c567c558d3a76cb8d715cbde03096"));
    json_object_set(cfg, "enableRawOutput", json_false());
    json_object_set(cfg, "format", json_string("Json"));

    FILE *fp;
    char buffer[256];
    int sockfd, portno, n, socket_size;
    unsigned int m = sizeof(socket_size);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = 13854;

    //Network stuff I don't understand. I only accept that it works. For now.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    //Get the socket size.
    //getsockopt(fdsocket,SOL_SOCKET,SO_RCVBUF,(void *)&socket_size, &m);

    char  *cfg_string = json_dumps(cfg, 0);
    char *auth_string = json_dumps(auth, 0);
    sleep(2);
    /*
    n = write(sockfd, auth_string, strlen(auth_string));
    if (n < 0) 
         error("ERROR writing to socket");
    */
    n = write(sockfd, cfg_string, strlen(cfg_string));
    if (n < 0) 
         error("ERROR writing to socket");
    sleep(2);
    fp = fopen("brainoutput.txt", "a+");

    bzero(buffer, 256);
    do {
        read(sockfd,buffer,1);
    } while (buffer[0] != '\r');
    int i, k = 0;
    for (i = 0; i < 50; i++)
    {
        bzero(buffer, 256);
        while(read(sockfd,&buffer[k],1) && buffer[k] != '\r' && k < 256) {
            k++;
        }
        braindata = json_loads(buffer, k, errors);
        printf("%s\n", json_dumps(braindata, 0));
        if (errors && errors->text)
            printf("%s\n", errors->text);
        k = 0;
    }
    fclose(fp);
    close(sockfd);
    free(cfg_string);
    free(auth_string);
    return 0;
}
