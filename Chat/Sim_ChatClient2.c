#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 256

int main() {
    int fd1, fd2, n;
    char inmsg[MAXLINE];

    // Open FIFOs for communication with the server
    fd1 = open("./chatfifo3", O_RDWR | O_CREAT, 0666);
    fd2 = open("./chatfifo4", O_RDWR | O_CREAT, 0666);

    if (fd1 == -1 || fd2 == -1) {
        perror("open");
        exit(1);
    }

    printf("* Client starts\n");

    while (1) {
        // Client writes to the server through fd1
        printf("[Client] : ");
        fgets(inmsg, MAXLINE, stdin);
        write(fd1, inmsg, strlen(inmsg) + 1);

        // Client reads from the server through fd2
        n = read(fd2, inmsg, MAXLINE);
        printf("[Server] -> %s\n", inmsg);
    }
}

