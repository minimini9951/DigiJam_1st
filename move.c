#include "cprocessing.h"
#include "move.h"
#include "walls.h"
#include "utils.h"
#include "draw.h"

void move_walls(struct HEXAGON* hexagon, int dir)
{
	const float total_sec = 8.0f; //���� ���� �������� ���� �ð�
	float frame = CP_System_GetDt(); //������ �����ӿ��� ����� �ð�(��)�� ��ȯ�մϴ�
	
	hexagon->angle += 15 * CP_System_GetDt();

	//Reset hexa
	if (hexagon->sec >= total_sec)//�������� sec�� 5���� ũ�ų� ������
	{
		hexagon->sec = 0;//�ٽ� 0���� �ʱ�ȭ
		//random walls
		hexagon->amount = walls_count();
		//reset the hex arr
		for (int i = 0; i < 6; i++)
			hexagon->arr[i] = 0;

		walls_position(hexagon, hexagon->amount); //������ arr[������]�� ��ġ�� 1�� ����(�������� �� �迭�� �ִٴ� ����)
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
		if(dir)
			hexagon->radius = lerp(hexagon->max_radius, hexagon->min_radius, v);
		else
			hexagon->radius = lerp(hexagon->min_radius, hexagon->max_radius, v);
		//max_radius,min_radius�� v�� ������ ��Ÿ����. 
		//�� 5�ʵ��� ���� ���������� ����� ���� �ϴ� ���̴�.
	}
}

//����κ��� ĳ���� ��ġ �ǵ��

void move_char(struct HEXAGON* hexagon, struct CHARACTER* character)
{
	if (hexagon == NULL)
		return;
	//������ ��� count ������Ű��
	if (CP_Input_KeyTriggered(KEY_LEFT))
	{
		character->pos = 1;
		character->count++;
	}
	//�������� ���� count ���� ��Ŵ
	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		character->pos = -1;
		character->count--;
	}

	//���� Ű�� -1
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