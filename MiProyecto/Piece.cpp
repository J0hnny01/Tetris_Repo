#include "Piece.h"

void Piece::rotateRight(){
	currentRotation = (currentRotation + 1) % 4;
}

void Piece::rotateLeft(){
	currentRotation = (currentRotation + 3) % 4;
}

void Piece::unRotate() {
	rotateLeft();
	rotateLeft();
	rotateLeft();
}

void Piece::moveLeft(){
	x--;
}

void Piece::moveRight(){
	x++;
}

void Piece::moveDown(){
	y++;
}

void Piece::moveUp(){
	y--;
}

int Piece::getBlock(int row, int col){
	return shape[currentRotation][row][col];
}

int Piece::getX(){
	return x;
}

int Piece::getY(){
	return y;
}

sf::Color Piece::getColor(){
	return color;
}

int Piece::getType() {
	return type;
}

void Piece::draw(sf::RenderWindow& window) {
	float offsetX = 250.f;
	for(int r = 0; r < 4; r++){
		for(int c = 0; c < 4; c++){
			if(getBlock(r, c) != 0){
				sf::RectangleShape block(sf::Vector2f(30.f, 30.f));
				block.setPosition(sf::Vector2f((x + c) * 30.f + offsetX, ((y + r) * 30.f) - 30.f)); 
				block.setFillColor(color);
				block.setOutlineThickness(1.f);
				block.setOutlineColor(sf::Color(50, 50, 50));
				window.draw(block);
			}
		}
	}
}

Piece::Piece(int pieceType) {
	this->type = pieceType;
	this->currentRotation = 0;
	this->x = 3;
	this->y = 0;
	
	for(int i = 0; i < 4; i ++){
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				shape[i][j][k] = 0;
			}
		}
	}
	
	switch(type){
		case 0:{
			color = sf::Color::Magenta;
			int tempShape[4][4][4]{
			{
				{0,0,0,0},
				{0,1,0,0},
				{1,1,1,0},
				{0,0,0,0}
			},
			{
				{0,0,0,0},
				{0,1,0,0},
				{0,1,1,0},
				{0,1,0,0}
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,0},
				{0,1,0,0}
			},
			{
				{0,0,0,0},
				{0,1,0,0},
				{1,1,0,0},
				{0,1,0,0}
			}
		};
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j ++){
				for(int k = 0; k < 4; k++){
					shape[i][j][k] = tempShape[i][j][k];
				}
			}
		}
		break;
	}
		case 1:{
			color = sf::Color::Cyan;
			int tempShape[4][4][4]{
			{
				{0,1,0,0},
				{0,1,0,0},
				{0,1,0,0},
				{0,1,0,0}
			},
			{
				{0,0,0,0},
				{1,1,1,1},
				{0,0,0,0},
				{0,0,0,0}
			},
			{
				{0,1,0,0},
				{0,1,0,0},
				{0,1,0,0},
				{0,1,0,0}
			},
			{
				{0,0,0,0},
				{1,1,1,1},
				{0,0,0,0},
				{0,0,0,0}
			}				
		};		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j ++){
				for(int k = 0; k < 4; k++){
					shape[i][j][k] = tempShape[i][j][k];
				}
			}
		}
		break;		
	}
		case 2:{
			color = sf::Color::Yellow;
			int tempShape[4][4][4]{
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,1,0},
				{0,0,0,0}
			},
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,1,0},
				{0,0,0,0}
			},
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,1,0},
				{0,0,0,0}
			},
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,1,0},
				{0,0,0,0}
			}				
		};		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j ++){
				for(int k = 0; k < 4; k++){
					shape[i][j][k] = tempShape[i][j][k];
				}
			}
		}
		break;		
	}
		case 3:{
			color = sf::Color::Green;
			int tempShape[4][4][4]{
			{
				{0,0,0,0},
				{0,0,1,0},
				{0,1,1,0},
				{0,1,0,0}
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{0,1,1,0},
				{0,0,1,1}
			},
			{
				{0,0,0,0},
				{0,0,1,0},
				{0,1,1,0},
				{0,1,0,0}
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{0,1,1,0},
				{0,0,1,1}
			}				
		};		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j ++){
				for(int k = 0; k < 4; k++){
					shape[i][j][k] = tempShape[i][j][k];
				}
			}
		}
		break;		
	}
		case 4:{
			color = sf::Color::Red;
			int tempShape[4][4][4]{
			{
				{0,0,0,0},
				{0,1,0,0},
				{0,1,1,0},
				{0,0,1,0}
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,1,1},
				{0,1,1,0}
			},
			{
				{0,0,0,0},
				{0,1,0,0},
				{0,1,1,0},
				{0,0,1,0}
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,1,1},
				{0,1,1,0}
			}				
		};		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j ++){
				for(int k = 0; k < 4; k++){
					shape[i][j][k] = tempShape[i][j][k];
				}
			}
		}
		break;		
	}
		case 5:{
			color = sf::Color::Blue;
			int tempShape[4][4][4]{
			{
				{0,0,0,0},
				{0,1,0,0},
				{0,1,0,0},
				{1,1,0,0}
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,0,0,0},
				{1,1,1,0}
			},
			{
				{0,0,0,0},
				{1,1,0,0},
				{1,0,0,0},
				{1,0,0,0}
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,0},
				{0,0,1,0}
			}				
		};		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j ++){
				for(int k = 0; k < 4; k++){
					shape[i][j][k] = tempShape[i][j][k];
				}
			}
		}
		break;		
	}
		case 6:{
			color = sf::Color(255, 165, 0);
			int tempShape[4][4][4]{
			{
				{0,0,0,0},
				{1,0,0,0},
				{1,0,0,0},
				{1,1,0,0}
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,0},
				{1,0,0,0}
			},
			{
				{0,0,0,0},
				{1,1,0,0},
				{0,1,0,0},
				{0,1,0,0}
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{0,0,1,0},
				{1,1,1,0}
			}				
		};		
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j ++){
				for(int k = 0; k < 4; k++){
					shape[i][j][k] = tempShape[i][j][k];
				}
			}
		}
		break;		
	}
	
}
}

int Piece::getRotation() {
	return currentRotation;
}

