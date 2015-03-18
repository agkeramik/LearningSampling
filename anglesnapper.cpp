#include "anglesnapper.h"

AngleSnapper::AngleSnapper(double period, double range_2):
    range_2(range_2),
    period(period)
{

}

//theta in degrees between 0-360
bool AngleSnapper::shouldSnap(int theta){
    //range_2=range/2
    theta=theta%((int) period);
    if(theta<range_2 || theta>period-range_2)
        return true;
    return false;
}

//snap theta to values multiple of 45
void AngleSnapper::snapFurntiureAngles(Room &room){
    vector<Furniture> &furnitures=room.getFurnitures();
    for(unsigned int i=0;i<furnitures.size();++i){
        int theta=(int)(furnitures[i].getTheta()*180./M_PI);
        theta=(theta+360)%360;
        if(shouldSnap(theta)){
            //    cout<<"round"<<round(theta/15.);
            theta=round(theta/period);
            theta=theta*period;
            //   cout<<"theta after"<<theta<<endl;
            theta=(theta+360)%360;
            furnitures[i].setTheta(theta*M_PI/180.);
        }
    }
}
