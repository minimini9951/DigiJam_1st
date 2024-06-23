#pragma once

struct HEXAGON;
struct CHARACTER;
struct EFHEXA;

void draw_walls(struct HEXAGON* hexagon, int value);
void draw_min_walls(struct HEXAGON* hexagon);
void draw_char(struct HEXAGON* hexagon, struct CHARACTER* character);
void draw_line(struct HEXAGON* hexagon);
void DrawRect_GameOver(CP_Color color1, CP_Color color2, float x, float y, float w, float h);