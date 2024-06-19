#pragma once

struct HEXAGON;
struct CHARACTER;
struct EFHEXA;

void move_walls(struct HEXAGON* hexagon, int dir);
void move_char(struct HEXAGON* hexagon, struct CHARACTER* character);

