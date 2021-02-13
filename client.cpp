//
// Created by 姚雨 on 2021/2/11.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "client.h"

void error_handling(char *message);

int main(int argc, char *argv []) {
    int sd;
    struct sockaddr_in serv_addr;
    int str_len;

    char  message[] = "xxx";

    // check the input
    if(argc != 3) {
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }

    //  fd-socket
    sd = socket(PF_INET,SOCK_STREAM,0);
    if(sd == -1){
        error_handling("socket() error");
        exit(1);
    }

    // clean the add var and init
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; //地址族 https://blog.csdn.net/ordeder/article/details/19284715
    serv_addr.sin_addr.s_addr =inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]);
    sleep(10);
    printf("begin connect\r\n");
    if (connect(sd, (struct sockaddr *)&serv_addr, sizeof (serv_addr) == -1))) {
        error_handling("connect() error\r\n");
    }
    printf("begin send message\r\n");
    write(sd, message, sizeof(message));
    printf("end send message:%s to server\r\n", message);

    sleep(10);
    close(sd);
    return 0;

//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
//    serv_addr.sin_port = htons(atoi(argv[2]));
//
//    sleep(10);
//    printf("begin connect\r\n");
//    if(connect(sd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1){
//        error_handling("connect() error\r\n");
//    }
//    printf("end connect\r\n\r\n");
//
//    sleep(10);
//    printf("begin send message\r\n");
//    write(sd, message, sizeof(message));
//    printf("end send message:%s to server\r\n", message);
//
//    sleep(10);
//    close(sd);
//    return 0;

}

void error_handling(char *message){
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}
