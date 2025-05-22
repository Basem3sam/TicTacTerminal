#include "../utils/Validation.h"
#include "../utils/TextUtils.h"
#include <iostream>
#include "Game.h"

Game::Game(IGameUI* ui) : UI(ui) {}

void Game::addPlayer(int index, const PlayerInfo& info) {
  std::unique_ptr<Player> player;

  switch(info.type) {
    case PlayerType::Human:
      player = std::make_unique<Human>(info.name);
      break;
    case PlayerType::Bot:
      player = std::make_unique<Bot>(info.name);
      break;
    default:
      std::cerr << "Error: Unknown player type '" << TextUtils::playerTypeToString(info.type) << "'\n";
      return; // or throw an exception, or handle gracefully
  }

  player->setSymbol(info.symbol);
  players[index] = std::move(player);

  if (players[index]) {
    UI->printPlayerAdded(*players[index]);
  } else {
    std::cerr << "Error: Failed to create player for index " << index << "\n";
  }
}

void Game::setup() {
  Human::resetIdCounter(); //reset static id's

  switch (UI->askGameMode()) {
    case GameMode::MultiPlayer: {
      PlayerInfo info1 = UI->promptPlayerInfo(1, '\0', true);
      addPlayer(0, info1);

      PlayerInfo info2 = UI->promptPlayerInfo(2, info1.symbol, true);
      addPlayer(1, info2);

      break;
    }
    case GameMode::SinglePlayer: {
      PlayerInfo info1 = UI->promptPlayerInfo(1, '\0', false);
      addPlayer(0, info1);

      char botSymbol = (info1.symbol == 'X') ? 'O' : 'X';
      PlayerInfo botInfo;
      botInfo.name = "BOT";
      botInfo.symbol = botSymbol;
      botInfo.type = PlayerType::Bot;
      std::cout << "\n";
      addPlayer(1, botInfo);
      break;
    }
    default:
      std::cerr << "Invalid mode.\n";
      break;
  }
}

void Game::multiPlay() {
  short turn = 0;
  board.reset();

  while (true) {
    UI->printBoard(board.platform);
    Player* player = players[turn % 2].get();
    char symbol = player->getSymbol();

    short move = UI->getPlayerMove(player->getName(), symbol, board.platform);
    short row = (move - 1) / Board::MAX_HEIGHT;
    short col = (move - 1) % Board::MAX_WIDTH;

    board.platform[row][col] = symbol;

    if (Valid::isWin(board.platform, symbol)) {
      UI->printBoard(board.platform);
      player->incrementScore();

      if (auto human = dynamic_cast<Human*>(player)) {
        UI->printWinMessage(*human);
      }

      TextUtils::sleepMilliSec(2000);
      break;
    }

    if (++turn == Board::MAX_HEIGHT * Board::MAX_WIDTH) {
      UI->printBoard(board.platform);
      UI->printDrawMessage();
      break;
    }
  }
}


void Game::loop() {
  UI->printWelcome();
  do {
    setup();
    multiPlay();
  } while (UI->wantPlay());
  UI->displayGameOver();
}