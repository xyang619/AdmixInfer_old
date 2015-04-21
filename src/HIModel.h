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
	double dist(double x, double cutoff = 0, double length = kInfinity) const;
};

#endif /* HIMODEL_H_ */
