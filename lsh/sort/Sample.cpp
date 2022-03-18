#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>

// sort(정렬) 처리속도 비교

int compare(const void* a, const void* b) // 값 비교함수
{
	int num1 = *(int*)a;
	int num2 = *(int*)b;
	if (num1 < num2)
		return -1;
	if (num1 > num2)
		return 1;
	return 0;
}

bool SwapGreat(int* a, int* b)
{
	if (*a > *b)
	{
		int t = *a;
		*a = *b;
		*b = t;
		return true;
	}
	return false;
}

// 데이터 세팅
void SetData(int item[], int iCount)
{
	// 반복적으로 같은 배열 값이 나오도록 처리한다.
	srand((unsigned int)time(NULL));

	for (int a = 0; a < iCount; a++)
	{
		item[a] = rand() % iCount;
	}
	DataPrint(item, iCount);
}

// 선택정렬
// 배열중 최소값을 찾아 정렬, 처음정렬한것 이외 나머지들 순차적으로 정렬
void SelectionSort(int item[], int count)
{
	int iIndex;
	for (int a = 0; a < count - 1; a++)
	{
		iIndex = a;
		for (int b = a + 1; b < count; b++)
		{
			if (item[b] < item[iIndex])
			{
				iIndex = b;
			}
		}
		if (a != iIndex)
		{
			SwapGreat(&item[a], &item[iIndex]);
		}
	}
}

// 거품정렬
// 두개의 인접한 원소를 비교해 정렬
void BubbleSort(int item[], int count)
{
	for (int a = 0; a < count - 1; a++)
	{
		bool bFlag = false;
		for (int b = 0; b < count - a - 1; b++)
		{
			if (SwapGreat(&item[b], &item[b + 1]))
			{
				bFlag = true;
			}
		}
		if (bFlag == false) break;
	}
}

// 삽입정렬
// 모든요소를 앞에서부터 차례대로 비교하여 위치를 찾아 정렬, 배열이 길수록 비효율적
void InsertionSort(int item[], int count, int iStart = 1, int iStep = 1)
{
	for (int a = iStart; a < count; a += iStep)
	{
		int temp = item[a];
		int b = a - iStep;
		while (b >= 0 && item[b] > temp)
		{
			item[b + iStep] = item[b];
			b -= iStep;
		}
		item[b + iStep] = temp;
	}
}

// 쉘 정렬
// 삽입정렬을 보완한 정렬,
void shellsort(int item[], int n)
{
	// n수 보다 작은 최대 그룹의 개수를 찾는다.
	// 1, 2, 3,  4,  5
	// 1, 4, 13, 40, 121, ...
	int maxGroup = 1;
	for (int k = 1; k < n; k++)
	{
		int g = (pow(3, k) - 1) / 2;
		if (g > n)
		{
			break;
		}
		maxGroup = k;
	};

	while (maxGroup > 0)
	{
		int g = (pow(3, maxGroup--) - 1) / 2;
		// 부분정렬 수행
		for (int s = 0; s < g; s++)
		{
			InsertionSort(item, n, s, g);
		}
	}
}

// 퀵정렬
// 1. 리스트안에 있는 요소를 선택한다 이것을 피벗이라고 부름.
// 2. 피벗을 기준으로 비벗보다 작은것들은 왼쪽 큰것들은 오른쪽에 옮겨짐
// 3. 피벗을 제외한 왼쪽 오른쪽 리스트를 다시정렬한다
// 4. 부분리스트들이 더이상 분할이 불가능할때까지 반복

// 퀵정렬은 셀 정렬보다 2~3배 빠르다. 하지만 쉘정렬도 무시 못할 정도로 빠르다.
// 쉘 정렬은 메모리 한도내에서 얼마든지 정렬할 수 있으나
// 퀵 정렬은 스택을 사용함으로써 스택넘침(Stack overflow)의 우려를 내포하고 있다.
void QuickSort(int item[], int iStart, int iEnd)
{
	int iPivot = item[iStart];
	int iBeginStart = iStart;
	int iBeginEnd = iEnd;
	while (iStart < iEnd)
	{
		while (iPivot <= item[iEnd] && iStart < iEnd)
		{
			iEnd--;
		}
		if (iStart > iEnd) break;
		while (iPivot >= item[iStart] && iStart < iEnd)
		{
			iStart++;
		}
		if (iStart > iEnd) break;
		SwapGreat(&item[iStart], &item[iEnd]);
	}
	SwapGreat(&item[iBeginStart], &item[iStart]);

	if (iBeginStart < iStart)
		QuickSort(item, iBeginStart, iStart - 1);
	if (iBeginEnd > iEnd)
		QuickSort(item, iStart + 1, iBeginEnd);
}

// 화면출력
void DataPrint(int item[], int iCount)
{
	return;
	for (int t = 0; t < iCount; t++)
	{
		if (t % 20 == 0)
		{
			printf("\n");
		}
		printf(" %d", item[t]);
	}
}


void main()
{
	int item[100000];
	int count = 10000;

	clock_t sTime, eTime;
	printf("How many numbers(MAX=10000? ");
	scanf("  %d", &count);
	getchar();

	// 선택정렬
	printf("\nSelect Sort ");
	SetData(item, count);
	sTime = clock();
	SelectionSort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime => [%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	// 거품정렬
	printf("\nBubble Sort ");
	SetData(item, count);
	sTime = clock();
	BubbleSort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime => [%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	// 삽입정렬
	printf("\nInsert Sort ");
	SetData(item, count);
	sTime = clock();
	InsertionSort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	// 쉘정렬
	printf("\nshell Sort ");
	SetData(item, count);
	sTime = clock();
	shellsort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	// 퀵정렬
	printf("\nQuick Sort ");
	SetData(item, count);
	sTime = clock();
	QuickSort(item, 0, count - 1);
	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	printf("\nQuick Sort ");
	SetData(item, count);
	sTime = clock();
	qsort(item, count, sizeof(int), compare);

	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	getchar();
}
