#include "force.hpp"

#define TRAILS_LENGTH 1024
#define TRAILS_DENSITY 0.5

class PhysicsObject {
  protected:
    sf::Shape* shape;
    int id;
    double mass;
    sf::Vector2f coordinates;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    std::vector<Force> forces;
    Force netForce;
    sf::VertexArray trails;
    bool hovered;
    bool targeted;
  public:
    PhysicsObject(int id_): id(id_) {}
    PhysicsObject(sf::Vector2f position_, double mass_, int id_);
    sf::Shape* getShape();
    sf::Vector2f getPosition();
    double getMass();
    sf::Vector2f getVelocity();
    sf::Vector2f getAcceleration();
    int getID();
    Force getNetForce();
    bool isHovered();
    bool isTargeted();
    sf::VertexArray getTrails();
    void setPosition(sf::Vector2f position_);
    void setMass(double mass_);
    void setVelocity(sf::Vector2f vel_);
    void setAcceleration(sf::Vector2f acc_);
    void setID(int id_);
    void updateTrails();
    float distanceTo(PhysicsObject other);
    float distanceTo(sf::Vector2f other);
    void applyForce(Force newForce);
    void calculateNetForce();
    Force calculateGravitalForce(PhysicsObject other);
    void clearForces();
    void setHover(bool hovered_);
    void setTarget(bool targeted_);
};