#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H
/*
Author: Junseong
Header discription: This header file helps to set up the linear system
*/
#include <iostream>
#include <vector>
#include "point.h"
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

class LinearSystem
{
	//it is for solving linear system
	friend class LinearSystemSolver;
protected:
	int ROW;
	int COL;
	std::vector <std::vector<double>> mat;
	//Future work:
	//it is for least square solution
	//using linear algebra library eigen, I need to calculate A.T@A and A.T@b
	std::vector <Point> point;
	struct Exceptionshape : public std::exception
	{
		Exceptionshape(std::string msg) : _msg(msg) {}
		std::string _msg;
	};
public:
	friend std::ostream& operator <<(std::ostream &out, const LinearSystem &ls);
	//set up Ax = b
	LinearSystem(size_t nequation, size_t nvariable, std::vector <std::vector<double>> val, std::vector<double> b);
	//Future work: it is for the least square solution
	LinearSystem(Point* point, int n, int deg);
	//show matrix
	void matrixPrint(std::ofstream & os);
	void matrixPrint();
	int getRow() { return ROW; }
	int getCol() { return COL; }

	void setLinearSystem_Points();
};
#endif // !LINEAR_SYSTEM_H


