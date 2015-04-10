/*
 * SpecModel.h
 *
 *  Created on: Feb 12, 2015
 *  Author: young
 *  A Specified model has two member, admixture proportion m and generation T;
 *	two member function:
 *	this class is base class of HI, GA, CGFR and CGFD models.
 *	with the distribution of a model, likelihoods can be calculated
 */

#ifndef SPECMODEL_H_
#define SPECMODEL_H_

#include <vector>

class SpecModel
{
public:
	SpecModel(int T = 1, double m = 0.5);
	virtual ~SpecModel();
	int getT() const;
	double getM() const;
	void setT(int T);
	void setM(double m);
	double loglik(std::vector<double> observ, double cutoff = 0) const;
	virtual double dist(double x, double cutoff = 0) const = 0;
private:
	int mT;
	double mm;
};

#endif /* SPECMODEL_H_ */
