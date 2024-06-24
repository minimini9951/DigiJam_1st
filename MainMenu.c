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

#define DisplayLength 540
#define Base 300
#define Height 100



CP_Font myFont;
CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;

struct Image image;

void DrawRect(CP_Color color, float x, float y, float w, float h) 
{
	CP_Settings_Fill(color);
	CP_Graphics_DrawRect(x, y, w, h);
}

void Main_Menu_Init(void)
{

	int display_height = CP_System_GetDisplayHeight();
	CP_System_SetWindowSize(display_height, display_height);
	myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	image.logo = CP_Image_Load("./Assets/DigiPen_WHITE.png");
	image.sec = 0.0f;
	image.v = 0.0f;
}

void Main_Menu_Update(void) 
{
	image.sec += CP_System_GetDt();
	image.v += image.sec / 16;
	CP_Color color_red = CP_Color_Create(225, 0, 0, 255);//빨간색 저장
	CP_Color color_black = CP_Color_Create(30, 30, 30, 255);
	CP_Graphics_ClearBackground(color_black);
	CP_Color color_white = CP_Color_Create(225, 225, 225, 255);
	if(image.sec <= 2)
		CP_Image_Draw(image.logo, 540, 540, 1026, 249, (int)lerp(0, 255, image.v));
	else
	{

		DrawRect(color_red, DisplayLength - (Base / 2), 500, Base, 100);
		CP_Settings_Fill(color_black);
		CP_Font_DrawText("Play", DisplayLength, 540);
		DrawRect(color_red, DisplayLength - (Base / 2), 650, Base, 100);
		CP_Settings_Fill(color_black);
		CP_Font_DrawText("Rules", DisplayLength, 690);
		DrawRect(color_red, DisplayLength - (Base / 2), 800, Base, 100);
		CP_Settings_Fill(color_black);
		CP_Font_DrawText("Exit", DisplayLength, 840);


		CP_Settings_TextAlignment(horizontal, vertical);
		CP_Settings_TextSize(80);

		float mouseX = CP_Input_GetMouseX();
		float mouseY = CP_Input_GetMouseY();

		if (CP_Input_MouseClicked())
		{
			if (mouseX > DisplayLength - (Base / 2) && mouseX < DisplayLength + (Base / 2) && mouseY>500 && mouseY < 600)
			{
				CP_Engine_SetNextGameState(game_init, game_update, game_exit);
			}

			if (mouseX > DisplayLength - (Base / 2) && mouseX < DisplayLength + (Base / 2) && mouseY>650 && mouseY < 750)
			{
				//룰 적는 곳(예비)
			}

			if (mouseX > DisplayLength - (Base / 2) && mouseX < DisplayLength + (Base / 2) && mouseY>800 && mouseY < 900)
			{
				CP_Engine_Terminate();
			}

		}

		CP_Settings_Fill(color_white);
	}
}


void Main_Menu_Exit(void)
{

}
int main(void)
{
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	CP_Engine_Run();
	return 0;
}