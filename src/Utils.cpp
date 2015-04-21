/*
 * Utils.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: young
 */

#include "Utils.h"

//find the index of max
int indexOfMax(const double * data, int size)
{
	double maxVal = data[0];
	int index = 0;
	for (int i = 1; i < size; ++i)
	{
		if (data[i] > maxVal)
		{
			maxVal = data[i];
			index = i;
		}
	}
	return index;
}

//perform summation, i.e. return s=∑data
double sum(const vector<double> &data)
{
	double sum = 0;
	size_t size = data.size();
	for (size_t i = 0; i < size; ++i)
	{
		sum += data.at(i);
	}
	return sum;
}

//non-weighted mean, mean = ∑data(i) / n;
double mean(const vector<double> &data)
{
	return sum(data) / data.size();
}

//non-weighted variance, given data and mean
//var = ∑(data(i)-mean)^2/ (n-1)
double var(const vector<double> &data, double avg)
{
	double sum = 0;
	size_t size = data.size();
	for (size_t i = 0; i < size; ++i)
	{
		sum += (data.at(i) - avg) * (data.at(i) - avg);
	}
	return sum / (size - 1);
}

//weighted mean, mean = ∑data(i)*weight(i)
double mean(const vector<double> &data, const vector<double> &weights)
{
	double sum = 0;
	size_t size = data.size();
	for (size_t i = 0; i < size; ++i)
	{
		sum += data.at(i) * weights.at(i);
	}
	return sum;
}

//weighted variance, var = ∑weight(i)*(data(i)-mean)^2
double var(const vector<double> &data, const vector<double> &weights, double avg)
{
	double sum = 0;
	size_t size = data.size();
	for (size_t i = 0; i < size; ++i)
	{
		sum += (data.at(i) - avg) * (data.at(i) - avg) * weights.at(i);
	}
	return sum;
}

