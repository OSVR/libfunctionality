
# Build libfunctionality
include $(CLEAR_VARS)
LOCAL_PATH := $(LIBFUNC_DIR)/src/

LOCAL_CPP_FEATURES += exceptions
LOCAL_CFLAGS += -fpermissive -frtti

LOCAL_C_INCLUDES := $(LIBFUNC_DIR)/inc/
LOCAL_C_INCLUDES += $(LIBFUNC_DIR)/src/

LOCAL_MODULE    := functionality
LOCAL_CPP_EXTENSION := .C .cpp
LOCAL_SRC_FILES := \
	libfunctionality/LibraryHandleLibdl.cpp \
	libfunctionality/LoadPlugin.cpp \
	libfunctionality/PluginHandle.cpp 

include $(BUILD_STATIC_LIBRARY)
include $(CLEAR_VARS)