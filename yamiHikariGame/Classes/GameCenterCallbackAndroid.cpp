//
//  GameCenterCallbackAndroid.cpp
//  
//
//  Created by ichiko on 13/09/15.
//
//

#include "GameCenterCallbackAndroid.h"
#include "GameEngine.h"

extern "C" {
    
    /*
     * Class:     cc_clv_yamiHikariGame_gamecenter_GameCenter
     * Method:    onSignInProcessCompleted
     * Signature: (Z)V
     */
    JNIEXPORT void JNICALL Java_cc_clv_yamiHikariGame_gamecenter_GameCenter_onSignInProcessCompleted
    (JNIEnv *env, jclass classObj, jboolean boolVal) {
        GameEngine::sharedEngine()->singInStateChanged(boolVal == JNI_TRUE);
    }
    
    /*
     * Class:     cc_clv_yamiHikariGame_gamecenter_GameCenter
     * Method:    onSignOutProcessCompleted
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_cc_clv_yamiHikariGame_gamecenter_GameCenter_onSignOutProcessCompleted
    (JNIEnv *env, jclass classObj) {
        GameEngine::sharedEngine()->singInStateChanged(false);
    }
    
}

