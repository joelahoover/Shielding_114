#include "main/main_app.hpp"

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "state/main_menu.hpp"

MainApp::MainApp(int argc, const char* argv[]) { }

MainApp::~MainApp() { }

int MainApp::run() {
	// Create a window for the game
	sf::RenderWindow window(sf::VideoMode(640, 480), "Shielding: Incident 114", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0, 0, 2));

	std::unique_ptr<State> current_state(new MainMenu);

	bool running = true;

	while(running)
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			// Handle events
			if(event.type == sf::Event::Closed) {
				running = false;
			}
			current_state->handleEvent(event);
		}

		// Update
		current_state->update(current_state);

		if(!current_state) {
			// The state decided to quit
			break;
		}

		// Draw
		window.clear();
		window.draw(*current_state);
		window.display();
	}

	// And . . . we're done!
	window.close();

	return 0;
}

