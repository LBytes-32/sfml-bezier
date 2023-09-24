#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <cmath>

#include "bezier/visual.hpp"
#include "bezier/editor.hpp"


int main() {
    // Use antialiasing.
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    // Create the window at 60 FPS.
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 500), "SFML Bezier", sf::Style::Default, settings);
    window->setFramerateLimit(60);
    
    Bezier bezierX;
    Bezier bezierY;
    
    bezierX.Control1 = sf::Vector2f {0, 0};
    bezierX.Control2 = sf::Vector2f {1, 1};
    
    bezierY.Control1 = sf::Vector2f {0, 0};
    bezierY.Control1 = sf::Vector2f {1, 1};
    
    BezierVisual visual(bezierX, bezierY, {520, 150}, {720, 350}, 0.03);
    BezierEditor editorX(bezierX, {20, 20}, {200, 460});
    BezierEditor editorY(bezierY, {240, 20}, {200, 460});
    
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
        
        sf::Vector2f mouse;
        mouse.x = sf::Mouse::getPosition(*window).x;
        mouse.y = sf::Mouse::getPosition(*window).y;
        
        editorX.Update(mouse);
        editorY.Update(mouse);
        visual.Update();

        window->draw(editorX);
        window->draw(editorY);
        window->draw(visual);
        window->display();
    }
    
    // Deallocate the window.
    delete window;
    return 0;
}

