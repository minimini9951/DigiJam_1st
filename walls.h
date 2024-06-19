#pragma once

struct HEXAGON
{
	CP_Vector center;
	float min_radius;
	float max_radius;
	float radius;
	float angle;
	int amount; //not
	float sec;
	int arr[6]; //diff
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
int move_to_angle(float move);
int get_area_index(int angle);
int check_empty(struct HEXAGON* hexagon);
void make_wall(struct HEXAGON* hexagon, struct CHARACTER* character);
void check_walls(struct HEXAGON* hexagon, struct CHARACTER* character);
void create_hexa(struct HEXAGON* hexagon, float base, int efornot, int index);
struct HEXAGON* find_closest_hexa(struct HEXAGON* hexagon, int size);