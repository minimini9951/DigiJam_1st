#include "cprocessing.h"
#include "walls.h"
#include "move.h"
#include "collision.h"
#include "utils.h"
#include "draw.h"
#include"tetrishexagon.h"
#include "MainMenu.h"
#include <math.h>

struct HEXAGON g_wall_hexa[4];
struct HEXAGON g_efhexa[6];
struct HEXAGON g_big_efhexa[6];
struct CHARACTER g_char;

CP_Font myFont;
CP_TEXT_ALIGN_HORIZONTAL Horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL Vertical = CP_TEXT_ALIGN_V_MIDDLE;

void DrawRect_GameOver(CP_Color color, float x, float y, float w, float h)
{
	CP_Settings_Fill(color);
	CP_Graphics_DrawRect(x, y, w, h);
}


void game_init(void)
{
	myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");

	int display_height = CP_System_GetDisplayHeight();
	const float k = 1;
	CP_System_SetWindowSize(display_height, display_height);
	for (int i = 0; i < 4; i++)
	{
		create_hexa(&g_wall_hexa[i], display_height / 2 * k, 0, i);
	}

	for (int i = 0; i < 6; i++)
	{
		create_hexa(&g_efhexa[i], 0, 1, i);
		create_hexa(&g_big_efhexa[i], 0, 1, i);
	}
	g_char.Alive = 1;//MEAN LIVE

	//create ehexa
	//create gbighexa
}

void game_update(void)
{
	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Color blue = CP_Color_Create(0, 0, 255, 255);
	CP_Color red = CP_Color_Create(255, 0, 0, 255);
	CP_Graphics_ClearBackground(black);
	CP_Settings_Stroke(white);

	CP_Settings_TextAlignment(Horizontal, Vertical);
	CP_Settings_TextSize(160);


	//MOVE
	//플레이어가 살아있는 경우에만 이동
	//플레이어가 살아있는지 죽었는지 확인할려고 Alive 변수로 확인
	//Move 자체가 멈추는 기능(g_char가 살아있으면 1, 죽으면 0)
	//살아있는 판정은 collision_check로 반환해서 값을 암
	if (g_char.Alive == 1) {
		for (int i = 0; i < 4; i++)
			move_walls(&g_wall_hexa[i], 1);

		//FindClosestHexa
		struct HEXAGON* close_wall = find_closest_hexa(g_wall_hexa, 4);
		move_char(close_wall, &g_char);
		for (int i = 0; i < 6; i++)
			move_walls(&g_efhexa[i], 0);


		//Check if player collided //선수를 죽이다
		if (collision_check(close_wall, &g_char) == 1)
		{
			//End Game Code
			g_char.Alive = 0;//Die
		}
	}

	//DRAW
	draw_line(&g_wall_hexa[0]);
	for (int i = 0; i < 4; i++)
		draw_walls(&g_wall_hexa[i]);

	draw_min_walls(&g_wall_hexa[0]);
	draw_char(&g_wall_hexa[0], &g_char);

	for (int i = 0; i < 6; i++)
	{
		CP_Settings_Stroke(blue);
		draw_walls(&g_efhexa[i]);

		CP_Settings_Stroke(red);
		draw_walls(&g_big_efhexa[i]);	
	}


	if (g_char.Alive == 0)
	{
		//Game Over Text
		CP_Settings_Fill(white);//색상은 취향껏
		CP_Font_DrawText("Game", 540, 40);
		CP_Font_DrawText("Over", 540, 195);
		//Game Play Time 

		//Game Restart Button
		CP_Settings_TextSize(80);
		DrawRect_GameOver(blue, 390, 650, 300, 100);
		CP_Settings_Fill(white);
		CP_Font_DrawText("ReStart", 540, 690);

	}
}

void game_exit(void)
{
}


/*
int main(void)
{
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	//CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
*/