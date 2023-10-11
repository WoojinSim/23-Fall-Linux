#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#define _USE_MATH_DEFINES
#define N 4

/* 테일러 급수응용 sin() 함수 */
void sinx_taylor(int num_elements, int terms, double* x, double* result) {
	// num_elements: 입력 배열 X의 갯수
	// terms: 테일러 급수의 항 수
	// x: 입력 각도 (포인터)
	// result: 결과값을 저장할 배열 (포인터)

	for(int i=0; i<num_elements; i++) {
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
		result[i] = value;
	}
}

int main() {
	double x[N] = {0, M_PI/6., M_PI/3., 0.134};
	double res[N];

	for (int i = 0; i < N; i++) {
		pid_t pid = fork(); // 자식 프로세스 생성
		if (pid == 0) {
			sinx_taylor(N, 3, x, res); // 테일러
			printf("Child Process %d : sin(%f) by Taylor series = %f\n", i, x[i], res[i]);
			_exit(0); // 자식 프로세스 종료
		}
	}

	for (int i = 0; i < N; i++) {
		wait(NULL);
	}

	return 0;
}
