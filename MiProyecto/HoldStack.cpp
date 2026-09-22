#include "HoldStack.h"

StackNode::StackNode(int type) {
	this->pieceType = type;
	this->next = nullptr;
}

HoldStack::HoldStack() {
	top = nullptr;
}

HoldStack::~HoldStack() {
	if (top != nullptr) {
		delete top;
		top = nullptr;
	}
}

void HoldStack::push(int type) {
	if (top != nullptr) {
		delete top; 
		top = nullptr;
	}
	top = new StackNode(type);
}

int HoldStack::pop() {
	if (top == nullptr){ 
		return -1; 
	}
	int savedType = top->pieceType;
	delete top;
	top = nullptr;	
	return savedType;
}

int HoldStack::peek() {
	if (top == nullptr) return -1;
	return top->pieceType;
}

bool HoldStack::isEmpty() {
	return top == nullptr;
}
