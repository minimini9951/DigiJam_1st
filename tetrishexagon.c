#include "cprocessing.h"
#include "walls.h"
#include "move.h"
#include "collision.h"
#include "utils.h"
#include "draw.h"
#include"tetrishexagon.h"
#include "MainMenu.h"
#include "color.h"
#include <math.h>
#include <stdio.h>

struct HEXAGON g_wall_hexa[WallNumber];
struct HEXAGON g_efhexa[6];
struct HEXAGON g_big_efhexa[6];
struct CHARACTER g_char;
struct RANDOMANGLE g_angle;
struct COLORS colors;

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
	g_angle.random_angle = 60;
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
	g_char.total_Time = 0; //ALive Time

	g_char.copyCounter = 0;
	for(int i = 0; i < 6; i++)
		g_char.confusedCounters_arr[i] = 0;
	g_char.confused = 0;
	g_char.moveConfuse = 0;

	g_angle.rotation_Time = -6.0f; //-6은 처음대기시간. 변수로 바꿀것

	colors.first = 0;
	colors.col_sec = 0.0f;
	make_wall_color(&colors);
}

void game_update(void)
{
	//CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Color red = CP_Color_Create(255, 0, 0, 255);
	CP_Color green = CP_Color_Create(0, 255, 0, 255);
	CP_Color blue = CP_Color_Create(0, 0, 255, 255);
	CP_Color red_green = CP_Color_Create(255, 255, 0, 255);

	CP_Graphics_ClearBackground(colors.current_color);
	//make_wall_color();
	CP_Settings_Stroke(white);

	CP_Settings_TextAlignment(Horizontal, Vertical);
	CP_Settings_TextSize(160);

	//MOVE
	//FindClosestHexa
	if (g_char.Alive == 1) {

		g_char.total_Time += CP_System_GetDt();//시간을 계속 저장하는 함수

		rotate_wall(g_wall_hexa, &g_angle);
		rotate_wall(g_efhexa, &g_angle);
		rotate_wall(g_big_efhexa, &g_angle);

		move_char(&g_char);
		for (int i = 0; i < WallNumber; i++)
			move_walls(&g_wall_hexa[i], normal, 6); // rotation_Time과 동일하게 할 것. 변수로 변경 대기시간 10초로 하기 위함

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
	make_wall_color(&colors);
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
		sprintf_s(buffer, 16, "%.2f", g_char.total_Time);
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