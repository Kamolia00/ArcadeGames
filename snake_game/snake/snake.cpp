#include "snake.h"
#include "constants.h"
#include <vector>

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

bool Snake::checkSelfCollision() const {
    Vector2 head = getHead();
    for (size_t i = 0; i < body.size() - 1; ++i) {
        if (body[i].x == head.x && body[i].y == head.y) {
            return true;
        }
    }
    return false;
}
Vector2 Snake::getHead() const {
    return body.back();
}

const std::deque<Vector2> &Snake::getBody() const {
    return body;
}

Vector2 Snake::getDirection() const {
    return direction;
}

void Snake::draw() const {
    Color c;
    switch(getSymbol()) {
        case 'r': c = RED; break;
        case 'g': c = GREEN; break;
        case 'b': c = BLUE; break;
        default:  c = DARKGREEN;
    }

    for (auto& seg : body) {
        Rectangle rec = {
            seg.x * CELL_SIZE + OFFSET_X,
            seg.y * CELL_SIZE + OFFSET_Y,
            CELL_SIZE,
            CELL_SIZE
        };
        DrawRectangleRounded(rec, 0.3f, 6, c);
    }
}