#ifndef BAYESIANSAMPLER_H
#define BAYESIANSAMPLER_H

#include <vector>
#include <string>

class BayesianSampler
{
public:
    BayesianSampler();
    std::vector<std::string> sample();
};

#endif // BAYESIANSAMPLER_H
