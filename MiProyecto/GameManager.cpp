#include "GameManager.h"
#include <string>

GameManager::GameManager() : currentPiece(0) {
	gameOver = false;
	canHold = true;
	score = 0;
	spawnNewPiece();
}

void GameManager::spawnNewPiece() {
	int newType = futureQueue.dequeue();
	currentPiece = Piece(newType);
	canHold = true; 
	if (board.checkCollision(currentPiece)) {
		gameOver = true;
	}
}

bool GameManager::isGameOver(){
	return gameOver;
}

void GameManager::updateGravity() {
	if (gameOver) return;	
	currentPiece.moveDown();
	if (board.checkCollision(currentPiece)) {
		currentPiece.moveUp();
		board.lockPiece(currentPiece);
		int cleanedLines = board.clearLines();
		if (cleanedLines > 0) {
			score += (cleanedLines * 10);
		}
		takeSnap();
		spawnNewPiece();
	}
}

void GameManager::takeSnap() {
	int matrizFotografia[20][10];
	board.getSnapshot(matrizFotografia);	
	historial.saveState(currentPiece.getType(), currentPiece.getX(), currentPiece.getY(), matrizFotografia);
}

void GameManager::holdPiece() {
	if (!canHold){ 
		return;
	} 	
	if (hold.isEmpty()) {
		hold.push(currentPiece.getType());
		spawnNewPiece(); 
	} else {
		int holdedType = hold.pop();
		hold.push(currentPiece.getType());
		currentPiece = Piece(holdedType);
	}
	canHold = false; 
}

void GameManager::processInput(sf::Keyboard::Key key) {
	if (gameOver) {
		return; 
	}
	
	switch (key) {
	case sf::Keyboard::Left:
		currentPiece.moveLeft();
	if (board.checkCollision(currentPiece)) currentPiece.moveRight();
	break;
	
	case sf::Keyboard::Right:
		currentPiece.moveRight();
	if (board.checkCollision(currentPiece)) currentPiece.moveLeft();
	break;
	
	case sf::Keyboard::Up: 
		currentPiece.rotateLeft();
	if (board.checkCollision(currentPiece)) {
		currentPiece.unRotate(); 
	}
	break;
	
	case sf::Keyboard::Down:
		updateGravity(); 
	break;
	
	case sf::Keyboard::C: 
		holdPiece();
	break;
	
	case sf::Keyboard::Z: 
		// TODO el ctrl z básicamente
		break;
	
	default:
		break;
	}
}

void GameManager::draw(sf::RenderWindow& window, sf::Font& font, int seconds){
	board.draw(window);
	if (!gameOver) {
		currentPiece.draw(window);
	}	
	sf::Text scoreLabel;
	scoreLabel.setFont(font);
	scoreLabel.setString("Puntos: " + std::to_string(score));
	scoreLabel.setCharacterSize(24);
	scoreLabel.setFillColor(sf::Color::White);
	scoreLabel.setPosition(50.f, 300.f); 
	window.draw(scoreLabel);
	int minutes = seconds / 60;
	int secondsPassed = seconds % 60;
	std::string stringSeconds = (secondsPassed < 10 ? "0" : "") + std::to_string(secondsPassed);
	std::string tiempoStr = "Tiempo: " + std::to_string(minutes) + ":" + stringSeconds;
	sf::Text timeLabel;
	timeLabel.setFont(font);
	timeLabel.setString(tiempoStr);
	timeLabel.setCharacterSize(24);
	timeLabel.setFillColor(sf::Color::White);
	timeLabel.setPosition(50.f, 350.f); 
	window.draw(timeLabel);
	float cellSize = 30.f; 
	sf::RectangleShape blockUI(sf::Vector2f(cellSize, cellSize));
	blockUI.setOutlineThickness(-1.f);
	blockUI.setOutlineColor(sf::Color(50, 50, 50)); 
	auto applyColor = [&blockUI](int tipo) {
		switch(tipo) {
		case 0: blockUI.setFillColor(sf::Color::Magenta); break;     
		case 1: blockUI.setFillColor(sf::Color::Cyan); break;       
		case 2: blockUI.setFillColor(sf::Color::Yellow); break;      
		case 3: blockUI.setFillColor(sf::Color::Green); break;     
		case 4: blockUI.setFillColor(sf::Color::Red); break;         
		case 5: blockUI.setFillColor(sf::Color::Blue); break;     
		case 6: blockUI.setFillColor(sf::Color(255, 165, 0)); break; 
		default: blockUI.setFillColor(sf::Color::White); break;
		}
	};
	int holdType = hold.peek();
	if (holdType != -1) { 
		Piece holdPiece(holdType);
		applyColor(holdType);
		if (!canHold) blockUI.setFillColor(sf::Color(100, 100, 100)); 
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				if (holdPiece.getBlock(r, c) != 0) {
					float x = 50.f + (c * cellSize);
					float y = 100.f + (r * cellSize);
					blockUI.setPosition(x, y);
					window.draw(blockUI);
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		int futureType = futureQueue.getFuturePiece(i);
		Piece futurePiece(futureType);
		applyColor(futureType);     
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (futurePiece.getBlock(j, k) != 0) {
					float x = 550.f + (k * cellSize);
					float y = 100.f + (i * 120.f) + (j * cellSize);
					blockUI.setPosition(x, y);
					window.draw(blockUI);
				}
			}
		}
	}
}
