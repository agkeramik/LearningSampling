#include "Furniture.h"
#include <iostream>

Furniture::Furniture(int _id, std::string _catalogId):id(_id), catalogId(_catalogId), features(3)
{
    depth=10;
    width=10;
    height=10;
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
        virDepth=width;
    localPoly.clear();
    localPoly<<ClipperLib::IntPoint((int)(-width/2.0),(int)(-virDepth/2.0))
            <<ClipperLib::IntPoint((int)(width/2.0),(int)(-virDepth/2.0))
           <<ClipperLib::IntPoint((int)(width/2.0),(int)(virDepth/2.0))
          <<ClipperLib::IntPoint((int)(-width/2.0),(int)(virDepth/2.0));
    if(!ClipperLib::Orientation(localPoly))
        ClipperLib::ReversePath(localPoly);
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

double Furniture::getX() { return this->features.at(0); }
double Furniture::getY() { return this->features.at(1); }
double Furniture::getTheta() { return this->features.at(2); }

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
