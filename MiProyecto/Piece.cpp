#include "Piece.h"

void Piece::rotateRight(){
	currentRotation = (currentRotation + 1) % 4;
}

void Piece::rotateLeft(){
	currentRotation = (currentRotation + 3) % 4;
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

