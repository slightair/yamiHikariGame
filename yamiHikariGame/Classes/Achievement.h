//
//  Achievement.h
//  yamiHikariGame
//
//  Created by slightair on 2013/08/29.
//
//

#ifndef __yamiHikariGame__Achievement__
#define __yamiHikariGame__Achievement__

#include <iostream>

using namespace std;

class Achievement
{
protected:
    string _name;
    string _iOSAchievementID;
    string _androidAchievementID;
    int _process;
    int _goal;

public:
    string getName(){ return _name; }
    string getIOSAchievementID(){ return _iOSAchievementID; }
    string getAndroidAchievementID(){ return _androidAchievementID; }
    int getProcess(){ return _process; }
    int getGoal(){ return _goal; }

    void setName(string name){ _name = name; }
    void setIOSAchievementID(string id){ _iOSAchievementID = id; }
    void setAndroidAchievementID(string id){ _androidAchievementID = id; }
    void setProcess(int process){ _process = process; }
    void setGoal(int goal){ _goal = goal; }
};

#endif /* defined(__yamiHikariGame__Achievement__) */