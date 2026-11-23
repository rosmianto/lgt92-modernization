#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "radio.h"

static void RadioMockNoOp(void)
{
}

static uint32_t RadioMockInit(RadioEvents_t *events)
{
    (void)events;
    return 0U;
}

static RadioState_t RadioMockGetStatus(void)
{
    return RF_IDLE;
}

static bool RadioMockIsChannelFree(RadioModems_t modem,
                                   uint32_t frequency,
                                   int16_t rssi_threshold,
                                   uint32_t max_carrier_sense_time)
{
    (void)modem;
    (void)frequency;
    (void)rssi_threshold;
    (void)max_carrier_sense_time;
    return true;
}

static void RadioMockSetModem(RadioModems_t modem)
{
    (void)modem;
}

static void RadioMockSetChannel(uint32_t frequency)
{
    (void)frequency;
}

static uint32_t RadioMockRandom(void)
{
    return 0x4C475439UL;
}

static void RadioMockSetRxConfig(RadioModems_t modem,
                                 uint32_t bandwidth,
                                 uint32_t datarate,
                                 uint8_t coderate,
                                 uint32_t bandwidth_afc,
                                 uint16_t preamble_length,
                                 uint16_t symbol_timeout,
                                 bool fixed_length,
                                 uint8_t payload_length,
                                 bool crc_on,
                                 bool frequency_hopping,
                                 uint8_t hop_period,
                                 bool iq_inverted,
                                 bool rx_continuous)
{
    (void)modem;
    (void)bandwidth;
    (void)datarate;
    (void)coderate;
    (void)bandwidth_afc;
    (void)preamble_length;
    (void)symbol_timeout;
    (void)fixed_length;
    (void)payload_length;
    (void)crc_on;
    (void)frequency_hopping;
    (void)hop_period;
    (void)iq_inverted;
    (void)rx_continuous;
}

static void RadioMockSetTxConfig(RadioModems_t modem,
                                 int8_t power,
                                 uint32_t frequency_deviation,
                                 uint32_t bandwidth,
                                 uint32_t datarate,
                                 uint8_t coderate,
                                 uint16_t preamble_length,
                                 bool fixed_length,
                                 bool crc_on,
                                 bool frequency_hopping,
                                 uint8_t hop_period,
                                 bool iq_inverted,
                                 uint32_t timeout)
{
    (void)modem;
    (void)power;
    (void)frequency_deviation;
    (void)bandwidth;
    (void)datarate;
    (void)coderate;
    (void)preamble_length;
    (void)fixed_length;
    (void)crc_on;
    (void)frequency_hopping;
    (void)hop_period;
    (void)iq_inverted;
    (void)timeout;
}

static bool RadioMockCheckRfFrequency(uint32_t frequency)
{
    (void)frequency;
    return true;
}

static uint32_t RadioMockTimeOnAir(RadioModems_t modem, uint8_t packet_length)
{
    (void)modem;
    (void)packet_length;
    return 0U;
}

static void RadioMockSend(uint8_t *buffer, uint8_t size)
{
    (void)buffer;
    (void)size;
}

static void RadioMockRx(uint32_t timeout)
{
    (void)timeout;
}

static void RadioMockSetTxContinuousWave(uint32_t frequency, int8_t power, uint16_t time)
{
    (void)frequency;
    (void)power;
    (void)time;
}

static int16_t RadioMockRssi(RadioModems_t modem)
{
    (void)modem;
    return -100;
}

static void RadioMockWrite(uint8_t address, uint8_t data)
{
    (void)address;
    (void)data;
}

static uint8_t RadioMockRead(uint8_t address)
{
    (void)address;
    return 0U;
}

static void RadioMockWriteBuffer(uint8_t address, uint8_t *buffer, uint8_t size)
{
    (void)address;
    (void)buffer;
    (void)size;
}

static void RadioMockReadBuffer(uint8_t address, uint8_t *buffer, uint8_t size)
{
    (void)address;
    if (buffer != NULL)
    {
        (void)memset(buffer, 0, size);
    }
}

static void RadioMockSetMaxPayloadLength(RadioModems_t modem, uint8_t max)
{
    (void)modem;
    (void)max;
}

static void RadioMockSetPublicNetwork(bool enable)
{
    (void)enable;
}

static uint32_t RadioMockGetRadioWakeUpTime(void)
{
    return 0U;
}

const struct Radio_s Radio = {
    .IoInit = RadioMockNoOp,
    .IoDeInit = RadioMockNoOp,
    .Init = RadioMockInit,
    .GetStatus = RadioMockGetStatus,
    .SetModem = RadioMockSetModem,
    .SetChannel = RadioMockSetChannel,
    .IsChannelFree = RadioMockIsChannelFree,
    .Random = RadioMockRandom,
    .SetRxConfig = RadioMockSetRxConfig,
    .SetTxConfig = RadioMockSetTxConfig,
    .CheckRfFrequency = RadioMockCheckRfFrequency,
    .TimeOnAir = RadioMockTimeOnAir,
    .Send = RadioMockSend,
    .Sleep = RadioMockNoOp,
    .Standby = RadioMockNoOp,
    .Rx = RadioMockRx,
    .StartCad = RadioMockNoOp,
    .SetTxContinuousWave = RadioMockSetTxContinuousWave,
    .Rssi = RadioMockRssi,
    .Write = RadioMockWrite,
    .Read = RadioMockRead,
    .WriteBuffer = RadioMockWriteBuffer,
    .ReadBuffer = RadioMockReadBuffer,
    .SetMaxPayloadLength = RadioMockSetMaxPayloadLength,
    .SetPublicNetwork = RadioMockSetPublicNetwork,
    .GetRadioWakeUpTime = RadioMockGetRadioWakeUpTime,
};
