#include "Arduino.h"
#include "Accel32.h"

Accel32::Accel32() {
    Wire.begin(17, 16);
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
}

Accel32::Accel32(int SDA, int SCL) {
    Wire.begin(SDA, SCL);
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
}

void Accel32::SensitiveSet(int sense) {
    sensitivity = sense;
}

int Accel32::Count() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > 100) {
        i++;
        if (i >= 20) {
            i = 1;
        }
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
        x = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
        y = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        z = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        temp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
        gx = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        gy = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        gz = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
        ax[i] = x / sensitivity; ay[i] = y / sensitivity; az[i] = z / sensitivity;
        dx = ax[i] - ax[0];       dy = ay[i] - ay[0];       dz = az[i] - az[0];
        ax[i] = ax[i] / ax[0];    ay[i] = ay[i] / ay[0];    az[i] = az[i] / az[0];
        a = sqrt(ax[i] * ax[i] + ay[i] * ay[i] + az[i] * az[i]);
        if (a > 3 && (((dz > 0.06 || dz < -0.06) && (dx < -0.06 || dx > 0.06)) || ((dz > 0.06 || dz < -0.06) && (dy < -0.06 || dy > 0.06)) || ((dy > 0.06 || dy < -0.06) && (dx < -0.06 || dx > 0.06))) && j > 3) {
            j = 0;
            counter++;
            checkangle = true;
            dx_old = dx; dy_old = dy; dz_old = dz;
            return_angle = 0;
        }
        if (checkangle) {
            if (( dx_old - dx > 0.02) || ( dx_old - dx < -0.02)) {
                return_angle++;
            }
            if (( dy_old - dy > 0.02) || ( dy_old - dy < -0.02)) {
                return_angle++;
            }
            if (( dz_old - dz > 0.02) || ( dz_old - dz < -0.02)) {
                return_angle++;
            }
        }
        if (j == 3 && checkangle && (return_angle < 2)) {
            Recalibrate();
            checkangle = false;
        }
        j++;
        previousMillis = currentMillis;
    }
    return(counter);
}

bool Accel32::Detected() {
    detected = false;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > 100) {
        i++;
        if (i >= 20) {
            i = 1;
        }
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
        x = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
        y = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        z = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        temp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
        gx = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        gy = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        gz = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
        ax[i] = x / sensitivity; ay[i] = y / sensitivity; az[i] = z / sensitivity;
        dx = ax[i] - ax[0];       dy = ay[i] - ay[0];       dz = az[i] - az[0];
        ax[i] = ax[i] / ax[0];    ay[i] = ay[i] / ay[0];    az[i] = az[i] / az[0];
        a = sqrt(ax[i] * ax[i] + ay[i] * ay[i] + az[i] * az[i]);
        if (a > 3 && (((dz > 0.06 || dz < -0.06) && (dx < -0.06 || dx > 0.06)) || ((dz > 0.06 || dz < -0.06) && (dy < -0.06 || dy > 0.06)) || ((dy > 0.06 || dy < -0.06) && (dx < -0.06 || dx > 0.06))) && j > 3) {
            j = 0;
            detected = true;
            checkangle = true;
            dx_old = dx; dy_old = dy; dz_old = dz;
            return_angle = 0;
        }
        if (checkangle) {
            if (( dx_old - dx > 0.02) || ( dx_old - dx < -0.02)) {
                return_angle++;
            }
            if (( dy_old - dy > 0.02) || ( dy_old - dy < -0.02)) {
                return_angle++;
            }
            if (( dz_old - dz > 0.02) || ( dz_old - dz < -0.02)) {
                return_angle++;
            }
        }
        if (j == 3 && checkangle && (return_angle < 2)) {
            Recalibrate();
            checkangle = false;
        }
        j++;
        previousMillis = currentMillis;
    }
    return(detected);
}

void Accel32::Recalibrate() {
    for ( int i = 1; i <= 50; i++) {
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
        x = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
        y = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        z = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        temp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
        gx = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        gy = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        gz = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    }
    ax[0] = x / sensitivity; ay[0] = y / sensitivity; az[0] = z / sensitivity;
}
