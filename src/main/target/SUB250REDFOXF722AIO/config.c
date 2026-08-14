/*
 * This file is part of INAV Project.
 *
 * INAV is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * INAV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with INAV.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#include "platform.h"

#include "drivers/pwm_mapping.h"

#include "fc/fc_msp_box.h"
#include "fc/config.h"

#include "flight/mixer.h"

#include "io/piniobox.h"
#include "io/serial.h"

#include "sensors/boardalignment.h"

void targetConfiguration(void)
{
    // Gyro chips are mounted CW90; the board itself sits at -45 degrees yaw
    boardAlignmentMutable()->yawDeciDegrees = -450;

    pinioBoxConfigMutable()->permanentId[0] = BOX_PERMANENT_ID_USER1;
    pinioBoxConfigMutable()->permanentId[1] = BOX_PERMANENT_ID_USER2;

    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART6)].functionMask = FUNCTION_GPS;

    motorConfigMutable()->motorPwmProtocol = PWM_TYPE_DSHOT600;
}
