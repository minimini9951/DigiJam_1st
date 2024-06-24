#pragma once

struct HEXAGON
{
	CP_Vector center;
	float min_radius;
	float max_radius;
	float radius;
	float angle;
	int amount; //not
	float sec; //육각형 시간 
	int arr[6]; //diff

};

struct CHARACTER
{
	int pos;
	int count;
	float move;
	int area;
	int Alive;//살아있는 판정

	float total_Time;
	float Best_TimeTXT;//텍스트파일의 값 받아오는 변수


	int copyCounter;
	int confusedCounter;
	int still_confused;
	int confusedCounters_arr[12];
	int confused; // 0, 1
	int moveConfuse;
};

struct RANDOMANGLE
{
	float rotation_Time;
	float random_angle;
};

enum wall_type
{
	blue_ef = 0,
	normal = 1,
	big = 2
};


struct Speed
{
	float wallspeed;
};

struct Music 
{
	int isPlay;
	int buttonPlay;
};


int walls_count();
void walls_position(struct HEXAGON* hexagon, int random_number);
int move_to_angle(float move);
int get_area_index(int angle);
int check_count(struct HEXAGON* hexagon);
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
#define ColorMax 180

extern struct HEXAGON g_wall_hexa[WallNumber];
extern struct HEXAGON g_efhexa[6];
extern struct HEXAGON g_big_efhexa[6];
extern struct CHARACTER g_char;
extern struct RANDOMANGLE g_angle;
extern struct COLORS g_colors;