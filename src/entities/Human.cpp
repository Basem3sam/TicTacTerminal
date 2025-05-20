#include "Human.h"
#include "../utils/Validation.h"
#include <iostream>
#include <string>

short Human::nextId = 0;

Human::Human(): id(++nextId) ,name("NOTHING"), Player("Human") {}

Human::Human(const std::string& name) : id(++nextId), Player("Human"){
  setName(name);
}

void Human::setName(std::string name) {
if(Valid::isValidName(name))
  this->name = name;
else
  std::cout << "Invalid name! Name must only contain letters and spaces, and cannot be empty.\n";
}

short Human::getId() {
  return id;
}

std::string Human::getName() {
  return name;
}

void Human::setSymbol(char symbol) {
  Player::setSymbol(symbol);
}

int Human::getScore() {
  return Player::getScore();
}

char Human::getSymbol() {
  return Player::getSymbol();
}

void Human::incrementScore(){
  Player::incrementScore();
}

void Human::resetIdCounter() {
  nextId = 0;
}
