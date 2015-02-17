#include "MGSampler.h"


MGSampler::MGSampler(Context *context) : Sampler(context)
{
}


MGSampler::~MGSampler()
{
}


int MGSampler::pickFromCDF(const vector<double> &cdf){
    double total = cdf[cdf.size()-1];
    double choice = total * (double)std::rand() / RAND_MAX;

    for (int i = 0; i < cdf.size(); ++i)
        if (choice <= cdf[i])
            return i;
    return -1;
}

void MGSampler::transformLocalToGlobal(arma::Col<double> &v, const arma::Col<double> &transformed){
    double x,y;
    x = v(0)*cos(transformed(2)) - v(1)*sin(transformed(2));
    y = v(1)*cos(transformed(2)) + v(0)*sin(transformed(2));

    v(0)=transformed(0)+x;
    v(1)=transformed(1)+y;

    v(2)=transformed(2)+v(2);
}

bool MGSampler::accept(Furniture &f, vector<Furniture*> &furnitures){
    DEBUG( "\tAccept Condition For:\n\t\t");DEBUG_LINE(f.getTransformedGeometry());
    for (int i = 0; i < furnitures.size(); ++i)
        if (f.collision(*(furnitures[i]))){
            DEBUG( "\t We have collision between ");DEBUG(f.catalogId);DEBUG(" and ");DEBUG_LINE(furnitures[i]->catalogId);
            DEBUG("\t\t");DEBUG_LINE(furnitures[i]->getTransformedGeometry());
            return false;
        }
    return true;
}

bool MGSampler::place(Furniture& toPlace){
    vector<Furniture*> alreadyPlaced = this->context->room.getFurnitures();
    vector<const WeightedMixture*> weightedGMMS;
    vector<double> cdf;

    double total = 0;

    DEBUG( ">>>>>>>>>>>>Placing ");DEBUG( toPlace.catalogId);DEBUG_LINE("<<<<<<<<<<<<<");
    DEBUG( "\tScene contains ");DEBUG(alreadyPlaced.size());DEBUG_LINE(" furnitures");
    for (int i = 0; i < alreadyPlaced.size(); ++i){
        const WeightedMixture &wgmm = this->context->mixtures.getMixture(toPlace.catalogId, alreadyPlaced[i]->catalogId);
        total += wgmm.second;
        cdf.push_back(total);
        weightedGMMS.push_back(&wgmm);
        DEBUG( "\t\tMixture "); DEBUG(toPlace.catalogId); DEBUG("-");DEBUG(alreadyPlaced[i]->catalogId);DEBUG(" has a weight of: ");DEBUG_LINE(wgmm.second);
    }

    bool ok = false;
    int nbTries = 0;
    while (!ok && nbTries <= MAX_TRIES){
        DEBUG("\tTry #:"); DEBUG_LINE(nbTries);

        int choice = pickFromCDF(cdf);

        DEBUG("\t\tPicked mixture #:"); DEBUG_LINE(choice);

        arma::Col<double> v = weightedGMMS[choice]->first.Random();
        DEBUG_LINE( "\t\tMixture gave this vector:" ); DEBUG("\t\t"); DEBUG_LINE(v);

        Furniture *relativeFurniture = alreadyPlaced[choice];

        transformLocalToGlobal(v, relativeFurniture->features);
        DEBUG_LINE( "\t\tTransformation gave this vector:"); DEBUG("\t\t"); DEBUG_LINE(v);

        toPlace.setFeatureVector(v);

        ok = accept(toPlace, alreadyPlaced);
        ++nbTries;
    }

    if (ok)
        this->context->room.addFurniture(toPlace);
    return ok;
}

void MGSampler::furnish(vector<Furniture> &toPlace){
    vector<Furniture*> rejected;
    for (int i = 0; i < toPlace.size(); ++i)
        if (!place(toPlace[i]))
            rejected.push_back(&(toPlace[i]));
}

void MGSampler::furnish(){ this->furnish(this->context->toAdd);}
