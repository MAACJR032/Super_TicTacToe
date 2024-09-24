#pragma once

#include <cstdint>

enum class GameState : uint8_t {
    MENU, CREDITS, NAME_INPUT, PLAYING, WAITING_INPUT, END_SCREEN
};