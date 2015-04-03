/*
 * CGFDModel.h
 *
 *  Created on: Feb 12, 2015
 *      Author: young
 */

#ifndef CGFDMODEL_H_
#define CGFDMODEL_H_

#include "SpecModel.h"

class CGFDModel: public SpecModel
{
public:
	CGFDModel(int T = 1, double m = 0.5);
	~CGFDModel();
	double dist(double x, double cutoff = 0) const;
};

#endif /* CGFDMODEL_H_ */
