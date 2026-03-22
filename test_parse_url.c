#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parse_url.h"

#define PASS "\033[32mPASS\033[0m"
#define FAIL "\033[31mFAIL\033[0m"

static int tests_run = 0;
static int tests_passed = 0;

#define CHECK(label, cond) do { \
    tests_run++; \
    if(cond){ tests_passed++; printf("[" PASS "] %s\n", label); } \
    else { printf("[" FAIL "] %s\n", label); } \
} while(0)

/* --- is_tls --- */
void test_is_tls(void){
    CHECK("is_tls: https",  is_tls("https://example.com:443/path") == true);
    CHECK("is_tls: http",   is_tls("http://example.com:80/path")   == false);
    CHECK("is_tls: no scheme", is_tls("example.com") == false);
}

/* --- get_ip --- */
void test_get_ip(void){
    char ip[64];

    get_ip("https://example.com:443/path", ip, sizeof(ip));
    CHECK("get_ip: domain", strcmp(ip, "example.com") == 0);

    get_ip("http://192.168.1.1:8080/", ip, sizeof(ip));
    CHECK("get_ip: ip addr", strcmp(ip, "192.168.1.1") == 0);

    get_ip("no-scheme-url", ip, sizeof(ip));
    CHECK("get_ip: no scheme → empty", ip[0] == '\0');
}

/* --- get_port --- */
void test_get_port(void){
    /* get_port читает argv[3] */
    char *argv_443[] = {"prog", "arg1", "arg2", "https://example.com:443/path", NULL};
    CHECK("get_port: 443", get_port(argv_443) == 443);

    char *argv_8080[] = {"prog", "arg1", "arg2", "http://localhost:8080/api", NULL};
    CHECK("get_port: 8080", get_port(argv_8080) == 8080);

    char *argv_bad[] = {"prog", "arg1", "arg2", "http://localhost/noport", NULL};
    CHECK("get_port: no port → -1", get_port(argv_bad) == -1);
}

/* --- parse_full_url --- */
void test_parse_full_url(void){
    char url[256], method[32];

    /* URL без флагов */
    char *argv1[] = {"prog", "https://example.com:443/path", NULL};
    method[0] = '\0';
    parse_full_url(2, argv1, url, sizeof(url), method, sizeof(method));
    CHECK("parse_full_url: plain url", strcmp(url, "https://example.com:443/path") == 0);

    /* -X перед URL */
    char *argv2[] = {"prog", "-X", "POST", "https://api.example.com:80/", NULL};
    method[0] = '\0'; url[0] = '\0';
    parse_full_url(4, argv2, url, sizeof(url), method, sizeof(method));
    CHECK("parse_full_url: -X method", strcmp(method, "POST") == 0);
    CHECK("parse_full_url: url after -X", strcmp(url, "https://api.example.com:80/") == 0);

    /* нет URL */
    char *argv3[] = {"prog", "-X", "GET", NULL};
    url[0] = '\0'; method[0] = '\0';
    parse_full_url(3, argv3, url, sizeof(url), method, sizeof(method));
    CHECK("parse_full_url: no url → empty", url[0] == '\0');
}

/* --- parse_flags --- */
void test_parse_flags(void){
    char headers[2048] = "";
    char body[4096]    = "";

    char *argv[] = {"prog", "-d", "{\"key\":\"val\"}", "-H", "Content-Type: application/json", NULL};
    parse_flags(5, argv, headers, body);

    CHECK("parse_flags: body",    strcmp(body, "{\"key\":\"val\"}") == 0);
    CHECK("parse_flags: header",  strstr(headers, "Content-Type: application/json") != NULL);
    CHECK("parse_flags: CRLF",    strstr(headers, "\r\n") != NULL);
}

/* --- is_domain_name --- */
void test_is_domain_name(void){
    CHECK("is_domain_name: domain",  is_domain_name("example.com") == true);
    CHECK("is_domain_name: ip",      is_domain_name("192.168.1.1") == false);
    CHECK("is_domain_name: letter",  is_domain_name("localhost")   == true);
}

/* --- get_path --- */
void test_get_path(void){
    char path[256];

    char *argv1[] = {"prog", "https://example.com:443/some/path?q=1", NULL};
    get_path(argv1, path, sizeof(path));
    CHECK("get_path: with path", strcmp(path, "/some/path?q=1") == 0);

    char *argv2[] = {"prog", "http://example.com:80", NULL};
    get_path(argv2, path, sizeof(path));
    CHECK("get_path: no path → /", strcmp(path, "/") == 0);

    char *argv3[] = {"prog", "-X", "GET", "https://api.example.com:443/v1", NULL};
    get_path(argv3, path, sizeof(path));
    CHECK("get_path: skips flags", strcmp(path, "/v1") == 0);
}

/* --- main --- */
int main(void){
    printf("=== parse_url tests ===\n\n");

    test_is_tls();
    printf("\n");
    test_get_ip();
    printf("\n");
    test_get_port();
    printf("\n");
    test_parse_full_url();
    printf("\n");
    test_parse_flags();
    printf("\n");
    test_is_domain_name();
    printf("\n");
    test_get_path();

    printf("\n=== %d/%d passed ===\n", tests_passed, tests_run);
    return tests_passed == tests_run ? 0 : 1;
}
