#include <stdio.h>
#include <time.h>
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// Greedy Search Algorithm
void getGreedyPath(int, unsigned short **, int*, int*, int);
void two_Opt_Path(int, unsigned short **, int*, int*, int);
void pathSwap(int *path, int first, int second);
int costCheck(int *path, int** distance, int nOfCity);
void pathSwap2(int *, int, int);
// Main Function
int main(int argc, const char * argv[]) {
	// init 
	int i = 0, j = 0;
	int score = 0;
	int best_score = 0;
	int nOfCity = 600;
	int * path = (int *)malloc(sizeof(int)*nOfCity);
	int * best_path = (int *)malloc(sizeof(int)*nOfCity);

	unsigned short ** distances = (unsigned short **)malloc(sizeof(unsigned short*)*nOfCity);
	unsigned short num;

	clock_t begin, end;

	begin = clock();
	// open file
	FILE *in = fopen("input_600.txt", "rb");
	FILE *out = fopen("result.txt", "w");
	if (!in) {
		fputs("File not found!\n", stderr);
		return 1;
	}
	for (i = 0; i < nOfCity; i++) {
		distances[i] = (unsigned short *)malloc(sizeof(unsigned short)*nOfCity);
	}
	// read file
	int k = 0;
	for (i = 0; i < nOfCity; i++) {
		for (j = 0; j < k + 1; j++) {

			fscanf(in, "%hd", &num);
			distances[i][j] = num;
			distances[j][i] = num;
		}
		k++;
	}

	// close file
	fclose(in);



	// get Path
	getGreedyPath(nOfCity, distances, path, &score, 0);

	best_score = score;
	for (i = 1; i < nOfCity; i++) {
		getGreedyPath(nOfCity, distances, path, &score, i);
		if (score < best_score) {

			best_score = score;
			memcpy(best_path, path, sizeof(int)*nOfCity);

		}
	}
	end = clock();
	printf("greed time = %f\n", (double)(end - begin) / CLOCKS_PER_SEC);




	two_Opt_Path(nOfCity, distances, best_path, &best_score, 0);




	// print result & write file
	fprintf(out, "%d\n", best_score);
	for (i = 0; i < nOfCity; i++) {
		printf("%d-", best_path[i]);
		fprintf(out, "%d\n", best_path[i]);
	}
	printf("score = %d\n\n", best_score);
	return 0;
}

// Greedy Search Algorithm
void getGreedyPath(int nOfCity, unsigned short ** distance, int * path, int * score, int startpoint) {
	// init
	int i, j, start, next, min;
	short length;
	int * isRemain = (int *)malloc(sizeof(int)*nOfCity);
	for (i = 0; i < nOfCity; i++) isRemain[i] = 1;
	// start
	start = startpoint;
	isRemain[start] = 0;
	path[0] = start;
	*score = 0;
	// append closest city
	for (i = 1; i < nOfCity; i++) {
		next = 0;
		min = 999999;
		// iterate remain city & find Minimum distance
		for (j = 0; j < nOfCity; j++) {
			if (isRemain[j]) {
				length = distance[start][j];
				if (length < min) {
					min = length;
					next = j;
				}
			}
		}
		// append to path
		path[i] = next;
		isRemain[next] = 0;
		*score += min;
		start = next;
	}
}

void two_Opt_Path(int nOfCity, unsigned short ** distance, int * path, int * score, int startpoint) {
	int i, j, start;
	int test_score = 0;
	int * test_path = (int *)malloc(sizeof(int)*nOfCity);
	int * isRemain = (int *)malloc(sizeof(int)*nOfCity);
	clock_t begin, end;

	for (i = 0; i < nOfCity; i++) isRemain[i] = 1;
	srand(time(NULL));
	
	begin = clock();
	end = clock();


	for (int k = 0; k < nOfCity;){

		start = rand() % nOfCity;

		if (isRemain[start]){
			isRemain[start] = 0;
			k++;
			getGreedyPath(nOfCity, distance, test_path, &test_score, start);

			while (1){
				
				

				int max = 0, maxi = -1, maxj = -1;
				for (i = 1; i < nOfCity - 1; i++){
					for (j = i + 1; j < nOfCity - 1; j++){
						int change =
							distance[test_path[i]][test_path[i + 1]] + distance[test_path[j]][test_path[j + 1]]
							- distance[test_path[i]][test_path[j]] - distance[test_path[i + 1]][test_path[j + 1]];

						if (max < change){
							max = change;

							maxi = i;
							maxj = j;
						}
					}
				}
				if (maxi == -1) break;
				pathSwap2(test_path, maxi, maxj);

				end = clock();
				if ((double)(end - begin) / CLOCKS_PER_SEC > 29.99) {
					printf("2-opt time = %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
					return;
				}
			}

			int test_score = costCheck(test_path, distance, nOfCity);
			if (*score > test_score) {
				*score = test_score;
				memcpy(path, test_path, sizeof(int)*nOfCity);
				printf("%d..%d\n", start, *score);
			}
		}
	}

	end = clock();
	printf("2-opt time = %f\n", (double)(end - begin) / CLOCKS_PER_SEC);

}

void pathSwap2(int *path, int first, int second){
	int dec = 0;

	for (int i = first + 1; i <= first + (second - first) / 2; i++){

		int temp = path[i];
		path[i] = path[second - i + first + 1];
		path[second - i + first + 1] = temp;


	}

}

void pathSwap(int *path, int first, int second){

	for (int i = 0; i < (second - first) / 2; i++){
		int temp = path[second - i];
		path[second - i] = path[first + i];
		path[first + i] = temp;
	}

}

int costCheck(int *path, unsigned short** distance, int nOfCity){
	int total = 0;

	for (int i = 0; i < nOfCity - 1; i++)
		total += distance[path[i]][path[i + 1]];


	return total;
}
