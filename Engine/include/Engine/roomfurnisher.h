#ifndef ROOMFURNISHER_H
#define ROOMFURNISHER_H

#include "roomoptimiser.h"
#include "roomsampler.h"
#include "bayesiansampler.h"
#include "anglesnapper.h"
#include "Engine/sidetableplacer.h"

#include "Utils/properties.h"
#include "Model/furniturecatalog.h"
#include "Model/room.h"
#include <vector>


class RoomFurnisher
{
    BayesianSampler *bs;
    RoomSampler *rs;
    RoomOptimiser *opt;
    Cost *c;
    AngleSnapper *snapper;
    FurnitureCatalog *catalog;
    SideTablePlacer *sideTablePlacer;

public:
    RoomFurnisher(RoomSampler *_rs, const Properties &props, FurnitureCatalog *catalog);
    std::vector<Room> furnish(const Room &roomProp);
    virtual ~RoomFurnisher();
};

#endif // ROOMFURNISHER_H
