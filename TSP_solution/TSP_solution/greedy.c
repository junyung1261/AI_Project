#include <stdio.h>

// Greedy Search Algorithm
void getGreedyPath(int, unsigned short **, int*, int*);

// Main Function
int main(int argc, const char * argv[]) {
	// init 
	int i, j=0;
	int score = 0;
	int nOfCity = 100;
	int * path = (int *)malloc(sizeof(int)*nOfCity);
	unsigned short ** distances = (unsigned short **)malloc(sizeof(unsigned short*)*nOfCity);
	unsigned short num;

	// open file
	FILE *in = fopen("input.txt", "rb");
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
	for (i = 0; i<nOfCity; i++) {
		distances[i] = (unsigned short *)malloc(sizeof(unsigned short)*nOfCity);
		for (j = 0; j<k+1; j++) {
			
				fscanf(in, "%hd", &num);
				distances[i][j] = num;
				distances[k][i] = num;
			
		}
		k++;
	}
	

	printf("%hd, %hd--\n", distances[0][1], distances[77][60]);
	
	// close file
	fclose(in);

	// get Path
	getGreedyPath(nOfCity, distances, path, &score);

	// print result & write file
	fprintf(out, "%d\n", score);
	for (i = 0; i<nOfCity; i++) {
		printf("%d\n", path[i]);
		fprintf(out, "%d\n", path[i]);
	}
	printf("score = %d\n\n", score);
	return 0;
}

// Greedy Search Algorithm
void getGreedyPath(int nOfCity, unsigned short ** distance, int * path, int * score) {
	// init
	int i, j, start, next, min;
	short length;
	int * isRemain = (int *)malloc(sizeof(int)*nOfCity);
	for (i = 0; i<nOfCity; i++) isRemain[i] = 1;
	// start
	start = 0;
	isRemain[start] = 0;
	path[0] = start;
	*score = 0;
	// append closest city
	for (i = 1; i<nOfCity; i++) {
		next = 0;
		min = 999999;
		// iterate remain city & find Minimum distance
		for (j = 0; j<nOfCity; j++) {
			if (isRemain[j]) {
				length = distance[start][j];
				if (length<min) {
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
