#include "MGMM.h"


MGMM::MGMM()
{
}

MGMM::WeightedGMM* MGMM::getWeightedGMM(Furniture& f1, Furniture& f2){
	return this->gmms[f1.catalogId][f2.catalogId];
}

void MGMM::loadGMMs(std::string filename){
	std::cout << "loadGMMs not implements" << std::endl;
}

MGMM::~MGMM()
{
}
