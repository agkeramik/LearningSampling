#include "mgmm.h"
#include <fstream>
#include <iostream>
#include <map>
#include <mlpack/core.hpp>

#include <mlpack/methods/gmm/gmm.hpp>
#include <mlpack/methods/gmm/phi.hpp>

#include <mlpack/methods/gmm/no_constraint.hpp>
#include <mlpack/methods/gmm/positive_definite_constraint.hpp>
#include <mlpack/methods/gmm/diagonal_constraint.hpp>
#include <mlpack/methods/gmm/eigenvalue_ratio_constraint.hpp>

#ifdef WINDOWS
#include <direct.h>
#include <windows.h>
#define GetCurrentDir _getcwd
#define CreateDir CreateDirectory
#else
#include <unistd.h>
#include <sys/stat.h>
#define GetCurrentDir getcwd
#define CreateDir mkdir
#endif

double MGMM::findGap(arma::vec &t)
{
    arma::vec c=arma::sort(t);
    double dist=-1;
    unsigned int ind=0;
    for (unsigned int i=0;i<c.n_rows-1;++i){
        if((c(i)-c(i+1))*(c(i)-c(i+1))>dist){
            dist=(c(i)-c(i+1))*(c(i)-c(i+1));
            ind=i;
        }
    }
    return .5*(c(ind)+c(ind+1));
}

std::map<std::string, double> MGMM::readF1F2WeightFile(const char *fileName)
{
        std::ifstream fin;
        fin.open(fileName);
        std::string line;
        if (!fin.is_open()){
            std::cout<<"unable to open file "<<fileName;
        }
        std::map<std::string,double> furnDB;
        int i=0;
        std::string file;
        while(std::getline(fin,line)){
           if (i==0){
               if(line.find('-')!=std::string::npos){
                   file=line;
                   i=1;
               }
           }else{
               //not checking if line is empty
               double weight=atof(line.c_str());
               furnDB.insert(std::pair<std::string,double>(file,weight));
               i=0;
           }
        }
        fin.close();
        std::cout<<furnDB.size()<<std::endl;
        return furnDB;
}

double MGMM::calcAIC(int nbGaussians, int nbDimensions, double logLikelihood, double sampleSize)
{
    double nbParameters = nbGaussians - 1 + nbGaussians * (nbDimensions + 0.5 * nbDimensions * (nbDimensions + 1));
    return 2 * (nbParameters) - 2 * logLikelihood + 2 * nbParameters * (nbParameters + 1.) / (sampleSize - nbParameters - 1);
}

mlpack::gmm::GMM<> MGMM::getGMM(arma::mat &A)
{
    int numDim=A.n_rows;
    int sampleSize = A.n_cols;
    //find the gap
    arma::vec theta=A.row(numDim-1).t();

    double gap=MGMM::findGap(theta);
    std::cout<<gap<<std::endl;
    for(int i=0;i<A.n_cols;++i)
        if(A(numDim-1,i)>gap)
            A(numDim-1,i)-=2.0*arma::datum::pi;


    double bestAIC = std::numeric_limits<double>::max();

    mlpack::gmm::GMM<> gmmBest;

    int MAX_GAUSSIANS = 25;
    int NB_TRIES = 20;
    for (int i = 1; i <= MAX_GAUSSIANS; ++i){
        double bestLocalAIC = std::numeric_limits<double>::max();
        mlpack::gmm::GMM<> bestLocalGMM;
        for (int j = 0; j < NB_TRIES; ++j){
            try{
                mlpack::gmm::GMM<> gmmCur(i, numDim);
                double logLikelihood = gmmCur.Estimate(A,1);
                double currAIC = calcAIC(i, numDim, logLikelihood, sampleSize);
                if (currAIC < bestLocalAIC){
                    bestLocalAIC = currAIC;
                    bestLocalGMM = gmmCur;
                }
            } catch (const std::exception& ex){
                std::cout<<"caught exception"<<std::endl;
            }
        }

        //		std::cout << bestLocalAIC << std::endl;

        if (bestLocalAIC < bestAIC){
            bestAIC = bestLocalAIC;
            gmmBest = bestLocalGMM;
        }else{
            return gmmBest;	//quits on first regression
        }
    }
    return gmmBest;
}

MGMM::MGMM()
{

}

//MGMM::MGMM(const char *fileName,const char *directoryOfGMMs)
//{

//}

MGMM MGMM::learnMGMM(const char *fileName, const char *dataDirectory)
{
    MGMM model;
    std::map<std::string,double> map=MGMM::readF1F2WeightFile(fileName);
   // CreateDir(prop.getGMMsFolder().c_str(),0777);

    for(std::map<std::string,double>::iterator it=map.begin();it!=map.end();++it){
        if(it->second!=0){
            std::string dataFileName=std::string(dataDirectory)+it->first;
            arma::mat dat;
            dat.load(dataFileName.c_str());
            dat=dat.t();

            mlpack::gmm::GMM<> gmmBest = getGMM(dat);
            model.gmms.insert(std::make_pair(it->first,std::make_pair(gmmBest,it->second)));
        }
    }
    return model;
}

MGMM MGMM::loadMGMM(const char *fileName, const char *directoryOfGMMs)
{
    MGMM model;
    std::ifstream fin;
    const std::map<std::string,double> &list=MGMM::readF1F2WeightFile(fileName);
    for (std::map<std::string,double>::const_iterator it=list.begin();it!=list.end();++it){
        mlpack::gmm::GMM<> gmm;
        if(it->second!=0){
            std::string s=directoryOfGMMs;
            s=s+"/"+it->first+".xml";
            gmm.Load(s.c_str());
        }
        model.gmms.insert(std::make_pair(it->first,std::make_pair(gmm,it->second)));
    }
    return model;
}

const WeightedMixture &MGMM::getMixture(std::string fur1,std::string givenfur2) const
{
    GMMMap::const_iterator it=gmms.find(fur1+"-"+givenfur2);
    if(it!=gmms.end())
        return it->second;
    std::string e("Key not found in MGMM: "+fur1+"-"+givenfur2);
    throw e.c_str();
}

void MGMM::save(const char *directory) const
{
    CreateDir(directory,0777);
    for(GMMMap::const_iterator it=gmms.begin();it!=gmms.end();++it){
        if(it->second.second!=0){
            std::string gmmFileName=std::string(directory)+it->first+".xml";
            it->second.first.Save(gmmFileName.c_str());
        }
    }
}

void MGMM::print() const
{
    for(GMMMap::const_iterator it=gmms.begin();it!=gmms.end();++it){
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
