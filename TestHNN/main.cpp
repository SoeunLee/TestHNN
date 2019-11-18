#include <iostream>
#include <algorithm>

using namespace std;

typedef double type_point;

// #define DEBUG	1

#define DIM		2	// dimension
#define X		0
#define Y		1

struct Point {
	type_point coords[DIM];
	double distance;

	Point() {
		coords[X] = 0.0;
		coords[Y] = 0.0;
		distance = 0.0;
	};

	Point(const Point& other) {
		coords[X] = other.coords[X];
		coords[Y] = other.coords[Y];
		distance = other.distance;
	}

	type_point operator[](size_t idx) const { return coords[idx]; }
	type_point& operator[](size_t idx) { return coords[idx]; }
};

#define WAIT()	getchar();
#define END(x)	WAIT(); exit(x);

Point* readPoints(char* path, int& size, int& k) {
	FILE* file = NULL;
	fopen_s(&file, path, "r");

	if (!file) {
		printf("Invalid file: %s\n", path);
		END(1);
	}

	if (k < 0)
		fscanf_s(file, "%d", &size);
	else
		fscanf_s(file, "%d %d", &size, &k);

	Point* points = new Point[size];
	for (int i = 0; i < size; i++)
		fscanf_s(file, "%lf %lf", &points[i].coords[X], &points[i].coords[Y]);

#ifdef DEBUG
	printf("%s:\n", path);
	for (int i = 0; i < size; i++)
		printf("%g %g\n", points[i].coords[X], points[i].coords[Y]);
	printf("\n");
#endif // DEBUG

	fclose(file);
	return points;
}

int compare(const void* _a, const void* _b) {
	Point* a = (Point*)_a;
	Point* b = (Point*)_b;
	if (a->distance > b->distance) return 1;
	else if (a->distance < b->distance) return -1;
	else return 0;
}

#define EPSILON		0.1

int main(int argc, char* argv[]) {
	/*
	points_file
		- first line: input_size
		- the others: inputs_coords_x inputs_coords_y
	queries_file
		- first line: query_size k
		- the others: queries_coords_x queries_coords_y
	*/

	// input params exception
	if (argc < 2) {
		printf("Usage: executive_file points_file [queries_file]\n");
		END(-1);
	}

	// read input points
	int k = -1;
	int input_size = 0;
	Point* inputs = readPoints(argv[1], input_size, k);

	if (argc == 2) {
		printf("no queries_file\n");
		END(-2);
	}

	// read query points
	k = 0;
	int query_size = 0;
	Point* queries = readPoints(argv[2], query_size, k);

	double epsilon = EPSILON;

	// query
	for (int i = 0; i < query_size; i++) {
		Point* result = new Point[k];	// save 1st minimum ~ kth distance
		double distance = 0;

		printf("query #%d: (%g %g)\n", i, queries[i].coords[X], queries[i].coords[Y]);

		for (int j = 0; j < input_size; j++) {
			distance = sqrt(pow(inputs[j].coords[X] - queries[i].coords[X], 2) + pow(inputs[j].coords[Y] - queries[i].coords[Y], 2));

			int r = 0;
			while (r < k - 1) {
				if (result[r].distance == 0) break;
				r++;
			}
			if (r == k - 1 && distance > result[r].distance) continue;

			result[r] = inputs[j];
			result[r].distance = distance;
			qsort(result, k, sizeof(Point), compare);
		}
		for (int j = 0; j < k; j++)
			printf("(%g %g) %g\n", result[j].coords[X], result[j].coords[Y], result[j].distance);
	}

	printf("done.\n");
	END(0);
}