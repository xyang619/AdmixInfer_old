/*
 * CGFRModel.h
 *
 *  Created on: Feb 12, 2015
 *      Author: young
 */

#ifndef CGFRMODEL_H_
#define CGFRMODEL_H_

#include "SpecModel.h"

class CGFRModel: public SpecModel
{
public:
	CGFRModel(int T = 1, double m = 0.5);
	~CGFRModel();
	double dist(double x) const;
	double getCorrector(double cutoff = 0, double length = kInfinity) const;
};

#endif /* CGFRMODEL_H_ */
