#pragma once

struct HEXAGON
{
	CP_Vector center;
	float radius;
	float angle;
	int* pos;
};

int walls_count();
void walls_position(struct HEXAGON* hexa, int random_number, int arr[]);
void draw_walls(struct HEXAGON* hexa, int amount, int* pos);
void move_walls();
void make_wall();