/*
 * Utils.h
 *
 *  Created on: Mar 23, 2015
 *  Author: young
 *  a set of helper functions
 *  indexOfMax, find the index of value, given a array of data
 *  sum, sum over a list of data
 *  mean, calculate the mean value of given data, either weighted or non-weighted
 *  var, calculate the variance of of given data, either weighted or non-weighted
 */
#include <vector>

using namespace std;

int indexOfMax(double * data, int size);
double sum(vector<double> data);
double mean(vector<double> data);
double mean(vector<double> data, vector<double> weights);
double var(vector<double> data, double avg);
double var(vector<double> data, vector<double> weights, double avg);

