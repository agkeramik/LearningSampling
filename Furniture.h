#pragma once
#include <string>
#include <iostream>
#ifndef FURNITURE_H
#define FURNITURE_H

#include <mlpack/core.hpp>
#include "Global.h"
#include <ostream>
#include "clipper.hpp"

class Furniture
{
    ClipperLib::Path localPoly;
    ClipperLib::Path clearancePoly;

public:
    int id;
    std::string catalogId, name;
    double width, height, depth;
    //positive OffsetX, negative OffsetX ...
    double pOffX,nOffX,pOffY,nOffY;
    arma::Col<double> features;


    Furniture(int _id=-1, std::string _catalogId="unitialized");
    Furniture(std::string xmlContent);

    void updateGeometry();

	double getX();
	double getY();
	double getTheta();

	void setX(double x);
	void setY(double y);
	void setTheta(double theta);
    void setFeatureVector(arma::Col<double> vec);

    void setWidth(double width);
    void setHeight(double height);
    void setDepth(double depth);
    void setPositiveOffsetX(double off);
    void setPositiveOffsetY(double off);
    void setNegativeOffsetX(double off);
    void setNegativeOffsetY(double off);

    ClipperLib::Path getGlobalGeometry() const;
    ClipperLib::Path getClearanceGeometry() const;
    bool collision(const Furniture &f) const;


	virtual ~Furniture();
    void print(std::ostream &out) const;
};

//std::ostream &operator<<(std::ostream& out, const Funriture &f);

#endif
