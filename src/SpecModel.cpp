/*
 * SpecModel.cpp
 *
 *  Created on: Feb 12, 2015
 *  Author: young
 */

#include "SpecModel.h"

SpecModel::SpecModel(int T, double m) :
		mT(T), mm(m)
{
	// TODO Auto-generated constructor stub
}

SpecModel::~SpecModel()
{
	// TODO Auto-generated destructor stub
}

int SpecModel::getT() const
{
	return mT;
}

double SpecModel::getM() const
{
	return mm;
}

void SpecModel::setT(int T)
{
	mT = T;
}

void SpecModel::setM(double m)
{
	mm = m;
}

//calculate sum of the log likelihood, given the distribution and observation
double SpecModel::loglik(const std::vector<double> &observ, double cutoff, double length) const
{
	double llk = 0;
	for (unsigned int i = 0; i < observ.size(); ++i)
	{
		llk += log(dist(observ.at(i)));
	}
	double corrector = getCorrector(cutoff, length);
	llk -= observ.size() * log(corrector);
	return llk;
}

