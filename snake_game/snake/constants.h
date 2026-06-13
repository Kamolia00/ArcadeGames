#ifndef constants_h
#define constants_h

constexpr int CELL_SIZE = 20;
constexpr int GRID_WIDTH = 40;
constexpr int GRID_HEIGHT = 28;

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

constexpr int OFFSET_X = (WINDOW_WIDTH - GRID_WIDTH * CELL_SIZE) / 2;   // 240
constexpr int OFFSET_Y = (WINDOW_HEIGHT - GRID_HEIGHT * CELL_SIZE) / 2; // 80

#endif