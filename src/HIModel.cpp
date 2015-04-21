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
double HIModel::dist(double x) const
{
	int T = getT();
	double m = getM();
	double lambda = T * (1 - m);
	return lambda * exp(-lambda * x);
}

double HIModel::getCorrector(double cutoff, double length) const
{
	double lambda = getT() * (1 - getM());
	double corrector = exp(-lambda * cutoff) - exp(-lambda * length);
	return corrector;
}

