#include "Furniture.h"

Furniture::Furniture(int _id, std::string _catalogId):id(_id), catalogId(_catalogId), features(3)
{
}

Furniture::Furniture() : id(-1), catalogId("uninitialized"), features(3)
{

}

Furniture::Furniture(std::string xmlContent){

}

void Furniture::setFeatureVector(arma::Col<double> vec){
    this->features = vec;
    this->translation = Transform(CGAL::TRANSLATION, Vector(getX(), getY()));
    this->rotation = Transform(CGAL::ROTATION, cos(getTheta()), sin(getTheta()));
}

void Furniture::updateGeometry(){


    this->centeredGeometry.clear();
    this->centeredGeometry.push_back(Point(-width/2.0, -depth/2.0));
    this->centeredGeometry.push_back(Point(width/2.0, -depth/2.0));
    this->centeredGeometry.push_back(Point(width/2.0, depth/2.0));
    this->centeredGeometry.push_back(Point(-width/2.0, depth/2.0));

    if (this->centeredGeometry.is_clockwise_oriented()){

        this->centeredGeometry.clear();
        this->centeredGeometry.push_back(Point(-width/2.0, depth/2.0));
        this->centeredGeometry.push_back(Point(width/2.0, depth/2.0));
        this->centeredGeometry.push_back(Point(width/2.0, -depth/2.0));
        this->centeredGeometry.push_back(Point(-width/2.0, -depth/2.0));

    }
}

void Furniture::setWidth(double width){
    this->width = width;
    this->updateGeometry();
}

void Furniture::setHeight(double height){
    this->height = height;
    this->updateGeometry();
}

void Furniture::setDepth(double depth){
    this->depth = depth;
    this->updateGeometry();
}

double Furniture::getX() { return this->features.at(0); }
double Furniture::getY() { return this->features.at(1); }
double Furniture::getTheta() { return this->features.at(2); }

void Furniture::setX(double x) {
    this->features(0) = x;
    this->translation = Transform(CGAL::TRANSLATION, Vector(getX(), getY()));
}
void Furniture::setY(double y) {
    this->features(1) = y;
    this->translation = Transform(CGAL::TRANSLATION, Vector(getX(), getY()));
}
void Furniture::setTheta(double theta) {
    this->features(2) = theta;
    this->rotation = Transform(CGAL::ROTATION, cos(theta), sin(theta));
}

Polygon Furniture::getTransformedGeometry(){
    this->updateGeometry();
    return CGAL::transform(this->translation, CGAL::transform(this->rotation, this->centeredGeometry));
}

bool Furniture::collision(Furniture& f){
    Polygon p1 = f.getTransformedGeometry();
    Polygon p2 = getTransformedGeometry();
    //std::cout << p1 << std::endl << p2 << std::endl;

    return CGAL::do_intersect(p1, p2);
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
