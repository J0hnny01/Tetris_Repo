#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameManager.h" 
#include <cstdlib> 
#include <ctime>

enum GameStates{   
	MENU,
	GAME
};

int main(){
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(800, 600), "Main");	
	sf::Font myFont;
	if (!myFont.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
		// TODO
	}
	Button playButton(300, 250, 200, 50, "Jugar", myFont, sf::Color::Blue);
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
			if (event.type == sf::Event::Closed)
				window.close();			
			if (event.type == sf::Event::KeyPressed && currentState == GAME) {
				gameManager.processInput(event.key.code);
			}
		}
		if(currentState == MENU){
			if(playButton.isPressed(window)){
				currentState = GAME;
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
			}
		}
		window.clear(sf::Color::Black);
		if(currentState == MENU){
			playButton.draw(window);
		}else if(currentState == GAME) {
			gameManager.draw(window, myFont, secondsPlayed); 
		}
		
		window.display();
	}
	
	return 0;
}
