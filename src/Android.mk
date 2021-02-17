LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main
	
LOCAL_CFLAGS += -frtti
LOCAL_CPP_FEATURES += exceptions

# START_SRC FILES
LOCAL_SRC_FILES := \
	$(wildcard $(LOCAL_PATH)/BasicPhysic/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Events/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Frames/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Graphics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Sound/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Test/*.cpp) \
	$(wildcard $(LOCAL_PATH)/*.cpp) \
# END_SRC_FILES

LOCAL_SHARED_LIBRARIES := hidapi libcpp SDL2 SDL2_gfx SDL2_image SDL2_mixer SDL2_net SDL2_ttf freetype libmpg123

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
