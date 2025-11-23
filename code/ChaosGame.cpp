#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

double calculateSF(int n) {

	//n = number of vertices
	if ( n % 4 == 0 ) { return (1 / (1 + tan(M_PI / n))); }

	if ( n % 4 == 1 || n % 4 == 3) { return (1 / (1 + (2 * sin(M_PI / (2 * n))))); }

	if ( n % 4 == 2) { return (1 / (1 + sin(M_PI/n))); }

	return 0;
}

int main() {

	sf::VideoMode vm({1920, 1080});
	sf::RenderWindow window(vm, "Chaos Game", sf::Style::Default);
	sf::Font font("AdwaitaSans-Regular.ttf");

	std::vector<sf::Vector2f> vertices;
	std::vector<sf::Vector2f> points;
	std::vector<sf::Vector2f> buffer;

	//int frame {0};
	int lastPt {0};
	int prevVert {-1}; //hmmmmm
	double r {0};

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
					buffer.push_back(sf::Vector2f(mb->position.x, mb->position.y));

				}
			}
			
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scan::Enter) {
					for (int i {0}; i < buffer.size() - 1; i++) {
						vertices.push_back(buffer[i]);
					}
					points.push_back(buffer[buffer.size() - 1]);
					r = calculateSF(vertices.size());
					std::cout << "r = " << r << std::endl;
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

				int randVert = rand() % vertices.size();
				if (vertices.size() > 3 && (randVert == prevVert)) {
					while (randVert == prevVert) {
						randVert = rand() % vertices.size();
					}
				}
				prevVert = randVert;

				nxtPt.x = (vertices[randVert].x + points[lastPt].x) - ((vertices[randVert].x + points[lastPt].x) * r);
				nxtPt.y = (vertices[randVert].y + points[lastPt].y) - ((vertices[randVert].y + points[lastPt].y) * r);
				points.push_back(nxtPt);
				lastPt++;
			}
		}

		window.clear();

		sf::Text text(font);
		if (vertices.size() == 0 || points.size() == 0) {
			text.setString("Pick some points then press enter");
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			window.draw(text);
		}

		if (buffer.size() > 0 && vertices.size() == 0 && points.size() == 0) {
			for (int i {0}; i < buffer.size(); i++) {
				sf::RectangleShape rect(sf::Vector2f(10,10));
				rect.setPosition(sf::Vector2f(buffer[i].x, buffer[i].y));
				rect.setFillColor(sf::Color::White);
				window.draw(rect);
			}
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
