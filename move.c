#include "cprocessing.h"
#include "move.h"
#include "walls.h"
#include "utils.h"
#include "draw.h"

void rotate_wall(struct HEXAGON* hexagon, struct RANDOMANGLE* angle)
{
	if (angle->rotation_Time >= 10) // 18초 경과시
	{
		// 10초당 한번만 실행
		if (CP_Random_RangeInt(0, 1))
			angle->random_angle = (float)CP_Random_RangeInt(45, 75);
		else
			angle->random_angle = -1 * (float)CP_Random_RangeInt(45, 75);

		angle->rotation_Time = 0;
	}
	else
	{
		// 0 
		angle->rotation_Time += CP_System_GetDt();
		for(int i = 0; i < 6; i++)
			hexagon[i].angle += angle->random_angle * CP_System_GetDt();
	}
}

void move_walls(struct HEXAGON* hexagon, int dir, float total_sec)
{
	//벽이 작은 육각형에 가는 시간
	float frame = CP_System_GetDt(); //마지막 프레임에서 경과된 시간(초)을 반환합니다

	//Reset hexa
	if (hexagon->sec >= total_sec)//육각형의 sec이 5보다 크거나 같으면
	{
		hexagon->sec = 0;//다시 0으로 초기화

		if (dir == normal)
		{
			//random walls
			hexagon->amount = walls_count();
			//reset the hex arr
			for (int i = 0; i < 6; i++)
				hexagon->arr[i] = 0;

			walls_position(hexagon, hexagon->amount); //육각형 arr[랜덤값]의 위치에 1을 넣음(육각형이 그 배열에 있다는 거임)
		}
		else
		{
			set_empty(hexagon);
		}
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
		if(dir == 1)
			hexagon->radius = lerp(hexagon->max_radius, hexagon->min_radius, v);
		else if(dir == 0)
			hexagon->radius = lerp(hexagon->min_radius, hexagon->max_radius * 2, v);
		//max_radius,min_radius의 v는 비율을 나타낸다. 
		//즉 5초동안 작은 육각형으로 가까워 지게 하는 식이다.
	}
}

//여기부분이 캐릭터 위치 건들기

void move_char(struct CHARACTER* character)
{
	//왼쪽이 양수 count 증각시키고
	if (CP_Input_KeyTriggered(KEY_LEFT))
	{
		character->pos = 1;
		character->copyCounter = character->count;
		character->count++;
		confused(character);
	}
	//오른쪽은 음수 count 감소 시킴
	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		character->pos = -1;
		character->copyCounter = character->count;
		character->count--;
		confused(character);
	}

	//왼쪽 키는 -1
	if (character->pos == -1)
	{
		//move
		character->move -= CP_System_GetDt() * 450;
		if (character->move <= 60 * character->count)
		{
			character->pos = 0;
			character->move = 60.0f * character->count;

			int p_angle = move_to_angle(character->move);
			character->area = get_area_index(p_angle);
			struct HEXAGON* close_wall = find_closest_hexa(g_wall_hexa, WallNumber);

			if (close_wall == NULL)
				return;

			if (close_wall->arr[character->area] == 0)
				make_effect(character->area);
		}
	}
	if (character->pos == 1)
	{
		character->move += CP_System_GetDt() * 450;
		if (character->move >= 60 * character->count)
		{
			character->pos = 0;
			character->move = 60.0f * character->count;

			int p_angle = move_to_angle(character->move);
			character->area = get_area_index(p_angle);

			struct HEXAGON* close_wall = find_closest_hexa(g_wall_hexa, WallNumber);

			if (close_wall == NULL)
				return;

			if (close_wall->arr[character->area] == 0)
				make_effect(character->area);
		}
	}
}

void confused(struct CHARACTER* character)
{
	// If player moves 6 time same direction, player's character is be confused

	if (character->confusedCounters_arr[character->confusedCounter] == 0)
		character->confusedCounters_arr[character->confusedCounter] = character->copyCounter;

	for (int i = character->confusedCounter; i < 6; i++)
	{
		if (character->confusedCounters_arr[i] != 0)
		{
			character->confusedCounter++;
			if (character->confusedCounter == 6)
			{
				for (int j = 0; j < 5; j++)
				{
					if (character->confusedCounters_arr[j + 1] == character->confusedCounters_arr[j] + 1)
					{
						character->still_confused++;
						if (character->still_confused == 5)
						{
							character->confused = 1;
						}
						else
						{
							character->confused = 0;
						}
					}
					if (character->confusedCounters_arr[j + 1] == character->confusedCounters_arr[j] - 1)
					{
						character->still_confused--;
						if (character->still_confused == -5)
						{
							character->confused = 1;
						}
						else
						{
							character->confused = 0;
						}
					}
				}
				character->confusedCounter = 0;
				character->still_confused = 0;
				for(int j = 0; j < 6; j++)
					character->confusedCounters_arr[j] = 0;
			}
		}
	}
	// In confused condition, 50% move reverse position
	if (character->confused)
	{
		if (CP_Random_RangeInt(0, 3))
		{
			if (character->pos * -1 == -1)
			{
				character->count -= 2;
			}
			else if (character->pos * -1 == 1)
			{
				character->count += 2;
			}
			character->pos *= -1;
		}
		character->moveConfuse++;
	}
	// If move 3 times in confused, exit confused.
	if (character->moveConfuse == 3)
	{
		character->moveConfuse = 0;
		character->confused = 0;
	}
}
