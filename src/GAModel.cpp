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
double GAModel::dist(double x, double cutoff) const
{
	int T = getT();
	double m = getM();
	double num = 0;
	double den = 0;
	double tmp = 0;

	for (int t = 2; t <= T; ++t)
	{
		tmp = (T - t + 1) * pow(1 - 1.0 / T, 1 - t);
		num += tmp * (T - t + 1) * exp(-(1 - m) * (T - t + 1) * x);
		den += tmp * exp(-(1 - m) * (T - t + 1) * cutoff);
	}

	num = (1 - m) * (T * T * exp(-(1 - m) * T * x) + num / T);
	den = T * exp(-(1 - m) * T * cutoff) + den / T;

	return num / den;
}

