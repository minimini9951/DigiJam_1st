#pragma once

struct HEXAGON;
struct CHARACTER;

void draw_walls(struct HEXAGON* hexagon);
void draw_min_walls(struct HEXAGON* hexagon);
void draw_char(struct HEXAGON* hexagon, struct CHARACTER* character);
void draw_line(struct HEXAGON* hexagon);