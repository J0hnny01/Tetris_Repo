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

bool Board::checkCollision(Piece& piece) {
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (piece.getBlock(r, c) != 0) {
				int globalX = piece.getX() + c;
				int globalY = piece.getY() + r;
				if (globalY >= 20 || globalX < 0 || globalX >= 10) {
					return true; 
				}
				if (globalY >= 0) {
					Node* targetRow = head;
					for (int i = 0; i < globalY; i++) {
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
}     

int Board::clearLines() {
	int lineasBorradas = 0;
	Node* current = head;
	Node* prev = nullptr;	
	while (current != nullptr) {
		bool isFull = true;
		for (int c = 0; c < 10; c++) {
			if (current->cells[c] == 0) {
				isFull = false;
				break;
			}
		}
		if (isFull) {
			Node* nodoABorrar = current;
			if (prev == nullptr) { 
				head = current->next;
				current = head;
			} else {
				prev->next = current->next;
				current = current->next; 
			}
			delete nodoABorrar; 
			Node* nuevaFilaArriba = new Node(); 
			nuevaFilaArriba->next = head;
			head = nuevaFilaArriba;			
			lineasBorradas++;
		} else {
			prev = current;
			current = current->next;
		}
	}
	return lineasBorradas; 
}

void Board::draw(sf::RenderWindow& window) {
	Node* temp = head;
	int j = 0;
	float offsetX = 250.f;
	float cellSize = 30.f; 
	
	while(temp){
		for(int i = 0; i < 10; i++){
			if (temp->cells[i] != 0) {
				sf::RectangleShape block(sf::Vector2f(cellSize, cellSize));
				block.setPosition(sf::Vector2f(i * cellSize + offsetX, j * cellSize));
				int tipo = temp->cells[i] - 1; 
				switch(tipo) {
				case 0: block.setFillColor(sf::Color::Magenta); break;     
				case 1: block.setFillColor(sf::Color::Cyan); break;        
				case 2: block.setFillColor(sf::Color::Yellow); break;      
				case 3: block.setFillColor(sf::Color::Green); break;       
				case 4: block.setFillColor(sf::Color::Red); break;         
				case 5: block.setFillColor(sf::Color::Blue); break;        
				case 6: block.setFillColor(sf::Color(255, 165, 0)); break; 
				default: block.setFillColor(sf::Color::White); break;
				}
				block.setOutlineThickness(-1.f); 
				block.setOutlineColor(sf::Color::Black);
				window.draw(block);
			} else {
				sf::RectangleShape emptyCell(sf::Vector2f(cellSize, cellSize));
				emptyCell.setPosition(sf::Vector2f(i * cellSize + offsetX, j * cellSize));
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

void Board::getSnapshot(int snapshot[20][10]) {
	Node* current = head;	
	for (int r = 0; r < 20; r++) {
		if (current != nullptr) {
			for (int c = 0; c < 10; c++) {
				snapshot[r][c] = current->cells[c];
			}
			current = current->next;
		} else {
			for (int c = 0; c < 10; c++) {
				snapshot[r][c] = 0;
			}
		}
	}
}


