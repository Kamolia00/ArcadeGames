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

void Snake::draw(bool dead, Vector2 deathPos) const {
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

    // draw eyes on the head to distinguish it from the body
    if (!body.empty()) {
        Vector2 head = getHead();
        Vector2 dir = getDirection();
        // if death animation requested, use provided deathPos as head
        if (dead) {
            head = deathPos;
        }
        float cx = head.x * CELL_SIZE + OFFSET_X + CELL_SIZE/2.0f;
        float cy = head.y * CELL_SIZE + OFFSET_Y + CELL_SIZE/2.0f;

        // r
        float along = CELL_SIZE * 0.18f; // in front of center
        float perp  = CELL_SIZE * 0.18f; // side offset

        Vector2 e1 = {0,0}, e2 = {0,0};
        if (dir.x > 0.5f) { // moving right
            e1 = {cx + along, cy - perp};
            e2 = {cx + along, cy + perp};
        } else if (dir.x < -0.5f) { // moving left
            e1 = {cx - along, cy - perp};
            e2 = {cx - along, cy + perp};
        } else if (dir.y < -0.5f) { // moving up
            e1 = {cx - perp, cy - along};
            e2 = {cx + perp, cy - along};
        } else { // moving down (or default)
            e1 = {cx - perp, cy + along};
            e2 = {cx + perp, cy + along};
        }

        float eyeRadius = CELL_SIZE * 0.12f;
        if (!dead) {
            // white eye and small black pupil
            DrawCircleV(e1, eyeRadius, WHITE);
            DrawCircleV(e2, eyeRadius, WHITE);
            DrawCircleV(e1, eyeRadius * 0.45f, BLACK);
            DrawCircleV(e2, eyeRadius * 0.45f, BLACK);
        } else {
            // draw X for dead eyes
            float xr = eyeRadius;
            // left eye X
            DrawLineV({e1.x - xr, e1.y - xr}, {e1.x + xr, e1.y + xr}, RED);
            DrawLineV({e1.x - xr, e1.y + xr}, {e1.x + xr, e1.y - xr}, RED);
            // right eye X
            DrawLineV({e2.x - xr, e2.y - xr}, {e2.x + xr, e2.y + xr}, RED);
            DrawLineV({e2.x - xr, e2.y + xr}, {e2.x + xr, e2.y - xr}, RED);
        }
    }
}