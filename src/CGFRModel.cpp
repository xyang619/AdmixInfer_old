/*
 * CGFRModel.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: young
 */

#include "CGFRModel.h"
#include <cmath>

CGFRModel::CGFRModel(int T, double m) :
		SpecModel(T, m)
{
	// TODO Auto-generated constructor stub
}

CGFRModel::~CGFRModel()
{
	// TODO Auto-generated destructor stub
}

//distribution of CGFR model
double CGFRModel::dist(double x, double cutoff) const
{
	int T = getT();
	double m = getM();
	double u = pow(m, 1.0 / T);
	u = T - (1 - m) * u / (1 - u);
	return u * exp(-u * (x - cutoff));
}

