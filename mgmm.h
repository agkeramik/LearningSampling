#ifndef MGMM_H
#define MGMM_H
#include <map>
#include <mlpack/methods/gmm/gmm.hpp>
#include <string>

typedef std::pair<mlpack::gmm::GMM<>,double> WeightedMixture;
typedef std::map<std::string,WeightedMixture> GMMMap;

class MGMM
{
    GMMMap gmms;
public:
    MGMM(const char *fileName,const char *directoryOfGMMs);
    const WeightedMixture &getMixture(std::string fur1,std::string givenfur2) const;
    void print();
};

#endif // MGMM_H
