#include "../include/gameWindow.hpp"
#include "Platform/Platform.hpp"

GameWindow::GameWindow() {
  // Creating Windows' window
  util::Platform platform;
  float screenScalingFactor = platform.getScreenScalingFactor(getSystemHandle());
  create(sf::VideoMode(1920.f * screenScalingFactor,
      1080.f * screenScalingFactor), "Hydrae");
  ::ShowWindow(getSystemHandle(), SW_MAXIMIZE);
  requestFocus();
  platform.setIcon(getSystemHandle());

  // Creating background
  sf::RectangleShape background;
  background.setFillColor(sf::Color(3, 6, 46));

  // Initializing views
  gameView = getDefaultView();
  hudView = getDefaultView();
}

void GameWindow::zoom(float factor) {
  gameView.zoom(factor);
  setView(gameView);
}

void GameWindow::move(sf::Vector2f deltaPosition) {
  gameView.setCenter(gameView.getCenter() + deltaPosition);
  setView(gameView);
}

void GameWindow::loadDebugHud() {
  setView(hudView);
  sf::Font font;
  sf::Text text;
  if (!font.loadFromFile("./content/UbuntuMono-Regular.ttf")) {
    std::cout << "Error loading font" << std::endl;
  } else {
    text.setFont(font);
    text.setString("Hello World");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
    draw(text);
  }
  setView(gameView);
}