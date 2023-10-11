#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int system(const char *cmdstring) {
	pid_t pid; int status;
	if (cmdstring == NULL) /* 명령어가 NULL인 경우 */
		return 1;
	if ( (pid = fork()) < 0) {
		status = -1; /* /* 프로세스 생성 실패 */
	} else if (pid == 0) { /* 자식 */
		execl("/bin/sh", "sh", "-c", cmdstring, (char *) 0);
		exit(127); /* execl 실패 */
	} else { /* 부모 */
		while (waitpid(pid, &status, 0) < 0) {
			if (error != EINTR) {
				status = -1; /* waitpid()로부터 EINTR외의 오류 */
				break;
			}
		}
	}
	return status;
}

int main() {
	int status;
	if ((status = system("date")) < 0)
		perror("system() error");
	printf("Return code = %d\n", WEXITSTATUS(status));
	if ((status = system("hello")) < 0)
		perror("system() error ");
	printf("Return code = %d\n", WEXITSTATUS(status));
	if ((status = system("who; exit 44")) < 0)
		perror("system() error ");
	printf("Return code = %d\n", WEXITSTATUS(status));
	return 0;
}
