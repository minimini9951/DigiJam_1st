#include "cprocessing.h"
#include "collision.h"
#include "walls.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include"tetrishexagon.h"

int collision_check(struct HEXAGON* hexagon, struct CHARACTER* character)
{
	if (hexagon == NULL)
		return 0;
	//�̰� ĳ������ ���� ��(�Ƚ� ��)
	
	float multiply = 1.25f;
	float circle_x = hexagon->center.x + hexagon->min_radius * multiply * cosf(CP_Math_Radians(60 + hexagon->angle + character->move));
	float circle_y = hexagon->center.y - hexagon->min_radius * multiply * sinf(CP_Math_Radians(60 + hexagon->angle + character->move));
	
	
	float middleX;
	float middleY;

	for (int i = 0; i < 6; i++)
	{
		if (hexagon->arr[i] == 1)
		{
			//�����ִ� ��
			float x1 = hexagon->center.x + hexagon->radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * i));
			float y1 = hexagon->center.y - hexagon->radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * i));
			float x2 = hexagon->center.x + hexagon->radius * cosf(CP_Math_Radians(30 + hexagon->angle + 60 * (i + 1)));
			float y2 = hexagon->center.y - hexagon->radius * sinf(CP_Math_Radians(30 + hexagon->angle + 60 * (i + 1)));

			middleX = (x1 + x2) / 2;
			middleY = (y1 + y2) / 2;

			//�浹�ϸ� ���� 1�� ��ȯ

			if (pow((middleX-circle_x), 2) + pow((middleY-circle_y), 2)-(pow(7.5f,2))<=0)
			{
				return 1;
			}
			
		}
	}
	 //�浹 �������� 0�� ��ȯ
	return 0;	
}
