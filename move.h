#pragma once

struct HEXAGON;
struct CHARACTER;
struct EFHEXA;

void move_walls(struct HEXAGON* hexagon, int dir, float total_sec);
void move_char(struct CHARACTER* character);