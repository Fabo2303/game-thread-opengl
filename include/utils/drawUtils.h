#ifndef DRAW_UTILS_H
#define DRAW_UTILS_H

#include <string>

const float WHITE_COLOR[3] = {1.0f, 1.0f, 1.0f};
const float BLACK_COLOR[3] = {0.0f, 0.0f, 0.0f};

void drawSquare(float x, float y, float size = 3.0f);

void drawText(float x, float y, const std::string& text, const float color[3] = WHITE_COLOR);

void drawLevel(float x, float y, int level);

#endif
