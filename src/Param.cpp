/*
 * Param.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: young
 */

#include "Param.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

Param::Param(int argc, char ** argv) :
		maxT(500), cutoff(0.0), output("loglik.txt")
{
	if (argc < 2)
	{
		cerr << "More arguments required, please use -h/--help to get help!" << endl;
		exit(1);
	}
	//process command arguments
	for (int i = 1; i < argc; ++i)
	{
		string agv(argv[i]);
		if (agv == "-h" || agv == "--help")
		{
			help();
			exit(0);
		}
		else if (agv == "-f" || agv == "--file")
		{
			fname = string(argv[++i]);
		}
		else if (agv == "-m" || agv == "--maxT")
		{
			maxT = atoi(argv[++i]);
		}
		else if (agv == "-c" || agv == "--cutoff")
		{
			cutoff = atof(argv[++i]);
		}
		else if (agv == "-o" || agv == "--output")
		{
			output = string(argv[++i]);
		}
	}
	if (!check())
	{
		exit(1);
	}
}

Param::~Param()
{
	// TODO Auto-generated destructor stub
}

int Param::getMaxT() const
{
	return maxT;
}
double Param::getCutoff() const
{
	return cutoff;
}
string Param::getFname() const
{
	return fname;
}
string Param::getOutput() const
{
	return output;
}

//perform check, validate the inputs
bool Param::check() const
{
	if (maxT < 1)
	{
		cerr << "Maximum generation to search should be larger than 1!" << endl;
		return 0;
	}
	if (cutoff < 0)
	{
		cerr << "Cutoff to discard short tracks should not be negative!" << endl;
		return 0;
	}
	if (fname.length() == 0)
	{
		cerr << "Input filename is empty!" << endl;
		return 0;
	}
	return 1;
}

//print help information
void Param::help() const
{
	cout << "AdmixInfer v1.0.0" << endl;
	cout << "AdmixInfer is designed to optimize the parameters of admixture model via maximum" << endl;
	cout << "likelihood estimation and figure out the model best fit the data. The optimization" << endl;
	cout << "is under assumption of HI, GA, CGFR and CGFD model" << endl;
	cout << "Arguments:" << endl;
	cout << "\t-h/--help\tprint help message [optional]" << endl;
	cout << "\t-f/--file\tfilename of the ancestral tracks [required]" << endl;
	cout << "\t-m/--maxT\tmaximum generation to search [optional, default=500]" << endl;
	cout << "\t-c/--cutoff\tcutoff to discard short tracks [optional, default=0]" << endl;
	cout << "\t-o/--output\toutput for likelihoods [optional, default=loglik.txt]" << endl;
}

