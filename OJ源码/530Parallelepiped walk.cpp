#include <iostream>
#include <math.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
const int maxint = 0x7FFFFFFF;

int ans;

void walk(int i, int j, int x0, int y0, int x, int y, int z, int l, int w, int h)
{
    if (z == 0)
        ans = min((x0 - x) * (x0 - x) + (y0 - y) * (y0 - y), ans);
    else
    {
        if (i >= 0 && i < 2)
            walk(i + 1, j, x0, y0 - w, x, z, w - y, l, h, w);
        if (i <= 0 && i > -2)
            walk(i - 1, j, x0, y0 + h, x, h - z, y, l, h, w);
        if (j >= 0 && j < 2)
            walk(i, j + 1, x0 - l, y0, z, y, l - x, h, w, l);
        if (j <= 0 && j > -2)
            walk(i, j - 1, x0 + h, y0, h - z, y, x, h, w, l);
    }
}

int main()
{
    int l, w, h, x1, y1, z1, x2, y2, z2;
    while (scanf("%d%d%d", &l, &w, &h) != EOF)
	{
        scanf("%d%d%d", &x1, &y1, &z1);
        scanf("%d%d%d", &x2, &y2, &z2);
        if (z1 != 0 && z1 != h)
        {
            if (y1 != 0 && y1 != w) 
			{
				swap(x1, z1); swap(x2, z2); swap(l, h);
			}
            else
			{
				swap(y1, z1); swap(y2, z2); swap(w, h);
			}
        }
        if (z1 == h) 
		{
			z1 = 0; z2 = h - z2;
		}
        ans = maxint;
        walk(0, 0, x1, y1, x2, y2, z2, l, w, h);
        printf("%d\n", ans);
    }
}
