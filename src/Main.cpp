#include "Platform/Platform.hpp"
#include "include/world.hpp"

int hydrae() {
  #if defined(_DEBUG)
    std::cout << "Debug mode!" << std::endl;
    int targetedIndex = -1;
  #endif

  GameWindow window;
  World testWorld;
  sf::Event event;
  sf::Clock clock;
  sf::Vector2f oldPos;
  PhysicsObject nullObject = PhysicsObject(sf::Vector2f(0, 0), 0, -1);
  int planetIndex = 0;
  bool movingView = false;
  bool paused = false;

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
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
          paused = !paused;
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
          #ifdef _DEBUG
            int hoveredIndex = testWorld.getHoveredIndex();
            std::vector<PhysicsObject> objects = testWorld.getObjects();
            if (hoveredIndex != -1 && !objects[hoveredIndex].isTargeted()) {
              testWorld.clearTargets();
              objects[hoveredIndex].setTarget(true);
              targetedIndex = hoveredIndex;
            } else if (hoveredIndex != -1 && objects[hoveredIndex].isTargeted()) {
              objects[hoveredIndex].setTarget(false);
              targetedIndex = -1;
            }
            testWorld.setObjects(objects);
          #endif
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
    if (!paused) {
      testWorld.update(elapsed);
    }
    window.clear(sf::Color(3, 6, 46));
    testWorld.draw(window);
    #ifdef _DEBUG
      if (targetedIndex != -1) {
        std::vector<PhysicsObject> objects = testWorld.getObjects();
        window.loadDebugHud(objects[targetedIndex]);
      } else {
        window.loadDebugHud(nullObject);
      }
    #endif
    window.display();
  }
  return 0;
}

int main() {
  try {
    return hydrae();
  } catch (const std::exception& e) {
    std::cerr<< "EXCEPTION: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}