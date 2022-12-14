/*
 * File            : test_stl_epoll_client.c
 * Author          : ZhangLe
 * CreateTime      : 2022-10-08 18:44:34
 * LastModified    : 2022-10-10 07:14:25
 * Vim             : ts=4, sw=4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./test_stl_epoll.h"
#include "../src/stl_socket.h"

demo_request* demo_request_alloc(char* service_addr) {

    demo_request* request = NULL;

    if (service_addr) {
        size_t len = strlen(service_addr);
        request = (demo_request *)calloc(1, sizeof(demo_request) + len);
        request->num = 2;
    }

    return request;
}

static void demo_request_print(demo_request* req) {
    printf("send num %d success!\n", req->num);
}

int main(int argc, char *argv[]){
    int fd = 0;
    int ret = -1;
    int try = 0, max_try = 3;
    char service_addr[] = "127.0.0.1:8081";
    demo_request *req = demo_request_alloc(service_addr);

    if (req) {
        fd = stl_socket_init_client("127.0.0.1", "8081");
        while(try < max_try) {
            ret = write(fd, req, sizeof(*req) + strlen(service_addr) + 1);
            printf("fd = %d\n", fd);
            printf("ret = %d\n", ret);
            if (ret > 0) {
                demo_request_print(req);
                break;
            }
            try ++;
        }
    }

    return 0;
}
