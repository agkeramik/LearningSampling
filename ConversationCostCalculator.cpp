#include "ConversationCostCalculator.h"
#include <iostream>
#include <math.h>
#include <fstream>

double ConversationCostCalculator::costFunction(Furniture &f1,Furniture &f2)
{
    double cost= -(cosineDeltaAngle(f1,f2)+1)*(cosineDeltaAngle(f2,f1)+1);
    if(cost>-2)
        cost=3*cost*cost+12*cost+10;
    return cost;
}

double ConversationCostCalculator::cosineDeltaAngle(Furniture &f1, Furniture &f2)
{
    //assuming that f1,f2 centroids are resp. the positions of f1,f2
    //v is the vector going from f1's centroid towards f2's centroid
    Vec2 v(f2.getX()-f1.getX(), f2.getY()-f1.getY());
    //we are taking theta+pi/2 because the orientation of
    //the chairs are along the y axis in the local coordinates
    Vec2 f1Dir(-sin(f1.getTheta()),cos(f1.getTheta()));
    return f1Dir.dot(v)/sqrt(v.lengthSqrd()*f1Dir.lengthSqrd());
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
    return cost/furnitures.size();
}

void ConversationCostCalculator::print(std::ostream &out)
{
    out<<"Conversation Cost Calc: ";
}

ConversationCostCalculator::~ConversationCostCalculator()
{

}
