#include "../include/gameWindow.hpp"
#include "Platform/Platform.hpp"

/**
 * @brief Construct a new GameWindow::GameWindow object, creates the background color
 * and initializes the views.
 */
GameWindow::GameWindow() {
  util::Platform platform;
  float screenScalingFactor = platform.getScreenScalingFactor(getSystemHandle());
  create(sf::VideoMode(1920.f * screenScalingFactor,
      1080.f * screenScalingFactor), "Hydrae");
  ::ShowWindow(getSystemHandle(), SW_MAXIMIZE);
  requestFocus();
  platform.setIcon(getSystemHandle());

  sf::RectangleShape background;
  background.setFillColor(sf::Color(3, 6, 46));

  gameView = getDefaultView();
  hudView = getDefaultView();
}

/**
 * @brief Zooms the camera in or out.
 *
 * @param factor Factor by which the camera is zoomed.
 */
void GameWindow::zoom(float factor) {
  gameView.zoom(factor);
  setView(gameView);
}

/**
 * @brief Moves the camera.
 *
 * @param deltaPosition Distance in (x, y) by which the camera has moved.
 */
void GameWindow::move(sf::Vector2f deltaPosition) {
  gameView.setCenter(gameView.getCenter() + deltaPosition);
  setView(gameView);
}

/**
 * @brief Loads the debug HUD and shows the targeted object data if available.
 *
 * @param targetedObject Object to display its data.
 */
void GameWindow::loadDebugHud(PhysicsObject targetedObject) {
  setView(hudView);
  sf::Font font;
  sf::Text title, mousePos, objectData;
  if (!font.loadFromFile("./content/UbuntuMono-Regular.ttf")) {
    std::cout << "Error loading font" << std::endl;
  } else {
    title.setFont(font);
    title.setString("Debug Mode");
    title.setCharacterSize(24);
    title.setPosition(10, 10);
    title.setStyle(sf::Text::Bold);

    mousePos.setFont(font);
    mousePos.setString("Mouse Position: " + std::to_string(sf::Mouse::getPosition(*this).x)
      + ", " + std::to_string(sf::Mouse::getPosition(*this).y));
    mousePos.setCharacterSize(16);
    mousePos.setPosition(10, 40);

    if (targetedObject.getID() != -1) {
      objectData.setFont(font);
      objectData.setString("Targeted Object: \n\tID: " + std::to_string(targetedObject.getID()) + "\n\tPosition: "
        + std::to_string(targetedObject.getPosition().x) + ", " + std::to_string(targetedObject.getPosition().y)
        + "\n\tMass: " + std::to_string(targetedObject.getMass()) + "\n\tVelocity: "
        + std::to_string(targetedObject.getVelocity().x) + ", " + std::to_string(targetedObject.getVelocity().y)
        + "\n\tAcceleration: " + std::to_string(targetedObject.getAcceleration().x) + ", " + std::to_string(targetedObject.getAcceleration().y)
        + "\n\tNet Force direction: " + std::to_string(targetedObject.getNetForce().getDirection().x) + ", " + std::to_string(targetedObject.getNetForce().getDirection().y)
        + "\n\tNet Force magnitude: " + std::to_string(targetedObject.getNetForce().getMagnitude())
        + "\n\tNet Force Angle: " + std::to_string(targetedObject.getNetForce().getAngle() * RAD_TO_DEG));
      objectData.setCharacterSize(16);
      objectData.setPosition(10, 70);
      draw(objectData);
    }
    draw(title);
    draw(mousePos);
  }
  setView(gameView);
}