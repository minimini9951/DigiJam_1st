#include "cprocessing.h"
#include "move.h"
#include "walls.h"
#include "utils.h"
#include "draw.h"

void move_walls(struct HEXAGON* hexagon, int dir)
{
	const float total_sec = 8.0f; //벽이 작은 육각형에 가는 시간
	float frame = CP_System_GetDt(); //마지막 프레임에서 경과된 시간(초)을 반환합니다
	
	hexagon->angle += 15 * CP_System_GetDt();

	//Reset hexa
	if (hexagon->sec >= total_sec)//육각형의 sec이 5보다 크거나 같으면
	{
		hexagon->sec = 0;//다시 0으로 초기화
		//random walls
		hexagon->amount = walls_count();
		//reset the hex arr
		for (int i = 0; i < 6; i++)
			hexagon->arr[i] = 0;

		walls_position(hexagon, hexagon->amount); //육각형 arr[랜덤값]의 위치에 1을 넣음(육각형이 그 배열에 있다는 거임)
	}
	else
	{
		hexagon->sec += frame; //마지막 프레임에서 경과된 시간(초)를 계속 더한다 즉 1초 더한다?
		float v = CP_Math_ClampFloat(hexagon->sec / total_sec, 0, 1); //frame하나가 0.016초를 그래도 반환하기 위해서
		/* 
		부동 소수점을 범위로 고정하고 고정된 값을 반환합니다. 
		제공된 부동 소수점 값이 제공된 최소값보다 작으면 최소값이 반환됩니다. 
		제공된 부동 소수점 값이 제공된 최대 값보다 크면 최대 값이 반환됩니다. 
		그렇지 않으면 제공된 부동 소수점 값이 반환됩니다.
		*/
		if(dir)
			hexagon->radius = lerp(hexagon->max_radius, hexagon->min_radius, v);
		else
			hexagon->radius = lerp(hexagon->min_radius, hexagon->max_radius, v);
		//max_radius,min_radius의 v는 비율을 나타낸다. 
		//즉 5초동안 작은 육각형으로 가까워 지게 하는 식이다.
	}
}

//여기부분이 캐릭터 위치 건들기

void move_char(struct HEXAGON* hexagon, struct CHARACTER* character)
{
	if (hexagon == NULL)
		return;
	//왼쪽이 양수 count 증각시키고
	if (CP_Input_KeyTriggered(KEY_LEFT))
	{
		character->pos = 1;
		character->count++;
	}
	//오른쪽은 음수 count 감소 시킴
	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		character->pos = -1;
		character->count--;
	}

	//왼쪽 키는 -1
	if (character->pos == -1)
	{
		//move
		character->move -= CP_System_GetDt() * 600;
		if (character->move <= 60 * character->count)
		{
			character->pos = 0;
			character->move = 60.0f * character->count;
			make_wall(hexagon, character);
			check_walls(hexagon, character);
		}
	}
	if (character->pos == 1)
	{
		character->move += CP_System_GetDt() * 600;
		if (character->move >= 60 * character->count)
		{
			character->pos = 0;
			character->move = 60.0f * character->count;
			make_wall(hexagon, character);
			check_walls(hexagon, character);
			//move_efwalls(efhexa);
		}
	}
}