#include "Platform/Platform.hpp"
#include "include/world.hpp"
#include "include/gameWindow.hpp"

int main() {
  #if defined(_DEBUG)
    std::cout << "Debug mode!" << std::endl;
  #endif

  GameWindow window;
  World testWorld;
  sf::Event event;
  sf::Clock clock;
  sf::Vector2f oldPos;
  int planetIndex = 0;
  bool movingView = false;

  // MAIN GAME LOOP
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::Resized) {
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
          movingView = true;
          oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        }
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
          sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
          PhysicsObject planet(worldPos, 10e10, planetIndex);
          testWorld.summon(planet);
          planetIndex++;
        }
        if (event.mouseButton.button == sf::Mouse::Right) {
          movingView = false;
        }
      }
      if (event.type == sf::Event::MouseMoved) {
        if (movingView) {
          const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
          const sf::Vector2f deltaPos = oldPos - newPos;
          window.move(deltaPos);
          oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        }
      }
      if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta <= -1)
          window.zoom(1.1);
        else if (event.mouseWheelScroll.delta >= 1)
          window.zoom(0.9);
      }
    }
    sf::Time elapsed = clock.restart();
    testWorld.update(elapsed);
    window.clear(sf::Color(3, 6, 46));
    #ifdef _DEBUG
      window.loadDebugHud();
    #endif
    testWorld.draw(window);
    window.display();
  }
  return 0;
}
