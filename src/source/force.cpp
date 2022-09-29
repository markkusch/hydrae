#include "../include/force.hpp"

/**
 * @brief Construct a new Force::Force object given an application point and direction.
 *
 * @param direction_ Direction of the force vector in world coordinates.
 * @param applicationPoint_ World coordinates where the vector "starts".
 */
Force::Force(sf::Vector2<double> direction_, sf::Vector2f applicationPoint_) {
  direction = direction_;
  applicationPoint = applicationPoint_;
  magnitude = sqrt(pow(direction.x - applicationPoint.x, 2.0) + pow(direction.y - applicationPoint.y, 2.0));
  angle = atan2(direction.y - applicationPoint.y, direction.x - applicationPoint.x);
  buildVectorShape();
}

/**
 * @brief Construct a new Force::Force object given an application point, angle and magnitude.
 *
 * @param angle_ Angle of the force vector in radians.
 * @param magnitude_ Module of the force vector.
 * @param applicationPoint_ World coordinates where the vector "starts".
 */
Force::Force(float angle_, float magnitude_, sf::Vector2f applicationPoint_) {
  angle = angle_;
  magnitude = magnitude_;
  applicationPoint = applicationPoint_;
  direction.x = applicationPoint.x + (magnitude * cos(angle));
  direction.y = applicationPoint.y + (magnitude * sin(angle));
  buildVectorShape();
}

/**
 * @brief Get the angle of the force vector.
 *
 * @return float Angle of the force vector in radians.
 */
float Force::getAngle() {
  return angle;
}

/**
 * @brief Get the magnitude of the force vector.
 *
 * @return float Module of the force vector.
 */
float Force::getMagnitude() {
  return magnitude;
}

/**
 * @brief Get the direction of the force vector.
 *
 * @return sf::Vector2<double> Direction of the force vector in world coordinates.
 */
sf::Vector2<double> Force::getDirection() {
  return direction;
}

/**
 * @brief Get the application point of the force vector.
 *
 * @return sf::Vector2f World coordinates where the vector "starts".
 */
sf::Vector2f Force::getApplicationPoint() {
  return applicationPoint;
}

/**
 * @brief Calculates the unit vector of the force vector.
 *
 * @return sf::Vector2f Unit vector of the force vector.
 */
sf::Vector2f Force::getUnitVector() {
  return sf::Vector2f((direction.x - applicationPoint.x) / magnitude,
    (direction.y - applicationPoint.y) / magnitude);
}

/**
 * @brief Get the vector shape of the force vector.
 *
 * @return sf::RectangleShape Line to visualize the force.
 */
sf::RectangleShape Force::getVectorShape() {
  return vectorShape;
}

/**
 * @brief Set the angle of the force vector.
 *
 * @param angle_ Angle of the force vector in radians.
 */
void Force::setAngle(float angle_) {
  angle = angle_;
}

/**
 * @brief Set the magnitude of the force vector.
 *
 * @param magnitude_ Module of the force vector.
 */
void Force::setMagnitude(float magnitude_) {
  magnitude = magnitude_;
}

/**
 * @brief Set the direction of the force vector.
 *
 * @param direction_ Direction of the force vector in world coordinates.
 */
void Force::setDirection(sf::Vector2<double> direction_) {
  direction = direction_;
}

/**
 * @brief Set the application point of the force vector.
 *
 * @param applicationPoint_ World coordinates where the vector "starts".
 */
void Force::setApplicationPoint(sf::Vector2f applicationPoint_) {
  applicationPoint = applicationPoint_;
}

/**
 * @brief Builds the vector shape of the force vector as a red sf::RectangleShape.
 */
void Force::buildVectorShape() {
  vectorShape = sf::RectangleShape(sf::Vector2f(150, 3.f));
  vectorShape.setOrigin(sf::Vector2f(0, 1.5f));
  vectorShape.setPosition(applicationPoint);
  vectorShape.setRotation(angle * RAD_TO_DEG);
  vectorShape.setFillColor(sf::Color::Red);
}

/**
 * @brief Sum of two forces, adding their directions.
 *
 * @param other Force to be added to this one.
 * @return Force result of the sum.
 */
Force Force::operator+(Force other) {
  return Force(direction + other.getDirection(), applicationPoint);
}

/**
 * @brief Subtraction of two forces, subtracting their directions.
 *
 * @param other Force to be subtracted from this one.
 * @return Force result of the subtraction.
 */
Force Force::operator-(Force other) {
  return Force(direction - other.getDirection(), applicationPoint);
}

/**
 * @brief Multiplication of a force by a scalar, multiplying its magnitude.
 *
 * @param scalar Scalar to multiply the magnitude of the force.
 * @return Force result of the multiplication.
 */
Force Force::operator*(float scalar) {
  sf::Vector2<double> newDirection(direction.x * scalar, direction.y * scalar);
  return Force(newDirection, applicationPoint);
}