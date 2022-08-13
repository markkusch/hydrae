#include "../include/force.hpp"

Force::Force(sf::Vector2f direction_, sf::Vector2f applicationPoint_) {
  direction = direction_;
  applicationPoint = applicationPoint_;
  magnitude = sqrt(pow(direction.x - applicationPoint.x, 2.0) + pow(direction.y - applicationPoint.y, 2.0));
  float acosPatch = (direction.x - applicationPoint.x) / magnitude;
  if (acosPatch > 1.f) {
    acosPatch = 1.f;
  } else if (acosPatch < -1.f) {
    acosPatch = -1.f;
  }
  //angle = atan(direction.y / direction.x);
  angle = acos(acosPatch);
  vectorShape = sf::VertexArray(sf::Lines, 2);
  vectorShape[0].position = applicationPoint;
  vectorShape[1].position = direction;
}

Force::Force(float angle_, float magnitude_, sf::Vector2f applicationPoint_) {
  angle = angle_;
  magnitude = magnitude_;
  applicationPoint = applicationPoint_;
  direction.x = applicationPoint.x + (magnitude * cos(angle));
  direction.y = applicationPoint.y + (magnitude * sin(angle));
  vectorShape = sf::VertexArray(sf::Lines, 2);
  vectorShape[0].position = applicationPoint;
  vectorShape[1].position = direction;
}

float Force::getAngle() {
  return angle;
}

float Force::getMagnitude() {
  return magnitude;
}

sf::Vector2f Force::getDirection() {
  return direction;
}

sf::Vector2f Force::getApplicationPoint() {
  return applicationPoint;
}

sf::Vector2f Force::getUnitVector() {
  return sf::Vector2f((direction.x - applicationPoint.x) / magnitude,
    (direction.y - applicationPoint.y) / magnitude);
}

sf::VertexArray Force::getVectorShape() {
  return vectorShape;
}

void Force::setAngle(float angle_) {
  angle = angle_;
}

void Force::setMagnitude(float magnitude_) {
  magnitude = magnitude_;
}

void Force::setDirection(sf::Vector2f direction_) {
  direction = direction_;
}

void Force::setApplicationPoint(sf::Vector2f applicationPoint_) {
  applicationPoint = applicationPoint_;
}

Force Force::operator+(Force other) {
  return Force(direction + other.getDirection(), applicationPoint);
}

Force Force::operator-(Force other) {
  return Force(direction - other.getDirection(), applicationPoint);
}

Force Force::operator*(float scalar) {
  return Force(direction * scalar, applicationPoint);
}