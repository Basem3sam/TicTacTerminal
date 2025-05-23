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
      player = std::make_unique<Bot>(info.name, info.difficulty);
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

GameMode Game::setup() {
  Human::resetIdCounter(); //reset static id's
  GameMode mode = UI->askGameMode();
  switch (mode) {
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
      botInfo.difficulty = UI->askBotDifficulty();  // <-- Ask user here

      std::cout << "\n";
      addPlayer(1, botInfo);
      break;
    }
    case GameMode::Quit:
      break;
    default:
      std::cerr << "Invalid mode.\n";
      break;
  }
  return mode;
}

void Game::multiPlay() {
  short turn = 0;
  board.reset();

  while (true) {
    UI->printBoard(board.platform);
    Player* player = players[turn % 2].get();
    char symbol = player->getSymbol();
    short move;

    if (player->getRule() == "Bot") {
      if (auto bot = dynamic_cast<Bot*>(player)) {
        move = bot->decideMove(board.platform);
      } else {
        std::cerr << "Error: Player claims to be a bot but isn't.\n";
        break;
      }
    } else {
      move = UI->getPlayerMove(player->getName(), symbol, board.platform);
    }

    short row = (move - 1) / Board::MAX_HEIGHT;
    short col = (move - 1) % Board::MAX_WIDTH;
    board.platform[row][col] = symbol;

    if (Valid::isWin(board.platform, symbol)) {
      UI->printBoard(board.platform);
      player->incrementScore();

      // Show correct win message
      if (player->getRule() == "Bot") {
        if (auto bot = dynamic_cast<Bot*>(player)) {
          UI->printWinMessage(*bot);
        }
      } else {
        if (auto human = dynamic_cast<Human*>(player)) {
          UI->printWinMessage(*human);
        }
      }

      TextUtils::sleepMilliSec(2000);
      break;
    } else { TextUtils::sleepMilliSec(500); }

    if (++turn == Board::MAX_HEIGHT * Board::MAX_WIDTH) {
      UI->printBoard(board.platform);
      UI->printDrawMessage();
      break;
    }
  }
}


void Game::singlePlay() {
  short turn = 0;
  board.reset();

  Player* human = players[0].get();
  Player* bot = players[1].get();

  while (true) {
    UI->printBoard(board.platform);
    Player* current = (turn % 2 == 0) ? human : bot;
    char symbol = current->getSymbol();

    short move = -1;

    if (auto humanPlayer = dynamic_cast<Human*>(current)) {
      move = UI->getPlayerMove(humanPlayer->getName(), symbol, board.platform);
    } else if (auto botPlayer = dynamic_cast<Bot*>(current)) {
      move = botPlayer->decideMove(board.platform);
      TextUtils::sleepMilliSec(100);
    }

    if (move == -1) continue;

    short row = (move - 1) / Board::MAX_HEIGHT;
    short col = (move - 1) % Board::MAX_WIDTH;
    board.platform[row][col] = symbol;

    if (Valid::isWin(board.platform, symbol)) {
      UI->printBoard(board.platform);
      current->incrementScore();

      // Dynamically cast to handle win message appropriately
      if (auto humanWinner = dynamic_cast<Human*>(current)) {
        UI->printWinMessage(*humanWinner);
      } else if (auto botWinner = dynamic_cast<Bot*>(current)) {
        UI->printWinMessage(*botWinner);
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


bool Game::play() {
  UI->printWelcome();
  do {
    GameMode mode = setup();

    if (mode == GameMode::Quit) {
      return false; // User quit before playing
    }

    switch (mode) {
      case GameMode::SinglePlayer:
        singlePlay();
        break;
      case GameMode::MultiPlayer:
        multiPlay();
        break;
      default:
        break;
    }

  } while (UI->wantPlay());

  UI->displayGameOver();
  return true;
}
