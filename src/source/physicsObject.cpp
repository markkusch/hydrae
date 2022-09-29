#include "../include/physicsObject.hpp"

/**
 * @brief Construct a new PhysicsObject::PhysicsObject given its basic properties.
 *
 * @param position_ World coordinates of the object.
 * @param mass_ Mass of the object.
 * @param id_ Unique ID of the object.
 */
PhysicsObject::PhysicsObject(sf::Vector2f position_, double mass_, int id_) {
  shape = new sf::CircleShape(10.f);
  shape -> setFillColor(sf::Color(124, 124, 124));
  sf::Vector2f origin_ = sf::Vector2f(getPosition().x + 10, getPosition().y + 10);
  shape -> setOrigin(origin_);
  setPosition(position_);
  acceleration = sf::Vector2f(0, 0);
  velocity = sf::Vector2f(0, 0);
  mass = mass_;
  id = id_;
  trails = sf::VertexArray(sf::Points, TRAILS_LENGTH);
  for (uint i = 0; i < TRAILS_LENGTH; i++) {
    float mappedIndex = i / (float)TRAILS_LENGTH * 255;
    trails[i].color = sf::Color(255, 255, 255, mappedIndex);
    trails[i].position = position_;
  }
  hovered = false;
  targeted = false;
}

/**
 * @brief Get the shape of the object.
 *
 * @return sf::Shape* Pointer to the shape of the object.
 */
sf::Shape* PhysicsObject::getShape() {
  return shape;
}

/**
 * @brief Get the position of the object.
 *
 * @return sf::Vector2f Position of the object.
 */
sf::Vector2f PhysicsObject::getPosition() {
  return shape -> getPosition();
}

/**
 * @brief Get the mass of the object.
 *
 * @return double Mass of the object.
 */
double PhysicsObject::getMass() {
  return mass;
}

/**
 * @brief Get the velocity of the object.
 *
 * @return sf::Vector2f Velocity of the object.
 */
sf::Vector2f PhysicsObject::getVelocity() {
  return velocity;
}

/**
 * @brief Get the acceleration of the object.
 *
 * @return sf::Vector2f Acceleration of the object.
 */
sf::Vector2f PhysicsObject::getAcceleration() {
  return acceleration;
}

/**
 * @brief Get the unique ID of the object.
 *
 * @return int Unique ID of the object.
 */
int PhysicsObject::getID() {
  return id;
}

/**
 * @brief Get the net force acting on the object.
 *
 * @return Force Net force acting on the object.
 */
Force PhysicsObject::getNetForce() {
  return netForce;
}

/**
 * @brief Check if the object is being hovered by the mouse.
 *
 * @return true If the object is being hovered by the mouse.
 * @return false If the object is not being hovered by the mouse.
 */
bool PhysicsObject::isHovered() {
  return hovered;
}

/**
 * @brief Check if the object is being targeted by the player.
 *
 * @return true If the object is being targeted by the player.
 * @return false If the object is not being targeted by the player.
 */
bool PhysicsObject::isTargeted() {
  return targeted;
}

/**
 * @brief Get the trails of the object.
 *
 * @return sf::VertexArray Trails of the object.
 */
sf::VertexArray PhysicsObject::getTrails() {
  return trails;
}

/**
 * @brief Set the position of the object.
 *
 * @param position_ New position of the object.
 */
void PhysicsObject::setPosition(sf::Vector2f position_) {
  shape -> setPosition(position_);
}

/**
 * @brief Set the mass of the object.
 *
 * @param mass_ New mass of the object.
 */
void PhysicsObject::setMass(double mass_) {
  mass = mass_;
}

/**
 * @brief Set the velocity of the object.
 *
 * @param velocity_ New velocity of the object.
 */
void PhysicsObject::setVelocity(sf::Vector2f vel_) {
  velocity = vel_;
}

/**
 * @brief Set the acceleration of the object.
 *
 * @param acceleration_ New acceleration of the object.
 */
void PhysicsObject::setAcceleration(sf::Vector2f acc_) {
  acceleration = acc_;
}

/**
 * @brief Set the unique ID of the object.
 *
 * @param id_ New unique ID of the object.
 */
void PhysicsObject::setID(int id_) {
  id = id_;
}

/**
 * @brief Moves all dots of the trails one position closer to the object.
 */
void PhysicsObject::updateTrails() {
  if (distanceTo(trails[TRAILS_LENGTH - 1].position) > TRAILS_DENSITY) {
    for (uint i = 0; i < TRAILS_LENGTH - 1; i++) {
      trails[i].position = trails[i + 1].position;
    }
    trails[TRAILS_LENGTH - 1].position = shape -> getPosition();
  }
}

/**
 * @brief Calculate the distance between two objects.
 *
 * @param other Object to calculate the distance to.
 * @return double Distance between the two objects.
 */
float PhysicsObject::distanceTo(PhysicsObject other) {
  return distanceTo(other.getPosition());
}

/**
 * @brief Calculate the distance between the object and a point.
 *
 * @param other Point to calculate the distance to.
 * @return double Distance between the object and the point.
 */
float PhysicsObject::distanceTo(sf::Vector2f other) {
  return sqrt(pow(other.x - getPosition().x, 2.0) +
    pow(other.y - getPosition().y, 2.0));
}

/**
 * @brief Calculates the net force as the sum of all forces acting on the object.
 */
void PhysicsObject::calculateNetForce() {
  for (uint i = 0; i < forces.size(); i++) {
    netForce = forces[i] + netForce;
  }
}

/**
 * @brief Adds a new force to this object.
 *
 * @param newForce Force to add to the object.
 */
void PhysicsObject::applyForce(Force newForce) {
  forces.push_back(newForce);
}

/**
 * @brief Calculates the gravitational force between two objects as the formula F = G * m1 * m2 / r^2.
 *
 * @param other Object to calculate the gravitational force to.
 * @return Force Gravitational force between the two objects.
 */
Force PhysicsObject::calculateGravitalForce(PhysicsObject other) {
  sf::Vector2<double> resultingDir(other.getPosition().x - getPosition().x, other.getPosition().y - getPosition().y);
  float resultingMagnitude = (GRAV_CONST * mass * other.getMass()) / distanceTo(other);
  resultingDir.x = resultingDir.x * resultingMagnitude;
  resultingDir.y = resultingDir.y * resultingMagnitude;
  Force resultingForce(resultingDir, getPosition());
  return resultingForce;
}

/**
 * @brief Sets the net force to zero and clears the forces vector.
 */
void PhysicsObject::clearForces() {
  netForce = Force(0, 0, getPosition());
  forces.clear();
}

/**
 * @brief Set the hovered state of the object.
 *
 * @param hovered_ New hovered state of the object.
 */
void PhysicsObject::setHover(bool hovered_) {
  hovered = hovered_;
}

/**
 * @brief Set the targeted state of the object.
 *
 * @param targeted_ New targeted state of the object.
 */
void PhysicsObject::setTarget(bool targeted_) {
  targeted = targeted_;
}