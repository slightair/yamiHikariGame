LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hiberlite_static

LOCAL_MODULE_FILENAME := libhiberlite

LOCAL_CPPFLAGS   := -fexceptions -frtti

LOCAL_SRC_FILES := \
SQLiteStmt.cpp \
BeanLoader.cpp \
Database.cpp \
ChildKiller.cpp \
BeanUpdater.cpp \
shared_res.cpp \
ModelExtractor.cpp \
Visitor.cpp \
CppModel.cpp \
Registry.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../proj.android/jni/external/sqlite3

include $(BUILD_STATIC_LIBRARY)
