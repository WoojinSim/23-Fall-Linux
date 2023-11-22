#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void intHandler();
void intHandler2();

int main() {
	signal(SIGALRM, intHandler);
	signal(SIGINT, intHandler2);
	alarm(10);
	
	int correct = 0;
	while(!correct) {
		if(getchar() == "1") {
			if(getchar() == "2") {
				if(getchar() == "3") {
					if(getchar() == "\n") {
						correct = 1;
					}
				}
			}
		}
	}
	printf("비밀번호 일치!");
}

void intHandler(int signo) {
	printf("비밀번호 불일치!");
	exit(0);
}

void intHandler2(int signo) {
	printf("10초 초기화");
	alarm(10);
}
