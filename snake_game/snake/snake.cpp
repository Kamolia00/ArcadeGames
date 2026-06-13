#include "snake.h"
Snake::Snake()
    : Player(), isGrowing(false), direction({1, 0})
{
   body.push_back({10, 10});
   body.push_back({11, 10});
   body.push_back({12, 10});
}
Snake::Snake(std::string name, char symbol)
    : Player(name, symbol), isGrowing(false), direction({1, 0})
{
   body.push_back({10, 10});
   body.push_back({11, 10});
   body.push_back({12, 10});
}
void Snake::move() {
    Vector2 newHead = body.back();
    newHead.x += direction.x;
    newHead.y += direction.y;

    body.push_back(newHead);

    if (!isGrowing) {
        body.pop_front();
    } else {
        isGrowing = false;
    }
}

void Snake::setDirection(Vector2 newDirection) {
    if (newDirection.x == -direction.x && newDirection.y == -direction.y)
        return; // Prevent reversing direction
    direction = newDirection;
}
void Snake::grow() {
    isGrowing = true;
}
void Snake::reset() {
    body.clear();
    body.push_back({10, 10});
    body.push_back({11, 10});
    body.push_back({12, 10});
    direction = {1, 0};
    isGrowing = false;
}