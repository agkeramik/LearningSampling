#include "Furniture.h"
#include <iostream>

Furniture::Furniture(int _id, std::string _catalogId):id(_id), catalogId(_catalogId), features(3)
{
    is_Movable=true;
    depth=10;
    width=10;
    height=10;
    pOffX=0;
    pOffY=0;
    nOffX=0;
    nOffY=0;
    this->updateGeometry();
}

Furniture::Furniture(std::string xmlContent)
{

}

void Furniture::setFeatureVector(arma::Col<double> vec)
{
    this->features = vec;
}

void Furniture::updateGeometry()
{
    double virDepth=depth;
    if(catalogId=="eTeks#door" || catalogId=="eTeks#doubleFrenchWindow126x200" ||
            catalogId=="eTeks#frenchWindow85x200")
        virDepth=2*width;
    localPoly.clear();
    localPoly<<ClipperLib::IntPoint((int)(-width/2.0),(int)(-virDepth/2.0))
            <<ClipperLib::IntPoint((int)(width/2.0),(int)(-virDepth/2.0))
           <<ClipperLib::IntPoint((int)(width/2.0),(int)(virDepth/2.0))
          <<ClipperLib::IntPoint((int)(-width/2.0),(int)(virDepth/2.0));
    if(!ClipperLib::Orientation(localPoly))
        ClipperLib::ReversePath(localPoly);

    clearancePoly.clear();
    clearancePoly<<ClipperLib::IntPoint((int)(-width/2.0-nOffX),(int)(-virDepth/2.0-nOffY))
                <<ClipperLib::IntPoint((int)(width/2.0+pOffX),(int)(-virDepth/2.0-nOffY))
               <<ClipperLib::IntPoint((int)(width/2.0+pOffX),(int)(virDepth/2.0+pOffY))
              <<ClipperLib::IntPoint((int)(-width/2.0-nOffX),(int)(virDepth/2.0+pOffY));
    if(!ClipperLib::Orientation(clearancePoly))
        ClipperLib::ReversePath(clearancePoly);

}

bool Furniture::isMovable() const
{
    return is_Movable;
}

void Furniture::isMovable(bool movable)
{
    is_Movable=movable;
}

void Furniture::setWidth(double width)
{
    this->width = width;
    this->updateGeometry();
}

void Furniture::setHeight(double height)
{
    this->height = height;
    this->updateGeometry();
}

void Furniture::setDepth(double depth)
{
    this->depth = depth;
    this->updateGeometry();
}

void Furniture::setPositiveOffsetX(double off)
{
    pOffX=off;
    this->updateGeometry();
}

void Furniture::setPositiveOffsetY(double off)
{
    pOffY=off;
    this->updateGeometry();
}

void Furniture::setNegativeOffsetX(double off)
{
    nOffX=off;
    this->updateGeometry();
}

void Furniture::setNegativeOffsetY(double off)
{
    nOffY=off;
    this->updateGeometry();
}

double Furniture::getX() const { return this->features.at(0); }
double Furniture::getY() const { return this->features.at(1); }
double Furniture::getTheta() const { return this->features.at(2); }

void Furniture::setX(double x)
{
    this->features(0) = x;
}
void Furniture::setY(double y)
{
    this->features(1) = y;
}
void Furniture::setTheta(double theta)
{
    this->features(2) = theta;
}

ClipperLib::Path Furniture::getGlobalGeometry() const
{
    return ClipperLib::RotateTranslate(localPoly,features.at(0),features.at(1),features.at(2));
}

ClipperLib::Path Furniture::getClearanceGeometry() const
{
    return ClipperLib::RotateTranslate(clearancePoly,features.at(0),features.at(1),features.at(2));
}

bool Furniture::collision(const Furniture &f) const
{
    ClipperLib::Path p1=getGlobalGeometry();
    ClipperLib::Path p2=f.getGlobalGeometry();
    return Global::intersectionArea(p1,p2)>0;
}

Furniture::~Furniture()
{

}

void Furniture::print(std::ostream &out) const
{
    out<<"<Furniture width=\""<<width<<"\" depth=\""<<depth<<"\" height=\""<<height<<"\" rotation=\""<<features(2)<<"\">\n";
    out<<"<CatalogId>"<<catalogId<<"</CatalogId>\n";
    out<<"<Name>"<<name<<"</Name>\n";
    out<<"<Position posX=\""<<features(0);
    out<<"\" posY=\""<<features(1)<<"\"/>\n";
    out<<"</Furniture>\n";
}

//std::ostream &operator<<(std::ostream& out, const Funriture &f){
//    f.print(out);
//}
