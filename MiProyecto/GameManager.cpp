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
	takeSnap();
}

bool GameManager::isGameOver(){
	return gameOver;
}

int GameManager::getScore(){
	return score;
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
		spawnNewPiece();
	} else {
		takeSnap();
	}
}

void GameManager::takeSnap() {
	int matrizFotografia[20][10];
	board.getSnapshot(matrizFotografia);	
	historial.saveState(currentPiece.getType(), currentPiece.getX(), currentPiece.getY(), currentPiece.getRotation(), hold.peek(), matrizFotografia);
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
	
	case sf::Keyboard::H: 
		holdPiece();
	break;
	
	case sf::Keyboard::Z: 
		// TODO el ctrl z bsicamente
		break;
	
	default:
		break;
	}
	takeSnap();
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

void GameManager::exportHistory(std::string filename) {
	historial.exportToFile(filename);
}

bool GameManager::loadReplay(std::string filename) {
	historial.loadFromFile(filename);
	historial.getFirstState();
	return historial.getCurrentState() != nullptr;
}

void GameManager::stepReplay(int direction) {
	if (direction == 1) historial.getNextState(); 
	else if (direction == -1) historial.undo();   
}

void GameManager::drawReplay(sf::RenderWindow& window, sf::Font& font) {
	StateNode* frame = historial.getCurrentState();
	if (!frame) return;
	float offsetX = 250.f;
	float offsetY = 0.f; 
	for (int r = 0; r < 20; r++) {
		for (int c = 0; c < 10; c++) {
			sf::RectangleShape cell(sf::Vector2f(30.f, 30.f));
			cell.setPosition(offsetX + c * 30.f, offsetY + r * 30.f);
			cell.setFillColor(sf::Color::Black);
			cell.setOutlineThickness(1.f);
			cell.setOutlineColor(sf::Color(50, 50, 50));
			window.draw(cell);
		}
	}
	for (int r = 0; r < 20; r++) {
		for (int c = 0; c < 10; c++) {
			int cellValue = frame->boardSnapshot[r][c];
			if (cellValue != 0) { 
				Piece tempColorPiece(cellValue - 1);
				sf::RectangleShape block(sf::Vector2f(30.f, 30.f));
				block.setPosition(offsetX + c * 30.f, offsetY + r * 30.f);
				block.setFillColor(tempColorPiece.getColor());
				block.setOutlineThickness(1.f);
				block.setOutlineColor(sf::Color(50, 50, 50));
				window.draw(block);
			}
		}
	}
	Piece tempPiece(frame->pieceType);
	for (int i = 0; i < frame->pieceRotation; i++) {
		tempPiece.rotateRight();
	}
	for(int r = 0; r < 4; r++){
		for(int c = 0; c < 4; c++){
			if(tempPiece.getBlock(r, c) != 0){
				sf::RectangleShape block(sf::Vector2f(30.f, 30.f));
				block.setPosition(offsetX + (frame->pieceX + c) * 30.f, offsetY + ((frame->pieceY + r) * 30.f) - 30.f); 
				block.setFillColor(tempPiece.getColor());
				block.setOutlineThickness(1.f);
				block.setOutlineColor(sf::Color(50, 50, 50));
				window.draw(block);
			}
		}
	}
	if (frame->holdPieceType != -1) {
		Piece tempHold(frame->holdPieceType);
		sf::RectangleShape blockUI(sf::Vector2f(30.f, 30.f));
		blockUI.setFillColor(tempHold.getColor());
		blockUI.setOutlineThickness(-1.f);
		blockUI.setOutlineColor(sf::Color(50, 50, 50)); 
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				if (tempHold.getBlock(r, c) != 0) {
					float x = 50.f + (c * 30.f);
					float y = 100.f + (r * 30.f);
					blockUI.setPosition(x, y);
					window.draw(blockUI);
				}
			}
		}
	}
	sf::Text info("MODO REPETICION", font, 24);
	info.setPosition(20.f, 50.f);
	info.setFillColor(sf::Color::Magenta);
	window.draw(info);
	
	sf::Text controls("ESPACIO: Play/Pausa\nFLECHAS: Adelante/Atras", font, 18);
	controls.setPosition(20.f, 90.f);
	window.draw(controls);
}
