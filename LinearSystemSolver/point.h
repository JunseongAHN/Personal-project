#pragma once

#ifndef POINT_H
#define POINT_H

#include <iostream>

/*********************************************
* POINT
* A single position.
*********************************************/
class Point
{
public:
	// constructors
	Point() : x(0.0), y(0.0) {}
	Point(bool check) : x(0.0), y(0.0) {}
	Point(double x, double y);

	// getters
	double getX()       const { return x; }
	double getY()       const { return y; }

	// setters
	void setX(double x);
	void setY(double y);
	void addX(double dx) { setX(getX() + dx); }
	void addY(double dy) { setY(getY() + dy); }

private:
	double x;           // horizontal position
	double y;           // vertical position
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in, Point & pt);

#endif // POINT_H
