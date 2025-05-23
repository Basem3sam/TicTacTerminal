#pragma once
#include "IGameUI.h"

class UISwitcher {
  static void initGetChoice(std::string &input);
  public:
  static bool initWindow(std::unique_ptr<IGameUI> &ui);
};