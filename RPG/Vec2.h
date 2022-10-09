#pragma once
class CVec2
{
public:
	CVec2()
	{
		x = 0;
		y = 0;
		xBk = 0;
		yBk = 0;
	}
	CVec2(int nX, int nY)
	{
		x = nX;
		y = nY;
		xBk = nX;
		yBk = nY;
	}
	int x;//ÐÐ
	int y;//ÁÐ
	int xBk;
	int yBk;
};

