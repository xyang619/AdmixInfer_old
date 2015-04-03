/*
 * CGFDModel.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: young
 */

#include "CGFDModel.h"
#include <cmath>

CGFDModel::CGFDModel(int T, double m) :
		SpecModel(T, m)
{
	// TODO Auto-generated constructor stub
}

CGFDModel::~CGFDModel()
{
	// TODO Auto-generated destructor stub
}

//distribution of CGFD model
double CGFDModel::dist(double x, double cutoff) const
{
	int T = getT();
	double m = getM();
	double num = 0;
	double den = 0;
	double tmp1 = 0;

	double tmp2 = pow(m, (T + 1.0) / T);
	double tmp3 = 1 - pow(m, 1.0 / T);
	for (int t = 1; t <= T; ++t)
	{
		tmp1 = pow(m, t * 1.0 / T);
		num += (tmp1 - tmp2) * (tmp1 - tmp2) * exp(-(tmp1 - tmp2) * x / tmp3) / tmp1;
		den += tmp3 * (tmp1 - tmp2) * exp(-(tmp1 - tmp2) * cutoff / tmp3) / tmp1;
	}

	return num / den;
}

