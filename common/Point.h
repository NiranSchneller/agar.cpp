#ifndef POINT_H
#define POINT_H

class Point {
private:
	double x, y;

public:
	Point(double x = 0, double y = 0);
	~Point() = default;

	double GetY();
	double GetX();
	void SetY(double x);
	void SetX(double y);
};

#endif
