/*
 * SpecModel.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: young
 */

#include <cmath>
#include "SpecModel.h"

SpecModel::SpecModel(int T, double m) :
		T_(T), m_(m)
{
	// TODO Auto-generated constructor stub
}

SpecModel::~SpecModel()
{
	// TODO Auto-generated destructor stub
}

int SpecModel::getT() const
{
	return T_;
}

double SpecModel::getM() const
{
	return m_;
}

void SpecModel::setT(int T)
{
	T_ = T;
}

void SpecModel::setM(double m)
{
	m_ = m;
}

//calculate sum of the log likelihood, given the distribution and observation
double SpecModel::loglik(std::vector<double> observ, double cutoff) const
{
	double llk = 0;
	for (unsigned int i = 0; i < observ.size(); ++i)
	{
		llk += log(dist(observ.at(i), cutoff));
	}
	return llk;
}

