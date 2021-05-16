#include <iostream>
#include <queue>
using namespace std;
int a;

queue<int> MakeSTL(int size)
{
	queue<int> res;
	int tmp;
	for (int i = 0; i < size; i++)
	{
		cout << "Введите элемент " << i + 1 << ": ";
		cin >> tmp;
		res.push(tmp);
	}
	return res;
}

void PrintSTL(queue<int> st)
{
	if (st.empty())
	{
		cout << "Стек пустой" << endl;
		return;
	}

	while (!st.empty())
	{
		cout << st.front() << " ";
		st.pop();
	}
	cout << endl;
}

queue<int> DeleteSTL(queue<int> st)
{
	int n = st.size();
	queue<int> per;
	int* ar = new int[n];
	int tmp = -1;
	for (int i = 0; i < n; i++)
	{
		ar[i] = st.front();
		st.pop();
		if (ar[i] % 2 == 0) {
			tmp = i;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (i != tmp) {
			per.push(ar[i]);
		}
	}
	return per;
}

struct QueueItem
{
	int data;
	QueueItem* prev;
};

struct Queue
{
	QueueItem* front;
	QueueItem* back;
};

QueueItem* newItem(int element)
{
	QueueItem* newElement = new QueueItem;
	newElement->data = element;
	newElement->prev = 0;
	return newElement;
}

void push(Queue** queue, int element)
{
	QueueItem* newElement = newItem(element);
	(*queue)->back->prev = newElement;
	(*queue)->back = newElement;
	if (!(*queue)->front) {
		(*queue)->front = newElement;
	}
}

int pop(Queue** queue)
{
	int el = (*queue)->front->data;
	QueueItem* rem = (*queue)->front;
	(*queue)->front = (*queue)->front->prev;
	delete rem;
	return el;
}

Queue* make_queue(int size)
{
	int tmp;
	Queue* queue = new Queue;
	cout << "Введите элемент 1: ";
	cin >> tmp;

	QueueItem* item = newItem(tmp);
	queue->front = item;
	queue->back = item;
	
	for (int i = 2; i <= size; i++)
	{
		cout << "Введите элемент " << i << ": ";
		cin >> tmp;
		push(&queue, tmp);
	}
	return queue;
}

void print(Queue*& queue)
{
	if (!queue->front) {
		cout << "Стек пустой" << endl;
		return;
	}
	vector<int> copy = vector<int>();
	while (queue->front)
	{
		copy.push_back(pop(&queue));
	}
	for (int i = 0; i < copy.size(); i++) {
		cout << copy[i] << " ";
		push(&queue, copy[i]);
	}
	cout << endl;
}

void deleteEl(Queue*& queue)
{
	if (!queue->front)
	{
		cout << "Стек пустой" << endl;
		return;
	}
	
	vector<int> copy = vector<int>();
	int tmp = -1;
	int item;
	while (queue->front)
	{
		item = pop(&queue);
		copy.push_back(item);
		if (item % 2 == 0) {
			tmp = copy.size() - 1;
		}
	}
	for (int i = 0; i < copy.size(); i++) {
		if (i != tmp) {
			push(&queue, copy[i]);
		}
	}
}

int main()
{
	system("color F0");
	setlocale(LC_ALL, "RUS");
	cout << "Очередь через STL библиотеку." << endl;
	int size;
	do
	{
		cout << "Введите кол-во элементов очереди: ";
		cin >> size;
	} while (size <= 0);
	queue<int> st1 = MakeSTL(size);
	PrintSTL(st1);
	queue<int> st2 = DeleteSTL(st1);
	PrintSTL(st2);

	cout << "Очередь через структуру." << endl;
	int size2;
	do
	{
		cout << "Введите кол-во элементов очереди: ";
		cin >> size2;
	} while (size2 <= 0);
	
	Queue* st3 = make_queue(size2);
	print(st3);
	deleteEl(st3);
	print(st3);

	return 0;
}