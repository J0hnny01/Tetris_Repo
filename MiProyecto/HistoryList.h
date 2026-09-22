#ifndef HISTORYLIST_H
#define HISTORYLIST_H

class StateNode {
public:
	int pieceType;
	int pieceX;
	int pieceY;
	int boardSnapshot[20][10];
	StateNode* prev;
	StateNode* next;
	StateNode(); 
};

class HistoryList {
private:
	StateNode* head;    
	StateNode* tail;    
	StateNode* current; 
	
public:
	HistoryList();
	~HistoryList();
	void saveState(int pieceType, int pieceX, int pieceY, int currentBoard[20][10]);
	StateNode* undo();
	StateNode* redo();
	StateNode* getFirstState();
	StateNode* getNextState(); 
	void truncateFuture(); 
};

#endif
