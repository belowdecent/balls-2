#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "SFML/Window/VideoMode.hpp"
#include "src/BallArray.hpp"
#include "src/BallMonitor.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(600, 400), "works", sf::Style::Resize);
	window.setVerticalSyncEnabled(true);

	BallArray balls;
	balls.addBall({10, 10}, {20, 20}, 15);
	balls.addBall({150, 10}, {-30, 20}, 35);
	balls.setWindowSize(window.getSize());

	BallMonitor monitor;

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event e;
		float dt = clock.restart().asSeconds();

		balls.updateVelocities();
		balls.updatePositions(dt);

		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			} else if (e.type == sf::Event::Resized) {
				balls.setWindowSize(window.getSize());
			} else if (e.type == sf::Event::MouseButtonPressed) {
				float vx, vy;
				monitor.getVelocity(vx, vy);

				if (e.mouseButton.button == sf::Mouse::Left) {
					balls.addBall({
							static_cast<float>(e.mouseButton.x), 
							static_cast<float>(e.mouseButton.y)
						}, {vx, vy}, 15);
				} else if (e.mouseButton.button == sf::Mouse::Right) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
						balls.addFadingBall({
								static_cast<float>(e.mouseButton.x), 
								static_cast<float>(e.mouseButton.y)
							}, {vx, vy}, 20, sf::Color::Magenta);
					} else {
						balls.addColoredBall({
								static_cast<float>(e.mouseButton.x), 
								static_cast<float>(e.mouseButton.y)
							}, {vx, vy}, 20, sf::Color::Green);
					}
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			monitor.angleDown(1);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			monitor.angleUp(1);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			monitor.speedUp(1);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			monitor.speedDown(1);
		}

		window.clear(sf::Color::White);
		balls.draw(window);
		monitor.draw(window);
		window.display();
	}

	return 0;
}
