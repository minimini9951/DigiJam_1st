#include "cprocessing.h"
#include "walls.h"
#include <stdlib.h>
#include <math.h>

int walls_count()
{
	int random_number = CP_Random_RangeInt(1, 5);
	return random_number;
}

void walls_position(struct HEXAGON* hexagon, int random_number, int arr[])
{
	int* new_arr = (int*)malloc(sizeof(int) * random_number);
	for (int i = 0; i < random_number; i++)
	{
		*(new_arr + i) = arr[i];
	}

	if(hexagon->pos != NULL)
		free(hexagon->pos);

	hexagon->pos = new_arr;
}

void draw_walls(struct HEXAGON* hexagon, int amount, int* pos)
{
	for (int i = 0; i < amount; i++)
	{
		float x1 = hexagon->center.x + hexagon->radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * (pos[i] - 1)));
		float y1 = hexagon->center.y + hexagon->radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * (pos[i] - 1)));
		float x2 = hexagon->center.x + hexagon->radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * (pos[i])));
		float y2 = hexagon->center.y + hexagon->radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * (pos[i])));

		CP_Graphics_DrawLine(x1, y1, x2, y2);
	}
}

void move_walls()
{
}

void make_wall()
{
}
