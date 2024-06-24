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

struct Music button_music;
CP_Sound Button;

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

	myFont = CP_Font_Load("./Assets/Exo2-Regular.ttf");

	Button = CP_Sound_LoadMusic("./Assets/button-sound.mp3");

	image.logo = CP_Image_Load("./Assets/DigiPen_WHITE.png");
	button_music.buttonPlay = 0;
	image.sec = 0.0f;
	image.v = 0.0f;
}

void Main_Menu_Update(void) 
{
	image.sec += CP_System_GetDt();
	image.v += image.sec / 16;
	CP_Color color_red = CP_Color_Create(225, 0, 0, 255);//»¡°£»ö ÀúÀå
	CP_Color color_black = CP_Color_Create(30, 30, 30, 255);
	CP_Graphics_ClearBackground(color_black);
	CP_Color color_white = CP_Color_Create(225, 225, 225, 255);
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();


	if (mouseX > DisplayLength - (Base / 2) && mouseX < DisplayLength + (Base / 2) && mouseY>600 && mouseY < 700)
	{
		if (button_music.buttonPlay == 0) {
			CP_Sound_Play(Button);
			button_music.buttonPlay = 1;
		}
	}
	else if(mouseX > DisplayLength - (Base / 2) && mouseX < DisplayLength + (Base / 2) && mouseY>760 && mouseY < 860)
	{
		if (button_music.buttonPlay == 0) {
			CP_Sound_Play(Button);
			button_music.buttonPlay = 1;
		}
	}
	else
	{
		button_music.buttonPlay = 0;
	}

	if (CP_Input_MouseClicked())
	{
		if (mouseX > DisplayLength - (Base / 2) && mouseX < DisplayLength + (Base / 2) && mouseY>600 && mouseY < 700)
		{
			g_char.Alive = 1;
			CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		}

		if (mouseX > DisplayLength - (Base / 2) && mouseX < DisplayLength + (Base / 2) && mouseY>760 && mouseY < 860)
		{
			CP_Engine_Terminate();
		}
	}
	CP_Settings_TextSize(350);
	CP_Settings_Fill(color_red);
	CP_Font_DrawText("HEXRIS", DisplayLength, 300);

	CP_Settings_TextSize(80);
	DrawRect(color_red, DisplayLength-(Base/2), 600, Base, 100);
	CP_Settings_Fill(color_black);
	CP_Font_DrawText("Play", DisplayLength, 640);
	DrawRect(color_red, DisplayLength - (Base / 2), 760, Base, 100);
	CP_Settings_Fill(color_black);
	CP_Font_DrawText("Exit", DisplayLength, 800);
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_Fill(color_white);
}


void Main_Menu_Exit(void)
{
	CP_Sound_Free(&Button);
}
int main(void)
{
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	CP_Engine_Run();
	return 0;
}