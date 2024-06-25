#include "cprocessing.h"
#include "walls.h"
#include "move.h"
#include "collision.h"
#include "utils.h"
#include "draw.h"
#include"tetrishexagon.h"
#include "MainMenu.h"
#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

#include<sys/stat.h>
#include <sys/types.h>
int mkdir(const char* path, int mode);

struct HEXAGON g_wall_hexa[WallNumber];
struct HEXAGON g_efhexa[6];
struct HEXAGON g_big_efhexa[6];
struct CHARACTER g_char;
struct RANDOMANGLE g_angle;
struct COLORS g_colors;
struct Music music;
struct Speed wall_speed;
struct Image image;

int amplitude = 4;
int frequency = 2;
int offset = 6;

CP_Font myFont;
CP_TEXT_ALIGN_HORIZONTAL Horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL Vertical = CP_TEXT_ALIGN_V_MIDDLE;
CP_Sound mySound;


void game_init(void)
{
	myFont = CP_Font_Load("./Assets/Exo2-Regular.ttf");

	int display_height = CP_System_GetDisplayHeight();
	const float k = 1;
	CP_System_SetWindowSize(display_height, display_height);
	CP_System_SetWindowTitle("Hex_Ris");
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
	for (int i = 0; i < 6; i++)
		g_char.confusedCounters_arr[i] = 0;
	g_char.confused = 0;
	g_char.moveConfuse = 0;

	g_colors.first = 0;
	g_colors.col_sec = 0.0f;
	make_wall_color(&g_colors, &g_angle);

	wall_speed.wallspeed = 4;
	g_angle.rotation_Time = -1 * wall_speed.wallspeed; //-6은 처음대기시간. 변수로 바꿀것

	//Load music
	mySound = CP_Sound_LoadMusic("./Assets/Elektronomia - Sky High.mp3");
	music.isPlay = 0;
}
void game_update(void)
{
	
	//CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Color white = CP_Color_Create(225, 225, 225, 255);
	//CP_Color red = CP_Color_Create(255, 0, 0, 255);
	//CP_Color blue = CP_Color_Create(0, 0, 255, 255);
	//CP_Color red_green = CP_Color_Create(255, 255, 0, 255);

	//노래 재생부분
	
	if (music.isPlay==0) {
		CP_Sound_PlayAdvanced(mySound, 0.6f, 1.0f, TRUE, CP_SOUND_GROUP_1);
		//NCS사운드 부분
		music.isPlay = 1;
	}

	CP_Graphics_ClearBackground(g_colors.current_color);
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
		{
			move_walls(&g_wall_hexa[i], normal, wall_speed.wallspeed);// rotation_Time과 동일하게 할 것. 변수로 변경 대기시간 10초로 하기 위함
			//여기가 속도
		}

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
		//생존시간 부분
		CP_Settings_Fill(g_colors.bright_current);
		CP_Settings_TextSize(50);
		char buffer_AliveTime[16] = { 0 };
		sprintf_s(buffer_AliveTime, 16, "%.2f", g_char.total_Time);
		CP_Font_DrawText(buffer_AliveTime, 540, 540);
	}

	//DRAW
	make_wall_color(&g_colors, &g_angle);
	CP_Settings_Stroke(g_colors.bright_current);
	draw_line(&g_wall_hexa[0]);
	for (int i = 0; i < WallNumber; i++)
	{
		CP_Settings_Stroke(g_colors.inverse_current);
		float stroke_length = amplitude * cosf(g_char.total_Time * (float)M_PI * frequency) + offset;
		CP_Settings_StrokeWeight(stroke_length);
		draw_walls(&g_wall_hexa[i], 0);
	}

	draw_min_walls(&g_wall_hexa[0]);
	CP_Settings_StrokeWeight(2.0f);
	draw_char(&g_wall_hexa[0], &g_char);

	for (int i = 0; i < 6; i++)
	{
		CP_Settings_Stroke(g_colors.inverse_current);
		int count = check_count(&g_efhexa[i]);
		if (count >= 1 && count < 6)
		{
			CP_Settings_StrokeWeight(4.0f);
			draw_walls(&g_efhexa[i], 1);
		}

		CP_Settings_Stroke(g_colors.big_current);
		CP_Settings_StrokeWeight(5.0f);
		draw_walls(&g_big_efhexa[i], 1);
	}


	if (g_char.Alive == 0)
	{
		CP_Settings_TextSize(100);
		//성공(읽는 파트,쓰기 파트 성공), g_char.total_Time 게임 첫 스타트
		//FILE* fp;
		float value = 0.000f;
		char read_txt[16] = { 0 };//txt파일에 있는 값만 읽어서 저장하는 배열
		char BestRead[16] = { 0 };//갱신해야 할 값 저장하는  배열
		char PastBest[16] = { 0 };

		char* b;
		size_t S = 255;
		_dupenv_s(&b, &S, "USERPROFILE");
		char user[255];

		sprintf_s(user, 255, "%s\\Documents\\DigiPen", b);

		struct stat sfileInfo;

		//check directory exists or not
		if (stat(user, &sfileInfo) == -1)
		{
			mkdir(user, 0700);
			printf("[INFO] Directory Created: %s\n", user);
		}

		sprintf_s(user, 255, "%s\\Documents\\DigiPen\\HexRis", b);
		//check directory exists or not
		if (stat(user, &sfileInfo) == -1)
		{
			mkdir(user, 0700);
			printf("[INFO] Directory Created: %s\n", user);
		}

		sprintf_s(user, 255, "%s\\Documents\\DigiPen\\HexRis\\BestTime.txt", b);


		FILE* file_ptr = NULL;
		if (stat(user, &sfileInfo) == -1)
		{
			fopen_s(&file_ptr,user, "w");
			fclose(file_ptr);
		}
		fopen_s(&file_ptr, user, "r+");
		if (file_ptr != NULL)
		{

			if (fgets(read_txt, sizeof(read_txt), file_ptr) == 0)
			{
				fclose(file_ptr);
				fopen_s(&file_ptr, user, "w+");
				fprintf(file_ptr, "%.2f", value);
				fclose(file_ptr);
			}
			else
			{
				fgets(read_txt, sizeof(read_txt), file_ptr);
				g_char.Best_TimeTXT = (float)atof(read_txt);
				fclose(file_ptr);
			}
		}

		if (g_char.Best_TimeTXT<g_char.total_Time)
		{
			fopen_s(&file_ptr, user, "r+");

			if (file_ptr != NULL) 
			{
				fprintf_s(file_ptr, "%.2f", g_char.total_Time);
				fclose(file_ptr);
			}

			fopen_s(&file_ptr, user, "r+");
			if (file_ptr != NULL)
			{
				DrawRect_GameOver(g_colors.current_color, g_colors.bright_current, 150, 500, 680, 100);
				CP_Settings_Fill(white);
				fgets(BestRead, sizeof(BestRead), file_ptr);
				CP_Font_DrawText("Best Time:", 380, 550);
				CP_Font_DrawText(BestRead, 720, 550);
				fclose(file_ptr);
			}
		}
		else
		{
			//성공한 테스트 부분
			fopen_s(&file_ptr, user, "r+");
			if (file_ptr != NULL)
			{
				DrawRect_GameOver(g_colors.current_color, g_colors.bright_current, 150, 500, 680, 100);
				CP_Settings_Fill(white);
				fgets(PastBest, sizeof(PastBest), file_ptr);
				CP_Font_DrawText("Best Time:", 380, 550);
				CP_Font_DrawText(PastBest, 720, 550);
				fclose(file_ptr);
			}
		}



		//Game Over Text
		DrawRect_GameOver(g_colors.current_color, g_colors.bright_current, 390, 5, 300, 250);
		CP_Settings_Fill(white);//색상은 취향껏
		CP_Font_DrawText("Game", 540, 40);
		CP_Font_DrawText("Over", 540, 195);
		//Game Play Time 
		char buffer_totalTime[16] = { 0 };//현재 게임 플레이 하는 시간
		DrawRect_GameOver(g_colors.current_color, g_colors.bright_current, 150, 360, 680, 100);
		CP_Settings_Fill(white);
		sprintf_s(buffer_totalTime, 16, "%.2f", g_char.total_Time);//현재 게임 시간 저장
		CP_Font_DrawText("Alive Time:", 380, 400);
		CP_Font_DrawText(buffer_totalTime, 720, 400);


		//Game Restart Button
		CP_Settings_TextSize(80);
		DrawRect_GameOver(g_colors.current_color, g_colors.bright_current, 390, 650, 300, 100);
		CP_Settings_Fill(white);
		CP_Font_DrawText("ReStart", 540, 690);

		CP_Settings_TextSize(70);
		DrawRect_GameOver(g_colors.current_color, g_colors.bright_current, 390, 800, 300, 100);
		CP_Settings_Fill(white);
		CP_Font_DrawText("MainMenu", 540, 850);

		if (CP_Input_MouseClicked()) 
		{
			if (CP_Input_GetMouseX() > 390 && CP_Input_GetMouseX() < 690 && CP_Input_GetMouseY() > 650 && CP_Input_GetMouseX() < 750)
			{
				g_char.Alive = 1;
				music.isPlay = 0;
				CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
			}
			if (CP_Input_GetMouseX() > 390 && CP_Input_GetMouseX() < 690 && CP_Input_GetMouseY() > 800 && CP_Input_GetMouseX() < 900) 
			{
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			}


		}
		//키보드로 게임 시작, 메인메뉴
		if (CP_Input_KeyTriggered(KEY_SPACE))
		{
			g_char.Alive = 1;
			music.isPlay = 0;
			CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
		}
		if (CP_Input_KeyTriggered(KEY_ESCAPE))
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
	}
}

void game_exit(void)
{
	CP_Sound_Free(&mySound);
}