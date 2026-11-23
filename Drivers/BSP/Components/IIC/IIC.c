/**
  ******************************************************************************
  * @file    Project/User/IIC_OLED.c
  * @author  Dragino
  * @version
  * @date    8-May-2017
  * @brief   Hardware I2C transport for the MPU9250 sensor bus.
  ******************************************************************************
  * @attention
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include <stddef.h>

#include "hw.h"
#include "IIC.h"
#include "hw_rtc.h"

#define IIC_TRANSFER_TIMEOUT_MS 25U

/* 100 kHz at 32 MHz I2CCLK, scaled from RM0376 Table 122 (16 MHz). */
#define IIC_I2C_TIMING_100KHZ 0x70420F13UL

extern __IO uint32_t uwTick;

static I2C_HandleTypeDef IIC_Handle;
static uint8_t IIC_Initialized;
static uint8_t IIC_MspInitialized;
static uint8_t IIC_RtcTimebaseEnabled;

uint32_t HAL_GetTick(void)
{
  if (IIC_RtcTimebaseEnabled != 0U)
  {
    return (uint32_t)HW_RTC_Tick2ms(HW_RTC_GetTimerValue());
  }

  /* HAL_InitTick intentionally leaves SysTick disabled in this application. */
  return uwTick;
}

void IIC_GPIO_MODE_Config(void)
{
  if (IIC_Initialized != 0U)
  {
    return;
  }

  /* HW_Init() initializes the RTC before this startup hook is called. */
  IIC_RtcTimebaseEnabled = 1U;
  IIC_MspInitialized = 0U;

  IIC_Handle.Instance = I2Cx;
  IIC_Handle.Init.Timing = IIC_I2C_TIMING_100KHZ;
  IIC_Handle.Init.OwnAddress1 = 0U;
  IIC_Handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  IIC_Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  IIC_Handle.Init.OwnAddress2 = 0U;
  IIC_Handle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  IIC_Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  IIC_Handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  if ((HAL_I2C_Init(&IIC_Handle) != HAL_OK) || (IIC_MspInitialized == 0U))
  {
    Error_Handler();
    return;
  }

  IIC_Initialized = 1U;
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  if ((hi2c == NULL) || (hi2c->Instance != I2Cx))
  {
    return;
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2Cx;
  PeriphClkInit.I2c1ClockSelection = RCC_I2CxCLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    return;
  }

  I2Cx_SCL_GPIO_CLK_ENABLE();
  I2Cx_SDA_GPIO_CLK_ENABLE();
  I2Cx_CLK_ENABLE();

  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;

  GPIO_InitStruct.Pin = I2Cx_SCL_PIN;
  HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = I2Cx_SDA_PIN;
  HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);

  IIC_MspInitialized = 1U;
}

uint8_t IIC_MemRead(uint8_t device_address,
                    uint8_t register_address,
                    uint16_t length,
                    uint8_t *data)
{
  HAL_StatusTypeDef status;

  if ((IIC_Initialized == 0U) || (data == NULL) || (length == 0U) ||
      (device_address > 0x7FU))
  {
    return 1U;
  }

  status = HAL_I2C_Mem_Read(&IIC_Handle,
                            (uint16_t)((uint16_t)device_address << 1U),
                            register_address,
                            I2C_MEMADD_SIZE_8BIT,
                            data,
                            length,
                            IIC_TRANSFER_TIMEOUT_MS);
  return (status == HAL_OK) ? 0U : 1U;
}

uint8_t IIC_MemWrite(uint8_t device_address,
                     uint8_t register_address,
                     uint16_t length,
                     uint8_t *data)
{
  HAL_StatusTypeDef status;

  if ((IIC_Initialized == 0U) || (data == NULL) || (length == 0U) ||
      (device_address > 0x7FU))
  {
    return 1U;
  }

  status = HAL_I2C_Mem_Write(&IIC_Handle,
                             (uint16_t)((uint16_t)device_address << 1U),
                             register_address,
                             I2C_MEMADD_SIZE_8BIT,
                             data,
                             length,
                             IIC_TRANSFER_TIMEOUT_MS);
  return (status == HAL_OK) ? 0U : 1U;
}
