#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// 자식 프로세스를 생성하여 echo 명령어를 실행한다.
int main( ) {
printf("Parent process \n");
	if (fork( ) == 0) {
	execl("/bin/echo", "echo", "hello", NULL);
		fprintf(stderr, "Failed");
		exit(1);
	}
	printf("End of parent process\n");
	return 0;
}
