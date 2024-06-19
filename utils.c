#include "cprocessing.h"
#include "time.h"

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomize(int arr[], int n)
{

    for (int i = n - 1; i > 0; i--)
    {
        int j = CP_Random_RangeInt(0, i);

        swap(&arr[i], &arr[j]);
    }
}
/*
int g_arr[6] = { 0, 1, 2, 3, 4, 5 };
int g_n = sizeof(g_arr) / sizeof(g_arr[0]);
*/
float lerp(float a, float b, float v)
{
    return a + v * (b - a);
    //�� ���� ������ ���� ������ ���� �������� �����Ͽ� ���ο� ������ ������ ����
    
}