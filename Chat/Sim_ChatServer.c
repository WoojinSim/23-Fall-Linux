#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 256

int main() {
    int fd1_client1, fd2_client1, fd1_client2, fd2_client2, n;
    char msg[MAXLINE];

    // Open FIFOs for communication with two clients
    fd1_client1 = open("./chatfifo1", O_RDWR | O_CREAT, 0666);
    fd2_client1 = open("./chatfifo2", O_RDWR | O_CREAT, 0666);

    fd1_client2 = open("./chatfifo3", O_RDWR | O_CREAT, 0666);
    fd2_client2 = open("./chatfifo4", O_RDWR | O_CREAT, 0666);

    if (fd1_client1 == -1 || fd2_client1 == -1 || fd1_client2 == -1 || fd2_client2 == -1) {
        perror("open");
        exit(1);
    }

    printf("* Server starts\n");

    while (1) {
        // Read from client 1 and write to client 1
        n = read(fd1_client1, msg, MAXLINE);
        printf("[Client 1] -> %s\n", msg);
        printf("[Server] : ");
        fgets(msg, MAXLINE, stdin);
        write(fd2_client1, msg, strlen(msg) + 1);

        // Read from client 2 and write to client 2
        n = read(fd1_client2, msg, MAXLINE);
        printf("[Client 2] -> %s\n", msg);
        printf("[Server] : ");
        fgets(msg, MAXLINE, stdin);
        write(fd2_client2, msg, strlen(msg) + 1);
    }
}

