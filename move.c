#include "cprocessing.h"
#include "move.h"
#include "walls.h"
#include "utils.h"
#include "draw.h"

void move_walls(struct HEXAGON* hexagon, int dir)
{
	const float total_sec = 8.0f;
	float frame = CP_System_GetDt();
	
	hexagon->angle += 15 * CP_System_GetDt();

	//Reset hexa
	if (hexagon->sec >= total_sec)
	{
		hexagon->sec = 0;
		//random walls
		hexagon->amount = walls_count();
		//reset the hex arr
		for (int i = 0; i < 6; i++)
			hexagon->arr[i] = 0;

		walls_position(hexagon, hexagon->amount);
	}
	else
	{
		hexagon->sec += frame;
		float v = CP_Math_ClampFloat(hexagon->sec / total_sec, 0, 1);
		if(dir)
			hexagon->radius = lerp(hexagon->max_radius, hexagon->min_radius, v);
		else
			hexagon->radius = lerp(hexagon->min_radius, hexagon->max_radius, v);
	}
}

void move_char(struct HEXAGON* hexagon, struct CHARACTER* character)
{
	if (CP_Input_KeyTriggered(KEY_LEFT))
	{
		character->pos = 1;
		character->count++;
	}
	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		character->pos = -1;
		character->count--;
	}
	if (character->pos == -1)
	{
		character->move -= CP_System_GetDt() * 600;
		if (character->move <= 60 * character->count)
		{
			character->pos = 0;
			character->move = 60.0f * character->count;
			make_wall(hexagon, character);
			check_walls(hexagon, character);
		}
	}
	if (character->pos == 1)
	{
		character->move += CP_System_GetDt() * 600;
		if (character->move >= 60 * character->count)
		{
			character->pos = 0;
			character->move = 60.0f * character->count;
			make_wall(hexagon, character);
			check_walls(hexagon, character);
			//move_efwalls(efhexa);
		}
	}
}