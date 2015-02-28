#include "ConversationCostCalculator.h"
#include <iostream>
#include <math.h>
#include <fstream>

double ConversationCostCalculator::costFunction(Furniture &f1,Furniture &f2)
{
    //return exp(delta / 30.0) - 1.0;
    return -(cosineDeltaAngle(f1,f2)+1)*(cosineDeltaAngle(f2,f1)+1);
}

double ConversationCostCalculator::cosineDeltaAngle(Furniture &f1, Furniture &f2)
{

    Polygon f1g = f1.getTransformedGeometry();
    Point centroid1 = Global::centroid(f1g);
    Polygon f2g = f2.getTransformedGeometry();
    Point centroid2 = Global::centroid(f2g);
    Vector v(centroid1, centroid2);
    //we are taking theta+pi/2 because the orientation of
    //the chairs are along the y axis in the local coordinates
    Vector f1Dir(-sin(f1.getTheta()),cos(f1.getTheta()));
    return f1Dir*v/sqrt(v.squared_length()*f1Dir.squared_length());
}

bool ConversationCostCalculator::goesInConvCost(Furniture &f)
{
    for(unsigned int i=0;i<furConv.size();++i)
        if(f.catalogId.compare(furConv[i])==0)
            return true;
    return false;
}

ConversationCostCalculator::ConversationCostCalculator(const char *fileName)
{
    std::ifstream fin;
    fin.open(fileName);
    if(!fin.is_open()){
        std::cout<<"File Not Found:"<<*fileName<<std::endl;
        throw "File Not Found";
    }
    std::string line;
    while(std::getline(fin,line)>0){
        if(line.find('#')!=std::string::npos){
            furConv.push_back(line);
        }
    }
    fin.close();
}

double ConversationCostCalculator::calculateCost(Room &room)
{
    double cost = 0;
    vector<Furniture> &furnitures = room.getFurnitures();
    for(unsigned int i=0; i<furnitures.size()-1;++i){
        if(goesInConvCost(furnitures[i])){
            for(unsigned int j=i+1;j<furnitures.size();++j){
                if(goesInConvCost(furnitures[j])){
                    cost += costFunction(furnitures[i], furnitures[j]);
                }
            }
        }
    }
    return cost;
}

ConversationCostCalculator::~ConversationCostCalculator()
{

}
