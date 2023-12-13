#pragma once

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Ball: public sf::CircleShape {
	sf::Vector2u window_size;
public:
	sf::Vector2f velocity;

	Ball(const sf::Vector2f& position, const sf::Vector2f& velocity, float radius): sf::CircleShape(radius) {
		this->setFillColor(sf::Color::White);

		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(1);

		this->setPosition(position - sf::Vector2f(radius, radius));
		this->velocity = velocity;
	}

	void setWindowSize(const sf::Vector2u& window_size) {
		this->window_size = window_size;
	}

	void updatePosition(float dt) {
		if ((getPosition().x < 0 && velocity.x < 0)
			|| (getPosition().x + 2 * getRadius() > window_size.x && velocity.x > 0)) {
			velocity.x = -velocity.x;
		}

		if ((getPosition().y < 0 && velocity.y < 0) 
			|| (getPosition().y + 2 * getRadius() > window_size.y && velocity.y > 0)) {
			velocity.y = -velocity.y;
		}

		this->move(velocity * dt);
	}

	virtual void drawSelf(sf::RenderWindow& window) {
		window.draw(*this);
	}
};
