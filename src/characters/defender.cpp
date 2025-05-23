#include "../../include/characters/defender.h"
#include "../../include/utils/drawUtils.h"
#include <algorithm>

static const int vectorDefender[26][27] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 8, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0},
    {0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 7, 8, 8, 8, 7, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 6, 7, 8, 8, 8, 7, 6, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 5, 1, 0, 0, 6, 7, 8, 0, 8, 7, 6, 0, 0, 1, 5, 1, 0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0},
    {0, 1, 2, 1, 4, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 4, 1, 2, 1, 0},
    {0, 1, 2, 1, 1, 5, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 4, 1, 1, 2, 1, 0},
    {0, 1, 2, 1, 0, 1, 5, 1, 1, 2, 2, 1, 1, 2, 1, 1, 2, 2, 1, 1, 5, 1, 0, 1, 2, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 4, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 4, 1, 1, 0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0, 1, 1, 1, 5, 1, 1, 1, 1, 2, 1, 1, 1, 1, 5, 1, 1, 1, 0, 0, 1, 0, 0},
    {0, 0, 4, 0, 0, 1, 1, 1, 1, 4, 1, 1, 4, 4, 4, 1, 1, 4, 1, 1, 1, 1, 0, 0, 4, 0, 0},
    {0, 0, 5, 0, 0, 1, 1, 1, 0, 1, 1, 4, 5, 5, 5, 4, 1, 1, 0, 1, 1, 1, 0, 0, 5, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 4, 5, 5, 5, 5, 5, 4, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 4, 5, 5, 5, 4, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 1, 1, 4, 4, 4, 1, 1, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Defender::Defender(int x) : xOffset(x) {}

void Defender::moveRight(int xVelocity)
{
    xOffset = std::min(xOffset + xVelocity, 1320);
}

void Defender::moveLeft(int xVelocity)
{
    xOffset = std::max(xOffset - xVelocity, 0);
}

void Defender::draw()
{
    glPushMatrix();
    glTranslatef(static_cast<float>(xOffset), 0.0f, 0.0f);
    drawDefender();
    glPopMatrix();
}

void Defender::drawDefender()
{
    for (int i = 0; i < 26; ++i)
    {
        for (int j = 0; j < 27; ++j)
        {
            switch (vectorDefender[i][j])
            {
            case 1:
                glColor3f(0.0f, 0.0f, 0.0f);
                break;
            case 2:
                glColor3f(0.5f, 0.5f, 0.5f);
                break;
            case 4:
                glColor3f(1.0f, 0.0f, 1.0f);
                break;
            case 5:
                glColor3f(1.0f, 0.8f, 0.0f);
                break;
            case 6:
                glColor3f(1.0f, 0.0f, 0.0f);
                break;
            case 7:
                glColor3f(1.0f, 1.0f, 1.0f);
                break;
            case 8:
                glColor3f(1.0f, 1.0f, 0.0f);
                break;
            default:
                continue;
            }
            drawSquare(j, i);
        }
    }
}

int Defender::getXOffset() const
{
    return xOffset;
}
