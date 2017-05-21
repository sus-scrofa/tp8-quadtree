#pragma once
class Point
{
public:
	Point() { x = 0; y = 0; };
	Point(int x, int y) { this->x = x; this->y = y; };
	~Point() {};
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	float getX() { return x; }
	float getY() { return y; }
private:
	float x;
	float y;
};

