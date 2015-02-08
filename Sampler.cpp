#include "Sampler.h"
#include "Scene.h"

Sampler::Sampler(MContext* context){
    this->context = context;
}

int Sampler::pickFromCDF(vector<double> &cdf){
    double total = cdf[cdf.size()-1];
    double choice = total * (double)std::rand() / RAND_MAX;

    for (int i = 0; i < cdf.size(); ++i)
        if (choice <= cdf[i])
            return i;
    return -1;
}

void Sampler::transformLocalToGlobal(arma::Col<double> &v, arma::Col<double> &transformed){
    v(0) = v(0)*cos(transformed(2)) - v(1)*sin(transformed(2));
    v(1) = v(1)*cos(transformed(2)) + v(0)*sin(transformed(2));

    v(0)+=transformed(0);
    v(1)+=transformed(1);

    v(2)+=transformed(2);
}

bool Sampler::accept(Furniture &f, vector<Furniture*> &furnitures){
    for (int i = 0; i < furnitures.size(); ++i)
        if (f.collision(*(furnitures[i])))
            return false;
    return true;
}

bool Sampler::place(Furniture* toPlace){
    vector<Furniture*> alreadyPlaced = this->context->scene.furnitures;
    vector<const WeightedMixture*> weightedGMMS;
    vector<double> cdf;

    double total = 0;
    for (int i = 0; i < alreadyPlaced.size(); ++i){
        const WeightedMixture &wgmm = this->context->mixtures->getMixture(toPlace->catalogId, alreadyPlaced[i]->catalogId);
        total += wgmm.second;
        cdf.push_back(total);
        weightedGMMS.push_back(&wgmm);
    }

    int MAX_TRIES = 5;

    bool ok = false;
    int nbTries = 0;
    while (!ok && nbTries <= MAX_TRIES){
        int choice = pickFromCDF(cdf);

        arma::Col<double> v = weightedGMMS[choice]->first.Random();
        Furniture *relativeFurniture = alreadyPlaced[choice];

        transformLocalToGlobal(v, relativeFurniture->features);
        toPlace->setFeatureVector(v);

        ok = accept(*toPlace, alreadyPlaced);
        ++nbTries;
    }

    if (ok)
        this->context->scene.furnitures.push_back(toPlace);
    return ok;
}

void Sampler::furnish(vector<Furniture*> &toPlace){
    vector<Furniture*> rejected;
    for (int i = 0; i < toPlace.size(); ++i)
        if (!place(toPlace[i]))
            rejected.push_back(toPlace[i]);
}

void Sampler::furnish(){ this->furnish(this->context->toAdd);}

