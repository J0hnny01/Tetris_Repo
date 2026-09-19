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
