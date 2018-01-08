#ifndef TRASH_CAN
#define TRASH_CAN

#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
using namespace std;


class TrashCan
{
public:
    double latitude;
    double longitude;
    char desc[100];


    TrashCan(char * ad, char * st, char * de, double lat, double lng);
    static TrashCan * Nearest(vector<TrashCan*> cans, double lat, double lng);
    static float Distance(double lat1, double lng1, double lat2, double lng2);

};





#endif /* TRASH_CAN */