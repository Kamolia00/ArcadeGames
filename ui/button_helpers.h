#ifndef BUTTON_HELPERS_H
#define BUTTON_HELPERS_H

#include "raylib.h"

namespace menu_ui {

inline Color ButtonFill(bool hovered) {
    return hovered ? Color{50, 150, 200, 255} : DARKBLUE;
}

inline void DrawMenuButton(const Rectangle& button, const char* label, int font_size, Color text_color = WHITE) {
    const Vector2 mouse = GetMousePosition();
    const bool hovered = CheckCollisionPointRec(mouse, button);
    const Rectangle fill = hovered
        ? Rectangle{button.x - 2, button.y - 2, button.width + 4, button.height + 4}
        : button;

    DrawRectangleRec(fill, ButtonFill(hovered));

    const int label_width = MeasureText(label, font_size);
    DrawText(label,
             fill.x + (fill.width - label_width) / 2,
             fill.y + (fill.height - font_size) / 2,
             font_size,
             text_color);
}

}

#endif
