#include "../include/physicsObject.hpp"

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
  for (uint i = 0; i < trails.getVertexCount(); i++) {
    float mappedIndex = i / (float)trails.getVertexCount() * 255;
    trails[i].color = sf::Color(255, 255, 255, mappedIndex);
    trails[i].position = position_;
  }
  hovered = false;
  targeted = false;
}

sf::Shape* PhysicsObject::getShape() {
  return shape;
}

sf::Vector2f PhysicsObject::getPosition() {
  return shape -> getPosition();
}

double PhysicsObject::getMass() {
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

bool PhysicsObject::isHovered() {
  return hovered;
}

bool PhysicsObject::isTargeted() {
  return targeted;
}

sf::VertexArray PhysicsObject::getTrails() {
  return trails;
}

void PhysicsObject::setPosition(sf::Vector2f position_) {
  shape -> setPosition(position_);
}

void PhysicsObject::setMass(double mass_) {
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

void PhysicsObject::updateTrails() {
  if (distanceTo(trails[trails.getVertexCount()- 1].position) > TRAILS_DENSITY) {
    for (uint i = 0; i < trails.getVertexCount(); i++) {
      trails[i].position = trails[i + 1].position;
    }
    trails[trails.getVertexCount() - 1].position = shape -> getPosition();
  }
}

float PhysicsObject::distanceTo(PhysicsObject other) {
  return distanceTo(other.getPosition());
}

float PhysicsObject::distanceTo(sf::Vector2f other) {
  return sqrt(pow(other.x - getPosition().x, 2.0) +
    pow(other.y - getPosition().y, 2.0));
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
  sf::Vector2<double> resultingDir(other.getPosition().x - getPosition().x, other.getPosition().y - getPosition().y);
  float resultingMagnitude = (GRAV_CONST * mass * other.getMass()) / distanceTo(other);
  resultingDir.x = resultingDir.x * resultingMagnitude;
  resultingDir.y = resultingDir.y * resultingMagnitude;
  Force resultingForce(resultingDir, getPosition());
  return resultingForce;
}

void PhysicsObject::clearForces() {
  netForce = Force(0, 0, getPosition());
  forces.clear();
}

void PhysicsObject::setHover(bool hovered_) {
  hovered = hovered_;
}

void PhysicsObject::setTarget(bool targeted_) {
  targeted = targeted_;
}