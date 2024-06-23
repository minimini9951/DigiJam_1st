#include "cprocessing.h"
#include "walls.h"
#include "utils.h"

void InitializeColor(struct COLORS* color)
{
	int red = 0;
	int green = 0;
	int blue = 0;

	if (color->first == 0)
	{
		red = CP_Random_RangeInt(0, ColorMax);
		green = CP_Random_RangeInt(0, ColorMax - red);
		blue = ColorMax - red - green;
		color->start_color = CP_Color_Create(red, green, blue, 255);
		color->current_color = color->start_color;

		color->first = 1;
	}
	else
	{
		color->start_color = color->goal_color;
	}

	red = CP_Random_RangeInt(0, ColorMax);
	green = CP_Random_RangeInt(0, ColorMax - red);
	blue = ColorMax - red - green;
	color->goal_color = CP_Color_Create(red, green, blue, 255);
}

void make_wall_color(struct COLORS* color)
{
	if (color->first == 0)
	{
		InitializeColor(color);
	}
	else if (color->first == 1)
	{
		float frame = CP_System_GetDt();
		color->col_sec += frame;
		float v = CP_Math_ClampFloat(color->col_sec, 0, 1);

		color->current_color = CP_Color_Lerp(color->start_color, color->goal_color, v);
		
		if (color->col_sec >= 1)
		{
			color->col_sec = 0.0f;
			InitializeColor(color);
		}
	}
}