/*
 *  Copyright (c) 2017, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief
 *   This file includes the platform-specific initializers.
 */

#include <openthread/config.h>

#include <stdio.h>
#include <openthread/types.h>
#include "platform-cc2652.h"

#include "inc/hw_types.h"
#include "inc/hw_ccfg.h"
#include "inc/hw_ccfg_simple_struct.h"

extern const ccfg_t __ccfg;

const char *dummy_ccfg_ref = ((const char *)(&(__ccfg)));

/**
 * Function documented in platform-cc2652.h
 */
void PlatformInit(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    while (dummy_ccfg_ref == NULL)
    {
        /*
         * This provides a code reference to the customer configuration area of
         * the flash, otherwise the data is skipped by the linker and not put
         * into the final flash image.
         */
    }

    cc2652AlarmInit();
    cc2652RandomInit();
    cc2652RadioInit();
}

/**
 * Function documented in platform-cc2652.h
 */
void PlatformProcessDrivers(otInstance *aInstance)
{
    // should sleep and wait for interrupts here

    cc2652UartProcess();
    cc2652RadioProcess(aInstance);
    cc2652AlarmProcess(aInstance);
}
