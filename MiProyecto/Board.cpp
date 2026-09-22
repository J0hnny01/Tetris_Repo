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

bool Board::checkCollision(Piece& piece) {  //PRUEBA. NO DEFINITIVO
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece.getBlock(i, j) != 0) {
				int globalX = piece.getX() + j;
				int globalY = piece.getY() + i;
				if (globalX < 0 || globalX >= 10) {
					return true;
				}
				if (globalY >= 21) {
					return true;
				}
				if (globalY >= 0) {
					Node* targetRow = head;
					for (int k = 0; k < globalY; k++) {
						if (targetRow != nullptr) {
							targetRow = targetRow->next;
						}
					}
					if (targetRow != nullptr && targetRow->cells[globalX] != 0) {
						return true;
					}
				}
			}
		}
	}
	return false; 
}

void Board::lockPiece(Piece& piece) {
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (piece.getBlock(r, c) != 0) {				
				int globalX = piece.getX() + c;
				int globalY = piece.getY() + r;
				if (globalY >= 0 && globalY < 20 && globalX >= 0 && globalX < 10) {
					Node* targetRow = head;
					for (int i = 0; i < globalY; i++) {
						if (targetRow != nullptr) {
							targetRow = targetRow->next;
						}
					}
					if (targetRow != nullptr) {
						targetRow->cells[globalX] = piece.getType() + 1; 
					}
				}
			}
		}
	}
}     //NO FUNCIONA AUN

int clearLines(){return 0;}//TODO

void Board::draw(sf::RenderWindow& window) {
	Node* temp = head;
	int j = 0;
	float offsetX = 250.f;
	while(temp){
		for(int i = 0; i < 10; i++){
			if (temp->cells[i] != 0) {
				sf::RectangleShape block(sf::Vector2f(40.f, 40.f));
				block.setPosition(sf::Vector2f(i * 40.f + offsetX, j * 40.f)) ;
				block.setFillColor(sf::Color::Blue);
				window.draw(block);
			}else{
				sf::RectangleShape emptyCell(sf::Vector2f(30.f, 30.f));
				emptyCell.setPosition(sf::Vector2f(i * 30.f + offsetX, j * 30.f));
				emptyCell.setFillColor(sf::Color::Transparent);
				emptyCell.setOutlineThickness(1.f);
				emptyCell.setOutlineColor(sf::Color(50, 50, 50)); 
				window.draw(emptyCell);
			}
		}
		temp = temp->next;
		j++;
	}
}
