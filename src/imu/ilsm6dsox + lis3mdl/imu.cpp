#include "imu.h"
#include "pins.h"
#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS3MDL.h>



Adafruit_LSM6DSOX sox;
Adafruit_LIS3MDL lis3mdl;
const byte PICO_I2C_SDA = 18;
const byte PICO_I2C_SCL = 19;

bool init_imu(){
    Wire1.setSDA(PICO_I2C_SDA);
    Wire1.setSCL(PICO_I2C_SCL);


    if (!sox.begin_I2C(0x1c,&Wire1,0L)) {
        while (1) {
        delay(10);
        }
    }
    sox.setGyroDataRate(LSM6DS_RATE_104_HZ);
    sox.setAccelDataRate(LSM6DS_RATE_104_HZ);
    if (!lis3mdl.begin_I2C(0x1c,&Wire1)) {
        while (1) {
        delay(10);
        }
    }
    lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
    lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
    lis3mdl.setDataRate(LIS3MDL_DATARATE_80_HZ);
    lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
    lis3mdl.setIntThreshold(500);
    
}

bool imu_read(float *acceleration_mss, float *gyro_rads, float *mag_uT)
{
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    sox.getEvent(&accel, &gyro, &temp);
    sensors_event_t event; 
    lis3mdl.getEvent(&event);


    acceleration_mss[0] = accel.acceleration.x;
    acceleration_mss[1] = accel.acceleration.y;
    acceleration_mss[2] = accel.acceleration.z;

    gyro_rads[0] = gyro.gyro.x;
    gyro_rads[1] = gyro.gyro.y;
    gyro_rads[2] = -gyro.gyro.z;

    mag_uT[0] = event.magnetic.x;
    mag_uT[1] = event.magnetic.y;
    mag_uT[2] = event.magnetic.z;

    return true;
}

void imu_loop() {

}

