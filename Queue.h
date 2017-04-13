#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template<class T>
class Queue 
{
	// FIFO objects
public:
	Queue(int MaxQueueSize = 10);
	Queue(Queue<T> &Q);
	~Queue() { delete[] queue; }

	bool IsEmpty() const { return front == rear; }

	bool IsFull() const 
	{
		if ((rear + 1) % MaxSize == front) return 1;
		else return 0;
	}

	T Front() const; // return front element
	void enqueue(const T& x);
	void dequeue();

	int getMaxSize() const { return MaxSize; }

private:
	int front;   // one counterclockwise from first
	int rear;    // last element
	int MaxSize; // size of array queue
	T *queue;    // element array
};



template<class T>
Queue<T>::Queue(int MaxQueueSize)
{// Create an empty queue whose capacity
 // is MaxQueueSize.
	MaxSize = MaxQueueSize + 1;
	queue = new T[MaxSize];
	front = rear = 0;
}

template<class T>
Queue<T>::Queue(Queue<T> &Q)
{
	int i;
	front = 0; rear = 0;
	MaxSize = Q.getMaxSize();
	queue = new T[MaxSize];

	while (!Q.IsEmpty())
	{
		queue[rear] = Q.Front();
		Q.dequeue();
		rear = (rear + 1) % MaxSize;
	}

	for (i = front; i != rear; i = (i + 1) % MaxSize)
		Q.enqueue(queue[i]);
}


template<class T>
T Queue<T>::Front() const
{// Return first element of queue.  Throw
 // OutOfBounds exception if the queue is empty.

	if (IsEmpty())
		throw logic_error("Queue exception: cannot retrieve from empty queue ");
	return queue[front];
}


template<class T>
void Queue<T>::enqueue(const T& x)
{// Add x to the rear of the queue.  Throw
 // NoMem exception if the queue is full.
	if (IsFull()) throw logic_error("Queue exception: Queue is full ");
	queue[rear] = x;
	rear = (rear + 1) % MaxSize;
}


template<class T>
void Queue<T>::dequeue()
{// Delete first element and put in x.  Throw
 // OutOfBounds exception if the queue is empty.
	if (IsEmpty())
		throw logic_error("Queue exception:  cannot delete from empty queue ");
	front = (front + 1) % MaxSize;
}