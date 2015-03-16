#include "manhattancostcalculator.h"
#include <cmath>
#include <iostream>

ManhattanCostCalculator::ManhattanCostCalculator(std::vector<std::vector<int> > _blocks)
    :blocks02(_blocks[0]),blocks13(_blocks[1])
{
    for(unsigned int i=0;i<_blocks[2].size();++i)
        blocks02.push_back(_blocks[2][i]);
    for(unsigned int i=0;i<_blocks[3].size();++i)
        blocks13.push_back(_blocks[3][i]);

    std::cout<<"\nBlocks02:\n";
    for(int i=0;i<blocks02.size();++i)
        std::cout<<blocks02[i]<<" ";
    std::cout<<"\nBlocks13\n";
    for(int i=0;i<blocks13.size();++i)
        std::cout<<blocks13[i]<<" ";
    std::cout<<std::endl;

}

void ManhattanCostCalculator::print(std::ostream &out)
{
    out<<"Manhattan Cost:";
}


double ManhattanCostCalculator::calculateCost(const Room &room)
{
    const std::vector<Furniture> &furnitures=room.getFurnitures();
    //assume that we have a table in the room
    int tableIndex=-1;
    for(unsigned int i=0;i<furnitures.size();++i){
        if(furnitures[i].catalogId.find("Renouzate#Table")!=std::string::npos){
            tableIndex=i;
            break;
        }
    }
//    std::cout<<"TableIndex="<<tableIndex<<std::endl;
    //work on even blocks
    //evaluate y differences
    double sum=0;
    for(unsigned int i=0;i<blocks02.size()-1;++i){
        for(unsigned j=i+1;j<blocks02.size();++j){
            Vec2 a(furnitures[blocks02[i]].getY()-furnitures[blocks02[j]].getY(),0);
//            cout<<"i="<<i<<" ,j="<<j<<" ("<<a.x<<", "<<a.y<<")\n";
            sum+=a.lengthSqrd();
        }
    }
    //work on odd blocks
    //evaluate x differences
    for(unsigned int i=0;i<blocks13.size()-1;++i){
        for(unsigned j=i+1;j<blocks13.size();++j){
            Vec2 a(furnitures[blocks13[i]].getX()-furnitures[blocks13[j]].getX(),0);
//            cout<<"i="<<i<<" ,j="<<j<<" ("<<a.x<<", "<<a.y<<")\n";
            sum+=a.lengthSqrd();
        }
    }
    //with table
    for(unsigned int i=0;i<blocks02.size();++i)
        sum+=Vec2(furnitures[blocks02[i]].getY()-furnitures[tableIndex].getY(),0).lengthSqrd();
    for(unsigned int i=0;i<blocks13.size();++i)
        sum+=Vec2(furnitures[blocks13[i]].getX()-furnitures[tableIndex].getX(),0).lengthSqrd();
    return sqrt(sum);
}

ManhattanCostCalculator::~ManhattanCostCalculator()
{

}
