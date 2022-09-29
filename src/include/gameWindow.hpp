/**
 * @file gameWindow.hpp
 * @author Markus Schüller Perdigón (markuschue@gmail.com)
 *
 * @brief A window to display the game
 * @details An extension of the SFML RenderWindow class, this class contains
 * a few extra methods to control the camera and HUD.
 */

#include "physicsObject.hpp"

class GameWindow: public sf::RenderWindow {
  protected:
    sf::View gameView;
    sf::View hudView;
  public:
    GameWindow();
    void zoom(float factor);
    void move(sf::Vector2f deltaPosition);
    void loadDebugHud(PhysicsObject targetedObject);
};