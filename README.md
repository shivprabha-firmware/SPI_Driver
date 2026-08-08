# STM32 SPI Polling Driver

A bare-metal SPI driver developed in Embedded C for the STM32F051R8T6 microcontroller.

The driver directly configures the STM32 SPI peripheral registers and provides APIs for SPI initialization, peripheral control, polling-based transmission, polling-based reception, and status-flag checking.

## Features

- SPI1 peripheral support
- Master and Slave mode configuration
- Full-duplex and Half-duplex configuration
- 8-bit and 16-bit data frame support
- SPI clock prescaler configuration:
  - DIV2
  - DIV4
  - DIV8
  - DIV16
  - DIV32
  - DIV64
  - DIV128
  - DIV256
- CPOL configuration
- CPHA configuration
- Software Slave Management (SSM)
- SPI peripheral enable/disable
- Polling-based data transmission
- Polling-based data reception
- SPI status flag checking
- TXE flag polling during transmission
- RXNE flag polling during reception
- BSY flag checking after transmission

## Hardware

- Microcontroller: STM32F051R8T6
- SPI Peripheral: SPI1
- Development Environment: STM32CubeIDE
- Language: Embedded C

## SPI Configuration

The driver provides configuration through `SPI_Config_t`.

The following parameters can be configured:

| Parameter | Supported Configuration |
|---|---|
| Device Mode | Master / Slave |
| Bus Configuration | Full Duplex / Half Duplex |
| SPI Clock | DIV2 to DIV256 |
| Data Size | 8-bit / 16-bit |
| Clock Polarity | Low / High |
| Clock Phase | First Edge / Second Edge |
| Slave Management | Software SSM Enable / Disable |

## Driver APIs

### SPI_periclockcontrol()

Enables the clock for the SPI peripheral.

```c
void SPI_periclockcontrol(SPI_TypeDef *pSPIx, uint8_t ENorDI);
