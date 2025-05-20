#include "Game.h"
#include "../utils/Validation.h"
#include "../utils/Foundation.h"
#include <iostream>

GameUI Game::UI;
Board Game::board;
Bot Game::BOT;
Human Game::singlePlayer;
std::array<std::unique_ptr<Player>, 2> Game::players;

void Game::addPlayer(int index, const PlayerInfo& info) {
  std::unique_ptr<Player> player;

  if (info.type == "human") {
    player = std::make_unique<Human>(info.name);
  } else if (info.type == "bot") {
    player = std::make_unique<Bot>(info.name);
  }

  player->setSymbol(info.symbol);
  players[index] = std::move(player);

  UI.slowPrint("Player \"" + players[index]->getName() + "\" added with symbol '" + players[index]->getSymbol() + "'", 100);
  UI.sleepMilliSec(900)
}


// Human Game::addPlayer(int playerNumber, char takenSymbol) {
//   std::string name;
//   char symbol;

//   system(CLEAR_COMMAND);
//   std::cout << "Enter name for Player " << playerNumber << ": ";
//   std::getline(std::cin, name);

//   while (!Valid::isValidName(name)) {
//     std::cout << "Invalid name. Please enter again: ";
//     std::getline(std::cin, name);
//   }

//   do {
//     std::cout << "Choose your symbol (X or O): ";
//     std::cin >> symbol;
//     symbol = toupper(symbol);
//     std::cin.ignore();

//     if (!Valid::isValidSymbol(symbol)) {
//       std::cout << "Invalid symbol. Only 'X' or 'O' allowed. Try again: ";
//       continue;
//     }

//     if (symbol == takenSymbol) {
//       std::cout << "Symbol already taken by another player. Choose a different one.\n";
//       continue;
//     }
//     break;
//   } while (true);

//   Human player(name);
//   player.setSymbol(symbol);

//   UI.slowPrint("Player \"" + player.getName() + "\" added with symbol '" + player.getSymbol() + "'", 80);
//   std::cout << std::endl;
//   UI.sleepMilliSec(1000);
//   return player;
// }

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
      PlayerInfo info1 = UI.promptPlayerInfo(1, '\0');
      addPlayer(0, info1);
      PlayerInfo info2 = UI.promptPlayerInfo(2, info1.symbol);
      addPlayer(1, info2);

      break;
    }
    case GameMode::SinglePlayer: {
      PlayerInfo info1 = UI.promptPlayerInfo(1, '\0');
      addPlayer(0, info1);

      char botSymbol = (info1.symbol == 'X') ? 'O' : 'X';
      PlayerInfo botInfo;
      botInfo.name = "BOT";
      botInfo.symbol = botSymbol;
      botInfo.type = "bot";

      addPlayer(1, botInfo);

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
    Player* player = players[turn % 2].get();

    currName = player->getName();
    currSymbol = player->getSymbol();

    std::cout << "=> " << currName << "'s turn (" << currSymbol << "). Enter a position (1-9): ";
    short move = Valid::askValidMove(board.platform);

    short row = (move - 1) / board.MAX_HEIGHT;
    short col = (move - 1) % board.MAX_WIDTH;

    board.platform[row][col] = currSymbol;

    if (Valid::isWin(board.platform, currSymbol)) {
      UI.printBoard(board.platform);
      player->incrementScore();
      UI.printWinMessage(*dynamic_cast<Human*>(player)); // Safe only if Human
      GameUI::sleepMilliSec(2000);
      break;
    }

    if (++turn == board.MAX_HEIGHT * board.MAX_WIDTH) {
      UI.printBoard(board.platform);
      break;
    }
  }
}
