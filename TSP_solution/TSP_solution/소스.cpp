#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;

void swapResultS(int result[], int i, int j);

int main()
{
	clock_t begin, end;
	begin = clock();
	//----------------------------------------------
	static int graph[1000][1000] = { 0, };
	static int result[1000] = { 0, };
	static int resultS[1000] = { 0, };
	int graphSize = 0;
	//   ifstream input("inputdata.txt");
	ifstream input("input.txt");
	//-----------------입력받기---------------------
	while (input.eof() == false)
	{
		for (int i = 0; i <= graphSize; i++)
		{
			int inputInt;
			input >> inputInt;
			graph[graphSize][i] = inputInt;
			graph[i][graphSize] = inputInt;
		}
		graphSize++;
	}
	for (int i = 0; i < graphSize; i++)
		result[i] = -1;
	//-------------------그리디 알고리즘으로 초기 값 설정---------------------------
	int startNode = 302;
	int nowNode = startNode;
	for (int i = 0; i < graphSize - 1; i++)
	{
		int min = 9999, minj = -1;
		for (int j = 0; j < graphSize; j++)
		{
			if (min > graph[nowNode][j] && result[j] == -1 && graph[nowNode][j] > 0)
			{
				min = graph[nowNode][j];
				minj = j;
			}
		}
		result[nowNode] = minj;
		nowNode = minj;
	}
	result[nowNode] = startNode;
	/*   srand(time(NULL));
	for (int i = 0; i < graphSize - 1; i++)
	{
	int a;
	while (true)
	{
	a = rand() % graphSize;
	if (result[a] == -1)
	break;
	}
	result[nowNode] = a;
	nowNode = a;
	}
	result[nowNode] = startNode;*/
	end = clock();
	//--------------------데이터 출력--------------------------
	cout << "time : " << (double)(end - begin) / CLOCKS_PER_SEC << endl;

	nowNode = startNode;
	cout << startNode << "\t";
	int cost = 0;
	for (int i = 0; i < graphSize; i++)
	{
		resultS[i] = nowNode;
		cost += graph[nowNode][result[nowNode]];
		cout << result[nowNode] << "\t";
		nowNode = result[nowNode];
	}
	cout << endl << "cost : " << cost << endl;
	//------------------max 값을 기준으로 2opt----------------------------
	while (true)
	{
		int max = 0, maxi = -1, maxj = -1;
		for (int i = 0; i < graphSize - 4; i++)
			for (int j = i + 2; j < graphSize - 1; j++)
			{
				int originalCost = graph[resultS[i]][resultS[i + 1]] + graph[resultS[j]][resultS[j + 1]];
				int newCost = graph[resultS[i]][resultS[j]] + graph[resultS[i + 1]][resultS[j + 1]];
				if (max < (originalCost - newCost))
				{
					max = (originalCost - newCost);
					maxi = i;
					maxj = j;
				}
			}
		if (maxi == -1)
			break;
		swapResultS(resultS, maxi, maxj);
	}
	//-------------------min 값을 기준으로 2opt---------------------------
	/*   while (true)
	{
	int min = 9999, maxi = -1, maxj = -1;
	for (int i = 0; i < graphSize - 4; i++)
	for (int j = i + 2; j < graphSize - 1; j++)
	{
	int originalCost = graph[resultS[i]][resultS[i + 1]] + graph[resultS[j]][resultS[j + 1]];
	int newCost = graph[resultS[i]][resultS[j]] + graph[resultS[i + 1]][resultS[j + 1]];
	if (min > (originalCost - newCost) && (originalCost - newCost) > 0)
	{
	min = (originalCost - newCost);
	maxi = i;
	maxj = j;
	}
	}
	if (maxi == -1)
	break;
	swapResultS(resultS, maxi, maxj);
	}*/
	end = clock();
	//----------------------------------------------

	cout << "time : " << (double)(end - begin) / CLOCKS_PER_SEC << endl;

	cost = 0;
	for (int i = 0; i < graphSize; i++)
	{
		if (i == graphSize - 1)
			cost += graph[resultS[i]][resultS[startNode]];
		else
			cost += graph[resultS[i]][resultS[i + 1]];
		cout << resultS[i] << "\t";
	}
	cout << startNode << endl << "cost : " << cost << endl;

	return 0;
}

void swapResultS(int result[], int i, int j)
{
	for (int it = i + 1; it <= i + (j - i) / 2; it++)
	{
		int temp = result[it];
		result[it] = result[j - it + (i + 1)];
		result[i - it + (j + 1)] = temp;
	}
}