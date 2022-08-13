#include "../include/physicsObject.hpp"

PhysicsObject::PhysicsObject(sf::Vector2f position_, float mass_, int id_) {
  shape = new sf::CircleShape(10.f);
  shape -> setFillColor(sf::Color(124, 124, 124));
  sf::Vector2f origin_ = sf::Vector2f(getPosition().x + 10, getPosition().y + 10);
  shape -> setOrigin(origin_);
  setPosition(position_);
  acceleration = sf::Vector2f(0, 0);
  velocity = sf::Vector2f(0, 0);
  mass = mass_;
  id = id_;
}

sf::Shape* PhysicsObject::getShape() {
  return shape;
}

sf::Vector2f PhysicsObject::getPosition() {
  return shape -> getPosition();
}

float PhysicsObject::getMass() {
  return mass;
}

sf::Vector2f PhysicsObject::getVelocity() {
  return velocity;
}
sf::Vector2f PhysicsObject::getAcceleration() {
  return acceleration;
}

int PhysicsObject::getID() {
  return id;
}

Force PhysicsObject::getNetForce() {
  return netForce;
}

void PhysicsObject::setPosition(sf::Vector2f position_) {
  shape -> setPosition(position_);
}

void PhysicsObject::setMass(float mass_) {
  mass = mass_;
}

void PhysicsObject::setVelocity(sf::Vector2f vel_) {
  velocity = vel_;
}

void PhysicsObject::setAcceleration(sf::Vector2f acc_) {
  acceleration = acc_;
}

void PhysicsObject::setID(int id_) {
  id = id_;
}

float PhysicsObject::distanceTo(PhysicsObject other) {
  return sqrt(pow(other.getPosition().x - getPosition().x, 2.0) +
      pow(other.getPosition().y - getPosition().y, 2.0));
}

void PhysicsObject::calculateNetForce() {
  for (uint i = 0; i < forces.size(); i++) {
    netForce = forces[i] + netForce;
  }
}

void PhysicsObject::applyForce(Force newForce) {
  forces.push_back(newForce);
}

Force PhysicsObject::calculateGravitalForce(PhysicsObject other) {
  sf::Vector2f resultingDir = other.getPosition() - getPosition();
  float resultingMagnitude = (GRAV_CONST * mass * other.getMass()) / distanceTo(other);
  //resultingDir = resultingDir * static_cast<float>(resultingMagnitude * distanceTo(other) / pow(mass, 2.0));
  resultingDir = resultingDir * resultingMagnitude;
  Force resultingForce(resultingDir, getPosition());
  //std::cout << "res force: " << resultingForce.getDirection().x << ", " << resultingForce.getDirection().y << std::endl;
  return resultingForce;
}

void PhysicsObject::clearForces() {
  netForce = Force(0, 0, getPosition());
  forces.clear();
}
