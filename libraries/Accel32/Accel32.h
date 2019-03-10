#ifndef Accel32_h
#define Accel32_h
#include "Arduino.h"
#include "Wire.h"

class Accel32 {
    public:
        Accel32();
        Accel32(int SDA, int SCL);
        void Recalibrate();
        void SensitiveSet(int sense);
        int Count();
        int ReadTemp();
        bool Detected();
    private:
        const int MPU_addr = 0x68; // I2C address of the MPU-6050
        int16_t x, y, z, temp, gx, gy, gz;
        float sensitivity = 16384;
        float ax[20], ay[20], az[20];
        float dx, dy, dz;
        float dx_old, dy_old, dz_old;
        int a;
        int i = 0;
        int j = 0;
        int counter = 0;
        int return_angle = 0;
        long previousMillis = 0;
        bool checkangle = false;
        bool detected = false;
};
#endif