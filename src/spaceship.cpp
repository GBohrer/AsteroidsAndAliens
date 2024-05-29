#include "spaceship.h"
#include <raylib.h>

Spaceship::Spaceship()
{
    x = 100;
    y = 100;
    speedX = 5;
    speedY = 5;
    radius = 15;
}

void Spaceship::Update()
{
    x += speedX;
    y += speedY;

    if (x + radius >= GetScreenWidth() || x - radius <= 0)
        speedX *= -1;

    if (y + radius >= GetScreenHeight() || y - radius <= 0)
        speedY *= -1;
}

void Spaceship::Draw()
{
    DrawCircle(x, y, radius, WHITE);
}