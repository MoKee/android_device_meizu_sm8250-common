LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := android.hardware.vibrator@1.3-service.meizu_kona
LOCAL_MODULE_TAGS  := optional

LOCAL_MODULE_PATH := $(TARGET_OUT_PRODUCT)/vendor_overlay/$(PRODUCT_TARGET_VNDK_VERSION)/bin
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE_STEM := android.hardware.vibrator@1.3-service

LOCAL_SRC_FILES := \
    service.cpp \
    Vibrator.cpp

LOCAL_CFLAGS := -DMEIZU_HACK

LOCAL_REQUIRED_MODULES := \
    android.hardware.vibrator@1.3-service.meizu_kona.rc

LOCAL_SHARED_LIBRARIES := \
    libbase \
    libhardware \
    libhidlbase \
    libhidltransport \
    liblog \
    libutils \
    android.hardware.vibrator@1.0 \
    android.hardware.vibrator@1.1 \
    android.hardware.vibrator@1.2 \
    android.hardware.vibrator@1.3

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_MODULE := android.hardware.vibrator@1.3-service.meizu_kona.rc
LOCAL_MODULE_TAGS  := optional
LOCAL_MODULE_CLASS := ETC

LOCAL_MODULE_PATH := $(TARGET_OUT_PRODUCT)/vendor_overlay/$(PRODUCT_TARGET_VNDK_VERSION)/etc/init
LOCAL_MODULE_STEM := android.hardware.vibrator@1.3-service.rc

LOCAL_SRC_FILES := android.hardware.vibrator@1.3-service.meizu_kona.rc

include $(BUILD_PREBUILT)
