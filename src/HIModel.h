/*
 * HIModel.h
 *
 *  Created on: Feb 12, 2015
 *      Author: young
 */

#ifndef HIMODEL_H_
#define HIMODEL_H_

#include "SpecModel.h"

class HIModel: public SpecModel
{
public:
	HIModel(int T = 1, double m = 0.5);
	~HIModel();
	double getCorrector(double cutoff = 0, double length = kInfinity) const;
	double dist(double x) const;
};

#endif /* HIMODEL_H_ */
