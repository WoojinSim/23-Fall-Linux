#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void intHandler();
/* 인터럽트 시그널을 처리한다. */

int main( ) {
	signal(SIGINT, intHandler);
	sleep(3);
	raise(SIGINT);
	printf("\nEnd of main \n");
}

void intHandler(int signo) {
	printf("\nSIGINT \n");
	printf("\nSig No.: %d\n", signo);
	exit(0);
}
