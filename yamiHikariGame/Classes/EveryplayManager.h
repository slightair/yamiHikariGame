//
//  EveryplayManager.h
//  yamiHikariGame
//
//  Created by slightair on 2014/03/31.
//
//

#ifndef __yamiHikariGame__EveryplayManager__
#define __yamiHikariGame__EveryplayManager__

#include <iostream>

using namespace std;

class EveryplayManager
{
protected:
    bool init();
    EveryplayManager(){};
    EveryplayManager(const EveryplayManager& rhs);
    EveryplayManager& operator=(const EveryplayManager& rhs);

public:
    static EveryplayManager *sharedManager();

    void startRecording();
    void stopRecording();
    void mergeScore(int score);
    void playLastRecording();
};

#endif /* defined(__yamiHikariGame__EveryplayManager__) */
