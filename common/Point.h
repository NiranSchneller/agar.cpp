#ifndef POINT_H
#define POINT_H

class Point {
private:
	double x, y;

public:
	Point(double x = 0, double y = 0);
	double GetY();
	double GetX();
	void SetY(double x);
	void SetX(double y);
	~Point() = default;
	Point minus(Point other);
	Point plus(Point other);
	Point div(Point other);
	Point mul(Point other);
	bool inRectangle(Point topLeft, Point bottomRight);

};

#endif
