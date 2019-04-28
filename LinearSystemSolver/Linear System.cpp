#include "Linear System.h"


LinearSystem::LinearSystem(size_t nequation, size_t nvariable, std::vector <std::vector<double>> val, std::vector<double> b) : ROW(nequation), COL(nvariable + 1), mat(nequation, std::vector<double>(nvariable + 1))
{
	/*
	Parameter:
		nequation(int) = the number of equations
		nvariable(int) = the number of variables
		val(vector<vector<double>>, size = (nequation, nvariable)) = the value for A
		b(vector<double>, size = (nvariable, )) = the value for b
	Exception:
		When the shape of A, B are not right
	*/
	try
	{
		if (nequation != val.size())
		{
			throw Exceptionshape("nequation != val.size()");
		}
		else if (nvariable != b.size())
			throw Exceptionshape("nvariable != b.size()");
		for (size_t i = 0; i < val.size(); i++)
		{
			if (val[i].size() > nvariable)
				throw Exceptionshape("val[i].size() > nvariable");
		}
		for (size_t i = 0; i < nequation; i++)
		{
			//set up A
			for (size_t j = 0; j < nvariable; j++)
			{
				if (j < val[i].size())
					mat[i][j] = val[i][j];
				else
					mat[i][j] = 0;
			}
			//set up b
			mat[i][nvariable] = b[i];
		}
	}
	catch (const Exceptionshape & e)
	{
		std::cout << "ERROR: " << e._msg << std::endl;
		exit(0);
	}	
}
LinearSystem::LinearSystem(Point* point, int n, int deg) : ROW(n), COL(deg + 2), mat(n, std::vector<double>(deg + 2))
{
	/*
	parameter:
		point(Point *) : the data points
		n(int) : the number of points
		n(deg) : the degree of the polynomal for curve fitting
	Description:
		It is for curve fitting... Future work.
	*/
	for (int i = 0; i < n; i++)
	{
		this->point.push_back(point[i]);
	}

	setLinearSystem_Points();
}
void LinearSystem::setLinearSystem_Points()
{
	/*
	Parameter:

	Description:
		Make a linear system by pluging points in in polynomial
			a_0x1^0 + a_1x1^1 + ... + a_deg*x1^deg = y1
			a_0x2^0 + a_1x2^1 + ... + a_deg*x2^deg = y2
								.
								.
								.
			a_0xn^0 + a_1xn^1 + ... + a_deg*xn^deg = yn
	*/
	double x;
	//set A
	for (int i = 0; i < ROW; i++)
	{
		x = point[i].getX();
		for (int j = 0; j < COL - 1; j++)
		{
			mat[i][j] = pow(x, j);
		}
		//set b 
		mat[i][COL - 1] = point[i].getY();
	}
}
void LinearSystem::matrixPrint()
{

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			std::cout << std::setw(6) << std::setprecision(3) << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void LinearSystem::matrixPrint(std::ofstream& out)
{
	std::setprecision(4);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			out << std::setw(6) << std::setprecision(3) << mat[i][j] << " ";
		}
		out << std::endl;
	}
	out << std::endl;
}
std::ostream & operator <<(std::ostream &out, const LinearSystem &ls)
{
	for (int i = 0; i < ls.ROW; i++)
	{
		for (int j = 0; j < ls.COL; j++)
		{
			out << ls.mat[i][j] << " ";
		}
		out << std::endl;
	}
	return out;
}