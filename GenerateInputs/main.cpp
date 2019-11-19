#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
	/*
	argv[1]: output file type
	argv[2]: the number of test set
	argv[3]: points_file
		- first line: input_size
		- the others: inputs_coords_x inputs_coords_y
	argv[4]: queries_file
		- first line: query_size k
		- the others: queries_coords_x queries_coords_y
	*/
	if (argc < 5) return -1;

	int p_len = strlen(argv[1]) + strlen(argv[3]) + 10;
	int q_len = strlen(argv[1]) + strlen(argv[4]) + 10;
	char* p_path = (char*)calloc(p_len, sizeof(char));
	char* q_path = (char*)calloc(q_len, sizeof(char));
	int size_set = atoi(argv[2]);

	srand((unsigned)time(NULL));

	for (int i = 0; i < atoi(argv[2]); i++) {
		char buffer[10] = { '_', };
		_itoa_s(i, buffer + 1, sizeof(buffer + 1), 10);
		strcpy_s(p_path, p_len, argv[3]);
		// strcpy_s(p_path + strlen(p_path), p_len, buffer);
		strcpy_s(p_path + strlen(p_path), p_len, argv[1]);
		printf("%s\n", p_path);

		strcpy_s(q_path, q_len, argv[4]);
		// strcpy_s(q_path + strlen(q_path), q_len, buffer);
		strcpy_s(q_path + strlen(q_path), q_len, argv[1]);
		printf("%s\n", q_path);

		FILE* p_file = NULL;
		fopen_s(&p_file, p_path, "w");

		int input_size = 1000;// rand() % 100 + 1;
		fprintf(p_file, "%d\n", input_size);
		for (int j = 0; j < input_size; j++) {
			if (!(j % 1000)) printf("%g%%\n", (double)j / input_size * 100);
			fprintf(p_file, "%g %g\n", rand() % 100 + rand() % 100 / 100.0, rand() % 100 + rand() % 100 / 100.0);
		}
		fclose(p_file);

		FILE* q_file = NULL;
		fopen_s(&q_file, q_path, "w");

		int query_size = 1000; // rand() % 100 + 1;
		int k = rand() % input_size + 1;
		fprintf(q_file, "%d %d\n", query_size, k);
		for (int j = 0; j < query_size; j++) {
			if (!(j % 1000)) printf("%g%%\n", (double)j / query_size * 100);
			fprintf(q_file, "%g %g\n", rand() % 100 + rand() % 100 / 100.0, rand() % 100 + rand() % 100 / 100.0);
		}
		fclose(q_file);
	}

	printf("done.\n");
	getchar();
}