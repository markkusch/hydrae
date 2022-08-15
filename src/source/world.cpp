#include "../include/world.hpp"

World::World() {
  worldSize = sf::Vector2f(1024.f, 1024.f);
}

std::vector<PhysicsObject> World::getObjects() {
  return objects;
}

int World::getHoveredIndex() {
  for (uint i = 0; i < objects.size(); i++) {
    if (objects[i].isHovered()) {
      return i;
    }
  }
  return -1;
}

void World::setObjects(std::vector<PhysicsObject> objects_) {
  objects = objects_;
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
  }
}

void World::draw(GameWindow &window) {
  for (uint i = 0; i < objects.size(); i++) {
    // If mouse is over an object, draw an outline around it.
    if (objects[i].getShape() -> getGlobalBounds().contains((sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))) {
      objects[i].getShape()->setOutlineColor(sf::Color::White);
      objects[i].getShape()->setOutlineThickness(2.f);
      objects[i].setHover(true);
    } else {
      objects[i].getShape()->setOutlineThickness(0.f);
      objects[i].setHover(false);
    }
    window.draw(*objects[i].getShape());
    #ifdef _DEBUG
      window.draw(objects[i].getNetForce().getVectorShape());
    #endif
  }
}

void World::clearTargets() {
  for (uint i = 0; i < objects.size(); i++) {
    objects[i].setTarget(false);
  }
}