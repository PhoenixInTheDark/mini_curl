#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define N 100
#define BODY_SIZE 4096
#define HEADERS_SIZE 2048


bool is_tls(char full_url[]){
    char *method_search = strstr(full_url, "://");
    if(method_search == NULL) return false;
    int method_len = method_search - full_url;
    char method[N];
    strncpy(method, full_url, method_len);
    method[method_len] = '\0';
    if(strcmp(method, "https") == 0){
        return true;
    }
    else{
        return false;
    }
}

void get_ip(char full_url[], char *ip_out, int ip_size){
    char *after_search = strstr(full_url, "://");
    if(after_search == NULL){ ip_out[0] = '\0'; return; }
    after_search += 3;

    char *colon = strchr(after_search, ':');
    char *slash = strchr(after_search, '/');
    char *end;

    if(colon != NULL && (slash == NULL || colon < slash))
        end = colon;
    else if(slash != NULL)
        end = slash;
    else
        end = after_search + strlen(after_search);

    int ip_len = end - after_search;
    if(ip_len >= ip_size) ip_len = ip_size - 1;
    strncpy(ip_out, after_search, ip_len);
    ip_out[ip_len] = '\0';
}

int get_port(char *full_url){
    char *port_search = strchr(full_url, ':');
    if(port_search == NULL) return -1;
    port_search = strchr(port_search + 1, ':');
    if(port_search == NULL) return -1;

    int port_out = atoi(port_search + 1);
    return port_out;
}

void parse_full_url(int argc, char *argv[], char full_url_out[], int url_size, char method[], int method_size){
    for (int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-X") == 0 && i+1 < argc){
            strncpy(method, argv[i+1], method_size - 1);
            method[method_size - 1] = '\0';
            i++;
            continue;
        }
        if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-H") == 0){
            i++;
            continue;
        }
        if(argv[i][0] != '-'){
            strncpy(full_url_out, argv[i], url_size - 1);
            full_url_out[url_size - 1] = '\0';
            return;
        }
    }
    printf("URL not found!\nUse -h to show info.\n");
    full_url_out[0] = '\0';
}

void parse_flags(int argc, char *argv[], char headers[], char body[]){
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-d") == 0 && i + 1 < argc){
            strncpy(body, argv[++i], BODY_SIZE - 1);
            body[BODY_SIZE-1] = '\0';
        }
        else if(strcmp(argv[i], "-H") == 0 && i + 1 < argc){
            strncat(headers, argv[++i], HEADERS_SIZE - strlen(headers) - 1);
            strncat(headers, "\r\n", HEADERS_SIZE - strlen(headers) - 1);
        }
    }
}

bool is_domain_name(char domain_name[]){
    char *host = strstr(domain_name, "://");
    if(host != NULL) host += 3;
    else host = domain_name;
    if(isdigit((unsigned char)*host)) return false;
    else return true;
}

void get_path(char *argv[], char path[], int path_size){
    for(int i = 1; argv[i] != NULL; i++){
        if(argv[i][0] == '-'){ i++; continue; }
        char *after_scheme = strstr(argv[i], "://");
        if(after_scheme == NULL) continue;
        after_scheme += 3;
        char *slash = strchr(after_scheme, '/');
        if(slash != NULL){
            strncpy(path, slash, path_size - 1);
            path[path_size - 1] = '\0';
        } else {
            strncpy(path, "/", path_size - 1);
            path[path_size - 1] = '\0';
        }
        return;
    }
    strncpy(path, "/", path_size - 1);
    path[path_size - 1] = '\0';
}
