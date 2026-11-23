I see that this project uses bit-banged IIC.c to interact with the MPU9250.

Check if IIC.c is useful, and check if we can replace it with hardware I2C built into STM32L072 instead. Plan mode.