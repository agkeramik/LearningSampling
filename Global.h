#include <CGAL/Polygon_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Aff_transformation_2.h>
//#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
//#include <CGAL/Cartesian.h>
#include <CGAL/Boolean_set_operations_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Aff_transformation_2<Kernel> Transform;
