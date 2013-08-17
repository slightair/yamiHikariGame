LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hiberlite_static

LOCAL_MODULE_FILENAME := libhiberlite

LOCAL_CPPFLAGS   := -fexceptions -frtti

LOCAL_SRC_FILES := \
ChildKiller.h \
ModelExtractor.h \
Visitor.cpp \
hiberlite.h \
BeanLoader.cpp \
ChildKiller_impl.hpp \
ModelExtractor_impl.hpp \
Visitor.h \
nvp.h \
BeanLoader.h \
CppModel.cpp \
Registry.cpp \
Visitor_tmpl_impl.hpp \
shared_res.cpp \
BeanLoader_impl.hpp \
CppModel.h \
Registry.h \
bean_ptr.h \
shared_res.h \
BeanUpdater.cpp \
Database.cpp \
Registry_impl.hpp \
bean_ptr_impl.hpp \
some_types.h \
BeanUpdater.h \
Database.h \
SQLiteStmt.cpp \
common.h \
BeanUpdater_impl.hpp \
Database_tmpl_impl.hpp \
SQLiteStmt.h \
db_error.h \
ChildKiller.cpp \
ModelExtractor.cpp \
UpdateVisitor_tmpl.hpp \
hiberdefs.h

#BeanLoader.cpp \
#BeanLoader_impl.hpp \
#BeanUpdater.cpp \
#BeanUpdater_impl.hpp \
#ChildKiller.cpp \
#ChildKiller_impl.hpp \
#CppModel.cpp \
#Database.cpp \
#Database_tmpl_impl.hpp \
#ModelExtractor.cpp \
#ModelExtractor_impl.hpp \
#Registry.cpp \
#Registry_impl.hpp \
#SQLiteStmt.cpp \
#UpdateVisitor_tmpl.hpp \
#Visitor.cpp \
#Visitor_tmpl_impl.hpp \
#bean_ptr_impl.hpp \
#shared_res.cpp \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../proj.android/jni/external/sqlite3

include $(BUILD_STATIC_LIBRARY)
