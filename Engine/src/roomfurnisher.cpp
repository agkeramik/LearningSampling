#include "Engine/roomfurnisher.h"

#include "Engine/costcomposite.h"

#include "Engine/distancecost.h"
#include "Engine/clearancecost.h"
#include "Engine/collisioncost.h"
#include "Engine/finealignment.h"
#include "Engine/expansioncost.h"
#include "Engine/conversationcost.h"
#include "Engine/balancecost.h"

#include <iostream>

RoomFurnisher::RoomFurnisher(RoomSampler *_rs, const Properties &props):
    rs(_rs)
{
    bs=new BayesianSampler();
    c=new CostComposite();
    snapper=new AngleSnapper(45,9);
    CostComposite *cc=(CostComposite*) c;
    cc->addComponent(new DistanceCost(10));
    cc->addComponent(new ClearanceCost(400));
    cc->addComponent(new ConversationCost(0.5,props.getConversationProp().c_str()));
    cc->addComponent(new CollisionCost(10000000));
    cc->addComponent(new BalanceCost(0.4));
    cc->addComponent(new ExpansionCost(40));
    opt=new RoomOptimiser(c);
}

std::vector<Room> RoomFurnisher::furnish(const Room &roomProp)
{
    const int samples=40;
    int *permIndex=new int[samples];
    double *cost=new double[samples];

    std::vector<std::string> toAddList=bs->sample();
    std::vector<Room> roomSamples;
    for(int i=0;i<samples;++i){
        Room room(roomProp);
        rs->sample(&room,toAddList);
        opt->optimise(room);
        CostComposite *cc=new CostComposite();
        Cost *alig=new FineAlignment(10,room);
        cc->addComponent(alig);
        cc->addComponent(c);
        RoomOptimiser alopt(cc);
        alopt.optimise(room);
        delete alig;
        delete cc;
        snapper->snapFurntiureAngles(room);
        cost[i]=c->calculate(room);
        permIndex[i]=i;
        roomSamples.push_back(room);
    }

    //Sorting rooms
    for(int i=0;i<samples-1;++i){
        for(int j=i+1;j<samples;++j){
            if(cost[permIndex[i]]>cost[permIndex[j]]){
                int temp=permIndex[i];
                permIndex[i]=permIndex[j];
                permIndex[j]=temp;
            }
        }
    }

    std::vector<Room> sortedSamples;
    for(int i=0;i<samples;++i){
        std::cout<<"Room "<<i<<std::endl;
        std::cout<<cost[permIndex[i]];
        std::cout<<std::endl;
        sortedSamples.push_back(roomSamples[permIndex[i]]);
    }
    delete permIndex;
    delete cost;

    return sortedSamples;
}


RoomFurnisher::~RoomFurnisher()
{
    delete opt;
    delete bs;
    c->cleanMemory();
    delete c;
    delete snapper;
}
