#include "cprocessing.h"
#include "walls.h"
#include "move.h"
#include "collision.h"
#include "utils.h"
#include "draw.h"
#include"tetrishexagon.h"
#include <math.h>

struct HEXAGON g_wall_hexa[WallNumber];
struct HEXAGON g_efhexa[6];
struct HEXAGON g_big_efhexa[6];
struct CHARACTER g_char;

void game_init(void)
{
	int display_height = CP_System_GetDisplayHeight();
	const float k = 1;
	CP_System_SetWindowSize(display_height, display_height);
	for (int i = 0; i < WallNumber; i++)
	{
		create_hexa(&g_wall_hexa[i], display_height / 2 * k, 0, i);
	}

	for (int i = 0; i < 6; i++)
	{
		create_hexa(&g_efhexa[i], 0, 1, i);
		create_hexa(&g_big_efhexa[i], 0, 1, i);
	}
	//create ehexa
	//create gbighexa

}

#include <stdio.h>
void PrintArr(struct HEXAGON* hex)
{
	for(int i = 0; i < 6 ;i++)
	{
		printf("%d ", hex->arr[i]);
	}
	printf("\n");
}

void game_update(void)
{
	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Color blue = CP_Color_Create(0, 0, 255, 255);
	CP_Color red = CP_Color_Create(255, 0, 0, 255);
	CP_Graphics_ClearBackground(black);
	CP_Settings_Stroke(white);


	//MOVE
	//FindClosestHexa
	struct HEXAGON* close_wall = find_closest_hexa(g_wall_hexa, WallNumber);
	move_char(close_wall, &g_char);
	for (int i = 0; i < WallNumber; i++)
		move_walls(&g_wall_hexa[i], 1, 4);

	for (int i = 0; i < 6; i++)
	{
		move_walls(&g_efhexa[i], 0, 2);
		move_walls(&g_big_efhexa[i], 0, 1);
		change_eftowall(&g_wall_hexa[0], WallNumber, &g_efhexa[i]);

	}
	

	//collision_check(close_wall, &g_char);



	//DRAW
	draw_line(&g_wall_hexa[0]);
	for (int i = 0; i < WallNumber; i++)
		draw_walls(&g_wall_hexa[i]);

	draw_min_walls(&g_wall_hexa[0]);
	draw_char(&g_wall_hexa[0], &g_char);

	for (int i = 0; i < 6; i++)
	{
		CP_Settings_Stroke(blue);
		draw_walls(&g_efhexa[i]);
		//DEBUGPRINT
		PrintArr(&g_efhexa[i]);

		CP_Color col = CP_Color_Lerp(red, blue, g_big_efhexa[i].sec / 0.5f);
		CP_Settings_Stroke(col);
		draw_walls(&g_big_efhexa[i]);
	}
	printf("------------------------ \n");
}

void game_exit(void)
{
}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
