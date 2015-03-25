#include "Engine/expansioncost.h"

ExpansionCost::ExpansionCost(double weight):Cost(weight)
{
}

double ExpansionCost::calculate(const Room &room) const
{
    const unsigned int s=55;
    ClipperLib::Path path;
    const std::vector<Furniture> &furnitures=room.getFurnitures();
//    path<<ClipperLib::IntPoint(room.getTopLeftCornerX()+shift,room.getTopLeftCornerY()+shift)
//           <<ClipperLib::IntPoint(room.getTopLeftCornerX()+shift,room.getBottomRightCornerY()-shift)
//          <<ClipperLib::IntPoint(room.getBottomRightCornerX()-shift,room.getBottomRightCornerY()-shift)
//         <<ClipperLib::IntPoint(room.getBottomRightCornerX()-shift,room.getTopLeftCornerY()+shift);
    double tlx=room.getTopLeftCornerX();
    double tly=room.getTopLeftCornerY();
    double brx=room.getBottomRightCornerX();
    double bry=room.getBottomRightCornerY();
    path<<ClipperLib::IntPoint(tlx,tly)<<ClipperLib::IntPoint(tlx+s,tly)<<ClipperLib::IntPoint(tlx+s,tly+s)
          <<ClipperLib::IntPoint(brx-s,tly+s)<<ClipperLib::IntPoint(brx-s,tly)
          <<ClipperLib::IntPoint(brx,tly)<<ClipperLib::IntPoint(brx,tly+s)<<ClipperLib::IntPoint(brx-s,tly+s)
          <<ClipperLib::IntPoint(brx-s,bry-s)<<ClipperLib::IntPoint(brx,bry-s)
          <<ClipperLib::IntPoint(brx,bry)<<ClipperLib::IntPoint(brx-s,bry)
          <<ClipperLib::IntPoint(brx-s,bry-s)<<ClipperLib::IntPoint(tlx+s,bry-s)
          <<ClipperLib::IntPoint(tlx+s,bry)<<ClipperLib::IntPoint(tlx,bry)<<ClipperLib::IntPoint(tlx,bry-s)
          <<ClipperLib::IntPoint(tlx+s,bry-s)<<ClipperLib::IntPoint(tlx+s,tly+s)
          <<ClipperLib::IntPoint(tlx,tly+s)<<ClipperLib::IntPoint(tlx,tly);
    double area=0.0;
    for (unsigned int i=0;i<furnitures.size();++i){
        ClipperLib::Path pi=furnitures[i].getGlobalGeometry();
        area+=Global::differenceArea(path,pi);
    }
    return -weight*sqrt(area/10000);
}
