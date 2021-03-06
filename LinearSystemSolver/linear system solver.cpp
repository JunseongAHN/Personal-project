#include "linear system solver.h"
#include "Linear System.h"

LinearSystemSolver::LinearSystemSolver(LinearSystem linearsystem, bool show, std::string file) : ls(linearsystem), process(show), filename(file), inconsistent(false)
{
	/*
	Constructor:
		linearsystem(LinearSystem, ): linearsystem to solve
		show(bool, default = false): if it is true, show the process
		file(string, default = ""): if it is "", it uses standard output(cout). Otherwise, it uses a file output.
	*/
	pivot.row = 0;
	pivot.col = 0;
	ROW = ls.ROW;
	COL = ls.COL;
	if (file != "")
	{
		out.open(file);
	}
}
bool LinearSystemSolver::findPivotPosition(const int row)
{
	/*
	Parameter:
		row(const int): the starting row
	return:
		bool: if linear system is zero matrix, return 0; else 1 
	Description:
		find pivot position for the reduced row echelonForm
	*/
	for (int i = row; i >= 0; i--)
	{
		for (int j = 0; j < COL; j++)
		{
			//we found pivot
			if (ls.mat[i][j] != 0)
			{
				pivot.row = i;
				pivot.col = j;
				return 1;
			}
		}
	}
	return 0;
}
void LinearSystemSolver::reduced()
{
	/*
	Description:
		make every entry on the pivot column above the pivot row 0
	*/
	double scalar;
	for (int i = 0; i < pivot.row; i++)
	{
		if (ls.mat[i][pivot.col] != 0)
			{
				scalar = ls.mat[pivot.row][pivot.col] / ls.mat[i][pivot.col];
				//make every pivot column 1 if the entry is not zero
				scalarsMultiple(i, scalar);
				reducedUpperPivot(i);
			}
	}
}
void LinearSystemSolver::reducedUpperPivot(const int inx)
{
	/*
	Parameter:
		inx (const int): the target that we are going to substract
	Description:
		Using row operation, substract mat[inx] - mat[pivot.row] 
	*/

	//if the entry is zero, it doesn't do anything
	if (ls.mat[inx][pivot.col] == 0) return;
	
	//from pivot column, we are subtracting pivot row
	for (int j = pivot.col; j < COL; j++)
	{
		ls.mat[inx][j] -= ls.mat[pivot.row][j];
	}
	if (process == true)
	{
		ss << "Row operation: " << "R" << inx << " - R" << pivot.row << " -> " << "R" << inx << std::endl;
		printProcess(ss.str());
		ss.str("");
	}
}
bool LinearSystemSolver::pivotCheck()
{
	/*
	Description:
		Even if pivot column is not zero, pivot position is zero.
	*/
	bool alreadyreduced = 0;
	//if the pivot is already not zero, we don't need to swap it
	if (ls.mat[pivot.row][pivot.col] != 0)
		return 1;

	for (int i = pivot.row + 1; i < ROW; i++)
	{
		if (ls.mat[i][pivot.col] != 0)
		{
			alreadyreduced = 1;
			//we are swaping the pivot row with some non zero row
			elementaryRowOp(pivot.row, i);
			break;
		}
	}
	//if it is already reduced, we are going to move on
	if (alreadyreduced == 0)
		return 0;
	else
		return 1;
}
void LinearSystemSolver::elementaryRowOp(const int a, const int b)
{
	/*
	paramemter:
		a(const int): the row index for swaping
		b(cont inx): the another row index for swaping
	Description:
		swap two rows (mat[a], mat[b])
	*/
	for (int i = 0; i < COL; i++)
	{
		std::swap(ls.mat[a][i], ls.mat[b][i]);
	}
	if (process == true)
	{
		ss << "Row operation: " << "R" << a << " <-> R" << b << std::endl;
		printProcess(ss.str());
		ss.str("");
	}
}
void LinearSystemSolver::scalars()
{
	/*
	Description:
		change the value of every entry of the pivot column to 1 by multplying scalar.
	*/
	int i;

	double scalar;
	for (i = pivot.row; i < ROW; i++)
	{
		if (fabs(ls.mat[i][pivot.col]) >= DBL_EPSILON)
		{
			scalar = 1 / ls.mat[i][pivot.col];
			//if scalar is 1, we don't need to multiply it
			if (fabs(scalar - 1.0) > DBL_EPSILON)
			{
				scalarsMultiple(i, scalar);
			}
		}

	}
	MakePivotPosition();
	
}
void LinearSystemSolver::scalarsMultiple(const int row, double scalar)
{
	/*
	Desciption:
		This function multiplies the row with scalar
	*/
	for (int i = 0; i < COL; i++)
	{
		if(fabs(ls.mat[row][i]-0.0) > DBL_EPSILON)
			ls.mat[row][i] *= scalar;
	}
	if (process == true)
	{
		ss << "Row operation: " << scalar << " × R" << row << " -> " << "R" << row << std::endl;
		printProcess(ss.str());
		ss.str("");
	} 
}
void LinearSystemSolver::MakePivotPosition()
{
	/*
	Description:
		Using elementray row operation, it makes every entry in pivot column but pivot row index zero 
	*/
	int j = pivot.col;
	for (int i = pivot.row + 1; i < ROW; i++)
	{
		//when it is alreay 0, we are not going to minus it
		if (fabs(ls.mat[i][j] - 1.0) < DBL_EPSILON)
		{
			for (j = pivot.col; j < COL; j++)
			{
				ls.mat[i][j] -= ls.mat[pivot.row][j];
			}
			if (process == true)
			{
				ss << "Row operation: " << "R" << i << " + R" << pivot.row << " -> " << "R" << i << std::endl;
				printProcess(ss.str());
				ss.str("");
			}
			j = pivot.col;
		}
	}
}
void LinearSystemSolver::rowEchelonForm()
{
	/*
	Description:
		Calculate a row Echelon Form.
	*/
	printProcess("start:\n");
	//use Gaussian elimination
	while (pivot.row < ROW - 1 && pivot.row < COL - 1)
	{
		if (pivotCheck())
		{
			scalars();
			//we need to carefully check this
			pivot.row++;
			pivot.col++;
		}
		else
			//it means every entry in the previous pivot column was zero 
			pivot.col++;
	}//echlon form done
	printProcess("   Row Echelon Form :\n");
}
void LinearSystemSolver::reducedRowEchelonForm()
{
	/*
	Description:
		Calculate the reduced row Echelon Form.
	*/
	rowEchelonForm();
	//reduced start
	pivot.col = 0;
	pivot.row = ROW - 1;
	do
	{
		//when it is zero above (no pivot above)
		if (!findPivotPosition(pivot.row))
		{
			break;
		}
		else
		{
			//when the pivot column is not in b
			if (pivot.col != COL - 1) {
				reduced();
				scalarsMultiple(pivot.row, 1.0 / ls.mat[pivot.row][pivot.col]);
			}
			else {
				inconsistent = true;
			}
		}
		pivot.row--;
	} while (pivot.col >=0&& pivot.row >=0);
	if (inconsistent)
		printProcess("  Reduced Row Echelon Form(inconsistent) :\n");
	else
		printProcess("  Reduced Row Echelon Form(consistent) : \n");
}
void LinearSystemSolver::printProcess(std::string introduction)
{
	if (process == true)
	{
		if (filename == "")
		{
			std::cout << introduction;
			ls.matrixPrint();
		}
		else
		{
			out << introduction;
			ls.matrixPrint(out);
		}
	}

}
