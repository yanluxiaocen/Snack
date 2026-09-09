#pragma once
#include "Snack.h"

constexpr int PLAY_WIDTH = 32;
constexpr int PLAY_HEIGHT = 16;

void draw(const Snack &snake, const Point &food, int score);