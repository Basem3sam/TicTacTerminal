#include "Foundation.h"

Board::Board() {
  reset();
}

void Board::reset() {
  char cell = '1';
  for (int i = 0; i < MAX_HEIGHT; ++i) {
    for (int j = 0; j < MAX_WIDTH; ++j) {
      platform[i][j] = cell++;
    }
  }
}
