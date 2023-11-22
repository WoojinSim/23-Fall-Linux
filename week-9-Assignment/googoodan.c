#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void intHandler();
void intHandler2();
void intHandler3();

void print_gugu() {
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j < 10; j++) {
			printf("%d * %d = %d\n", i, j, i * j);
		}
		if (i == 9) {
			signal(SIGINT, intHandler3);
		}
	}
}

int main() {
	int pid;
	int child_id;
	if ((pid = fork()) == 0) {
		signal(SIGINT, intHandler2);
		print_gugu();
		pause();
	} else {
		child_id = pid;
		signal(SIGINT, intHandler);
		wait();
	}
}

void intHandler(int signo) {
	kill(child_id, SIGINT);
}

void intHandler2(int signo) {
	printf("구구단 실행 중이니 종료 불가\n");
}

void intHandler3(int signo) {
	kill(-getpid(), SIGKILL);
}
