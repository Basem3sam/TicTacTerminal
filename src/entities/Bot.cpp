#include "Bot.h"
#include <vector>
#include <cstdlib>

// Helper to get available moves
std::vector<short> getAvailableMoves(const char board[Board::MAX_HEIGHT][Board::MAX_WIDTH]) {
    std::vector<short> moves;
    for (short i = 0; i < Board::MAX_HEIGHT; ++i) {
        for (short j = 0; j < Board::MAX_WIDTH; ++j) {
            if (!(board[i][j] == 'X' || board[i][j] == 'O')) {
                moves.push_back(i * Board::MAX_WIDTH + j + 1);
            }
        }
    }
    return moves;
}

short Bot::decideMove(const char platform[Board::MAX_HEIGHT][Board::MAX_WIDTH]) {
    std::vector<short> moves = getAvailableMoves(platform);

    switch (difficulty) {
        case BotDifficulty::Easy:
            return moves[rand() % moves.size()];

        case BotDifficulty::Medium:
            // Simple strategy: center, corner, block win, etc. (to be implemented)
            return moves[0]; // placeholder

        case BotDifficulty::Hard:
            // Best move using minimax (to be implemented)
            return moves[0]; // placeholder
    }
    return moves[0]; // fallback
}
