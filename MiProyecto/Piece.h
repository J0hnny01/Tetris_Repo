#ifndef PIECE_H
#define PIECE_H
#include <SFML/Graphics.hpp>

class Piece {
private:
	int shape[4][4][4];
	int currentRotation;
	int x;
	int y;
	int type;
	sf::Color color;
public:
	Piece(int pieceType);
	void rotateLeft();
	void rotateRight();
	void unRotate();
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	int getBlock(int row, int col);
	int getX();
	int getY();
	sf::Color getColor();
	void draw(sf::RenderWindow& window);
	int getType();
	int getRotation();
};

#endif

