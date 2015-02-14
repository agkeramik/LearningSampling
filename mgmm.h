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
    static std::map<std::string, double> readF1F2WeightFile(const char * fileName);
    static double calcAIC(int nbGaussians, int nbDimensions, double logLikelihood, double sampleSize);
    static mlpack::gmm::GMM<> getGMM(arma::mat &A);
    MGMM();

public:
     static double findGap(arma::vec &t);
    //To be made private
    //MGMM(const char *fileName,const char *directoryOfGMMs);
    static MGMM learnMGMM(const char *fileName,const char *dataDirectory);
    static MGMM loadMGMM(const char *fileName, const char *directoryOfGMMs);
    const WeightedMixture &getMixture(std::string fur1,std::string givenfur2) const;
    void save(const char *directory) const;
    void print() const;
};

#endif // MGMM_H
