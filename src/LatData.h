/*
 * LatData.h
 *
 *  Created on: Mar 23, 2015
 *  Author: young
 *  Length of ancestral tracks (LAT) is derived from the start point, end point;
 *  chrs: a list of chromosomes
 *  labels: the labels of ancestral populations
 *  segs is a mapping with key=chromosome, value = map<ancestry, length>
 */

#ifndef LATDATA_H_
#define LATDATA_H_

#include <vector>
#include <map>
#include <string>

using namespace std;

class LatData
{
private:
	vector<string> chrs;
	vector<string> labels;
	map<string, map<string, vector<double> > > segs;
	void readDat(string & fname);
public:
	LatData(string & fname);
	virtual ~LatData();
	vector<string> getChrs() const;
	vector<string> getLabels() const;
	vector<double> getSums(string & pop) const;
	vector<double> getProps(string & pop) const;
	vector<double> getWeights(vector<string> & chrList, double cutoff = 0) const;
	vector<double> getLat(string & chr, string & label, double cutoff = 0) const;
};

#endif /* LATDATA_H_ */
