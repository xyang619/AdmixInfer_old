/*
 * LatData.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: young
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "LatData.h"

LatData::LatData(string & fname)
{
	readDat(fname);
}

LatData::~LatData()
{
	// TODO Auto-generated destructor stub
}

//reading data from external file
void LatData::readDat(string & fname)
{
	ifstream fin(fname.c_str());
	if (!fin.good())
	{
		cerr << "Can't open file " << fname << endl;
		exit(1);
	}
	string line;

	while (getline(fin, line))
	{
		stringstream ss(line);
		double start, end;
		string pop;
		string chr;
		ss >> start;
		ss >> end;
		ss >> pop;
		ss >> chr;
		double len = end - start;
		//if no population label find, push back
		if (find(labels.begin(), labels.end(), pop) == labels.end())
		{
			labels.push_back(pop);
		}
		//if chromosome not found, then create an new one
		if (find(chrs.begin(), chrs.end(), chr) == chrs.end())
		{
			chrs.push_back(chr);
			map<string, vector<double> > inmap;
			vector<double> tmp;
			inmap[pop] = tmp;
			segs[chr] = inmap;
		}
		else
		{
			if (segs.at(chr).find(pop) == segs.at(chr).end())
			{
				vector<double> tmp;
				segs.at(chr)[pop] = tmp;
			}
		}
		segs.at(chr).at(pop).push_back(len);
	}
	fin.close();
	if (labels.size() != 2)
	{
		cerr << "Tracks from either one population or more than two populations" << endl;
		exit(1);
	}
}

vector<string> LatData::getChrs() const
{
	return chrs;
}

vector<string> LatData::getLabels() const
{
	return labels;
}

//get the sum of the length of tracks for given parental population, chromosome by chomosome
vector<double> LatData::getSums(string & pop) const
{
	vector<double> ret;
	for (size_t i = 0; i < chrs.size(); ++i)
	{
		double sumL = 0;
		string chr = chrs.at(i);
		size_t size = segs.at(chr).at(pop).size();
		for (size_t j = 0; j < size; ++j)
		{
			sumL += segs.at(chr).at(pop).at(j);
		}
		ret.push_back(sumL);
	}
	return ret;
}

//get the admixture proportions for each chromosome, by given parental population
vector<double> LatData::getProps(string & pop) const
{
	vector<double> props;
	if (chrs.size() == 1)
	{
		double num = getSums(pop).at(0);
		double den = 0;
		for (size_t i = 0; i < labels.size(); ++i)
		{
			string tmp = labels.at(i);
			den += getSums(tmp).at(0);
		}
		props.push_back(num / den);
	}
	else
	{
		int index = 0;
		if (labels.at(1) == pop)
		{
			index = 1;
		}
		string pop2 = labels.at(1 - index);
		vector<double> sums1 = getSums(pop);
		vector<double> sums2 = getSums(pop2);
		for (size_t i = 0; i < chrs.size(); ++i)
		{
			double num = 0;
			double den = 0;
			for (size_t j = 0; j < chrs.size(); ++j)
			{
				if (j != i)
				{
					num += sums1.at(j);
					den += sums1.at(j) + sums2.at(j);
				}
			}
			props.push_back(num / den);
		}
	}

	return props;
}

//weight w_i = (∑X_i -Xi)/((N-1)*∑X_i), X_i is the counts of tracks in chromosome i
//N is the number of chromosome, cutoff is used to filter short tracks
vector<double> LatData::getWeights(vector<string> & chrList, double cutoff) const
{
	vector<double> weights;
	if (chrList.size() == 1)
	{
		weights.push_back(1);
		return weights;
	}
	//get counts for each chromosome X_i , and total counts ∑X_i
	vector<int> counts;
	int tc = 0;
	for (size_t i = 0; i < chrList.size(); ++i)
	{
		string chr = chrList.at(i);
		int count = 0;
		for (size_t j = 0; j < labels.size(); j++)
		{
			string pop = labels.at(j);
			size_t size = segs.at(chr).at(pop).size();
			for (size_t k = 0; k < size; ++k)
			{
				double tmp = segs.at(chr).at(pop).at(k);
				if (tmp >= cutoff)
				{
					count++;
				}
			}
		}
		counts.push_back(count);
		tc += count;
	}
	for (size_t i = 0; i < chrList.size(); ++i)
	{
		weights.push_back((tc - counts.at(i)) / ((chrList.size() - 1.0) * tc));
	}
	return weights;
}

//get the tracks of given chromosome, which from certain parental population
vector<double> LatData::getLat(string & chr, string & label, double cutoff) const
{
	vector<double> dat;
	size_t size = segs.at(chr).at(label).size();

	for (size_t i = 0; i < size; ++i)
	{
		double seg = segs.at(chr).at(label).at(i);
		if (seg >= cutoff)
			dat.push_back(seg);
	}
	return dat;
}

