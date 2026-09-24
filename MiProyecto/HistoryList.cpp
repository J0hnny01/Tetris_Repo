#include "HistoryList.h"

StateNode::StateNode() {
	pieceType = 0;
	pieceX = 0;
	pieceY = 0;
	prev = nullptr;
	next = nullptr;
	for (int r = 0; r < 20; r++) {
		for (int c = 0; c < 10; c++) {
			boardSnapshot[r][c] = 0;
		}
	}
}

HistoryList::HistoryList() {
	head = nullptr;
	tail = nullptr;
	current = nullptr;
}

HistoryList::~HistoryList() {
	StateNode* temp = head;
	while (temp != nullptr) {
		StateNode* nextNode = temp->next;
		delete temp;
		temp = nextNode;
	}
}

void HistoryList::truncateFuture() {
	if (current == nullptr || current->next == nullptr) return;	
	StateNode* temp = current->next;
	while (temp != nullptr) {
		StateNode* nextNode = temp->next;
		delete temp;
		temp = nextNode;
	}
	current->next = nullptr;
	tail = current;
}

void HistoryList::saveState(int pieceType, int pieceX, int pieceY, int currentBoard[20][10]) {
	if (current != tail) {
		truncateFuture();
	}
	StateNode* newNode = new StateNode();
	newNode->pieceType = pieceType;
	newNode->pieceX = pieceX;
	newNode->pieceY = pieceY;
	for (int r = 0; r < 20; r++) {
		for (int c = 0; c < 10; c++) {
			newNode->boardSnapshot[r][c] = currentBoard[r][c];
		}
	}
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		current = newNode;
	} else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		current = newNode;
	}
}

StateNode* HistoryList::undo() {
	if (current != nullptr && current->prev != nullptr) {
		current = current->prev;
	}
	return current; 
}

StateNode* HistoryList::redo() {
	if (current != nullptr && current->next != nullptr) {
		current = current->next;
	}
	return current;
}

StateNode* HistoryList::getFirstState() {
	current = head;
	return current;
}

StateNode* HistoryList::getNextState() {
	if (current != nullptr && current->next != nullptr) {
		current = current->next;
	}
	return current;
}
