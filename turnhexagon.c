#include "cprocessing.h"


void game_init(void)
{

}

void game_update(void)
{

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
