#include "MContext.h"
#include <vector>

using namespace std;

class Sampler{
public:
    MContext* context;

    Sampler(MContext* context);
    int pickFromCDF(vector<double> &cdf);
    void transformLocalToGlobal(arma::Col<double> &v, arma::Col<double> &transformed);
    bool accept(Furniture &f, vector<Furniture*> &furnitures);
    bool place(Furniture* toPlace);
    void furnish(vector<Furniture*> &toPlace);
    void furnish();
};
