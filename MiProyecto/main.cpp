#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Board.h"
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
	Board board;
	GameStates currentState = MENU;
	Piece piezaActual(0);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();			
		}
		
		if(currentState == MENU){
			if(playButton.isPressed(window)){
				currentState = GAME;
			}
		}
		
		window.clear(sf::Color::Black);
		
		if(currentState == MENU){
			playButton.draw(window);
		}else if(currentState == GAME){
			board.draw(window);
		}
		window.display();
	}
	
	return 0;
}
