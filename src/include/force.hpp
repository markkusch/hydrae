#define GRAV_CONST 6.67e-11
#define RAD_TO_DEG 57.295779513
#define PI 3.14159265359

class Force {
  private:
    float magnitude;                  // Module.
    float angle;                      // Calculated relative to the X-Axis in radians.
    sf::Vector2<double> direction;    // Direction relative to the application point.
    sf::Vector2f applicationPoint;    // Coordinates where the vector "starts".
    sf::RectangleShape vectorShape;   // Line to visualize the force.
  public:
    Force(): magnitude(0), angle(0), direction(0,0), applicationPoint(0,0) {}
    Force(sf::Vector2<double> direction_, sf::Vector2f applicationPoint_);
    Force(float angle_, float magnitude_, sf::Vector2f applicationPoint_);
    float getAngle();
    float getMagnitude();
    sf::Vector2<double> getDirection();
    sf::Vector2f getApplicationPoint();
    sf::Vector2f getUnitVector();
    sf::RectangleShape getVectorShape();
    void setAngle(float angle_);
    void setMagnitude(float magnitude_);
    void setDirection(sf::Vector2<double> direction_);
    void setApplicationPoint(sf::Vector2f applicationPoint_);
    void buildVectorShape();
    Force operator+(Force other);
    Force operator-(Force other);
    Force operator*(float scalar);
};