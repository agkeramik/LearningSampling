#ifndef MIXTURESAMPLER_H
#define MIXTURESAMPLER_H

#include "mgmm.h"
#include "Model/furniturecatalog.h"
#include <vector>
#include "Model/room.h"


class RoomSampler
{
    const MGMM &mixtures;
    const FurnitureCatalog &catalog;
    const int MAX_TRIES;
private:
    void transformLocalToGlobal(arma::Col<double> &v, const arma::Col<double> &transformed);
    int pickFromCDF(const vector<double> &cdf);
    bool place(Furniture &toPlace, Room &room);
    bool accept(Furniture &f, Room &room);
public:
    RoomSampler(const MGMM &_mixtures, const FurnitureCatalog &_catalog, int _MAX_TRIES=15);
    void sample(Room *room,std::vector<std::string> &toAddIds);
    virtual ~RoomSampler();
};

#endif // MIXTURESAMPLER_H
