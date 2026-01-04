/****************************************************************************
 *
 *   Copyright (C) 2025 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
#include <nuttx/config.h>
#include <board_config.h>

#include <px4_platform/board_determine_hw_info.h>
#include <drivers/ramtron/ramtron.h>
#include <drivers/i2c/eeprom.h>
#include <px4_platform_common/log.h>

int board_mtd_initialize()
{
    /* ========================================================
     * 1. SPI FRAM (原 spi5 / FM25V05A)
     * =======================================================
     * 设备信息:
     * - FM25V05A: 64K x 8 bit = 64 KB
     * - 分区: /fs/mtd_params
     * -------------------------------------------------------
     */

#ifdef CONFIG_RAMTRON
    {
        ramtron_config_t fram_cfg{};
        fram_cfg.bus = 5;                      // SPI5
        fram_cfg.devid = SPIDEV_FLASH(0);
        fram_cfg.frequency = 20 * 1000 * 1000; // 20MHz

        fram_cfg.blocksize = (1 << CONFIG_RAMTRON_EMULATE_SECTOR_SHIFT);
        fram_cfg.nblocks = (65536 / fram_cfg.blocksize);

        if (ramtron_initialize(&fram_cfg) != PX4_OK) {
            PX4_ERR("Failed to init FRAM on SPI5");
        } else {
            PX4_INFO("FRAM init OK: /fs/mtd_params");
        }
    }
#endif


    /* ========================================================
     * 2. I2C EEPROM (原 i2c4 / 24LC64T)
     * =======================================================
     * 设备信息:
     * - 24LC64T: 8KB
     * - 分为两个分区:
     *      /fs/mtd_caldata
     *      /fs/mtd_net
     * -------------------------------------------------------
     */

    {
        int bus = 4;  // I2C4
        int addr = 0x50;

        if (i2c_eeprom_initialize(bus, addr) != PX4_OK) {
            PX4_ERR("Failed to init I2C EEPROM");
        } else {
            PX4_INFO("EEPROM init OK: /fs/mtd_caldata, /fs/mtd_net");
        }
    }

    return OK;
}

// #include <nuttx/config.h>
// #include <board_config.h>

// #include <nuttx/spi/spi.h>
// #include <px4_platform_common/px4_manifest.h>
// //                                                              KiB BS    nB
// static const px4_mft_device_t spi5 = {             // FM25V05A on FMUM native: 64K X 8, emulated as (1024 Blocks of 64)
// 	.bus_type = px4_mft_device_t::SPI,
// 	.devid    = SPIDEV_FLASH(0)
// };
// static const px4_mft_device_t i2c4 = {             // 24LC64T on IMU   8K 32 X 256
// 	.bus_type =  px4_mft_device_t::I2C,
// 	.devid    =  PX4_MK_I2C_DEVID(4, 0x50)
// };

// static const px4_mtd_entry_t fmum_fram = {
// 	.device = &spi5,
// 	.npart = 1,
// 	.partd = {
// 		{
// 			.type = MTD_PARAMETERS,
// 			.path = "/fs/mtd_params",
// 			.nblocks = (65536 / (1 << CONFIG_RAMTRON_EMULATE_SECTOR_SHIFT))
// 		}
// 	},
// };

// static const px4_mtd_entry_t imu_eeprom = {
// 	.device = &i2c4,
// 	.npart = 2,
// 	.partd = {
// 		{
// 			.type = MTD_CALDATA,
// 			.path = "/fs/mtd_caldata",
// 			.nblocks = 248
// 		},
// 		{
// 			.type = MTD_NET,
// 			.path = "/fs/mtd_net",
// 			.nblocks = 8 // 256 = 32 * 8
// 		}
// 	},
// };

// static const px4_mtd_manifest_t board_mtd_config = {
// 	.nconfigs   = 2,
// 	.entries = {
// 		&fmum_fram,
// 		&imu_eeprom
// 	}
// };

// static const px4_mft_entry_s mtd_mft = {
// 	.type = MTD,
// 	.pmft = (void *) &board_mtd_config,
// };


// static const px4_mft_s mft = {
// 	.nmft = 1,
// 	.mfts = {
// 		&mtd_mft,
// 	}
// };

// const px4_mft_s *board_get_manifest(void)
// {
// 	return &mft;
// }
