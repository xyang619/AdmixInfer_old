/*
 * SpecModel.h
 *
 *  Created on: Feb 12, 2015
 *  Author: young
 *  A Specified model has two member, admixture proportion m and generation T;
 *	two member function:
 *	this class is base class of HI, GA, CGFR and CGFD models.
 *	with the distribution of a model, likelihoods can be calculated
 *
 *	Accelerating calculation:
 *	In calculating the likelihood, because for given m and T, the denominator is always the same,
 *	in order to avoid repeatedly calculation, the denominator thus can be calculated and stored,
 *	as a corrector, to corrector the results at the end of calculation.
 */

#ifndef SPECMODEL_H_
#define SPECMODEL_H_

#include <vector>
#include <cmath>

const double kInfinity = exp(1000);

class SpecModel
{
public:
	SpecModel(int T = 1, double m = 0.5);
	virtual ~SpecModel();
	int getT() const;
	double getM() const;
	void setT(int T);
	void setM(double m);
	double loglik(std::vector<double> observ, double cutoff = 0, double length = kInfinity) const;
	virtual double getCorrector(double cutoff = 0, double length = kInfinity) const = 0;
	virtual double dist(double x) const = 0;
private:
	int mT;
	double mm;
};

#endif /* SPECMODEL_H_ */
