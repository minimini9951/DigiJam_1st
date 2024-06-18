#pragma once

struct HEXAGON;
struct CHARACTER;

void move_walls(struct HEXAGON* hexagon);
//void move_char();
void move_char(struct HEXAGON* hexagon, struct CHARACTER* character);

