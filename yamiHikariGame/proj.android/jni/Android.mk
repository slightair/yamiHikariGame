LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

CPP_FILES := $(shell find $(LOCAL_PATH)/../../Classes -name *.cpp)

LOCAL_SRC_FILES := hellocpp/main.cpp
LOCAL_SRC_FILES += $(CPP_FILES:$(LOCAL_PATH)/%=%)
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../libs/hiberlite
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../libs/crypto/sha1
LOCAL_C_INCLUDES += $(LOCAL_PATH)/external/sqlite3

LOCAL_CFLAGS := -w

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static hiberlite_static cryptosha1_static sqlite3_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions) \
$(call import-module,crypto/sha1) \
$(call import-module,hiberlite) \
$(call import-module,sqlite3)
