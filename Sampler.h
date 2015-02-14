#ifndef SAMPLER_H
#define SAMPLER_H

#include "Context.h"
#include "Furniture.h"
#include <vector>

using namespace std;

class Sampler{
public:
    Context *context;
	int MAX_TRIES;

    Sampler(Context *context);
	virtual bool place(Furniture &toPlace) = 0;
    virtual bool accept(Furniture &toPlace, vector<Furniture*> &furnitures) = 0;
    virtual void furnish(vector<Furniture> &toPlace) = 0;
	virtual void furnish() = 0;
	virtual ~Sampler();
};

#endif
