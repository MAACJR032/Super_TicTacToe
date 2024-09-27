
#pragma once

#include <cstdint>

enum class Status : uint8_t {
    EMPTY, X, O, TIE
};

enum class Line : uint8_t {
    ROW1, ROW2, ROW3,
    COLUMN1, COLUMN2, COLUMN3,  
    DIAGONAL1, DIAGONAL2, EMPTY
};