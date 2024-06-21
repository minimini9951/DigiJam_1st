#include "cprocessing.h"
#include "walls.h"
#include "move.h"
#include "collision.h"
#include "utils.h"
#include "draw.h"
#include"tetrishexagon.h"
#include "MainMenu.h"
#include <math.h>
#include <stdio.h>

struct HEXAGON g_wall_hexa[WallNumber];
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
	for (int i = 0; i < WallNumber; i++)
	{
		create_hexa(&g_wall_hexa[i], display_height / 2 * k, 0, i);
	}

	for (int i = 0; i < 6; i++)
	{
		create_hexa(&g_efhexa[i], 0, 1, i);
		create_hexa(&g_big_efhexa[i], 0, 1, i);
	}
	g_char.Alive = 1;//MEAN LIVE
	g_char.Time = 0; //ALive Time
	//create ehexa
	//create gbighexa
}

void game_update(void)
{
	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Color red = CP_Color_Create(255, 0, 0, 255);
	CP_Color green = CP_Color_Create(0, 255, 0, 255);
	CP_Color blue = CP_Color_Create(0, 0, 255, 255);
	CP_Color red_green = CP_Color_Create(255, 255, 0, 255);
	//CP_Color green_blue = CP_Color_Create(0, 255, 255, 255);

	CP_Graphics_ClearBackground(black);
	CP_Settings_Stroke(white);

	CP_Settings_TextAlignment(Horizontal, Vertical);
	CP_Settings_TextSize(160);

	//MOVE
	//FindClosestHexa
	if (g_char.Alive == 1) {

		g_char.Time += CP_System_GetDt();//시간을 계속 저장하는 함수

		move_char(&g_char);
		for (int i = 0; i < WallNumber; i++)
			move_walls(&g_wall_hexa[i], normal, 6);

		for (int i = 0; i < 6; i++)
		{
			if (check_count(&g_efhexa[i]) >= 1)
			{
				move_walls(&g_efhexa[i], blue_ef, 2);
				change_eftowall(&g_wall_hexa[0], WallNumber, &g_efhexa[i]);
			}

			if (check_count(&g_big_efhexa[i]) >= 1)
			{
				move_walls(&g_big_efhexa[i], big, 1);
			}

		}
		//Check if player collided //선수를 죽이다
		struct HEXAGON* close_wall = find_closest_hexa(g_wall_hexa, WallNumber);

		if (close_wall != NULL)
		{
			if (collision_check(close_wall, &g_char) == 1)
			{
				//End Game Code
				g_char.Alive = 0;//Die
			}
		}
	}

	//DRAW
	draw_line(&g_wall_hexa[0]);
	for (int i = 0; i < WallNumber; i++)
		draw_walls(&g_wall_hexa[i], 0);

	draw_min_walls(&g_wall_hexa[0]);
	draw_char(&g_wall_hexa[0], &g_char);

	for (int i = 0; i < 6; i++)
	{
		CP_Settings_Stroke(red_green);
		int count = check_count(&g_efhexa[i]);
		if (count >= 1 && count < 6)
			draw_walls(&g_efhexa[i], 1);

		//CP_Color col = CP_Color_Lerp(green, green_blue, g_big_efhexa[i].sec / 0.5f);
		CP_Settings_Stroke(green);
		draw_walls(&g_big_efhexa[i], 1);
	}


	if (g_char.Alive == 0)
	{
		//Game Over Text
		CP_Settings_Fill(white);//색상은 취향껏
		CP_Font_DrawText("Game", 540, 40);
		CP_Font_DrawText("Over", 540, 195);
		//Game Play Time 
		CP_Settings_TextSize(100);
		char buffer[16] = { 0 };
		CP_Settings_Fill(red);
		sprintf_s(buffer, 16, "%.2f", g_char.Time);
		CP_Font_DrawText("Alive Time:", 380, 400);
		CP_Font_DrawText(buffer, 720, 400);


		//Game Restart Button
		CP_Settings_TextSize(80);
		DrawRect_GameOver(blue, 390, 650, 300, 100);
		CP_Settings_Fill(white);
		CP_Font_DrawText("ReStart", 540, 690);

		CP_Settings_TextSize(70);
		DrawRect_GameOver(blue, 390, 800, 300, 100);
		CP_Settings_Fill(white);
		CP_Font_DrawText("MainMenu", 540, 850);

		if (CP_Input_MouseClicked()) 
		{
			if (CP_Input_GetMouseX() > 390 && CP_Input_GetMouseX() < 690 && CP_Input_GetMouseY() > 650 && CP_Input_GetMouseX() < 750) 
			{
				g_char.Alive = 1;
				CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
			}

			if (CP_Input_GetMouseX() > 390 && CP_Input_GetMouseX() < 690 && CP_Input_GetMouseY() > 800 && CP_Input_GetMouseX() < 900) 
			{
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			}


		}

	}
}

void game_exit(void)
{
}