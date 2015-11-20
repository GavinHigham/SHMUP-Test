void * parse_the_junk(ALLEGRO_THREAD *le_thread, void *data)
{
    //Setup json objects
    json_error_t *errors = NULL;
    json_t *auth      = json_object();
    json_t *cfg       = json_object();
    json_t *braindata = json_object();
    json_object_set(auth, "appName", json_string("TestFour"));
    json_object_set(auth, "appKey", json_string("cad1aa3e1f6157363dd4b121d35ecdacb3a56fdf"));
    json_object_set(cfg, "enableRawOutput", json_false());
    json_object_set(cfg, "format", json_string("Json"));

    char buffer[BUFLEN];
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = 13854;

    //Network stuff I don't understand. I only accept that it works. For now.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("127.0.0.1");
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
    //Authenticate!
    printf("Attempting to authenticate with:\n%s\n", auth_string);
    n = write(sockfd, auth_string, strlen(auth_string));
    if (n < 0)
        error("ERROR writing to socket");
    //Configure!
    printf("Attempting to configure with:\n%s\n", cfg_string);
    n = write(sockfd, cfg_string, strlen(cfg_string));
    if (n < 0)
        error("ERROR writing to socket");

    printf("Advancing to first \\r.\n");
    bzero(buffer, BUFLEN);
    do {
        read(sockfd,buffer,1);
        printf("%c", buffer[0]);
    } while (buffer[0] != '\r');
    printf("Beginning to parse complete packets.\n");
    int k = 0;
    while(!doexit)
    {
        bzero(buffer, BUFLEN);
        while(read(sockfd,&buffer[k],1) && buffer[k] != '\r' && k < BUFLEN) {
            printf("%c", buffer[k]);
            k++;
        }
        braindata = json_loads(buffer, k, errors);
        json_t *eSense = json_object_get(braindata, "eSense");
        if (eSense != NULL) {
            int attention_tmp = (int)json_integer_value(json_object_get(eSense, "attention"));
            if (attention_tmp != 0) attention = attention_tmp;
            int meditation_tmp = (int)json_integer_value(json_object_get(eSense, "meditation"));
            if (meditation_tmp != 0) meditation = meditation_tmp; 
            printf("a: %i, m: %i\n", attention, meditation);
        }
        k = 0;
    }
    close(sockfd);
    free(cfg_string);
    free(auth_string);
    return NULL;
}