#pragma once

void DrawRect_GameOver(CP_Color color1, CP_Color color2, float x, float y, float w, float h);
void AliveTimeText(CP_Color color, char buffer[], float time, float x, float y);
void game_init(void);
void game_update(void);
void game_exit(void);