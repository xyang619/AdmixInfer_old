/*
 * AdmixInfer.cpp
 *
 *  Created on: Mar 23, 2015
 *  Author: young
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include "LatData.h"
#include "Param.h"
#include "HIModel.h"
#include "GAModel.h"
#include "CGFRModel.h"
#include "CGFDModel.h"
#include "Utils.h"
#include "omp.h"

using namespace std;

int main(int argc, char ** argv)
{
	int nchrs;					//number of chromosomes
	int maxT;					//max generation
	int * indexes;				//index of the maximum likelihoods
	double meanM, varM;			//mean and variance of proportion m
	double meanT, varT;			//mean and variance of optimal generation T
	double cutoff;				//cutoff to discard short tracks
	double *** llks;			//likelihoods for each chromosome and each generation
	double *** jack_llk;		//summation of likelihoods without 1 chromosome
	double * globalMax;			//array of maximum likelihoods under different models

	string pop1, pop2;			//population label
	string fname, outfile;		//input and output file name
	vector<double> props;		//jackknife proportions
	vector<double> mWeights;	//weights of proportions
	vector<double> optTs;		//optimal generation for each round of jackknife
	vector<double> TWeights;	//weights of optimal generation
	vector<string> labels;		//population labels
	vector<string> chrs;		//a list of chromosomes
	vector<string> optMods;		//a list of optimal models
	map<string, int> modCounts;	//a map of optimal model counts

	Param *par;					//parameters
	LatData *segs;				//tracks

	string models[4] = { "HI", "GA", "CGFR", "CGFD" };

	//initialize variables
	par = new Param(argc, argv);
	maxT = par->getMaxT();
	cutoff = par->getCutoff();
	fname = par->getFname();
	outfile = par->getOutput();
	segs = new LatData(fname);
	labels = segs->getLabels();
	chrs = segs->getChrs();
	pop1 = labels.at(0);
	pop2 = labels.at(1);
	nchrs = chrs.size();

	//calculate proportions, determine population 1
	props = segs->getProps(pop1);
	mWeights = segs->getWeights(chrs);
	meanM = mean(props, mWeights);
	varM = var(props, mWeights, meanM);

	if (meanM > 0.5)
	{
		pop1 = labels.at(1);
		pop2 = labels.at(0);
		meanM = 1 - meanM;
		for (int i = 0; i < nchrs; ++i)
		{
			props.at(i) = 1 - props.at(i);
		}
	}

	//allocate memory for likelihoods
	llks = new double **[nchrs];
	for (int i = 0; i < nchrs; ++i)
	{
		llks[i] = new double *[4];
		for (int j = 0; j < 4; ++j)
		{
			llks[i][j] = new double[maxT];
		}
	}

	//calculate likelihoods for each chromosome, each generation under different models
	for (int i = 0; i < nchrs; ++i)
	{
		vector<double> segs1 = segs->getLat(chrs.at(i), pop1, cutoff);
		vector<double> segs2 = segs->getLat(chrs.at(i), pop2, cutoff);
		double m = props.at(i);
		#pragma omp parallel for
		for (int t = 1; t <= maxT; ++t)
		{
			llks[i][0][t - 1] = HIModel(t, m).loglik(segs1, cutoff) + HIModel(t, 1 - m).loglik(segs2, cutoff);
			llks[i][1][t - 1] = GAModel(t, m).loglik(segs1, cutoff) + GAModel(t, 1 - m).loglik(segs2, cutoff);
			llks[i][2][t - 1] = CGFRModel(t, m).loglik(segs1, cutoff) + CGFDModel(t, m).loglik(segs2, cutoff);
			llks[i][3][t - 1] = CGFDModel(t, 1 - m).loglik(segs1, cutoff) + CGFRModel(t, 1 - m).loglik(segs2, cutoff);
		}
	}

	//save log-likelihoods
	ofstream fout(outfile.c_str());
	if (!fout.good())
	{
		cout << "Can't open file " << outfile << endl;
		cout << "Warning: results are not saved" << endl;
	}
	else
	{
		for (int i = 0; i < nchrs; ++i)
		{
			fout << "chr" << chrs.at(i) << endl;
			fout << "Generation";
			for (int j = 0; j < 4; ++j)
			{
				fout << "\t" << models[j];
			}
			fout << endl;
			for (int t = 0; t < maxT; ++t)
			{
				fout << t + 1;
				for (int j = 0; j < 4; ++j)
				{
					fout << "\t" << llks[i][j][t];
				}
				fout << endl;
			}
			fout << endl;
		}
	}
	fout.close();

	//allocate memory for jackknife
	jack_llk = new double **[nchrs];
	for (int i = 0; i < nchrs; ++i)
	{
		jack_llk[i] = new double *[4];
		for (int j = 0; j < 4; ++j)
		{
			jack_llk[i][j] = new double[maxT];
		}
	}

	//perform jackknife, discard one chromosome each time
	//if only one chromosome, no jackknife
	for (int i = 0; i < nchrs; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int t = 0; t < maxT; ++t)
			{
				if (nchrs == 1)
				{
					jack_llk[i][j][t] = llks[i][j][t];
				}
				else
				{
					double tmp = 0;
					for (int k = 0; k < nchrs; ++k)
					{
						if (k != i)
						{
							tmp += llks[k][j][t];
						}
					}
					jack_llk[i][j][t] = tmp;
				}
			}
		}
	}

	globalMax = new double[4];
	indexes = new int[4];

	//find optimal models and corresponding generations for each round of jackknife
	for (int i = 0; i < nchrs; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			indexes[j] = indexOfMax(jack_llk[i][j], maxT);
			globalMax[j] = jack_llk[i][j][indexes[j]];
		}
		int modIndex = indexOfMax(globalMax, 4);
		int optT = indexes[modIndex] + 1;
		optTs.push_back(optT);
		optMods.push_back(models[modIndex]);
		if (nchrs > 1)
		{
			cout << "Jackknife:" << chrs.at(i) << "\t" << props.at(i) << "\t" << models[modIndex] << "\t" << optT << "\t" << globalMax[modIndex] << endl;
		}
	}

	//counting the times of optimal models
	for (int i = 0; i < nchrs; ++i)
	{
		string mod = optMods.at(i);
		if (modCounts.find(mod) == modCounts.end())
		{
			modCounts[mod] = 1;
		}
		else
		{
			modCounts[mod]++;
		}
	}

	//print the summary of results to screen
	cout << "================================================================================" << endl;
	cout << "Results Summary" << endl;
	cout << "Parental-population-1: " << pop1 << endl;
	cout << "Admix-proportion: (" << meanM << " ± " << sqrt(varM) << ")" << endl;
	for (map<string, int>::iterator it = modCounts.begin(); it != modCounts.end(); ++it)
	{
		string mod = it->first;
		double perc = 100.0 * it->second / nchrs;
		vector<string> chrList;		//record the chromosomes with given model as optimal
		vector<double> timeList;	//record the optimal generations
		for (size_t i = 0; i < optMods.size(); ++i)
		{
			if (mod == optMods.at(i))
			{
				chrList.push_back(chrs.at(i));
				timeList.push_back(optTs.at(i));
			}
		}
		TWeights.clear();
		//calculate weights, mean and variance accordingly
		TWeights = segs->getWeights(chrList, cutoff);
		meanT = mean(timeList, TWeights);
		varT = var(timeList, TWeights, meanT);
		cout << "Optimal-model: " << mod << "(" << perc << "%); ";
		cout << "Optimal-generation: (" << meanT << " ± " << sqrt(varT) << ")" << endl;
	}
	cout << "================================================================================" << endl;

	//output the likelihoods

	//clean stuff
	if (par)
		delete par;
	if (segs)
		delete segs;
	if (indexes)
		delete[] indexes;
	if (globalMax)
		delete[] globalMax;
	if (llks)
	{
		for (int i = 0; i < nchrs; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				delete[] llks[i][j];
			}
			delete[] llks[i];
		}
		delete[] llks;
	}
	if (jack_llk)
	{
		for (int i = 0; i < nchrs; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				delete[] jack_llk[i][j];
			}
			delete[] jack_llk[i];
		}
		delete[] jack_llk;
	}
	return 0;
}

