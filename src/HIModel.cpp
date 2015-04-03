/*
 * HIModel.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: young
 */

#include "HIModel.h"
#include <cmath>

HIModel::HIModel(int T, double m) :
		SpecModel(T, m)
{
	// TODO Auto-generated constructor stub
}

HIModel::~HIModel()
{
	// TODO Auto-generated destructor stub
}

//distribution of HI model
double HIModel::dist(double x, double cutoff) const
{
	int T = getT();
	double m = getM();
	return (1 - m) * T * exp(-(1 - m) * T * (x - cutoff));
}

