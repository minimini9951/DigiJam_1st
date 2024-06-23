#include "cprocessing.h"
#include "move.h"
#include "walls.h"
#include "utils.h"
#include "draw.h"

void rotate_wall(struct HEXAGON* hexagon, struct RANDOMANGLE* angle)
{
	if (angle->rotation_Time >= 10) // 18�� �����
	{
		// 10�ʴ� �ѹ��� ����
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
	//���� ���� �������� ���� �ð�
	float frame = CP_System_GetDt(); //������ �����ӿ��� ����� �ð�(��)�� ��ȯ�մϴ�

	//Reset hexa
	if (hexagon->sec >= total_sec)//�������� sec�� 5���� ũ�ų� ������
	{
		hexagon->sec = 0;//�ٽ� 0���� �ʱ�ȭ

		if (dir == normal)
		{
			//random walls
			hexagon->amount = walls_count();
			//reset the hex arr
			for (int i = 0; i < 6; i++)
				hexagon->arr[i] = 0;

			walls_position(hexagon, hexagon->amount); //������ arr[������]�� ��ġ�� 1�� ����(�������� �� �迭�� �ִٴ� ����)
		}
		else
		{
			set_empty(hexagon);
		}
	}
	else
	{
		hexagon->sec += frame; //������ �����ӿ��� ����� �ð�(��)�� ��� ���Ѵ� �� 1�� ���Ѵ�?
		float v = CP_Math_ClampFloat(hexagon->sec / total_sec, 0, 1); //frame�ϳ��� 0.016�ʸ� �׷��� ��ȯ�ϱ� ���ؼ�
		/* 
		�ε� �Ҽ����� ������ �����ϰ� ������ ���� ��ȯ�մϴ�. 
		������ �ε� �Ҽ��� ���� ������ �ּҰ����� ������ �ּҰ��� ��ȯ�˴ϴ�. 
		������ �ε� �Ҽ��� ���� ������ �ִ� ������ ũ�� �ִ� ���� ��ȯ�˴ϴ�. 
		�׷��� ������ ������ �ε� �Ҽ��� ���� ��ȯ�˴ϴ�.
		*/
		if(dir == 1)
			hexagon->radius = lerp(hexagon->max_radius, hexagon->min_radius, v);
		else if(dir == 0)
			hexagon->radius = lerp(hexagon->min_radius, hexagon->max_radius * 2, v);
		//max_radius,min_radius�� v�� ������ ��Ÿ����. 
		//�� 5�ʵ��� ���� ���������� ����� ���� �ϴ� ���̴�.
	}
}

//����κ��� ĳ���� ��ġ �ǵ��

void move_char(struct CHARACTER* character)
{
	//������ ��� count ������Ű��
	if (CP_Input_KeyTriggered(KEY_LEFT))
	{
		character->pos = 1;
		character->copyCounter = character->count;
		character->count++;
		confused(character);
	}
	//�������� ���� count ���� ��Ŵ
	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		character->pos = -1;
		character->copyCounter = character->count;
		character->count--;
		confused(character);
	}

	//���� Ű�� -1
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
