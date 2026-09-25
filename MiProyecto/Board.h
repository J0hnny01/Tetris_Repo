#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Node {
public:
	int cells[10]; 
	Node* next;   
	Node();
};

class Board {
private:
	Node* head;	
public:
	Board();
	void draw(sf::RenderWindow& window);
	bool checkCollision(Piece& piece);
	void lockPiece(Piece& piece);
	int clearLines();
	void getSnapshot(int snapshot[20][10]);
	bool isRowFull(Node* row);
};

#endif
