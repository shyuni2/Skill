#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>

// sort(����) ó���ӵ� ��

int compare(const void* a, const void* b) // �� ���Լ�
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

// ������ ����
void SetData(int item[], int iCount)
{
	// �ݺ������� ���� �迭 ���� �������� ó���Ѵ�.
	srand((unsigned int)time(NULL));

	for (int a = 0; a < iCount; a++)
	{
		item[a] = rand() % iCount;
	}
	DataPrint(item, iCount);
}

// ��������
// �迭�� �ּҰ��� ã�� ����, ó�������Ѱ� �̿� �������� ���������� ����
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

// ��ǰ����
// �ΰ��� ������ ���Ҹ� ���� ����
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

// ��������
// ����Ҹ� �տ������� ���ʴ�� ���Ͽ� ��ġ�� ã�� ����, �迭�� ����� ��ȿ����
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

// �� ����
// ���������� ������ ����,
void shellsort(int item[], int n)
{
	// n�� ���� ���� �ִ� �׷��� ������ ã�´�.
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
		// �κ����� ����
		for (int s = 0; s < g; s++)
		{
			InsertionSort(item, n, s, g);
		}
	}
}

// ������
// 1. ����Ʈ�ȿ� �ִ� ��Ҹ� �����Ѵ� �̰��� �ǹ��̶�� �θ�.
// 2. �ǹ��� �������� ������� �����͵��� ���� ū�͵��� �����ʿ� �Ű���
// 3. �ǹ��� ������ ���� ������ ����Ʈ�� �ٽ������Ѵ�
// 4. �κи���Ʈ���� ���̻� ������ �Ұ����Ҷ����� �ݺ�

// �������� �� ���ĺ��� 2~3�� ������. ������ �����ĵ� ���� ���� ������ ������.
// �� ������ �޸� �ѵ������� �󸶵��� ������ �� ������
// �� ������ ������ ��������ν� ���ó�ħ(Stack overflow)�� ����� �����ϰ� �ִ�.
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

// ȭ�����
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

	// ��������
	printf("\nSelect Sort ");
	SetData(item, count);
	sTime = clock();
	SelectionSort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime => [%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	// ��ǰ����
	printf("\nBubble Sort ");
	SetData(item, count);
	sTime = clock();
	BubbleSort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime => [%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	// ��������
	printf("\nInsert Sort ");
	SetData(item, count);
	sTime = clock();
	InsertionSort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	// ������
	printf("\nshell Sort ");
	SetData(item, count);
	sTime = clock();
	shellsort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	// ������
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
