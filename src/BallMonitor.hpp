#pragma once

#include <cmath>
#include <memory>
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class BallMonitor {
	static constexpr float max_speed = 120;
	static constexpr float pi = 3.1415926359;
	float angle = 45;
	float speed = 50;

	sf::RectangleShape rect{sf::Vector2f(40, 40)};
	sf::RectangleShape line{sf::Vector2f(0, 0)};
	sf::CircleShape ball{2};
public:
	BallMonitor() {
		rect.setPosition(0, 0);

		rect.setOutlineThickness(1);
		rect.setOutlineColor(sf::Color::Black);
		rect.setFillColor(sf::Color::White);

		line.setPosition(20, 20);
		line.setFillColor(sf::Color::Black);

		rect.setOutlineThickness(1);
		rect.setOutlineColor(sf::Color::Black);

		ball.setFillColor(sf::Color::White);
		ball.setOutlineThickness(2);
		ball.setOutlineColor(sf::Color::Black);
	}

	void speedUp(float increment) {
		speed = (speed + increment < max_speed)
			? (speed + increment)
			: (max_speed);
	}

	void speedDown(float decrement) {
		speed = (speed - decrement > 0)
			? (speed - decrement)
			: 0;
	}

	void angleUp(float degrees) {
		angle += degrees;

		while (angle >= 360) {
			angle -= 360;
		}
	}

	void angleDown(float degrees) {
		angle -= degrees;

		while (angle < 0) {
			angle += 360;
		}
	}

	void getVelocity(float& vx, float& vy) {
		float angle_radians = angle / 180.0f * pi;
		vx = std::cos(angle_radians) * speed;
		vy = std::sin(angle_radians) * speed;
	}

	void draw(sf::RenderWindow& window) {
		float angle_radians = angle / 180.0f * pi;
		float length = speed / max_speed * 30;

		line.setSize(sf::Vector2f(length, 2));
		line.setOrigin(sf::Vector2f(length / 2, 1));
		line.setRotation(angle);

		ball.setPosition(sf::Vector2f(
			length * std::cos(angle_radians) / 2,
			length * std::sin(angle_radians) / 2
		) + sf::Vector2f(1, 1) * (20 - ball.getRadius()));

		window.draw(rect);
		window.draw(line);
		window.draw(ball);
	}
};
