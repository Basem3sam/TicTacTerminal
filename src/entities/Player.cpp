#include "Player.h"
#include <stdexcept>
#include <cctype>

Player::Player(const std::string& rule) : RULE(rule) {}

void Player::setSymbol(char s) {
  s = static_cast<char>(toupper(s));
  if (s != 'X' && s != 'O') {
    throw std::invalid_argument("Invalid symbol. Must be 'X' or 'O'.");
  }
  symbol = s;
}

char Player::getSymbol() const {
  return symbol;
}

void Player::setScore(int s) {
  score = s;
}

int Player::getScore() const {
  return score;
}

void Player::incrementScore() {
  ++score;
}

std::string Player::getRule() const {
  return RULE;
}

void Player::setId(short id) {
  this->id = id;
}

short Player::getId() const {
  return id;
}
