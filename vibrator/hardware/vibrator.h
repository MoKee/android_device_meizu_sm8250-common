/*
 * Copyright (C) 2013 The Android Open Source Project
 * Copyright (C) 2020 The MoKee Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef _HARDWARE_VIBRATOR_H
#define _HARDWARE_VIBRATOR_H

#include <hardware/hardware.h>

__BEGIN_DECLS

#define VIBRATOR_API_VERSION HARDWARE_MODULE_API_VERSION(1,0)

/**
 * The id of this module
 */
#define VIBRATOR_HARDWARE_MODULE_ID "vibrator"

/**
 * The id of the main vibrator device
 */
#define VIBRATOR_DEVICE_ID_MAIN "main_vibrator"

struct vibrator_device;
typedef struct vibrator_device {
    /**
     * Common methods of the vibrator device.  This *must* be the first member of
     * vibrator_device as users of this structure will cast a hw_device_t to
     * vibrator_device pointer in contexts where it's known the hw_device_t references a
     * vibrator_device.
     */
    struct hw_device_t common;

    /** Turn on vibrator
     *
     * This function must only be called after the previous timeout has expired or
     * was canceled (through vibrator_off()).
     *
     * @param timeout_ms number of milliseconds to vibrate
     *
     * @return 0 in case of success, negative errno code else
     */
    int (*vibrator_on)(struct vibrator_device* vibradev, unsigned int timeout_ms);

    /** Turn off vibrator
     *
     * Cancel a previously-started vibration, if any.
     *
     * @return 0 in case of success, negative errno code else
     */
    int (*vibrator_off)(struct vibrator_device* vibradev);

#ifdef MEIZU_HACK
    int (*vibrator_perform_effect)(struct vibrator_device* vibradev, uint32_t effect, uint8_t strength);
#endif
} vibrator_device_t;

static inline int vibrator_open(const struct hw_module_t* module, vibrator_device_t** device)
{
    return module->methods->open(module, VIBRATOR_DEVICE_ID_MAIN, TO_HW_DEVICE_T_OPEN(device));
}

__END_DECLS

#endif  // _HARDWARE_VIBRATOR_H
