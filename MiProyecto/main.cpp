#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameManager.h" 
#include <cstdlib> 
#include <ctime>

enum GameStates{   
	MENU,
	GAME,
	SCOREBOARD,
	LOGIN
};

int main(){
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(800, 600), "Main");	
	sf::Font myFont;
	if (!myFont.loadFromFile("C:/Users/johnn/Desktop/tetris/Tetris_Repo/MiProyecto/AldotheApache.ttf")) {

	}
	Button playButton(300, 250, 200, 50, "Jugar", myFont, sf::Color::Blue);
	Button scoreBoardButton(300, 330, 200, 50, "Puntajes", myFont, sf::Color::Red);
	Button backAfterGameOverButton(300, 300, 200, 50, "Volver", myFont, sf::Color::Blue);
	std::string playerName = "";
	sf::Text promptText("Ingresa tu nombre y presiona ENTER:", myFont, 24);
	promptText.setPosition(200.f, 200.f);
	sf::Text nameInputText("", myFont, 30);
	nameInputText.setPosition(200.f, 250.f);
	nameInputText.setFillColor(sf::Color::Yellow);
	sf::Text scoreboardTitle("Top 10 Mejores Puntajes", myFont, 30);
	scoreboardTitle.setPosition(250.f, 50.f);
	scoreboardTitle.setFillColor(sf::Color::Cyan);
	sf::Text gameOverText("Perdiste!", myFont, 60);
	gameOverText.setPosition(300.f, 50.f);
	gameOverText.setFillColor(sf::Color::Red);
	GameManager gameManager;
	sf::Clock gameClock;
	sf::Clock totalTimeClock;
	float fallDelay = 0.5f; 
	GameStates currentState = MENU;
	int secondsPlayed = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window.close();		
			}	
			if (event.type == sf::Event::KeyPressed && currentState == GAME) {
				gameManager.processInput(event.key.code);
			}
			else if(currentState == LOGIN && event.type == sf::Event::TextEntered){
				if (event.text.unicode == 8 && playerName.length() > 0) {
					playerName.pop_back();
				}
				else if (event.text.unicode == 13 && playerName.length() > 0) {
					currentState = GAME;
					gameClock.restart();
					totalTimeClock.restart(); 
					secondsPlayed = 0;
				}
				else if (event.text.unicode >= 33 && event.text.unicode <= 126 && playerName.length() < 12) {
					playerName += static_cast<char>(event.text.unicode);
				}
				nameInputText.setString(playerName);
			}
		}
		if(currentState == MENU){
			if(playButton.isPressed(window)){
				currentState = LOGIN;
				gameClock.restart();
				totalTimeClock.restart(); 
				secondsPlayed = 0;	
			}
		}
		else if (currentState == GAME) {
			if (!gameManager.isGameOver()) {
				if (gameClock.getElapsedTime().asSeconds() >= fallDelay) {
					gameManager.updateGravity();
					gameClock.restart();
				}
				secondsPlayed = static_cast<int>(totalTimeClock.getElapsedTime().asSeconds());
			}else if (backAfterGameOverButton.isPressed(window)){
				currentState = MENU;
				playerName = "";
				nameInputText.setString("");
				gameManager = GameManager();
			}
		}
		window.clear(sf::Color::Black);
		if(currentState == MENU){
			playButton.draw(window);
			scoreBoardButton.draw(window);
		}else if(currentState == GAME) {
			gameManager.draw(window, myFont, secondsPlayed); 
			if(gameManager.isGameOver()){
				backAfterGameOverButton.draw(window);
				window.draw(gameOverText);
			}
		}else if (currentState == LOGIN) {
			window.draw(promptText);
			window.draw(nameInputText);
		}
		window.display();
	}
	
	return 0;
}
