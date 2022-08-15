#include "../include/force.hpp"

Force::Force(sf::Vector2<double> direction_, sf::Vector2f applicationPoint_) {
  direction = direction_;
  applicationPoint = applicationPoint_;
  magnitude = sqrt(pow(direction.x - applicationPoint.x, 2.0) + pow(direction.y - applicationPoint.y, 2.0));
  // float acosPatch = (direction.x - applicationPoint.x) / magnitude;
  // if (acosPatch > 1.f) {
  //   acosPatch = 1.f;
  // } else if (acosPatch < -1.f) {
  //   acosPatch = -1.f;
  // }
  //angle = acos(acosPatch);
  angle = atan2(direction.y - applicationPoint.y, direction.x - applicationPoint.x);
  buildVectorShape();
}

Force::Force(float angle_, float magnitude_, sf::Vector2f applicationPoint_) {
  angle = angle_;
  magnitude = magnitude_;
  applicationPoint = applicationPoint_;
  direction.x = applicationPoint.x + (magnitude * cos(angle));
  direction.y = applicationPoint.y + (magnitude * sin(angle));
  buildVectorShape();
}

float Force::getAngle() {
  return angle;
}

float Force::getMagnitude() {
  return magnitude;
}

sf::Vector2<double> Force::getDirection() {
  return direction;
}

sf::Vector2f Force::getApplicationPoint() {
  return applicationPoint;
}

sf::Vector2f Force::getUnitVector() {
  return sf::Vector2f((direction.x - applicationPoint.x) / magnitude,
    (direction.y - applicationPoint.y) / magnitude);
}

sf::RectangleShape Force::getVectorShape() {
  return vectorShape;
}

void Force::setAngle(float angle_) {
  angle = angle_;
}

void Force::setMagnitude(float magnitude_) {
  magnitude = magnitude_;
}

void Force::setDirection(sf::Vector2<double> direction_) {
  direction = direction_;
}

void Force::setApplicationPoint(sf::Vector2f applicationPoint_) {
  applicationPoint = applicationPoint_;
}

void Force::buildVectorShape() {
  vectorShape = sf::RectangleShape(sf::Vector2f(150.f, 5.f));
  vectorShape.setOrigin(sf::Vector2f(0, 2.5f));
  vectorShape.setPosition(applicationPoint);
  vectorShape.setRotation(angle * RAD_TO_DEG);
  vectorShape.setFillColor(sf::Color::Red);
}

Force Force::operator+(Force other) {
  return Force(direction + other.getDirection(), applicationPoint);
}

Force Force::operator-(Force other) {
  return Force(direction - other.getDirection(), applicationPoint);
}

Force Force::operator*(float scalar) {
  sf::Vector2<double> newDirection(direction.x * scalar, direction.y * scalar);
  return Force(newDirection, applicationPoint);
}