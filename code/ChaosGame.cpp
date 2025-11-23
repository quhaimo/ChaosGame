#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

int main() {

	sf::VideoMode vm({1920, 1080});
	sf::RenderWindow window(vm, "Chaos Game", sf::Style::Default);
	sf::Font font("AdwaitaSans-Regular.ttf");

	std::vector<sf::Vector2f> vertices;
	std::vector<sf::Vector2f> points;

	//int frame {0};
	int lastPt {0};

	while (window.isOpen()) {


		//interactive block
		while (const std::optional event = window.pollEvent()) {

			//event is an "optional" container, you need to peel back the optional layer, then the event layer before being able to 
			//access the subevent
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			if (event->is<sf::Event::MouseButtonPressed>()) {
				//event->getif returns a pointer to the event subtype (MouseButtonPressed)
				//const because we only need to read the data from the event
				//auto because the data type is too long to type
				const auto* mb = event->getIf<sf::Event::MouseButtonPressed>();
				if (mb->button == sf::Mouse::Button::Left) {
					std::cout << "\nleft button pressed";
					std::cout << "\nx pos: " << mb->position.x;
					std::cout << "\ny pos: " << mb->position.y << std::endl;

					if (vertices.size() < 3) {
						vertices.push_back(sf::Vector2f(mb->position.x, mb->position.y));
					}
					else if (points.size() == 0) {
						points.push_back(sf::Vector2f(mb->position.x, mb->position.y));
					}
				}
			}

		}

		//i guess we making triangles now
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
			window.close();
		}

		const int PTS_PER_FRAME {5};
		if (points.size() > 0) {
			for (int i {0}; i < PTS_PER_FRAME; i++) {
				sf::Vector2f nxtPt;
				int randVert = rand() % 3;
				nxtPt.x = (vertices[randVert].x + points[lastPt].x) / 2;
				nxtPt.y = (vertices[randVert].y + points[lastPt].y) / 2;
				points.push_back(nxtPt);
				lastPt++;
			}
		}

		window.clear();

		sf::Text text(font);
		if (vertices.size() < 3 || points.size() == 0) {
			text.setString("Pick 4 points");
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			window.draw(text);
		}

		for (int i {0}; i < vertices.size(); i++) {
			sf::RectangleShape rect(sf::Vector2f(10,10));
			rect.setPosition(sf::Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(sf::Color::Blue);
			window.draw(rect);
		}

		for (int i {0}; i < points.size(); i++) {
			sf::RectangleShape rect(sf::Vector2f(10,10));
			rect.setPosition(sf::Vector2f(points[i].x, points[i].y));
			rect.setFillColor(sf::Color::Red);
			window.draw(rect);
		}

		window.display();

		//std::cout << "frame: " << frame << std::endl;
		//frame++;
		
	}

}
