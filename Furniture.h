#pragma once
#include <string>
#include <iostream>
#ifndef FURNITURE_H
#define FURNITURE_H

#include <mlpack/core.hpp>
#include "Global.h"
#include <ostream>

class Furniture
{

public:
    Furniture(int _id=-1, std::string _catalogId="unitialized");
    Furniture(std::string xmlContent);

    Transform rotation;
    Transform translation;
    Polygon centeredGeometry;

	int id;
    std::string catalogId, name;
	double width, height, depth;

	arma::Col<double> features;

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

    Polygon getTransformedGeometry() const;

    bool collision(const Furniture &f) const;


	virtual ~Furniture();
    void print(std::ostream &out) const;
};

//std::ostream &operator<<(std::ostream& out, const Funriture &f);

#endif
