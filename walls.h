#pragma once

struct HEXAGON
{
	CP_Vector center;
	float min_radius;
	float max_radius;
	float radius;
	float angle;
	int amount;
	float sec;
	int arr[6];
};

struct CHARACTER
{
	int pos;
	int count;
	float move;
	int area;
};

int walls_count();
void walls_position(struct HEXAGON* hexagon, int random_number);
void make_wall(struct HEXAGON* hexagon, struct CHARACTER* character);
void check_walls();


extern int g_arr[];
extern int g_n;