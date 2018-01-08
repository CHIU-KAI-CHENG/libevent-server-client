#include "trash_can.hpp"

TrashCan::TrashCan(char * ad, char * st, char * de, double lat, double lng)
{
    sprintf(desc, "%s%s%s", ad, st, de);
    latitude = lat;
    longitude = lng;
}

TrashCan * TrashCan::Nearest(vector<TrashCan*> cans, double lat, double lng)
{
    int closetCan = 0;
    float closet = 0;
    int i;
    for (i = 0; i < cans.size(); i++)
    {
        float dis = Distance(cans[i] -> latitude, lat, cans[i] -> longitude, lng);
        if (closet < dis)
        {
            closet = dis;
            closetCan = i;
        }
    }
    return cans[closetCan];
}

float TrashCan::Distance(double lat1, double lng1, double lat2, double lng2)
{
    float h = powf(fabs(lat2 - lat1), 2.f);
    float v = powf(lng2 - lng1, 2.f);
    return h + v;
}