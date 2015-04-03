/*
 * Param.h
 *
 *  Created on: Apr 1, 2015
 *  Author: young
 *  Param has four members:
 *  	maxT: maximum generation to search;
 *  	cutoff: cutoff to discard short tracks;
 *  	fname: input file name of the ancestral tracks;
 *  	output: output file name to save the likelihoods
 */

#ifndef PARAM_H_
#define PARAM_H_

#include<string>

class Param
{
public:
	Param(int argc, char ** argv);
	virtual ~Param();
	int getMaxT() const;
	double getCutoff() const;
	std::string getFname() const;
	std::string getOutput() const;
private:
	int maxT;
	double cutoff;
	std::string fname;
	std::string output;
	bool check() const;
	void help() const;
};

#endif /* PARAM_H_ */
