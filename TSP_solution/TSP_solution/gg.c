//#include <stdio.h>
//#include <time.h>
//
//// Greedy Search Algorithm
//void getGreedyPath(int, unsigned short **, int*, int*, int);
//void two_Opt_Path(int, unsigned short **, int*, int*, int);
//int* selectRandomOpt(int nOfCity, int startpoint);
//
//
//// Main Function
//int main(int argc, const char * argv[]) {
//	// init 
//	int i, j;
//	int score = 0;
//	int best_score = 0;
//	int nOfCity = 100;
//	int * path = (int *)malloc(sizeof(int)*nOfCity);
//	int * best_path = (int *)malloc(sizeof(int)*nOfCity);
//	unsigned short ** distances = (unsigned short **)malloc(sizeof(unsigned short*)*nOfCity);
//	unsigned short num;
//
//
//	// open file
//	FILE *in = fopen("input.txt", "rb");
//	FILE *out = fopen("result.txt", "w");
//	if (!in) {
//		fputs("File not found!\n", stderr);
//		return 1;
//	}
//
//
//
//	for (i = 0; i < nOfCity; i++) {
//		distances[i] = (unsigned short *)malloc(sizeof(unsigned short)*nOfCity);
//	}
//
//	// read file
//	int k = 0;
//	for (i = 0; i<nOfCity; i++) {
//		for (j = 0; j<k + 1; j++) {
//
//			fscanf(in, "%hd", &num);
//			distances[i][j] = num;
//			distances[j][i] = num;
//		}
//		k++;
//	}
//
//	// close file
//	fclose(in);
//
//
//
//	// get Path
//	getGreedyPath(nOfCity, distances, path, &score, 0);
//	/*best_score = score;
//	for (i = 1; i < nOfCity; i++) {
//	getGreedyPath(nOfCity, distances, path, &score, i);
//	if (score < best_score) {
//
//	best_score = score;
//	memcpy(best_path, path, sizeof(int)*nOfCity);
//	}
//	}*/
//
//
//
//	//two_Opt_Path(nOfCity, distances, best_path, &score,0);
//
//	// print result & write file
//	fprintf(out, "%d\n", best_score);
//	for (i = 0; i<nOfCity; i++) {
//		printf("%d\n", best_path[i]);
//		fprintf(out, "%d\n", best_path[i]);
//	}
//	printf("score = %d\n\n", best_score);
//	return 0;
//}
//
//// Greedy Search Algorithm
//void getGreedyPath(int nOfCity, unsigned short ** distance, int * path, int * score, int startpoint) {
//	// init
//	int i, j, start, next, min;
//	short length;
//	int * isRemain = (int *)malloc(sizeof(int)*nOfCity);
//	for (i = 0; i<nOfCity; i++) isRemain[i] = 1;
//	// start
//	start = startpoint;
//	isRemain[start] = 0;
//	path[0] = start;
//	*score = 0;
//	// append closest city
//	for (i = 1; i<nOfCity; i++) {
//		next = 0;
//		min = 999999;
//		// iterate remain city & find Minimum distance
//		for (j = 0; j<nOfCity; j++) {
//			if (isRemain[j]) {
//				length = distance[start][j];
//				if (length<min) {
//					min = length;
//					next = j;
//				}
//			}
//		}
//		// append to path
//		path[i] = next;
//		isRemain[next] = 0;
//		*score += min;
//		start = next;
//	}
//}
//
//void two_Opt_Path(int nOfCity, unsigned short ** distance, int * path, int * score, int startpoint) {
//	int i, j, start, next, min, count = 0;
//
//	short length;
//	int * isRemain = (int *)malloc(sizeof(int)*nOfCity);
//	for (i = 0; i<nOfCity; i++) isRemain[i] = 1;
//	srand(time(NULL));
//	*score = 0;
//	start = startpoint;
//	isRemain[start] = 0;
//
//
//
//
//
//
//
//}
////
////int* selectRandomOpt(int nOfCity, int startpoint) {
////	static int opts[2];
////
////	int opt_1 = rand()*nOfCity;
////	int opt_2 = rand()*nOfCity;
////
////	while (opt_1 == opt_2 || opt_1 == startpoint || opt_2 ==startpoint) opt_2 = rand()*nOfCity;
////	
////	opts[0] = opt_1;
////	opts[1] = opt_2;
////
////	return opts;
////}
//
//
//
