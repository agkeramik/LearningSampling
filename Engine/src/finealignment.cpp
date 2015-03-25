#include "Engine/finealignment.h"

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
#ifdef FACGM
    //find center of gravity of each block
    std::vector<double> yalig;
    if(block0.size()>0){
        double yG=0;
        double totalSurface=0;
        for(unsigned int i=0;i<block0.size();++i){
            totalSurface+=furnitures[block0[i]].getSurface();
            yG+=furnitures[block0[i]].getY()*furnitures[block0[i]].getSurface();
        }
        yalig.push_back(yG/totalSurface);
    }
    if(block2.size()>0){
        double yG=0;
        double totalSurface=0;
        for(unsigned int i=0;i<block2.size();++i){
            totalSurface+=furnitures[block2[i]].getSurface();
            yG+=furnitures[block2[i]].getY()*furnitures[block2[i]].getSurface();
        }
        yalig.push_back(yG/totalSurface);
    }
    std::vector<double> xalig;
    if(block1.size()>0){
        double xG=0;
        double totalSurface=0;
        for(unsigned int i=0;i<block1.size();++i){
            totalSurface+=furnitures[block1[i]].getSurface();
            xG+=furnitures[block1[i]].getX()*furnitures[block1[i]].getSurface();
        }
        xalig.push_back(xG/totalSurface);
    }
    if(block3.size()>0){
        double xG=0;
        double totalSurface=0;
        for(unsigned int i=0;i<block3.size();++i){
            totalSurface+=furnitures[block3[i]].getSurface();
            xG+=furnitures[block3[i]].getX()*furnitures[block3[i]].getSurface();
        }
        xalig.push_back(xG/totalSurface);
    }

    if(tableIndex!=-1){
        xalig.push_back(furnitures[tableIndex].getX());
        yalig.push_back(furnitures[tableIndex].getY());
    }
//    cout<<"\nxalig\n";
//    for(unsigned i=0;i<xalig.size();++i)
//        cout<<xalig[i]<<" ";
//    cout<<"\nyalig\n";
//    for(unsigned i=0;i<yalig.size();++i)
//        cout<<yalig[i]<<" ";

    for(unsigned int i=0;i<xalig.size()-1;++i){
        for(unsigned j=i+1;j<xalig.size();++j)
            sum+=(xalig[i]-xalig[j])*(xalig[i]-xalig[j]);
    }
    for(unsigned int i=0;i<yalig.size()-1;++i){
        for(unsigned j=i+1;j<yalig.size();++j)
            sum+=(yalig[i]-yalig[j])*(yalig[i]-yalig[j]);
    }
#else
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
    if(tableIndex!=-1){
        for(unsigned int i=0;i<blocks02.size();++i)
            sum+=Vec2(furnitures[blocks02[i]].getY()-furnitures[tableIndex].getY(),0).lengthSqrd();
        for(unsigned int i=0;i<blocks13.size();++i)
            sum+=Vec2(furnitures[blocks13[i]].getX()-furnitures[tableIndex].getX(),0).lengthSqrd();
    }
#endif
    return weight*sqrt(sum);
}

void FineAlignment::assignFurnToBlock(const Room &room){
#ifdef FACGM
    block0.clear();
    block1.clear();
    block2.clear();
    block3.clear();
#else
    blocks02.clear();
    blocks13.clear();
#endif
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
#ifdef FACGM
            switch (ind) {
            case 0:
                block0.push_back(i);
                break;
            case 1:
                block1.push_back(i);
                break;
            case 2:
                block2.push_back(i);
                break;
            case 3:
                block3.push_back(i);
                break;
            default:
                break;
            }

#else
            if(ind%2==0)
                blocks02.push_back(i);
            else
                blocks13.push_back(i);
#endif
        }
    }
//    std::cout<<std::endl<<"block0\n";
//    for(unsigned int i=0;i<block0.size();++i)
//        std::cout<<block0[i]<<" ";

//    std::cout<<std::endl<<"block1\n";
//    for(unsigned int i=0;i<block1.size();++i)
//        std::cout<<block1[i]<<" ";

//    std::cout<<std::endl<<"block2\n";
//    for(unsigned int i=0;i<block2.size();++i)
//        std::cout<<block2[i]<<" ";

//    std::cout<<std::endl<<"block3\n";
//    for(unsigned int i=0;i<block3.size();++i)
//        std::cout<<block3[i]<<" ";

    //    for(unsigned int i=0;i<blocks.size();++i){
    //        cout<<"Block "<<i<<" \n";
    //        for(unsigned int j=0;j<blocks[i].size();++j){
    //            furnitures[blocks[i][j]].print(cout);
    //        }
    //    }
    return;
}
