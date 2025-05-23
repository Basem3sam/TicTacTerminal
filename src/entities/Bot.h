#pragma once
#include "Player.h"
#include "../utils/BotDifficulty.h"
#include "../utils/Foundation.h"

class Bot : public Player {
    std::string name;
    BotDifficulty difficulty;

public:
    Bot(const std::string& name = "BOT", BotDifficulty difficulty = BotDifficulty::Easy)
        : Player("Bot"), name(name), difficulty(difficulty) {}

    std::string getName() const override { return name; }

    BotDifficulty getDifficulty() const { return difficulty; }

    short getId() const override { return 0; }

    // Add logic for bot's move decision
    short decideMove(const char platform[Board::MAX_HEIGHT][Board::MAX_WIDTH]);
};
