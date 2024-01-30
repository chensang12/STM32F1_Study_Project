/*
 * @Author: Chen 2603148225@qq.com
 * @Date: 2023-03-24 15:02:31
 * @LastEditors: Chen 2603148225@qq.com
 * @LastEditTime: 2023-03-24 15:16:21
 * @FilePath: \软件I2C读取MPU6050\Hardware\MPU6050_Reg.H
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MPU6050_REG_H
#define __MPU6050_REG_H

/*陀螺仪采样分频寄存器*/
#define MPU6050_SMPLRT_DIV      0X19
/*配置寄存器*/
#define MPU6050_CONFIG          0X1A
/*陀螺配置寄存器*/
#define MPU6050_GYRO_CONFIG     0X1B
/*加速度*/
#define MPU6050_ACCEL_CONFIG    0X1C

#define MPU6050_ACCEL_XOUT_H    0X3B
#define MPU6050_ACCEL_XOUT_L    0X3C
#define MPU6050_ACCEL_YOUT_H    0X3D
#define MPU6050_ACCEL_YOUT_L    0X3E
#define MPU6050_ACCEL_ZOUT_H    0X3F
#define MPU6050_ACCEL_ZOUT_L    0X40

#define MPU6050_TEMP_OUT_H      0X41
#define MPU6050_TEMP_OHT_L      0X42

#define MPU6050_GYRO_XOUT_H     0X43
#define MPU6050_GYRO_XOUT_L     0X44
#define MPU6050_GYRO_YOUT_H     0X45
#define MPU6050_GYRO_YOUT_L     0X46
#define MPU6050_GYRO_ZOUT_H     0X47
#define MPU6050_GYRO_ZOUT_L     0X48

#define MPU6050_PWR_MGMT_1      0X6B
#define MPU6050_PWR_MGMT_2      0X6C
#define MPU6050_WHO_AM_I        0X75

#endif
