#pragma once

struct HEXAGON;
struct CHARACTER;
struct EFHEXA;
struct RANDOMANGLE;

void rotate_wall(struct HEXAGON* hexagon, struct RANDOMANGLE* angle);
void move_walls(struct HEXAGON* hexagon, int dir, float total_sec);
void move_char(struct CHARACTER* character);
void confused(struct CHARACTER* character);
