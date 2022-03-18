#include <iostream>

#define MAX 10

using namespace std;

int queue[MAX];
int front, rear; // front는 끝 (삭제연산만 이루어짐) , rear은 시작 (삽입연산만 이루어짐)

void InitQueue() // 큐 초기화
{
	front = rear = 0; // 시작과 끝은 0
}

void ClearQueue() // 큐 클리어
{
	front = rear;
}

int put(int t) // 큐에 하나씩 넣기
{
	if ((rear)+1 % MAX == front) // 큐가 가득찼을때
	{
		cout << "Queue Overflow." << endl;
		return -1;
	}
	queue[rear] = t;
	rear = ++rear % MAX;
	return t;
}

int get()
{
	if (front == rear) // 큐가 비어있는지
	{
		cout << "Queue Underflow" << endl;
		return -1;
	}
	int i = queue[front];
	front = ++front % MAX;
	return i;
}

void PrintQueue()
{
	cout << " Queue Contents : Top -----> Bottom" << endl;
	for (int i = front; i != rear; i = ++i % MAX)
	{
		cout << queue[i];
	}
}

void main()
{
	InitQueue();
	printf("\nPush 5,4,7,8,2,1");
	put(5);
	put(4);
	put(7);
	put(8);
	put(2);
	put(1);

	PrintQueue();

	printf("\nGet");
	int i = get();
	PrintQueue();

	printf("\n Put 3,2,5,7");
	put(3);
	put(2);
	put(5);
	put(7);
	PrintQueue();

	printf("\nNow queue is full, push 3");
	put(3);
	PrintQueue();

	printf("\n Initialize queue");
	ClearQueue();
	PrintQueue();

	printf("\nNow queue is empty, pop");
	i = get();
	printf("\n poppint value is %d", i);
}