# Sub250 Redfox A3 F722 AIO (SUB250REDFOXF722AIO)

Whoop-style 25.5×25.5 mm AIO flight controller with integrated 35A/45A BLHeli_32
4-in-1 ESC, sold in Sub250 2.5"–3.5" builds. Same target name as Betaflight
(`SUB250REDFOXF722AIO`).

## Hardware

| Component | Detail |
|-----------|--------|
| MCU | STM32F722RET6 |
| IMU | ICM42688P on production boards (SPI1, CS PA4). MPU6000 and BMI270 drivers are also compiled in for board revisions. |
| Sensor orientation | Gyro mounted CW90; board yaw offset −45°. Both are preconfigured in the target — verify in the Setup tab: nose down must pitch the model nose down, roll right must roll it right. |
| Barometer | DPS310 or BMP280 (revision-dependent), on internal I2C1 |
| OSD | AT7456E (MAX7456-compatible) analog OSD on SPI2 |
| Blackbox | 16 MB SPI NOR flash on SPI3. Note: production boards carry a Puya PY25Q128HA (JEDEC 0x852018), not the Winbond part the Betaflight config names. Supported since INAV 9.1. |
| ESC | 35A (45A burst) BLHeli_32 4-in-1, DShot600 default |
| Battery | 2–6S, VBAT PC1, current sensor PC3 (scale 250, preset) |
| BEC | 5 V @ 2.5 A |

## Serial ports

| UART | Pins | Pads / socket | Notes |
|------|------|---------------|-------|
| UART1 | PB6/PB7 | T1/R1 | Target default: serial RX (CRSF). Any full-duplex use works (e.g. GPS). |
| UART2 | PA2/PA3 | T2/R2 | Free. Suggested optical flow port on DJI builds. |
| UART3 | PB11 (RX only) | DJI 6-pin socket, SBUS pin | SBUS output of a DJI air unit's built-in receiver. **RX-only**: the USART3 TX pin (PB10) is routed to the second gyro position's interrupt pad and is not available. |
| UART4 | PA0/PA1 | DJI 6-pin socket + T4/R4 side pads | DJI MSP DisplayPort, or IRC Tramp for an analog VTX. |
| UART5 | PC12/PD2 | internal | ESC telemetry from the 4-in-1. |
| UART6 | PC6/PC7 | GPS socket (T6/R6) | Target default: GPS. |

## I2C

I2C1 is broken out on the `CL`/`DA` pads (next to the GPS socket) and shared with
the onboard barometer. External compass, I2C rangefinder (VL53L1X flight tested),
temperature sensors etc. connect here. No address conflicts with the baro
(0x76/0x77).

## Motors and outputs

| Output | Pin | Note |
|--------|-----|------|
| M1–M4 | PC8, PC9, PA8, PA9 | On-board 4-in-1 ESC |
| M5–M8 | PB0, PB1, PA10, PB4 | Spare pads |
| LED strip | PB3 | `LED` pad |

All motor outputs have dedicated DMA; DShot works on all eight with blackbox
logging active.

## PINIO

| PINIO | Pin | Box |
|-------|-----|-----|
| PINIO1 | PC0 | USER1 |
| PINIO2 | PC2 | USER2 |

Both outputs are inverted, matching the Betaflight configuration.

## Nav peripherals (flight tested)

Tested on a 2.5" build: GPS (UART), PMW3901-based optical flow module using the
CXOF protocol (any free UART, 19200 baud), VL53L1X rangefinder (I2C1), and a
DJI O4 Air Unit Lite (MSP DisplayPort on UART4, SBUS fast on UART3).

## Flashing

The target is flashed like any INAV firmware via DFU (hold BOOT, connect USB).
Until it appears in a release, build from source and use
"Load firmware [Local]" in INAV Configurator. The board can always be restored
to Betaflight (target `SUB250REDFOXF722AIO`) over DFU.
