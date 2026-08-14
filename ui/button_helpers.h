#ifndef BUTTON_HELPERS_H
#define BUTTON_HELPERS_H

#include "raylib.h"

namespace menu_ui {

constexpr float kReferenceWidth = 1280.0f;
constexpr float kReferenceHeight = 720.0f;

inline Rectangle ReferenceRect(float x, float y, float width, float height) {
    const float screen_width = static_cast<float>(GetScreenWidth());
    const float screen_height = static_cast<float>(GetScreenHeight());
    if (screen_width <= 0.0f || screen_height <= 0.0f) {
        return Rectangle{x, y, width, height};
    }

    const float scale_x = screen_width / kReferenceWidth;
    const float scale_y = screen_height / kReferenceHeight;
    const float scale = scale_x < scale_y ? scale_x : scale_y;
    const float offset_x = (screen_width - kReferenceWidth * scale) * 0.5f;
    const float offset_y = (screen_height - kReferenceHeight * scale) * 0.5f;

    return Rectangle{
        offset_x + x * scale,
        offset_y + y * scale,
        width * scale,
        height * scale
    };
}

inline float ReferenceScale() {
    const float screen_width = static_cast<float>(GetScreenWidth());
    const float screen_height = static_cast<float>(GetScreenHeight());
    if (screen_width <= 0.0f || screen_height <= 0.0f) {
        return 1.0f;
    }
    const float scale_x = screen_width / kReferenceWidth;
    const float scale_y = screen_height / kReferenceHeight;
    return scale_x < scale_y ? scale_x : scale_y;
}

inline Vector2 ReferenceOffset() {
    const float screen_width = static_cast<float>(GetScreenWidth());
    const float screen_height = static_cast<float>(GetScreenHeight());
    const float scale = ReferenceScale();
    return Vector2{
        (screen_width - kReferenceWidth * scale) * 0.5f,
        (screen_height - kReferenceHeight * scale) * 0.5f
    };
}

inline Vector2 ReferencePoint(float x, float y) {
    const float scale = ReferenceScale();
    const Vector2 offset = ReferenceOffset();
    return Vector2{offset.x + x * scale, offset.y + y * scale};
}

inline Vector2 ReferencePoint(Vector2 point) {
    return ReferencePoint(point.x, point.y);
}

inline Vector2 ReferenceMousePosition() {
    const Vector2 mouse = GetMousePosition();
    const Vector2 offset = ReferenceOffset();
    const float scale = ReferenceScale();
    if (scale <= 0.0f) {
        return mouse;
    }
    return Vector2{(mouse.x - offset.x) / scale, (mouse.y - offset.y) / scale};
}

inline float ReferenceLength(float value) {
    return value * ReferenceScale();
}

inline int ReferenceFontSize(int font_size) {
    const int scaled = static_cast<int>(font_size * ReferenceScale() + 0.5f);
    return scaled > 0 ? scaled : 1;
}

inline Rectangle ReferenceRect(const Rectangle& rect) {
    return ReferenceRect(rect.x, rect.y, rect.width, rect.height);
}

inline void SyncAudioButtonRects(Rectangle& mute_button, Rectangle& sfx_button) {
    mute_button = ReferenceRect(20, 660, 100, 40);
    sfx_button = ReferenceRect(140, 660, 120, 40);
}

inline Color ButtonFill(bool hovered) {
    return hovered ? Color{50, 150, 200, 255} : DARKBLUE;
}

inline void DrawTextRef(const char* text, float x, float y, int font_size, Color color) {
    const Vector2 point = ReferencePoint(x, y);
    DrawText(text, static_cast<int>(point.x), static_cast<int>(point.y), ReferenceFontSize(font_size), color);
}

inline void DrawTextCenteredRef(const char* text, float center_x, float y, int font_size, Color color) {
    const int scaled_font_size = ReferenceFontSize(font_size);
    const Vector2 point = ReferencePoint(center_x, y);
    DrawText(text, static_cast<int>(point.x - MeasureText(text, scaled_font_size) / 2.0f),
             static_cast<int>(point.y), scaled_font_size, color);
}

inline void DrawTextExRef(Font font, const char* text, Vector2 position, float font_size, float spacing, Color tint) {
    DrawTextEx(font, text, ReferencePoint(position), ReferenceLength(font_size), ReferenceLength(spacing), tint);
}

inline void DrawCircleRef(float center_x, float center_y, float radius, Color color) {
    DrawCircleV(ReferencePoint(center_x, center_y), ReferenceLength(radius), color);
}

inline void DrawCircleVRef(Vector2 center, float radius, Color color) {
    DrawCircleV(ReferencePoint(center), ReferenceLength(radius), color);
}

inline void DrawRectangleRef(float x, float y, float width, float height, Color color) {
    DrawRectangleRec(ReferenceRect(x, y, width, height), color);
}

inline void DrawRectangleLinesRef(float x, float y, float width, float height, Color color) {
    const Rectangle rect = ReferenceRect(x, y, width, height);
    DrawRectangleLines(static_cast<int>(rect.x), static_cast<int>(rect.y),
                       static_cast<int>(rect.width), static_cast<int>(rect.height), color);
}

inline void DrawRectangleRoundedRef(Rectangle rect, float roundness, int segments, Color color) {
    DrawRectangleRounded(ReferenceRect(rect), roundness, segments, color);
}

inline void DrawRectangleProRef(Rectangle rect, Vector2 origin, float rotation, Color color) {
    DrawRectanglePro(ReferenceRect(rect), Vector2{ReferenceLength(origin.x), ReferenceLength(origin.y)}, rotation, color);
}

inline void DrawTriangleRef(Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
    DrawTriangle(ReferencePoint(v1), ReferencePoint(v2), ReferencePoint(v3), color);
}

inline void DrawLineRef(float start_x, float start_y, float end_x, float end_y, Color color) {
    const Vector2 start = ReferencePoint(start_x, start_y);
    const Vector2 end = ReferencePoint(end_x, end_y);
    DrawLine(static_cast<int>(start.x), static_cast<int>(start.y),
             static_cast<int>(end.x), static_cast<int>(end.y), color);
}

inline void DrawLineExRef(Vector2 start, Vector2 end, float thick, Color color) {
    DrawLineEx(ReferencePoint(start), ReferencePoint(end), ReferenceLength(thick), color);
}

inline void DrawMenuBackdrop(const float star_x[], const float star_y[], const float star_size[],
                             int star_count, float rocket_x, float rocket_y) {
    for (int i = 0; i < star_count; i++) {
        DrawCircleRef(star_x[i], star_y[i], star_size[i], Color{255, 255, 255, 180});
    }
    DrawRectangleProRef(Rectangle{rocket_x, rocket_y, 40, 20}, Vector2{20, 10}, -25.0f, DARKGRAY);
    DrawTriangleRef(Vector2{rocket_x + 28, rocket_y - 8}, Vector2{rocket_x + 28, rocket_y + 8},
                    Vector2{rocket_x + 48, rocket_y}, RED);
    DrawTriangleRef(Vector2{rocket_x - 10, rocket_y - 5}, Vector2{rocket_x - 10, rocket_y + 5},
                    Vector2{rocket_x - 25, rocket_y}, ORANGE);
    DrawCircleRef(rocket_x + 10, rocket_y, 5, SKYBLUE);
}

inline void DrawMenuButton(const Rectangle& button, const char* label, int font_size, Color text_color = WHITE) {
    const Vector2 mouse = GetMousePosition();
    const bool hovered = CheckCollisionPointRec(mouse, button);
    const Rectangle fill = hovered
        ? Rectangle{button.x - 2, button.y - 2, button.width + 4, button.height + 4}
        : button;

    DrawRectangleRec(fill, ButtonFill(hovered));

    const int scaled_font_size = ReferenceFontSize(font_size);
    const int label_width = MeasureText(label, scaled_font_size);
    DrawText(label,
             fill.x + (fill.width - label_width) / 2,
             fill.y + (fill.height - scaled_font_size) / 2,
             scaled_font_size,
             text_color);
}

}

#endif
