#include "finealignment.h"

FineAlignment::FineAlignment(double weight, const Room &room):Cost(weight)
{
    assignFurnToBlock(room);
}

double FineAlignment::calculate(const Room &room) const
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
    return weight*sqrt(sum);
}

void FineAlignment::assignFurnToBlock(const Room &room){

    blocks02.clear();
    blocks13.clear();

    std::vector<ClipperLib::Path> blockPath;

    double tlx=room.getTopLeftCornerX();
    double tly=room.getTopLeftCornerY();
    double brx=room.getBottomRightCornerX();
    double bry=room.getBottomRightCornerY();
    double s=95;
    double sc=80;
    ClipperLib::Path p;
    p<<ClipperLib::IntPoint(tlx,tly+sc)<<ClipperLib::IntPoint(tlx+s,tly+sc)
    <<ClipperLib::IntPoint(tlx+s,bry-sc)<<ClipperLib::IntPoint(tlx,bry-sc)
    <<ClipperLib::IntPoint(tlx,tly+sc);
    blockPath.push_back(p);
    p.clear();

    p<<ClipperLib::IntPoint(tlx+sc,tly+s)<<ClipperLib::IntPoint(tlx+sc,tly)
    <<ClipperLib::IntPoint(brx-sc,tly)<<ClipperLib::IntPoint(brx-sc,tly+s)
    <<ClipperLib::IntPoint(tlx+sc,tly+s);
    blockPath.push_back(p);
    p.clear();

    p<<ClipperLib::IntPoint(brx,tly+sc)<<ClipperLib::IntPoint(brx,bry-sc)
    <<ClipperLib::IntPoint(brx-s,bry-sc)<<ClipperLib::IntPoint(brx-s,tly+sc)
    <<ClipperLib::IntPoint(brx,tly+sc);
    blockPath.push_back(p);
    p.clear();

    p<<ClipperLib::IntPoint(tlx+sc,bry)<<ClipperLib::IntPoint(tlx+sc,bry-s)
    <<ClipperLib::IntPoint(brx-sc,bry-s)<<ClipperLib::IntPoint(brx-sc,bry)
    <<ClipperLib::IntPoint(tlx+sc,bry);
    blockPath.push_back(p);
    p.clear();

    const vector<Furniture> &furnitures=room.getFurnitures();
    for(unsigned int i=0;i<furnitures.size();++i){
        double interArea=0;
        int ind=0;
        ClipperLib::Path pf=furnitures[i].getGlobalGeometry();
        for(unsigned int j=0;j<blockPath.size();++j){
            double tempArea=Global::intersectionArea(blockPath[j],pf);
            //cout<<"block "<<j<<" Furniture "<<i<<":\n"<<tempArea<<endl;
            if(tempArea>interArea){
                interArea=tempArea;
                ind=j;
            }
        }
        if(interArea>0.35*furnitures[i].width*furnitures[i].depth){
            if(ind%2==0)
                blocks02.push_back(i);
            else
                blocks13.push_back(i);
        }
    }
    //    for(unsigned int i=0;i<blocks.size();++i){
    //        cout<<"Block "<<i<<" \n";
    //        for(unsigned int j=0;j<blocks[i].size();++j){
    //            furnitures[blocks[i][j]].print(cout);
    //        }
    //    }
    return;
}
