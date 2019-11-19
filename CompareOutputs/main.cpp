#include <iostream>

#define WAIT()	getchar();
#define END(x)	WAIT(); exit(x);

int main(int argc, char* argv[]) {
	FILE* correct = NULL;
	FILE* answer = NULL;
	fopen_s(&correct, argv[1], "r");
	fopen_s(&answer, argv[2], "r");

	FILE* correct_time = NULL;
	FILE* answer_time = NULL;
	fopen_s(&correct_time, argv[3], "r");
	fopen_s(&answer_time, argv[4], "r");

	if (!correct) {
		printf("Invalid file: %s\n", argv[1]);
		END(1);
	}

	int c_size = 0;
	int a_size = 0;

	fscanf_s(correct, "%d", &c_size);
	fscanf_s(answer, "%d", &a_size);

	if (c_size != a_size) {
		printf("Different query size: %d %d\n", c_size, a_size);
		END(2);
	}

	int cnt_wrong = 0;
	double cx, cy;
	double ax, ay;
	double ct, at;
	double sum_ct = 0, sum_at = 0;
	for (int i = 0; i < c_size; i++) {
		fscanf_s(correct, "%lf %lf", &cx, &cy);
		fscanf_s(answer, "%lf %lf", &ax, &ay);
		fscanf_s(correct_time, "%lf", &ct);
		fscanf_s(answer_time, "%lf", &at);
		if (cx != ax || cy != ay) cnt_wrong++;
		sum_ct += ct;
		sum_at += at;
	}
	printf("%g\n",cnt_wrong/(double)c_size*100);
	printf("c: %g\ta: %g\n", sum_ct / c_size, sum_at / c_size);
	printf("done.\n");
}