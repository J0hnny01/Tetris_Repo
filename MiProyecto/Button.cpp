#include "Button.h"
#include <SFML/Graphics.hpp>
#include <string>

Button::Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font, sf::Color color) {
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(x, y));
	text.setString(buttonText);
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	shape.setFillColor(color);
	sf::FloatRect textRect = text.getLocalBounds();
	float xPos = x + (width / 2.0f) - (textRect.width / 2.0f) - textRect.left;
	float yPos = y + (height / 2.0f) - (textRect.height / 2.0f) - textRect.top;
	text.setPosition(sf::Vector2f(xPos, yPos));
}

bool Button::isPressed(sf::RenderWindow& window){
	sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	if (shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		return true;
	}
	return false;
}

void Button::draw(sf::RenderWindow& window){
	window.draw(shape);
	window.draw(text);
}

