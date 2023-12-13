#pragma once

#include "src/ColoredBall.hpp"

class FadingBall: public ColoredBall {
public:
	using ColoredBall::ColoredBall;

	void drawSelf(sf::RenderWindow& window) {
		sf::Color color = this->getFillColor();
		color.r = (color.r < 255) ? color.r + 1 : 255;
		color.g = (color.g < 255) ? color.g + 1 : 255;
		color.b = (color.b < 255) ? color.b + 1 : 255;
		this->setFillColor(sf::Color(
			color.r, 
			color.g, 
			color.b
		));
		window.draw(*this);
	}
};
