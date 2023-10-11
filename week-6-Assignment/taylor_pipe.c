#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>
#define _USE_MATH_DEFINES
#define N 4
#define MAXLINE 100

/* 테일러 급수응용 sin() 함수 */
void sinx_taylor(int num_elements, int terms, double* x, double* result) {
	// num_elements: 입력 배열 X의 갯수
	// terms: 테일러 급수의 항 수
	// x: 입력 각도 (포인터)
	// result: 결과값을 저장할 배열 (포인터)
	
	for(int i=0; i<num_elements; i++) {
		int fd[2], length, n;
		char message[MAXLINE], line[MAXLINE];
		pid_t pid = fork(); // 자식 프로세스 생성
		pipe(fd);
		
		if (pid == 0) {
			close(fd[0]);
			double value = x[i]; // 초기값으로 x[i]를 설정

			// 테일러 급수의 첫 번째 항의 분자와 분모
			double numer = x[i] * x[i] * x[i];
			double denom = 6.; // 3! = 6
			
			int sign = -1; // 항의 음수 양수를 바꾸기위한 변수
			
			for(int j = 1; j <= terms; j++) {
				// 테일러 급수의 항을 더해 나감
				value += (double)sign * numer / denom;

				// 다음 항을 위한 분자와 분모 계산
				numer *= x[i] * x[i];
				denom *= (2.*(double)j+2.) * (2.*(double)j+3.);
				
				// 다음 항의 음수 양수를 변경
				sign *= -1;
			}

			// 계산된 값 저장
			sprintf(message, "%f", value); // 문자열로 변환 및 저장
			length = strlen(message) + 1; // 변환된 문자열 길이 저장
			write(fd[1], message, length); // 값 전달
			close(fd[1]); // 파이프 닫기
			_exit(0);
		} else {
			close(fd[1]); // 부모는 쓰지 않음
        		n = read(fd[0], line, MAXLINE);
			result[i] = atof(line);
			close(fd[0]); // 파이프 닫기
		}
	}
	
	for(int i=0; i<num_elements; i++) {
		wait(NULL);
	}
}

int main() {
	double x[N] = {0, M_PI/6., M_PI/3., 0.134};
	double res[N];
	
	sinx_taylor(N, 3, x, res);
	for(int i=0; i<N; i++) {
		printf("sin(%.2f) by Taylor series = %f\n", x[i], res[i]);
		printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
	}
	return 0;
}
