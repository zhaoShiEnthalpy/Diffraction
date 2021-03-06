#include "CircMultiRectDiffraction.h"

void CircMultiRectDiffraction::initialize()
{
	x1s = new vector * *[apCount];
	for (int i = 0; i < apCount; i++)
	{
		x1s[i] = new vector * [dimb];
		for (int j = 0; j < dimb; j++)
		{
			x1s[i][j] = new vector[dima];
			for (int k = 0; k < dima; k++)
			{
				x1s[i][j][k] = NULL_VEC;
				la.vec.initialize(x1s[i][j][k], 3);
			}
		}
	}
	const double dx = a / (double)dima;
	const double dy = b / (double)dimb;
	const double theta0 = 2.0 * pi / (double)apCount;
	for (int i = 0; i < apCount; i++)
	{
		double theta = i * theta0;
		double x = -a / 2.0 + dx / 2.0 + d * cos(theta);
		double y = -b / 2.0 + dy / 2.0 + d * sin(theta);
		for (int j = 0; j < dimb; j++)
		{
			for (int k = 0; k < dima; k++)
			{
				x1s[i][j][k].value[0] = x;
				x1s[i][j][k].value[1] = y;
				x += dx;
			}
			x = -a / 2.0 + dx / 2.0 + d * cos(theta);
			y += dy;
		}
	}
}

complex<double> CircMultiRectDiffraction::integral(vector& x2)
{
	const double dx = a / (double)dima;
	const double dy = b / (double)dimb;
	const double dS = dx * dy;
	complex<double> I{ 0.0,0.0 };
	for (int i = 0; i < apCount; i++)
	{
		for (int j = 0; j < dimb; j++)
		{
			for (int k = 0; k < dima; k++)
			{
				I += fk.f(x1s[i][j][k], x2) * dS;
			}
		}
	}
	return I;
}

void CircMultiRectDiffraction::dispose()
{
	for (int i = 0; i < apCount; i++)
	{
		for (int j = 0; j < dimb; j++)
		{
			for (int k = 0; k < dima; k++)
			{
				la.vec.dispose(x1s[i][j][k]);
			}
			delete[]x1s[i][j];
		}
		delete[]x1s[i];
	}
	delete[]x1s;
}