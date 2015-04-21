/*
 * GAModel.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: young
 */

#include "GAModel.h"
#include <cmath>

GAModel::GAModel(int T, double m) :
		SpecModel(T, m)
{
	// TODO Auto-generated constructor stub
}

GAModel::~GAModel()
{
	// TODO Auto-generated destructor stub
}

//distribution of GA model
double GAModel::dist(double x) const
{
	int T = getT();
	double m = 1 - getM();
	double num = 0;
	double tmp = 0;
	double lambda = 0;
	for (int t = 2; t <= T; ++t)
	{
		lambda = T - t + 1;
		tmp = lambda * pow(1 - 1.0 / T, 1 - t);
		num += tmp * lambda * exp(-lambda * m * x);
	}
	num = m * (T * T * exp(-m * T * x) + num / T);

	return num;
}

double GAModel::getCorrector(double cutoff, double length) const
{
	int T = getT();
	double m = 1 - getM();
	double tmp = 0;
	double lambda = 0;
	double corrector = 0;
	for (int t = 2; t <= T; ++t)
	{
		lambda = T - t + 1;
		tmp = lambda * pow(1 - 1.0 / T, 1 - t);
		corrector += tmp * (exp(-m * lambda * cutoff) - exp(-m * lambda * length));
	}
	corrector = corrector / T + T * (exp(-m * T * cutoff) - exp(-m * T * length));
	return corrector;
}

