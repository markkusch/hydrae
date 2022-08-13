#include "physicsObject.hpp"

class World {
  private:
    std::vector<PhysicsObject> objects;
    sf::Vector2f worldSize;
  public:
    World();
    std::vector<PhysicsObject> getObjects();
    void summon(PhysicsObject newObject);
    void updateForces();
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow &window);
};