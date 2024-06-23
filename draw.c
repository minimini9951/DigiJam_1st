#include "cprocessing.h"
#include "walls.h"
#include <math.h>

void draw_walls(struct HEXAGON* hexagon, int isefwall)
{
	for (int i = 0; i < 6; i++)
	{
		if (hexagon->arr[i] == 1)
		{
			float x1 = hexagon->center.x + hexagon->radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * i));
			float y1 = hexagon->center.y - hexagon->radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * i));
			float x2 = hexagon->center.x + hexagon->radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * (i + 1)));
			float y2 = hexagon->center.y - hexagon->radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * (i + 1)));
			CP_Graphics_DrawLine(x1, y1, x2, y2);
		}
	}
}

void draw_min_walls(struct HEXAGON* hexagon)
{
	for (int i = 0; i < 6; i++)
	{
		float x1 = hexagon->center.x + hexagon->min_radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * i));
		float y1 = hexagon->center.y - hexagon->min_radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * i ));
		float x2 = hexagon->center.x + hexagon->min_radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * i + 60));
		float y2 = hexagon->center.y - hexagon->min_radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * i + 60));

		CP_Graphics_DrawLine(x1, y1, x2, y2);
	}
}

void draw_char(struct HEXAGON* hexagon, struct CHARACTER* character)
{
	float multiply = 1.2f;
    float circle_x = hexagon->center.x + hexagon->min_radius * multiply * cosf(CP_Math_Radians(60 + hexagon->angle + character->move));
	float circle_y = hexagon->center.y - hexagon->min_radius * multiply * sinf(CP_Math_Radians(60 + hexagon->angle + character->move));
	CP_Graphics_DrawCircle(circle_x, circle_y, 15);

}

void draw_line(struct HEXAGON* hexagon)
{
	for (int i = 0; i < 6; i++)
	{
		float x1 = hexagon->center.x + hexagon->min_radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * i));
		float y1 = hexagon->center.y - hexagon->min_radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * i));
		float x2 = hexagon->center.x + hexagon->max_radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * i));
		float y2 = hexagon->center.y - hexagon->max_radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * i));

		CP_Graphics_DrawLine(x1, y1, x2, y2);
	}
}

void DrawRect_GameOver(CP_Color color1,CP_Color color2, float x, float y, float w, float h)
{
	CP_Color lerp = CP_Color_Lerp(color1, color2, 0.5f);
	CP_Settings_Fill(lerp);
	CP_Graphics_DrawRect(x, y, w, h);
}