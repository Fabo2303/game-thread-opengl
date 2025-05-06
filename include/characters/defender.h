#ifndef DEFENDER_H
#define DEFENDER_H

#include <GL/freeglut.h>

class Defender {
public:
    Defender(int x);

    void moveRight(int xVelocity);
    void moveLeft(int xVelocity);
    void draw();
    int getXOffset() const;

private:
    int xOffset;
    void drawDefender();
};

#endif // DEFENDER_H
