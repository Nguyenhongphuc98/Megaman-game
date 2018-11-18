#pragma once
#ifndef Box_H_
#define Box_H_

class Box
{
private:
	int x,y;
	int w, h;
public:
	Box();
	Box(int x, int y, int w, int h);
	~Box();

	void SetingBox(int x, int y, int w, int h);
	bool IsOverlap(Box otherBox);	
};


#endif // !Box_H_
