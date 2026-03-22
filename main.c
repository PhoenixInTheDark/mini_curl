#include <stdio.h>
#include <stdbool.h>
#include "parse_url.h"
#include <stdlib.h>


#define MAX_HEADERS_SIZE 2048

typedef struct req{
    bool isTLS;
    char method[16];
    char host[512];
    char path[512];
    int port;
    char headers[MAX_HEADERS_SIZE];
    char body[4096];

} request_t;

request_t *create_request(void){
    request_t *req = malloc(sizeof(request_t));
    req->isTLS = false; 
    req->method[0] = '\0';
    req->host[0] = '\0';
    req->path[0] = '\0';
    req->port = 0;
    req->headers[0] = '\0';
    req->body[0] = '\0';

    return req;
}

void destroy_request(request_t *req){
    free(req);
}

int main(int argc, char *argv[]){
    request_t *req = create_request();
    char *full_url = malloc(512);

    parse_full_url(argc, argv, full_url, 512, req->method, sizeof(req->method));
    
    if(is_domain_name(full_url)){
        // here we should do address resolve
    }
    else{
        get_ip(full_url, req->host, sizeof(req->host));
        req->port = get_port(full_url);
    }

    req->isTLS = is_tls(full_url);
    get_path(argv, req->path, sizeof(req->path));
    parse_flags(argc, argv, req->headers, req->body);

    //printf("%s\n%s\n%d\n%d\n%s\n%s\n%s\n", req->method, req->host, req->port, req->isTLS, req->path, req->headers, req->body);

    free(full_url);
    destroy_request(req);
    return 0;
}