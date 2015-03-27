#ifndef FURNITURE_H
#define FURNITURE_H

#include <string>
#include <iostream>
#include <mlpack/core.hpp>
#include "Geometry/Global.h"
#include <ostream>
#include "Geometry/clipper.hpp"
#include "Model/furniturecatalog.h"

class FurnitureCatalog;

class Furniture
{
    ClipperLib::Path localPoly;
    ClipperLib::Path clearancePoly;
    bool is_Movable;

public:
        Furniture(int _id=-1, std::string _catalogId="unitialized");
    int id;
    std::string catalogId, name;
    double width, height, depth;
    //positive OffsetX, negative OffsetX ...
    double pOffX,nOffX,pOffY,nOffY;
    arma::Col<double> features;




    void updateGeometry();

    bool isMovable() const;
    void isMovable(bool movable);

    double getX() const;
    double getY() const;
    double getTheta() const ;

    double getWidth() const;
    double getDepth() const;
    double getHeight() const;

    void setX(double x);
    void setY(double y) ;
    void setTheta(double theta);
    void setFeatureVector(arma::Col<double> vec);

    void setWidth(double width);
    void setHeight(double height);
    void setDepth(double depth);
    void setPositiveOffsetX(double off);
    void setPositiveOffsetY(double off);
    void setNegativeOffsetX(double off);
    void setNegativeOffsetY(double off);
    double getSurface() const;
    ClipperLib::Path getGlobalGeometry() const;
    ClipperLib::Path getClearanceGeometry() const;
    bool collision(const Furniture &f) const;


    void print(std::ostream &out) const;
    std::string toXML() const;
    virtual ~Furniture();
};

//std::ostream &operator<<(std::ostream& out, const Funriture &f);

#endif
