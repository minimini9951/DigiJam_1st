//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include "cprocessing.h"
#include "walls.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>


//벽 카운트 
int walls_count()
{
	int random_number = CP_Random_RangeInt(1, 5); //주어진 두 값과 같거나 그 사이에 있는 임의의 부동 소수점을 반환합니다.
	//random_number 1~5값을 반환해준다
	return random_number;
}

void walls_position(struct HEXAGON* hexagon, int random_number)
{
	for (int i = 0; i < random_number; i++)
	{
		int n = CP_Random_RangeInt(0, 5); //n에 0~5값의 랜덤 값을 넣고 
		hexagon->arr[n] = 1; //육각형의 arr에서 0~5의 배열을 1로 반환(0은 없다는 뜻이고 1은 있다는 뜻)
	}
}

int move_to_angle(float move)
{
	if (move >= 0)
	{
		int m = (int)move / 360;
		return (int)move - 360 * m; //정방향
	}
	else
	{
		int m = -1 * (int)move / 360 + 1;//반대 방향
		return 360 * m + (int)move;
	}
}

int get_area_index(int angle) //
{
	if (angle > 330 || angle < 30)
		return 0;
	else
	{
		int area = ((angle / 60) % 6);
		return area;
	}
}

int check_count(struct HEXAGON* hexagon)
{
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		if (hexagon->arr[i] == 1)
		{
			count++;
		}
	}
	return count;
}

void make_wall(struct HEXAGON* hexagon, int area)
{
	int check_null = check_count(hexagon);
	for (int i = 0; i < 6; i++)
	{
		if (area == i && hexagon->arr[i] == 0 && check_null >= 1)
		{
			hexagon->arr[i] = 1;
		}
	}
}

void check_walls(struct HEXAGON* hexagon) // todo
{
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		if (hexagon->arr[i] == 1)
		{
			count++;
			if (count == 6)
			{
				// efx alive = 1

				struct HEXAGON* empty_hexa = find_empty_hexa(g_big_efhexa, 6);
				if (empty_hexa != NULL)
					change_bigeftowall(&g_wall_hexa[0], WallNumber, empty_hexa);

				set_empty(hexagon);
			}
		}
	}
}

void set_empty(struct HEXAGON* hexagon)
{
	for (int i = 0; i < 6; i++)
	{
		hexagon->arr[i] = 0;
	}
}

void create_hexa(struct HEXAGON* hexagon, float base, int efornot, int index)
{
	hexagon->angle = 0;
	const float d = 90;
	const float t = 1;

	hexagon->center.x = CP_System_GetDisplayHeight() / 2.0f;
	hexagon->center.y = CP_System_GetDisplayHeight() / 2.0f;

	if (!efornot)
	{
		hexagon->sec = /*WallNumber - */index * t;
		hexagon->radius = base + index * d;
		hexagon->max_radius = base + 6 * d;
		hexagon->min_radius = base / 6;
		hexagon->amount = walls_count();
		walls_position(hexagon, hexagon->amount);
	}
	else
	{
		hexagon->radius = 0;
		hexagon->max_radius = 0;
		hexagon->min_radius = 0;
	}

	set_empty(hexagon);
}

struct HEXAGON* find_closest_hexa(struct HEXAGON* hexagon, int size)
{
	struct HEXAGON* res = NULL;
	
	for (int i = 0; i < size; i++)
	{
		//Not count empty
		if (check_count(&hexagon[i]) == 0)
			continue;

		if (res == NULL)
		{
			if(hexagon[i].radius > hexagon[i].min_radius * 1.25f)
				res = &hexagon[i];
		}
		else if (hexagon[i].radius < res->radius && hexagon[i].radius > hexagon[i].min_radius * 1.25f) //radius has to be > player
		{
			res = &hexagon[i];
		}
	}

	return res;
}

struct HEXAGON* find_empty_hexa(struct HEXAGON* hexagon, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (check_count(&hexagon[i]) == 0)
			return &hexagon[i];
	}

	return NULL;
}


void make_effect(int area)
{
	struct HEXAGON* empty_hexa = find_empty_hexa(g_efhexa, 6);
	if (empty_hexa == NULL)
		return;

	empty_hexa->radius = g_wall_hexa[0].min_radius;
	empty_hexa->min_radius = g_wall_hexa[0].min_radius;
	empty_hexa->max_radius = g_wall_hexa[0].max_radius;

	for (int i = 0; i < 6; i++)
	{
		empty_hexa->arr[i] = 0;
	}
	empty_hexa->arr[area] = 1;
	empty_hexa->sec = 0;
}

void change_eftowall(struct HEXAGON* hexagon_arr, int size, struct HEXAGON* hexagon)
{
	//get closest
	struct HEXAGON* closest_hexa = find_closest_hexa(hexagon_arr, size);

	if (closest_hexa == NULL)
		return;

	//check if we arrived to it
	if (closest_hexa->radius <= hexagon->radius)
	{
		//for each 1 in the hex arr, create wall
		//set a wall
		for (int i = 0; i < 6; i++)
		{
			if (hexagon->arr[i] == 1)
			{
				make_wall(closest_hexa, i);
				check_walls(closest_hexa);
			}
		}
		//reset the effect to empty
		set_empty(hexagon);
		hexagon->sec = 0;
	}
}

void change_bigeftowall(struct HEXAGON* hexagon_arr, int size, struct HEXAGON* hexagon)
{
	struct HEXAGON* closest_hexa = find_closest_hexa(hexagon_arr, size);

	if (closest_hexa == NULL)
		return;

	hexagon->radius = closest_hexa->radius;
	hexagon->min_radius = closest_hexa->radius;
	hexagon->max_radius = closest_hexa->radius;

	for (int i = 0; i < 6; i++)
	{
		hexagon->arr[i] = 1;
	}
}