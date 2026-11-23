/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____ )\____)_| |_|
    (C)2013 Semtech

Description: hardware I2C transport for the sensor bus

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/

/******************************************************************************
 * @file    IIC.h
 * @author  MCD Application Team
 * @version V1.1.2
 * @date    01-June-2017
 * @brief   hardware I2C transport declarations
 *
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific written permission.
 * 4. This software, including modifications and/or derivative works, must
 *    execute solely and exclusively on microcontroller or microprocessor
 *    devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY RIGHTS ARE
 * DISCLAIMED. IN NO EVENT SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#ifndef __IIC_H__
#define __IIC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Legacy startup hook retained for the existing application call site. */
void IIC_GPIO_MODE_Config(void);

/* Addresses are unshifted 7-bit I2C addresses. Return 0 on success. */
uint8_t IIC_MemRead(uint8_t device_address,
                    uint8_t register_address,
                    uint16_t length,
                    uint8_t *data);
uint8_t IIC_MemWrite(uint8_t device_address,
                     uint8_t register_address,
                     uint16_t length,
                     uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif /* __IIC_H__ */
