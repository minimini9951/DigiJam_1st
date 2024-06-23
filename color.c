#include "cprocessing.h"
#include "walls.h"
#include "utils.h"
#include "color.h"

void InitializeColor(struct COLORS* color)
{
	int red = 0;
	int green = 0;
	int blue = 0;
	color->v = 50;

	if (color->first == 0)
	{
		red = CP_Random_RangeInt(0, ColorMax);
		green = CP_Random_RangeInt(0, ColorMax - red);
		blue = ColorMax - red - green;
		color->start_color = CP_Color_Create(red - color->v, green - color->v, blue - color->v, 255);
		color->current_color = color->start_color;
		color->big_current = CP_Color_Create(color->current_color.r + color->v / 5, color->current_color.g + color->v / 5, color->current_color.b + color->v / 5, color->current_color.a);
		color->bright_current = CP_Color_Create(color->current_color.r + color->v, color->current_color.g + color->v, color->current_color.b + color->v, color->current_color.a);

		color->first = 1;
	}
	else
	{
		color->start_color = color->goal_color;
	}

	red = CP_Random_RangeInt(0, ColorMax);
	green = CP_Random_RangeInt(0, ColorMax - red);
	blue = ColorMax - red - green;
	color->goal_color = CP_Color_Create(red - color->v, green - color->v, blue - color->v, 255);
}

void make_wall_color(struct COLORS* color, struct RANDOMANGLE* angle)
{
	if (color->first == 0)
	{
		InitializeColor(color);
	}
	else if (color->first == 1)
	{
		//if (angle->rotation_Time >= 10)
		{
			float frame = CP_System_GetDt();
			color->col_sec += frame;
			float v2 = CP_Math_ClampFloat(color->col_sec, 0, 1);
			color->current_color = CP_Color_Lerp(color->start_color, color->goal_color, v2);
			color->big_current = CP_Color_Create(color->current_color.r + color->v / 5, color->current_color.g + color->v / 5, color->current_color.b + color->v / 5, color->current_color.a);
			color->bright_current = CP_Color_Create(color->current_color.r + color->v, color->current_color.g + color->v, color->current_color.b + color->v, color->current_color.a);
			if (color->col_sec >= 5)
			{
				color->col_sec = 0.0f;
				InitializeColor(color);
			}
		}
		if (angle->rotation_Time >= 10)
		{
			angle->rotation_Time = 1;
		 }
	}
}
