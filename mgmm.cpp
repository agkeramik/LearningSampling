#include "mgmm.h"
#include <fstream>
#include <iostream>
#include <map>
#include "datafiles.h"
#include <mlpack/core.hpp>

#include <mlpack/methods/gmm/gmm.hpp>
#include <mlpack/methods/gmm/phi.hpp>

#include <mlpack/methods/gmm/no_constraint.hpp>
#include <mlpack/methods/gmm/positive_definite_constraint.hpp>
#include <mlpack/methods/gmm/diagonal_constraint.hpp>
#include <mlpack/methods/gmm/eigenvalue_ratio_constraint.hpp>

MGMM::MGMM(const char *fileName,const char *directoryOfGMMs)
{
    std::ifstream fin;
    std::map<std::string,double> list=DataFiles::readF1F2WeightFile(fileName);
    for (std::map<std::string,double>::iterator it=list.begin();it!=list.end();++it){
        mlpack::gmm::GMM<> gmm;
        if(it->second!=0){
            std::string s=directoryOfGMMs;
            s=s+"/"+it->first+".xml";
            gmm.Load(s.c_str());
        }
        gmms.insert(std::make_pair(it->first,std::make_pair(gmm,it->second)));
    }
}

const WeightedMixture &MGMM::getMixture(std::string fur1,std::string givenfur2) const
{
    GMMMap::const_iterator it=gmms.find(fur1+"-"+givenfur2);
    if(it!=gmms.end())
        return it->second;
    std::string e("Key not found in MGMM: "+fur1+"-"+givenfur2);
    throw e.c_str();
}

void MGMM::print()
{
    for(GMMMap::iterator it=gmms.begin();it!=gmms.end();++it){
            std::cout<<it->first<<"   weight: "<<it->second.second<<std::endl;
            mlpack::gmm::GMM<> gmmBest=it->second.first;
            for(int n = 0; n < gmmBest.Gaussians(); ++n)
            {
                std::cout << "mean[" << n << "] = " << gmmBest.Means()[n].t();
                std::cout << "cov.[" << n << "] = " << gmmBest.Covariances()[n].t();
                std::cout << "wei.[" << n << "] = " << gmmBest.Weights()[n] << std::endl;
            }
    }
}
