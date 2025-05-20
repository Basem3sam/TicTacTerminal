#include "Player.h"
#include <stdexcept>

Player::Player(const std::string& RULE) : RULE(RULE) {}

void Player::setScore(int score) {
  this->score = score;
}

void Player::setSymbol(char symbol) {
  symbol = toupper(symbol);
  if (symbol != 'X' && symbol != 'O')
    throw std::invalid_argument("Invalid symbol.");
  this->symbol = symbol;
}

void Player::incrementScore() {
  score++;
}

int Player::getScore() const {
  return score;
}

char Player::getSymbol() const {
  return symbol;
}

std::string Player::getRule() const {
  return RULE;
}
