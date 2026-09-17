#include <SFML/Graphics.hpp>
#include "Button.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Main");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		sf::Font myFont;
		if (!myFont.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
		}
		Button botonJugar(100, 100, 200, 50, "Jugar", myFont, sf::Color::Blue);
		botonJugar.draw(window);
		window.display();
	}
	
	return 0;
}
