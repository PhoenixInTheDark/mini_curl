#ifndef PARSE_URL_H
#define PARSE_URL_H

#include <stdbool.h>

bool is_tls(char full_url[]);

void get_ip(char full_url[], char *ip_out, int ip_size);

int get_port(char *full_url);

void parse_full_url(int argc, char *argv[], char full_url_out[], int url_size, char method[], int method_size);

void parse_flags(int argc, char *argv[], char headers[], char body[]);

bool is_domain_name(char domain_name[]);

void get_path(char *argv[], char path[], int path_size);

#endif
