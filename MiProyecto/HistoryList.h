#ifndef HISTORYLIST_H
#define HISTORYLIST_H
#include <string>

class StateNode {
public:
	int pieceType;
	int pieceX;
	int pieceY;
	int pieceRotation;
	int holdPieceType;
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
	void saveState(int pieceType, int pieceX, int pieceY, int pieceRotation, int holdType, int currentBoard[20][10]);
	StateNode* undo();
	StateNode* redo();
	StateNode* getFirstState();
	StateNode* getCurrentState();
	StateNode* getNextState(); 
	void truncateFuture(); 
	void clear(); 
	void exportToFile(std::string filename);
	void loadFromFile(std::string filename);
};

#endif
