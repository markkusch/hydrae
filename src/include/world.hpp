#include "gameWindow.hpp"

class World {
  private:
    std::vector<PhysicsObject> objects;
    sf::Vector2f worldSize;
  public:
    World();
    std::vector<PhysicsObject> getObjects();
    PhysicsObject* getHoveredObject();
    void summon(PhysicsObject newObject);
    void updateForces();
    void update(sf::Time deltaTime);
    void draw(GameWindow &window);
    void clearTargets();
};