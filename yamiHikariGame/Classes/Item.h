//
//  Item.h
//  yamiHikariGame
//
//  Created by slightair on 2013/08/04.
//
//

#ifndef __yamiHikariGame__Item__
#define __yamiHikariGame__Item__

#include "hiberlite.h"

using namespace std;

class Item
{
    friend class hiberlite::access;
    template<class Archive>
    void hibernate(Archive &ar)
    {
        ar & HIBERLITE_NVP(name);
        ar & HIBERLITE_NVP(desc);
        ar & HIBERLITE_NVP(image);
        ar & HIBERLITE_NVP(stamina);
        ar & HIBERLITE_NVP(score);
        ar & HIBERLITE_NVP(count);
        ar & HIBERLITE_NVP(checksum);
    }

public:
    string name;
    string desc;
    string image;
    int stamina;
    int score;
    int count;
    string checksum;
};
HIBERLITE_EXPORT_CLASS(Item)

#endif /* defined(__yamiHikariGame__Item__) */
