/*
Author: Junseong
Header discription: This header file helps to solve the linear system
*/
#ifndef LINEAR_SYSTEM_SOLVER_H
#define LINEAR_SYSTEAM_SOLVER_H
#include "Linear System.h"
#include <fstream>
#include <sstream>

class LinearSystemSolver
{
private:
	int ROW;
	int COL;
	bool process;
	bool inconsistent;
	std::string filename = "";
	struct Pivot
	{
		int row;
		int col;
	};
	Pivot pivot;
	LinearSystem ls;
	std::ofstream out;
	std::stringstream ss;

private:

	void scalarsMultiple(const int row, double scalar);
	void scalars();
	void elementaryRowOp(const int a, const int b);

	void MakePivotPosition();
	bool pivotCheck();
	bool findPivotPosition(const int row);

	void reduced();
	void reducedUpperPivot(const int inx);
	void printProcess(std::string);
public:
	LinearSystemSolver(LinearSystem linearsystem, bool show = false, std::string file = "");
	void rowEchelonForm();
	void reducedRowEchelonForm();
};
#endif // !LINEAR_SYSTEM_SOLVER_H

