#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include "PieceQueue.h"
#include "HoldStack.h"
#include "HistoryList.h"

class GameManager {
private:
	Board board;
	Piece currentPiece;
	PieceQueue futureQueue;
	HoldStack hold;
	HistoryList historial;
	bool gameOver;
	bool canHold; 
	int score;
	
public:
	GameManager();
	void spawnNewPiece();
	void holdPiece();
	void takeSnap(); 
	void processInput(sf::Keyboard::Key key);
	void updateGravity(); 
	void draw(sf::RenderWindow& window, sf::Font& font, int seconds);
	bool isGameOver(); 
	int getScore();
	void exportHistory(std::string filename);
	bool loadReplay(std::string filename);
	void stepReplay(int direction);
	void drawReplay(sf::RenderWindow& window, sf::Font& font);
};

#endif
