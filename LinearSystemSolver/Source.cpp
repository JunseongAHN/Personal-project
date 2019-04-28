/*
Author: Junseong Ahn
Program discription: This program helps to set up and solve the linear system.
*/
#include <iostream>
#include <string>
#include "Linear System.h"
#include "point.h"
#include "linear system solver.h"

int main()
{
	/*********************************
	setup linear system Ax = b
	Example 
		1	5	2	4	|	1 
		2	6	0	0	|	3

	std::vector<std::vector <double>> A = { {1,5,2,4},{2,6,} }; // or A = { {1,5,2,4},{2,6,0,0} }; 
	std::vector<std::vector <double>> b = { {1,3} };

	Exception:
		If the shape is not right, it throws the exception.
	*********************************/
	
	/**********************************
	Set up A here
	***********************************/
	std::vector<std::vector <double>> A = { {3,4},{2,1} };
	/**********************************
	Set up b here
	**********************************/
	std::vector<double> b = { 0,2 };
	LinearSystem ls2(2,2,A,b);

	/*********************************
	setup linear system solver
	Constructor:
		ls(LinearSystem, ): linearsystem 
		show(bool, default = false): if it is true, show the process
		file(string, default = ""): if it is "", it uses standard output(cout). Otherwise, it uses a file output.
	*********************************/
	LinearSystemSolver solver(ls2,true,"output.txt");
	solver.reducedRowEchelonForm();
	return 0;
}
/*
Future work...
using data points to set up linear system
it works, but there is no utlity right now...
*/
//Point point[4];
//point[0].setX(0);
//point[0].setY(0);

//point[1].setX(0);
//point[1].setY(0);

//point[2].setX(0);
//point[2].setY(0);

//point[3].setX(4);
//point[3].setY(4);
//LinearSystem ls(point,4 , 1);

