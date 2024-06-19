#include "cprocessing.h"
#include "walls.h"
#include "move.h"
#include "collision.h"
#include "utils.h"
#include "draw.h"
#include"tetrishexagon.h"
#include <math.h>

int g_arr[6] = { 0, 1, 2, 3, 4, 5 };
int g_n = sizeof(g_arr) / sizeof(g_arr[0]); //6�̶�� �Ҹ�

struct HEXAGON g_hexa;
struct CHARACTER g_char;

void game_init(void)
{
	int display_height = CP_System_GetDisplayHeight();
	CP_System_SetWindowSize(display_height, display_height);
	g_hexa.angle = 0;
	const float k = 1;

	g_hexa.center.x = CP_System_GetDisplayHeight() / 2.0f;
	g_hexa.center.y = CP_System_GetDisplayHeight() / 2.0f;

	g_hexa.radius = display_height / 2 * k; //���÷����� ����
	g_hexa.max_radius = g_hexa.radius;
	g_hexa.min_radius = g_hexa.radius / 5;

	for (int i = 0; i < g_n; i++)
	{
		g_hexa.arr[i] = 0;
	}
	g_hexa.amount = walls_count();//������ amount�� 1~5�� �������� �ִ´�.
	walls_position(&g_hexa, g_hexa.amount); // ������ g_hexa����ü �� ��ü, ������ amount 1~5���� ���� �� ��ŭ �����ϰ�
	// ��ġ�� arr[]�� 0~5�� �������� �ְ� 1�� ��ȯ�� ���� ��Ų��
}

void game_update(void)
{
	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Graphics_ClearBackground(black);
	CP_Settings_Stroke(white);

	//g_hexa.angle += 5 * CP_System_GetDt();

	move_walls(&g_hexa);
	move_char(&g_hexa, &g_char);

	draw_line(&g_hexa);
	draw_walls(&g_hexa);
	draw_min_walls(&g_hexa);
	draw_char(&g_hexa, &g_char);
	collision_check(&g_hexa, &g_char);
}

void game_exit(void)
{
}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
