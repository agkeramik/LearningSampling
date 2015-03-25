#include "Engine/roomsampler.h"
#include "Model/Furniture.h"


RoomSampler::RoomSampler(const MGMM &_mixtures,const FurnitureCatalog &_catalog,int _MAX_TRIES):
    mixtures(_mixtures),
    catalog(_catalog),
    MAX_TRIES(_MAX_TRIES)
{

}

int RoomSampler::pickFromCDF(const vector<double> &cdf){
    double total = cdf[cdf.size()-1];
    double choice = total * (double)std::rand() / RAND_MAX;

    for (unsigned int i = 0; i < cdf.size(); ++i)
        if (choice <= cdf[i])
            return i;
    return -1;
}

void RoomSampler::transformLocalToGlobal(arma::Col<double> &v, const arma::Col<double> &transformed){
    double x,y;
    x = v(0)*cos(transformed(2)) - v(1)*sin(transformed(2));
    y = v(1)*cos(transformed(2)) + v(0)*sin(transformed(2));

    v(0)=transformed(0)+x;
    v(1)=transformed(1)+y;

    v(2)=transformed(2)+v(2);
}
void RoomSampler::sample(Room *room, std::vector<string> &toAddIds)
{
    if(room==NULL)
        return;
    //Construct the vector of furnitures toAdd from the vector of catalogIds toAddIds
    std::vector<Furniture> toAdd;
    for(unsigned int i=0;i<toAddIds.size();++i)
        toAdd.push_back(catalog.getNewFurniture(toAddIds[i]));
    //Order of placement follows the index in toAdd/toAddIds
    vector<Furniture> rejected;
    for (unsigned int i = 0; i < toAdd.size(); ++i)
        if (!place(toAdd[i],*room))
            rejected.push_back(toAdd[i]);

}

bool RoomSampler::place(Furniture &toPlace,Room &room)
{
    vector<Furniture> &alreadyPlaced = room.getFurnitures();
    vector<const WeightedMixture*> weightedGMMS;
    vector<double> cdf;

    double total = 0;
    DEBUG( ">>>>>>>>>>>>Placing ");DEBUG( toPlace.catalogId);DEBUG_LINE("<<<<<<<<<<<<<");
    DEBUG( "\tScene contains ");DEBUG(alreadyPlaced.size());DEBUG_LINE(" furnitures");
    for (unsigned int i = 0; i < alreadyPlaced.size(); ++i){
        const WeightedMixture &wgmm = mixtures.getMixture(toPlace.catalogId, alreadyPlaced[i].catalogId);
        total += wgmm.second;
        cdf.push_back(total);
        weightedGMMS.push_back(&wgmm);
        DEBUG( "\t\tMixture "); DEBUG(toPlace.catalogId); DEBUG("-");DEBUG(alreadyPlaced[i].catalogId);
        DEBUG(" has a weight of: ");DEBUG_LINE(wgmm.second);
    }

    bool ok = false;
    int nbTries = 0;
    while (!ok && nbTries <= MAX_TRIES){
        DEBUG("\tTry #:"); DEBUG_LINE(nbTries);

        int choice = pickFromCDF(cdf);

        DEBUG("\t\tPicked mixture #:"); DEBUG_LINE(choice);
        Furniture &relativeFurniture = alreadyPlaced[choice];
        arma::Col<double> v = weightedGMMS[choice]->first.Random();
        DEBUG_LINE( "\t\tMixture gave this vector:" ); DEBUG("\t\t"); DEBUG_LINE(v);



        transformLocalToGlobal(v, relativeFurniture.features);
        DEBUG_LINE( "\t\tTransformation gave this vector:"); DEBUG("\t\t"); DEBUG_LINE(v);

        toPlace.setFeatureVector(v);

        ok = accept(toPlace,room);
        ++nbTries;
    }
    if (ok)
        room.addFurniture(toPlace);
    return ok;
}

bool RoomSampler::accept(Furniture &f,Room &room)
{
    std::vector<Furniture> &furnitures=room.getFurnitures();
    if (f.getX()<room.getTopLeftCornerX() ||
            f.getX()>room.getBottomRightCornerX() ||
            f.getY()<room.getTopLeftCornerY() ||
            f.getY()>room.getBottomRightCornerY())
        return false;

    DEBUG( "\tAccept Condition For:\n\t\t");DEBUG_LINE(f.getGlobalGeometry());
    for (unsigned int i = 0; i < furnitures.size(); ++i)
        if (f.collision((furnitures[i]))){
            DEBUG( "\t We have collision between ");DEBUG(f.catalogId);DEBUG(" and ");DEBUG_LINE(furnitures[i].catalogId);
            DEBUG("\t\t");DEBUG_LINE(furnitures[i].getGlobalGeometry());
            return false;
        }

    const std::vector<Furniture> &doors=room.getDoors();
    for (unsigned int i=0;i<doors.size();++i)
        if (f.collision((doors[i]))){
            DEBUG( "\t We have collision between ");DEBUG(f.catalogId);DEBUG(" and ");DEBUG_LINE(doors[i].catalogId);
            DEBUG("\t\t");DEBUG_LINE(doors[i].getGlobalGeometry());
            return false;
        }
    return true;
}

RoomSampler::~RoomSampler()
{

}
