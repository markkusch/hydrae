/**
 * @file world.hpp
 * @author Markus Schüller Perdigón (markuschue@gmail.com)
 *
 * @brief A world in the game
 * @details This file contains the definition of a world in the game, where all
 * objects are contained and updated.
 */

#include "gameWindow.hpp"

class World {
  private:
    std::vector<PhysicsObject> objects;
  public:
    World();
    std::vector<PhysicsObject> getObjects();
    int getHoveredIndex();
    void setObjects(std::vector<PhysicsObject> objects_);
    void summon(PhysicsObject newObject);
    void updateForces();
    void update(sf::Time deltaTime);
    void draw(GameWindow &window);
    void clearTargets();
};