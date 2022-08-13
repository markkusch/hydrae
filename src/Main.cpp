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
  sf::View view = window.getDefaultView();
  float zoom = 1;
  int planetIndex = 0;

  while (window.isOpen()) {
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::Resized) {
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
          sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
          PhysicsObject planet(worldPos, 10e10, planetIndex);
          testWorld.summon(planet);
          planetIndex++;
        }
      }
      if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta <= -1)
          zoom = std::min(2.f, zoom + .1f);
        else if (event.mouseWheelScroll.delta >= 1)
          zoom = std::max(.5f, zoom - .1f);
        view.setSize(window.getDefaultView().getSize());
        view.zoom(zoom);
        window.setView(view);
      }
    }
    sf::Time elapsed = clock.restart();
    testWorld.update(elapsed);

    window.clear(sf::Color(3, 6, 46));
    testWorld.draw(window);
    window.display();
  }
  return 0;
}
