#include <iostream>
#include <webots/Robot.hpp>

constexpr int duration{1024};

int main() {
  webots::Robot controller;
  int i {0};
  while (controller.step(duration) != -1) {
    std::cout << i++ << std::endl;
  }
}