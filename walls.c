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
		int n = CP_Random_RangeInt(0, 5);
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

void make_wall(struct HEXAGON* hexagon, struct CHARACTER* character)
{
	int p_angle = move_to_angle(character->move);
	character->area = get_area_index(p_angle);
	printf("%d %d %d %d %d %d   %d %f\n", hexagon->arr[0], hexagon->arr[1], hexagon->arr[2], hexagon->arr[3], hexagon->arr[4], hexagon->arr[5], character->area, character->move);
	for (int i = 0; i < 6; i++)
	{
		if (character->area == i && hexagon->arr[i] == 0)
		hexagon->arr[i] = 1;
	}
}

void check_walls(struct HEXAGON* hexagon, struct CHARACTER* character)
{
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		if (hexagon->arr[i] == 1)
		{
			count++;
			if (count == 6)
			{
				for (int j = 0; j < 6; j++)
					hexagon->arr[j] = 0;
			}
		}
	}
}
