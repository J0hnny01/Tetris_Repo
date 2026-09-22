#ifndef HOLDSTACK_H
#define HOLDSTACK_H

class StackNode {
public:
	int pieceType;
	StackNode* next;
	
	StackNode(int type);
};

class HoldStack {
private:
	StackNode* top;
	
public:
	HoldStack();
	~HoldStack();
	void push(int type);
	int pop();
	int peek();
	bool isEmpty();
};

#endif
