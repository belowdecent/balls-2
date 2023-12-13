#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "SFML/Graphics/RenderWindow.hpp"
#include "src/Ball.hpp"
#include "src/ColoredBall.hpp"
#include "src/FadingBall.hpp"

class BallArray {
public:
	std::vector<std::unique_ptr<Ball>> balls;
	sf::Vector2u window_size;

	void addBall(const sf::Vector2f& position, const sf::Vector2f& velocity, const float& radius) {
		balls.push_back(std::make_unique<Ball>(position, velocity, radius));
		balls.back()->setWindowSize(window_size);
	}

	void addColoredBall(const sf::Vector2f& position, const sf::Vector2f& velocity, const float& radius, sf::Color color) {
		balls.push_back(std::make_unique<ColoredBall>(position, velocity, radius, color));
		balls.back()->setWindowSize(window_size);
	}

	void addFadingBall(const sf::Vector2f& position, const sf::Vector2f& velocity, const float& radius, sf::Color color) {
		balls.push_back(std::make_unique<FadingBall>(position, velocity, radius, color));
		balls.back()->setWindowSize(window_size);
	}

	void setWindowSize(const sf::Vector2u& window_size) {
		this->window_size = window_size;

		for (auto& ball : balls) {
			ball->setWindowSize(this->window_size);
		}
	}

	void updateVelocities() {
		for (int i = 0; i < balls.size(); i++) {
			for (int j = i + 1; j < balls.size(); j++) {
				sf::Vector2f c(balls[j]->getPosition() - balls[i]->getPosition());
				c += sf::Vector2f(1, 1) * (balls[j]->getRadius() - balls[i]->getRadius());
				float mag_sq = c.x * c.x + c.y * c.y;
				float distance = balls[i]->getRadius() + balls[j]->getRadius();

				if (mag_sq <= distance * distance) {
					sf::Vector2f b1v = balls[i]->velocity;
					sf::Vector2f b2v = balls[j]->velocity;

					float AC_dot = b1v.x * c.x + b1v.y * c.y;
					float BC_dot = b2v.x * c.x + b2v.y * c.y;

					sf::Vector2f b1v_normal = c * AC_dot / mag_sq;
					sf::Vector2f b2v_normal = c * BC_dot / mag_sq;

					sf::Vector2f b1v_tangent = b1v - b1v_normal;
					sf::Vector2f b2v_tangent = b2v - b2v_normal;

					balls[i]->velocity = b2v_normal + b1v_tangent;
					balls[j]->velocity = b1v_normal + b2v_tangent;
				}
			}
		}
	}

	void updatePositions(float dt) {
		for (auto& ball : balls) {
			ball->updatePosition(dt);
		}
	}

	void draw(sf::RenderWindow& window) {
		for (auto& ball : balls) {
			ball->drawSelf(window);
		}
	}
};
