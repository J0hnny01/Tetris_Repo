#include "Board.h"

Node::Node(){
	for(int i = 0; i < 10; i++){
		cells[i] = 0;
	}
	next = nullptr;
}

Board::Board() {
	head = new Node();
	Node* temp = head;
	for(int i = 0; i < 19; i++){
		temp->next = new Node();
		temp = temp->next;
	}
}

bool checkCollision(Piece& piece){return 0;}//TODO
void lockPiece(Piece& piece){}//TODO}
int clearLines(){return 0;}//TODO

void Board::draw(sf::RenderWindow& window) {

}
