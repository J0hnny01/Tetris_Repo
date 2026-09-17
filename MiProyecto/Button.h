#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>

class Button {

private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Color color;
	
public:
	Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font, sf::Color color);
	bool isPressed(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

#endif

