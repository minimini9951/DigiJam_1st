#pragma once

struct HEXAGON;
struct CHARACTER;
struct EFHEXA;

struct COLORS
{
	CP_Color start_color;
	CP_Color goal_color;
	CP_Color current_color;
	CP_Color big_current;
	CP_Color bright_current;

	int first;
	float col_sec;
	int v;
};

void make_wall_color(struct COLORS* color, struct RANDOMANGLE* angle);