#pragma once
#include <map>
#include <string>
#include <mlpack/methods/gmm/gmm.hpp>
#include "Furniture.h"

class MGMM
{
public:
	class WeightedGMM {
	public:
		int id;
		double weight;
		mlpack::gmm::GMM<> gmm;
	};

	MGMM();
	void loadGMMs(std::string filename);

	std::map<std::string, std::map<std::string, WeightedGMM*> > gmms;
    WeightedGMM* getWeightedGMM(Furniture& f1, Furniture& f2);

	virtual ~MGMM();
};

