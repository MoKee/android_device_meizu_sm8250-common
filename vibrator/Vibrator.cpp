/*
 * Copyright (C) 2019 The Android Open Source Project
 * Copyright (C) 2020 The MoKee Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#define LOG_TAG "VibratorService"

#include <android-base/logging.h>

#include "Vibrator.h"

namespace android {
namespace hardware {
namespace vibrator {
namespace V1_3 {
namespace implementation {

Vibrator::Vibrator(vibrator_device_t *device)
    : mDevice(device)
    {
}

// Methods from ::android::hardware::vibrator::V1_0::IVibrator follow.

Return<Status> Vibrator::on(uint32_t timeoutMs) {
    int32_t ret = mDevice->vibrator_on(mDevice, timeoutMs);
    if (ret != 0) {
        LOG(ERROR) << "On: command failed: " << strerror(-ret);
        return Status::UNKNOWN_ERROR;
    }
    return Status::OK;
}

Return<Status> Vibrator::off() {
    int32_t ret = mDevice->vibrator_off(mDevice);
    if (ret != 0) {
        LOG(ERROR) << "Off: command failed: " << strerror(-ret);
        return Status::UNKNOWN_ERROR;
    }
    return Status::OK;
}

Return<bool> Vibrator::supportsAmplitudeControl() {
    return false;
}

Return<Status> Vibrator::setAmplitude(uint8_t) {
    return Status::UNSUPPORTED_OPERATION;
}

Return<void> Vibrator::perform(V1_0::Effect effect, EffectStrength strength, perform_cb _hidl_cb) {
    return perform<decltype(effect)>(effect, strength, _hidl_cb);
}

// Methods from ::android::hardware::vibrator::V1_1::IVibrator follow.

Return<void> Vibrator::perform_1_1(V1_1::Effect_1_1 effect, EffectStrength strength,
                                   perform_cb _hidl_cb) {
    return perform<decltype(effect)>(effect, strength, _hidl_cb);
}

// Methods from ::android::hardware::vibrator::V1_2::IVibrator follow.

Return<void> Vibrator::perform_1_2(V1_2::Effect effect, EffectStrength strength,
                                   perform_cb _hidl_cb) {
    return perform<decltype(effect)>(effect, strength, _hidl_cb);
}

// Methods from ::android::hardware::vibrator::V1_3::IVibrator follow.

Return<bool> Vibrator::supportsExternalControl() {
    return false;
}

Return<Status> Vibrator::setExternalControl(bool) {
    return Status::UNSUPPORTED_OPERATION;
}

Return<void> Vibrator::perform_1_3(Effect effect, EffectStrength strength, perform_cb _hidl_cb) {
    return perform<decltype(effect)>(effect, strength, _hidl_cb);
}

// Private methods follow.

Return<void> Vibrator::perform(Effect effect, EffectStrength strength, perform_cb _hidl_cb) {
    uint32_t id;
    uint8_t strn;
    Status status = Status::OK;

    switch (effect) {
        case Effect::CLICK:
            id = 31008;
            break;
        case Effect::DOUBLE_CLICK:
            id = 31003;
            break;
        case Effect::TICK:
        case Effect::TEXTURE_TICK:
            id = 21000;
            break;
        case Effect::THUD:
            id = 30900;
            break;
        case Effect::POP:
            id = 22520;
            break;
        case Effect::HEAVY_CLICK:
            id = 30900;
            break;
        default:
            LOG(ERROR) << "Perform: Effect not supported: " << toString(effect);
            _hidl_cb(status, 0);
            return Void();
    }

    switch (strength) {
        case EffectStrength::LIGHT:
            strn = 50;
            break;
        case EffectStrength::MEDIUM:
            strn = 120;
            break;
        case EffectStrength::STRONG:
            strn = 255;
            break;
    }

    int32_t ret = mDevice->vibrator_perform_effect(mDevice, id, strn);
    if (ret != 0) {
        LOG(ERROR) << "Perform: command failed: " << strerror(-ret);
        status = Status::UNKNOWN_ERROR;
        _hidl_cb(status, 0);
        return Void();
    }

    LOG(INFO) << "Perform: Effect " << toString(effect) << " (" << toString(strength)  << ")"
              << " => " << id << " (" << (int) strn << ")";

    _hidl_cb(status, 200);

    return Void();
}

template <typename T>
Return<void> Vibrator::perform(T effect, EffectStrength strength, perform_cb _hidl_cb) {
    auto validRange = hidl_enum_range<T>();
    if (effect < *validRange.begin() || effect > *std::prev(validRange.end())) {
        _hidl_cb(Status::UNSUPPORTED_OPERATION, 0);
        return Void();
    }
    return perform(static_cast<Effect>(effect), strength, _hidl_cb);
}

}  // namespace implementation
}  // namespace V1_3
}  // namespace vibrator
}  // namespace hardware
}  // namespace android
