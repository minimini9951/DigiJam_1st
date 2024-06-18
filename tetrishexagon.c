#include "cprocessing.h"
#include "walls.h"
#include "move.h"
#include "collision.h"
#include "utils.h"
#include <math.h>

#define PI 3.141592

int arr[] = { 1, 2, 3, 4, 5, 6 };
int n = sizeof(arr) / sizeof(arr[0]);

struct HEXAGON hexa;

void game_init(void)
{
	// CP_System_Fullscreen();
	int display_height = CP_System_GetDisplayHeight();
	CP_System_SetWindowSize(display_height, display_height);
	hexa.angle = 0;
	const float k = 0.75;

	hexa.center.x = CP_System_GetDisplayHeight() / 2.0f;
	hexa.center.y = CP_System_GetDisplayHeight() / 2.0f;

	hexa.radius = display_height / 2 * k;

	hexa.pos = NULL;
}

void game_update(void)
{
	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Graphics_ClearBackground(black);
	CP_Settings_Stroke(white);

	randomize(arr, n);
	int amount = walls_count();
	walls_position(&hexa, amount, arr);
	draw_walls(&hexa, amount, hexa.pos);
}

void game_exit(void)
{
	//free(pos);
}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
