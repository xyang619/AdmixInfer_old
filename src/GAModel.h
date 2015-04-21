/*
 * GAModel.h
 *
 *  Created on: Feb 12, 2015
 *      Author: young
 */

#ifndef GAMODEL_H_
#define GAMODEL_H_

#include "SpecModel.h"

class GAModel: public SpecModel
{
public:
	GAModel(int T = 1, double m = 0.5);
	~GAModel();
	double dist(double x) const;
	double getCorrector(double cutoff = 0, double length = kInfinity) const;
};

#endif /* GAMODEL_H_ */
