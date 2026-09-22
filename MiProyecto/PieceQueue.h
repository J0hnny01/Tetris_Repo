#ifndef PIECEQUEUE_H
#define PIECEQUEUE_H


class QueueNode {
public:
	int pieceType;
	QueueNode* next;
	
	QueueNode(int type);
};

class PieceQueue {
private:
	QueueNode* front;
	QueueNode* rear;
	int count;
	
public:
	PieceQueue();
	~PieceQueue(); 
	int dequeue(); 
	void generateBag(); 
	void enqueue(int type);
	int getFuturePiece(int position); 
};

#endif
