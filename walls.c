//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include "cprocessing.h"
#include "walls.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int walls_count()
{
	int random_number = CP_Random_RangeInt(1, 5);
	return random_number;
}

void walls_position(struct HEXAGON* hexagon, int random_number)
{
	for (int i = 0; i < random_number; i++)
	{
		int n = CP_Random_RangeInt(0, 5); // todo
		hexagon->arr[n] = 1;
	}
}

int move_to_angle(float move)
{
	if (move >= 0)
	{
		int m = (int)move / 360;
		return (int)move - 360 * m;
	}
	else
	{
		int m = -1 * (int)move / 360 + 1;
		return 360 * m + (int)move;
	}
}

int get_area_index(int angle)
{
	if (angle > 330 || angle < 30)
		return 0;
	else
	{
		int area = ((angle / 60) % 6);
		return area;
	}
}

int check_empty(struct HEXAGON* hexagon)
{
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		if (hexagon->arr[i] == 0)
		{
			count++;
			if (count == 6)
				return 0;
		}
	}
	return 1;
}

void make_wall(struct HEXAGON* hexagon, struct CHARACTER* character)
{
	int p_angle = move_to_angle(character->move);
	character->area = get_area_index(p_angle);
	int check_null = check_empty(hexagon);
	for (int i = 0; i < 6; i++)
	{
		if (character->area == i && hexagon->arr[i] == 0 && check_null)
		{
			hexagon->arr[i] = 1;
		}
	}
}

void check_walls(struct HEXAGON* hexagon, struct CHARACTER* character) // todo
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
				for (int j = 0; j < 6; j++)
					hexagon->arr[j] = 0;
			}
		}
	}
}

void create_hexa(struct HEXAGON* hexagon, float base, int efornot, int index)
{
	hexagon->angle = 0;
	const float d = 100;
	const float t = 1;

	hexagon->center.x = CP_System_GetDisplayHeight() / 2.0f;
	hexagon->center.y = CP_System_GetDisplayHeight() / 2.0f;

	if (!efornot)
	{
		hexagon->sec = 4 - index * t;
		hexagon->radius = base + index * d;
		hexagon->max_radius = base + 3 * d;
		hexagon->min_radius = base / 5;
		hexagon->amount = walls_count();
		walls_position(hexagon, hexagon->amount);
	}
	else
	{
		hexagon->radius = 0;
		hexagon->max_radius = 0;
		hexagon->min_radius = 0;
	}


	for (int j = 0; j < 6; j++)
	{
		hexagon->arr[j] = 0;
	}

}

struct HEXAGON* find_closest_hexa(struct HEXAGON* hexagon, int size)
{
	struct HEXAGON* res = NULL;
	
	for (int i = 0; i < size; i++)
	{
		//Not count empty
		if (!check_empty(&hexagon[i]))
			continue;

		if(res == NULL)
			res = &hexagon[i];

		if (hexagon[i].radius < res->radius)
		{
			res = &hexagon[i];
		}
	}

	return res;
}
