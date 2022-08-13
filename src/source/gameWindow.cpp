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
}