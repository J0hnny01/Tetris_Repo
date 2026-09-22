#include "PieceQueue.h"
#include <cstdlib> 

QueueNode::QueueNode(int type) {
	this->pieceType = type;
	this->next = nullptr;
}

void PieceQueue::enqueue(int type) {
	QueueNode* newNode = new QueueNode(type);	
	if (front == nullptr) { 
		front = newNode;
		rear = newNode;
	} else { 
		rear->next = newNode;
		rear = newNode;
	}
	count++;
}

void PieceQueue::generateBag() {
	int bag[7] = {0, 1, 2, 3, 4, 5, 6};
	for (int i = 6; i > 0; i--) {
		int j = rand() % (i + 1); 
		int temp = bag[i];
		bag[i] = bag[j];
		bag[j] = temp;
	}
	if (rear != nullptr) {
		if (bag[0] == rear->pieceType) {
			int temp = bag[0];
			bag[0] = bag[1];
			bag[1] = temp;
		}
	}
	for (int i = 0; i < 7; i++) {
		enqueue(bag[i]);
	}
}

PieceQueue::PieceQueue() {
	front = nullptr;
	rear = nullptr;
	count = 0;
	generateBag(); 
	generateBag(); 
}

PieceQueue::~PieceQueue() {
	QueueNode* current = front;
	while (current != nullptr) {
		QueueNode* temp = current;
		current = current->next;
		delete temp; 
	}
	front = nullptr;
	rear = nullptr;
	count = 0;
}

int PieceQueue::dequeue() {
	if (front == nullptr) return 0; 
	QueueNode* temp = front;
	int upcomingPiece = temp->pieceType;
	front = front->next;
	delete temp;
	count--;
	if (front == nullptr) {
		rear = nullptr;
	}
	if (count <= 3) {
		generateBag();
	}
	return upcomingPiece;
}

int PieceQueue::getFuturePiece(int position) {
	if (position < 0 || position >= count) return 0; 
	QueueNode* current = front;
	for (int i = 0; i < position; i++) {
		if (current != nullptr) {
			current = current->next;
		}
	}
	if (current != nullptr) {
		return current->pieceType;
	}
	return 0; 
}
