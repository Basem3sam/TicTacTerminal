#pragma once

#ifdef ENABLE_SFML_GUI

#include "IGameUI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <string>

class GameGUI : public IGameUI {
public:
    GameGUI();
    ~GameGUI() override = default;

    PlayerInfo promptPlayerInfo(int playerNumber, char takenSymbol, bool askForType = true) override;
    bool wantPlay() override;
    GameMode askGameMode() override;
    void printBoard(char board[Board::MAX_HEIGHT][Board::MAX_WIDTH]) override;
    void printWinMessage(Player& player) override;
    void printWelcome() override;
    void printPlayerAdded(const Player& player) override;
    void printDrawMessage() override;
    short getPlayerMove(const std::string& name, char symbol, const char board[3][3]) override;
    void printInvalidMoveMessage() override;
    void printInvalidInputMessage() override;
    void displayGameOver() override;

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text message;
    void drawBoard(const char board[3][3]);
    void displayMessage(const std::string& msg, int duration = 2000);
    
    char lastBoard[Board::MAX_HEIGHT][Board::MAX_WIDTH]{};
    bool hasLastBoard = false;
    BotDifficulty askBotDifficulty() override;
};

#endif