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
double CGFRModel::dist(double x) const
{
	int T = getT();
	double m = getM();
	double lambda = pow(m, 1.0 / T);
	lambda = T - (1 - m) * lambda / (1 - lambda);
	return lambda * exp(-lambda * x);
}

double CGFRModel::getCorrector(double cutoff, double length) const
{
	int T = getT();
	double m = getM();
	double lambda = pow(m, 1.0 / T);
	double corrector = exp(-lambda * cutoff) - exp(-lambda * length);
	return corrector;
}

