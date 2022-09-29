#include "../include/world.hpp"

/**
 * @brief Construct a new World::World object
 */
World::World() {
  objects = std::vector<PhysicsObject>();
}

/**
 * @brief Get the objects in the world.
 *
 * @return std::vector<PhysicsObject> Vector of objects in the world.
 */
std::vector<PhysicsObject> World::getObjects() {
  return objects;
}

/**
 * @brief Get the index of the object that is being hovered by the mouse.
 *
 * @return int Index of the object that is being hovered by the mouse.
 */
int World::getHoveredIndex() {
  for (uint i = 0; i < objects.size(); i++) {
    if (objects[i].isHovered()) {
      return i;
    }
  }
  return -1;
}

/**
 * @brief Set the objects vector in the world.
 *
 * @param objects_ Vector of objects to be set in the world.
 */
void World::setObjects(std::vector<PhysicsObject> objects_) {
  objects = objects_;
}

/**
 * @brief Summon a new object in the world adding it to the objects vector.
 *
 * @param newObject Object to be summoned in the world.
 */
void World::summon(PhysicsObject newObject) {
  objects.push_back(newObject);
}

// Poco eficiente.
// En vez de borrar y aplicar nuevas fuerzas, debería actualizar las que tiene,
// para así poder mantener fuerzas constantes y que sea más eficiente.
/**
 * @brief Update the forces of all objects in the world.
 */
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
/**
 * @brief Update the state (forces, position, velocity...) of all objects in the world. This function should be called every frame.
 *
 * @param deltaTime Time since the last update.
 */
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
    objects[i].updateTrails();
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

/**
 * @brief Draw all objects in the world.
 *
 * @param window GameWindow to draw the objects in.
 */
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
    window.draw(objects[i].getTrails());
    window.draw(*objects[i].getShape());
    #ifdef _DEBUG
      window.draw(objects[i].getNetForce().getVectorShape());
    #endif
  }
}

/**
 * @brief Sets all objects in the world to be not targeted.
 */
void World::clearTargets() {
  for (uint i = 0; i < objects.size(); i++) {
    objects[i].setTarget(false);
  }
}