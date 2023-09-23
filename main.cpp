#include <SFML/Graphics.hpp>
#include <memory>
#include "bezier/visual.hpp"

int main() {
    // Use antialiasing.
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    // Create the window at 60 FPS.
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 500), "SFML Bezier", sf::Style::Default, settings);
    window->setFramerateLimit(60);
    
    BezierVisual visual({100, 100}, {400, 400}, 0.01);
    
    while (window->isOpen()) {
        sf::Event event;
        
        while (window->pollEvent(event)) {
            switch (event.type) {
                
                // Window close handler.
                case sf::Event::Closed:
                    window->close();
                    break;
                
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Key::Space) {
						visual.Redirect();
					}
					break;
            }
        }
        
        // Render the contents.
        window->clear();
        
        visual.Update();
        window->draw(visual);
        
        window->display();
    }
    
    // Deallocate the window.
    delete window;
    return 0;
}

