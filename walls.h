#pragma once

struct HEXAGON
{
	CP_Vector center;
	float min_radius;
	float max_radius;
	float radius;
	float angle;
	int amount; //not
	float sec; //À°°¢Çü ½Ã°£ 
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
void make_wall(struct HEXAGON* hexagon, int area);
void check_walls(struct HEXAGON* hexagon);
void set_empty(struct HEXAGON* hexagon);
void create_hexa(struct HEXAGON* hexagon, float base, int efornot, int index);
struct HEXAGON* find_closest_hexa(struct HEXAGON* hexagon, int size);
struct HEXAGON* find_empty_hexa(struct HEXAGON* hexagon, int size);
void make_effect(int area);
void change_eftowall(struct HEXAGON* hexagon_arr, int size, struct HEXAGON* hexagon);
void change_bigeftowall(struct HEXAGON* hexagon_arr, int size, struct HEXAGON* hexagon);

#define WallNumber 4

extern struct HEXAGON g_wall_hexa[WallNumber];
extern struct HEXAGON g_efhexa[6];
extern struct HEXAGON g_big_efhexa[6];