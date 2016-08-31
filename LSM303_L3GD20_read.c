// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LSM303DLHC
// This code is designed to work with the LSM303DLHC_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	char data[1] = {0};
	char reg[1] = {0x00};
	float rate_gyr_x = 0.0;
	float rate_gyr_y = 0.0;
	float rate_gyr_z = 0.0;
	
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}



int a = 0;
while (a<1) {
	

	// Get I2C device, LSM303DLHC ACCELERO I2C address is 0x19(25)
	ioctl(file, I2C_SLAVE, 0x19);

	// Select control register1(0x20)
	// X, Y and Z-axis enable, power on mode, o/p data rate 10 Hz(0x27)
	char config[2] = {0};
	config[0] = 0x20;
	config[1] = 0x27;
	write(file, config, 2);
	// Select control register4(0x23)
	// Full scale +/- 2g, continuous update(0x00)
	config[0] = 0x23;
	config[1] = 0x00;
	write(file, config, 2);
//	sleep(0.1);

	// Read 6 bytes of data
	// lsb first
	// Read xAccl lsb data from register(0x28)
	reg[1] = 0x28;
	write(file, reg, 1);
	data[1] = 0;
	if(read(file, data, 1) != 1)
	{
		printf("Erorr : Input/output Erorr \n");
		exit(1);
	}
	char data_0 = data[0];

	// Read xAccl msb data from register(0x29)
	reg[0] = 0x29;
	write(file, reg, 1);
	read(file, data, 1);
	char data_1 = data[0];

	// Read yAccl lsb data from register(0x2A)
	reg[0] = 0x2A;
	write(file, reg, 1);
	read(file, data, 1);
	char data_2 = data[0];

	// Read yAccl msb data from register(0x2B)
	reg[0] = 0x2B;
	write(file, reg, 1);
	read(file, data, 1);
	char data_3 = data[0];

	// Read zAccl lsb data from register(0x2C)
	reg[0] = 0x2C;
	write(file, reg, 1);
	read(file, data, 1);
	char data_4 = data[0];

	// Read zAccl msb data from register(0x2D)
	reg[0] = 0x2D;
	write(file, reg, 1);
	read(file, data, 1);
	char data_5 = data[0];

	// Convert the data
	int xAccl = (data_1 * 256 + data_0);
	if(xAccl > 32767)
	{
		xAccl -= 65536;
	}

	int yAccl = (data_3 * 256 + data_2);
	if(yAccl > 32767)
	{
		yAccl -= 65536;
	}

	int zAccl = (data_5 * 256 + data_4);
	if(zAccl > 32767)
	{
	zAccl -= 65536;
	}

	// Output data to screen
	printf("Acceleration in X-Axis : %d \n", xAccl);
	printf("Acceleration in Y-Axis : %d \n", yAccl);
	printf("Acceleration in Z-Axis : %d \n\n", zAccl);
//	sleep(0.1);

	
    
	
	// Get I2C device, LSM303DLHC MAGNETO I2C address is 0x1E(30)
	ioctl(file, I2C_SLAVE, 0x1E);

	// Select MR register(0x02)
	// Continuous conversion(0x00)
	config[0] = 0x02;
	config[1] = 0x00;
	write(file, config, 2);
	// Select CRA register(0x00)
	// Data output rate = 15Hz(0x10)
	config[0] = 0x00;
	config[1] = 0x10;
//	write(file, config, 2);
	// Select CRB register(0x01)
	// Set gain = +/- 1.3g(0x20)
	config[0] = 0x01;
	config[1] = 0x20;
//	write(file, config, 2);
//	sleep(0.1);

	// Read 6 bytes of data
	// msb first
	// Read xMag msb data from register(0x03)
	reg[0] = 0x03;
	write(file, reg, 1);
	read(file, data, 1);
	char data1_0 = data[0];

	// Read xMag lsb data from register(0x04)
	reg[0] = 0x04;
	write(file, reg, 1);
	read(file, data, 1);
	char data1_1 = data[0];

	// Read yMag msb data from register(0x05)
	reg[0] = 0x05;
	write(file, reg, 1);
	read(file, data, 1);
	char data1_2 = data[0];

	// Read yMag lsb data from register(0x06)
	reg[0] = 0x06;
	write(file, reg, 1);
	read(file, data, 1);
	char data1_3 = data[0];

	// Read zMag msb data from register(0x07)
	reg[0] = 0x07;
	write(file, reg, 1);
	read(file, data, 1);
	char data1_4 = data[0];

	// Read zMag lsb data from register(0x08)
	reg[0] = 0x08;
	write(file, reg, 1);
	read(file, data, 1);
	char data1_5 = data[0];

	// Convert the data
	int xMag = (data1_0 * 256 + data1_1);
	if(xMag > 32767)
	{
		xMag -= 65536;
	}	

	int yMag = (data1_4 * 256 + data1_5) ;
	if(yMag > 32767)
	{
		yMag -= 65536;
	}

	int zMag = (data1_2 * 256 + data1_3) ;
	if(zMag > 32767)
	{
		zMag -= 65536;
	}

	// Output data to screen
	printf("Magnetic field in X-Axis : %d \n", xMag);
	printf("Magnetic field in Y-Axis : %d \n", yMag);
	printf("Magnetic field in Z-Axis : %d \n\n", zMag);
//	sleep(0.1);
	
	
	

	
	// Get I2C device, L3GD20 Gyro 0x6b
	ioctl(file, I2C_SLAVE, 0x6b);

	//write 0x30 to L3G_CTRL_REG4 (0x23)
	config[0] = 0x23;
	config[1] = 0x30;
	write(file, config, 2);	
	
	// Enable the Gyro:
	//write  0x0f to L3G_CTRL_REG1 (0x20)
	config[0] = 0x20;
	config[1] = 0x0f;
	write(file, config, 2);
//	sleep(0.1);


	
	// Read gyro
	// Read 6 bytes of data
	// lsb first
	// Read gyro_x_lsb data from register(0x28)
	reg[0] = 0x28;
	write(file, reg, 1);
	data[1] = 0;
	if(read(file, data, 1) != 1)
	{
		printf("Erorr : Input/output Erorr \n");
		exit(1);
	}
//	printf("0x28 is: %#x\n", data[0]);
	data_0 = data[0];

	// Read  gyro_x_msb data from register(0x29)
	reg[0] = 0x29;
	write(file, reg, 1);
	read(file, data, 1);
//	printf("0x29 is: %#x\n", data[0]);
	data_1 = data[0];

	// Read  gyro_y_lsb data from register(0x2A)
	reg[0] = 0x2A;
	write(file, reg, 1);
	read(file, data, 1);
//	printf("0x2A is: %#x\n", data[0]);
	data_2 = data[0];

	// Read  gyro_y_msb data from register(0x2B)
	reg[0] = 0x2B;
	write(file, reg, 1);
	read(file, data, 1);
//	printf("0x2B is: %#x\n", data[0]);
	data_3 = data[0];

	// Read gyro_z_lsb data from register(0x2C)
	reg[0] = 0x2C;
	write(file, reg, 1);
	read(file, data, 1);
//	printf("0x2C is: %#x\n", data[0]);
	data_4 = data[0];

	// Read  gyro_x_msb data from register(0x2D)
	reg[0] = 0x2D;
	write(file, reg, 1);
	read(file, data, 1);
//	printf("0x2D is: %#x\n", data[0]);
	data_5 = data[0];



// Convert the data

	int xgyro_int = (data_1 << 8 | data_0);
	int ygyro_int = (data_3 << 8 | data_2);
	int zgyro_int = (data_5 << 8 | data_4);

//	short xgyro_sh = (short)xgyro_int;
//	short ygyro_sh = (short)ygyro_int;
//	short zgyro_sh = (short)zgyro_int;
	
	float xGyro = (float)(short)xgyro_int;
	float yGyro = (float)(short)ygyro_int;
	float zGyro = (float)(short)zgyro_int;
	
//	printf("xGyro f is: %f\n", xGyro);
//	printf("yGyro f is: %f\n", yGyro);
//	printf("zGyro f is: %f\n", zGyro);	
	
	float G_GAIN = 0.00875;

	rate_gyr_x = (float) xGyro * G_GAIN;
	rate_gyr_y = (float) yGyro * G_GAIN;
	rate_gyr_z = (float) zGyro * G_GAIN;
	
	// Output data to screen
	printf("Gyro Rate in X-Axis : %f \n", rate_gyr_x);
	printf("Gyro Rate in Y-Axis : %f \n", rate_gyr_y);
	printf("Gyro Rate in Z-Axis : %f \n\n", rate_gyr_z);
	sleep (1);

    }
	

}
