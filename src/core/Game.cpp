#include "Game.h"
#include "../utils/Validation.h"
#include <iostream>

GameUI Game::UI;
Board Game::board;
Bot Game::BOT;
Human Game::singlePlayer;
std::pair<Human, Human> Game::players;

Human Game::addPlayer(int playerNumber, char takenSymbol) {
  std::string name;
  char symbol;

  system(CLEAR_COMMAND);
  std::cout << "Enter name for Player " << playerNumber << ": ";
  std::getline(std::cin, name);

  while (!Valid::isValidName(name)) {
    std::cout << "Invalid name. Please enter again: ";
    std::getline(std::cin, name);
  }

  do {
    std::cout << "Choose your symbol (X or O): ";
    std::cin >> symbol;
    symbol = toupper(symbol);
    std::cin.ignore();

    if (!Valid::isValidSymbol(symbol)) {
      std::cout << "Invalid symbol. Only 'X' or 'O' allowed. Try again: ";
      continue;
    }

    if (symbol == takenSymbol) {
      std::cout << "Symbol already taken by another player. Choose a different one.\n";
      continue;
    }
    break;
  } while (true);

  Human player(name);
  player.setSymbol(symbol);

  UI.slowPrint("Player \"" + player.getName() + "\" added with symbol '" + player.getSymbol() + "'", 80);
  std::cout << std::endl;
  UI.sleepMilliSec(1000);
  return player;
}

void Game::loop() {
  UI.printWelcome();
  do {
    setup();
    multiPlay();
  } while (UI.wantPlayUI());
}

void Game::setup() {
  Human::resetIdCounter(); //reset static id's

  switch (UI.askGameMode()) {
    case GameMode::MultiPlayer: {
      Human p1 = addPlayer(1);
      Human p2 = addPlayer(2, p1.getSymbol());
      players = std::make_pair(p1, p2);
      break;
    }
    case GameMode::SinglePlayer: {
      singlePlayer = addPlayer(1);
      std::cout << "still in progress...";
      // BOT = addBot();
      break;
    }
    default:
      std::cout << "Invalid mode.\n";
      break;
  }
}

void Game::multiPlay() {
  std::string currName;
  char currSymbol;
  short turn = 0;

  board.reset();

  while (true) {
    UI.printBoard(board.platform);
    Human* player = (turn % 2 == 0) ? &players.first : &players.second;

    currName = player->getName();
    currSymbol = player->getSymbol();

    std::cout << "=> " << currName << "'s turn (" << currSymbol << "). Enter a position (1-9): ";
    short move = Valid::askValidMove(board.platform);

    short row = (move - 1) / 3;
    short col = (move - 1) % 3;

    board.platform[row][col] = currSymbol;

    if (Valid::isWin(board.platform, currSymbol)) {
      UI.printBoard(board.platform);
      player->incrementScore();
      UI.printWinMessage(*player);
      GameUI::sleepMilliSec(2000);
      break;
    }

    if (++turn == 9) {
      UI.printBoard(board.platform);
      break;
    }
  }
}
