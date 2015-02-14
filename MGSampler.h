#ifndef MGSAMPLER_H
#define MGSAMPLER_H

#include "Sampler.h"

using namespace std;

class MGSampler :
	public Sampler
{
private:
    void transformLocalToGlobal(arma::Col<double> &v, const arma::Col<double> &transformed);
	int pickFromCDF(const vector<double> &cdf);
public:
    MGSampler(Context *context);
    virtual ~MGSampler();
	virtual bool place(Furniture &toPlace);
    virtual bool accept(Furniture &toPlace, vector<Furniture*> &furnitures);
    virtual void furnish(vector<Furniture> &toPlace);
	virtual void furnish();
};

#endif
