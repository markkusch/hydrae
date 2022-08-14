#include "physicsObject.hpp"

class GameWindow: public sf::RenderWindow {
  protected:
    sf::View gameView;
    sf::View hudView;
  public:
    GameWindow();
    void zoom(float factor);
    void move(sf::Vector2f deltaPosition);
    void loadDebugHud(PhysicsObject* hoveredObject);
};