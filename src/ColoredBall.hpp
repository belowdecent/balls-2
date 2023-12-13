#pragma once

#include "src/Ball.hpp"

class ColoredBall: public Ball {
public:
	ColoredBall(
		const sf::Vector2f& position, 
		const sf::Vector2f& velocity, 
		float radius,
		sf::Color color
	): Ball(position, velocity, radius) {
		this->setFillColor(color);
	}

	void setColor(sf::Color color) {
		this->setFillColor(color);
	}

	void drawSelf(sf::RenderWindow& window) {
		window.draw(*this);
	}
};
