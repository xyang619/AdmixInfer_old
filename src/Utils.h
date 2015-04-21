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

int indexOfMax(const double * data, int size);

double sum(const vector<double> & data);

double mean(const vector<double> & data);

double mean(const vector<double> &data, const vector<double> &weights);

double var(const vector<double> &data, double avg);

double var(const vector<double> &data, const vector<double> &weights, double avg);

