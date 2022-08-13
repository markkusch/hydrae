#include "../include/world.hpp"

World::World() {
  worldSize = sf::Vector2f(1024.f, 1024.f);
}
std::vector<PhysicsObject> World::getObjects() {
  return objects;
}

void World::summon(PhysicsObject newObject) {
  objects.push_back(newObject);
}

// Poco eficiente.
void World::updateForces() {
  for (uint i = 0; i < objects.size(); i++) {
    objects[i].clearForces();
  }
  for (uint i = 0; i < objects.size(); i++) {
    for (uint j = 0; j < objects.size(); j++) {
      if (objects[i].getID() != objects[j].getID()) {
        objects[i].applyForce(objects[i].calculateGravitalForce(objects[j]));
      }
    }
  }
  for (uint i = 0; i < objects.size(); i++) {
    objects[i].calculateNetForce();
  }
}

// Se puede mejorar guardando la nueva aceleracion para evitar la primera llamada.
void World::update(sf::Time deltaTime) {
  // Update acceleration according to the forces and position according to that acceleration.
  for (uint i = 0; i < objects.size(); i++) {
    objects[i].setAcceleration(sf::Vector2f((objects[i].getNetForce().getDirection().x +
        objects[i].getNetForce().getApplicationPoint().x) / objects[i].getMass(),
        (objects[i].getNetForce().getDirection().y + objects[i].getNetForce().getApplicationPoint().y)
        / objects[i].getMass()));
    objects[i].setPosition(sf::Vector2f(objects[i].getPosition().x + (deltaTime.asSeconds() *
      (objects[i].getVelocity().x + deltaTime.asSeconds() * objects[i].getAcceleration().x / 2.f)),
      objects[i].getPosition().y + deltaTime.asSeconds() *
      (objects[i].getVelocity().y + deltaTime.asSeconds() * objects[i].getAcceleration().y / 2.f)));
    #if defined(_DEBUG)
      //std::cout << "old acc: " << objects[i].getAcceleration().x << ", " << objects[i].getAcceleration().y << std::endl;
      //std::cout << "pos: " << objects[i].getPosition().x << ", " << objects[i].getPosition().y << std::endl;
    #endif
  }
  // Update forces according to new position.
  updateForces();
  // Update velocity according to the new acceleration at the new position.
  for (uint i = 0; i < objects.size(); i++) {
    sf::Vector2f newAcceleration((objects[i].getNetForce().getDirection().x +
        objects[i].getNetForce().getApplicationPoint().x) / objects[i].getMass(),
        (objects[i].getNetForce().getDirection().y + objects[i].getNetForce().getApplicationPoint().y)
        / objects[i].getMass());
    objects[i].setVelocity(sf::Vector2f(objects[i].getVelocity().x + (deltaTime.asSeconds() *
        (objects[i].getAcceleration().x + newAcceleration.x)) / 2.f, objects[i].getVelocity().y +
        (deltaTime.asSeconds() * (objects[i].getAcceleration().y + newAcceleration.y)) / 2.f));
    objects[i].setAcceleration(newAcceleration);
    #if defined(_DEBUG)
      //std::cout << "vel: " << objects[i].getVelocity().x << ", " << objects[i].getVelocity().y << std::endl;
      //std::cout << "new acc: " << newAcceleration.x << ", " << newAcceleration.y << std::endl;
    #endif
  }
}

void World::draw(sf::RenderWindow &window) {
  for (uint i = 0; i < objects.size(); i++) {
    window.draw(*objects[i].getShape());
    #if defined(_DEBUG)
      window.draw(objects[i].getNetForce().getVectorShape());
      //std::cout << "Object " << i << "; X:" << objects[i].getPosition().x << ", Y:" << objects[i].getPosition().y << std::endl;
    #endif
  }
}