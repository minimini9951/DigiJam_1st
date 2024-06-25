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

struct Image image;

void Logo_Init(void) 
{
	int display_height = CP_System_GetDisplayHeight();
	CP_System_SetWindowSize(display_height, display_height);
	CP_System_SetWindowTitle("Hex_Ris");
	image.logo = CP_Image_Load("./Assets/DigiPen_WHITE.png");
	image.sec = 0.0f;
	image.v = 0.0f;
	image.first = 0;
}

void Logo_Update(void)
{
	CP_Color color_black = CP_Color_Create(30, 30, 30, 255);
	CP_Graphics_ClearBackground(color_black);
	image.sec += CP_System_GetDt();
	image.v += image.sec / 16;
	if (image.sec <= 2)
	{
		CP_Image_Draw(image.logo, 540, 540, 1026, 249, (int)lerp(0, 255, image.v));
	}
	else 
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Logo_Exit(void) 
{
	CP_Image_Free(&image.logo);
}

int main(void)
{
	CP_Engine_SetNextGameState(Logo_Init, Logo_Update, Logo_Exit);
	CP_Engine_Run();
	return 0;
}