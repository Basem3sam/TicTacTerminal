#include "GameGUI.h"
#include "../utils/Validation.h"
#include "../utils/TextUtils.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <sstream>
#include <iostream>

GameGUI::GameGUI() : window(sf::VideoMode(600, 700), "Tic-Tac-Toe") {
    if(!font.loadFromFile("media/arial.ttf")){
      std::cerr << "Error: Failed to load font media/arial.ttf\n";
    }
    message.setFont(font);
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::White);
    message.setPosition(10, 560);
}

void GameGUI::printWelcome() {
  displayMessage("Welcome to Tic-Tac-Toe!");
}

GameMode GameGUI::askGameMode() {
  // For simplicity, default to multiplayer in GUI
  return GameMode::MultiPlayer;
}

BotDifficulty GameGUI::askBotDifficulty() {
  displayMessage("Bot difficulty set to Medium (default)", 2000);
  return BotDifficulty::Medium;
}

PlayerInfo GameGUI::promptPlayerInfo(int playerNumber, char takenSymbol, bool askForType) {
  PlayerInfo info;

  // Simple default naming
  info.name = "Player " + std::string(playerNumber == 1 ? "One" : "Two");

  // Assign symbol: pick opposite of takenSymbol or fallback
  if (takenSymbol == '\0') {
    info.symbol = 'X';
  } else {
    info.symbol = (takenSymbol == 'X') ? 'O' : 'X';
  }

  // Assign type based on flag
  if (askForType) {
    // GUI currently doesn't support type selection UI — assume human
    info.type = PlayerType::Human;
  } else {
    info.type = PlayerType::Bot;
  }

  displayMessage(info.name + " assigned symbol '" + info.symbol + "' (" + TextUtils::playerTypeToString(info.type) + ")", 2000);

  return info;
}

bool GameGUI::wantPlay() {
  return false; // For now, return false to end game after one play
}

void GameGUI::printPlayerAdded(const Player& player) {
    displayMessage(player.getName() + " joined with symbol " + player.getSymbol());
}

void GameGUI::printWinMessage(Player& player) {
    displayMessage(player.getName() + " wins!");
}

void GameGUI::printDrawMessage() {
    displayMessage("It's a draw!");
}

void GameGUI::printInvalidMoveMessage() {
    displayMessage("Invalid move!", 1000);
}

void GameGUI::printInvalidInputMessage() {
    displayMessage("Invalid input!", 1000);
}

short GameGUI::getPlayerMove(const std::string& name, char symbol, const char board[3][3]) {
    drawBoard(board);
    window.display();
    displayMessage(name + "'s turn (" + symbol + ")");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / 200;
                int y = event.mouseButton.y / 200;
                
                if (x < 0 || x >= 3 || y < 0 || y >= 3) continue;

                short move = y * 3 + x + 1;
                if (Valid::isValidMove(board, move))
                    return move;
                else
                    printInvalidMoveMessage();
            }
        }
    }
    return -1;
}

void GameGUI::printBoard(char board[Board::MAX_HEIGHT][Board::MAX_WIDTH]) {
  for (int i = 0; i < Board::MAX_HEIGHT; ++i)
    for (int j = 0; j < Board::MAX_WIDTH; ++j)
      lastBoard[i][j] = board[i][j];
  hasLastBoard = true;

  drawBoard(board);
  window.display();
}

void GameGUI::drawBoard(const char board[3][3]) {
    window.clear(sf::Color::Black);

    // Draw grid lines
    sf::RectangleShape line(sf::Vector2f(600, 5));
    line.setFillColor(sf::Color::White);

    // Horizontal lines
    for (int i = 1; i < 3; ++i) {
        line.setPosition(0, i * 200);
        window.draw(line);
    }

    // Vertical lines
    line.setSize(sf::Vector2f(5, 600));
    for (int i = 1; i < 3; ++i) {
        line.setPosition(i * 200, 0);
        window.draw(line);
    }

    // Only draw symbols if board is valid
    if (board) {
        sf::Text symbol;
        symbol.setFont(font);
        symbol.setCharacterSize(100);
        symbol.setFillColor(sf::Color::White);

        for (int i = 0; i < Board::MAX_HEIGHT; ++i) {
            for (int j = 0; j < Board::MAX_WIDTH; ++j) {
                char c = board[i][j];
                if (c == 'X' || c == 'O') {
                    symbol.setString(c);
                    symbol.setPosition(j * 200 + 70, i * 200 + 50);
                    window.draw(symbol);
                }
            }
        }
    }
}


void GameGUI::displayMessage(const std::string& msg, int duration) {
  if (!window.isOpen()) return;

  if (hasLastBoard)
    drawBoard(lastBoard);
  else
    window.clear(sf::Color::Black);

    // Clear message area
    sf::RectangleShape messageBackground(sf::Vector2f(600, 90));
    messageBackground.setFillColor(sf::Color::Black);
    messageBackground.setPosition(0, 610);
    window.draw(messageBackground);

    // Redraw separator line
    sf::RectangleShape separator(sf::Vector2f(600, 2));
    separator.setFillColor(sf::Color::White);
    separator.setPosition(0, 610); // Just below board
    window.draw(separator);

    // Set & draw message
    message.setPosition(10, 620); // Clearly below grid
    message.setString(msg);
    window.draw(message);
    window.display();

    TextUtils::sleepMilliSec(duration);
}

void GameGUI::displayGameOver() {
    if (!window.isOpen()) return;
    
    // Prepare text
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over\nEngine created by Basem Esam");
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::White);
    
    // Center the text in the window
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.width / 2, textRect.height / 2);
    gameOverText.setPosition(600 / 2, 700 / 2); // Center of window
    
    // Clear, Draw and display
    window.clear(sf::Color::Black);
    window.draw(gameOverText);
    window.display();

    // Keep window alive & responsive for 3 seconds
    sf::Clock clock;
    while (window.isOpen() && clock.getElapsedTime().asSeconds() < 3.f) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }
        // small sleep to avoid busy-loop
        sf::sleep(sf::milliseconds(50));
    }

    // Finally, close the window
    window.close();
}
