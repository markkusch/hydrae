#include "force.hpp"

class PhysicsObject {
  protected:
    sf::Shape* shape;
    int id;
    float mass;
    sf::Vector2f coordinates;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    std::vector<Force> forces;
    Force netForce;
    bool hovered;
    bool targeted;
  public:
    PhysicsObject(int id_): id(id_) {}
    PhysicsObject(sf::Vector2f position_, float mass_, int id_);
    sf::Shape* getShape();
    sf::Vector2f getPosition();
    float getMass();
    sf::Vector2f getVelocity();
    sf::Vector2f getAcceleration();
    int getID();
    Force getNetForce();
    bool isHovered();
    bool isTargeted();
    void setPosition(sf::Vector2f position_);
    void setMass(float mass_);
    void setVelocity(sf::Vector2f vel_);
    void setAcceleration(sf::Vector2f acc_);
    void setID(int id_);
    float distanceTo(PhysicsObject other);
    void applyForce(Force newForce);
    void calculateNetForce();
    Force calculateGravitalForce(PhysicsObject other);
    void clearForces();
    void setHover(bool hovered_);
    void setTarget(bool targeted_);
};