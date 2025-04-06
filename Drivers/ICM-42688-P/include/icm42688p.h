//INCLUDE LIBRARIES AND GUARDS LATER WHEN YOU UNDERSTAND THEM BETTER


//REGISTER DEFINITIONS 

//The only register settings that user can modify during sensor operation are for ODR selection, FSR selection, and sensor mode
//changes (register parameters GYRO_ODR, ACCEL_ODR, GYRO_FS_SEL, ACCEL_FS_SEL, GYRO_MODE, ACCEL_MODE). User must not
//modify any other register values during sensor operation.

// Bank 0 registers
#define DEVICE_CONFIG 0x11 /* RV: 0x00 */ // BIT 4 FOR SPI MODE SELECTION, BIT 0 FOR SOFT_RESET_CONFIG
#define DRIVE_CONFIG 0x13 /* RV: 0x05 */ //BITS 2:0 DEFINE SPI SLEW RATE
#define INT_CONFIG 0x14 /* RV: 0x00 */ // INT2 MODE:CIRCUITS:POLARITY >> BITS 5:4:3 //INT1 MODE:CIRCUITS:POLARITY >> BITS 2:1:0
#define FIFO_CONFIG 0x16

#define UPPER_TEMP_DATA 0x80  // TEMP DATA [15:8] (Bits 9 -16)
#define LOWER_TEMP_DATA 0x00 // TEMP DATA [7:0] (Bits 1- 8)

#define UPPER_X_ACCEL_DATA 0x1F // X ACCL [15:8]
#define LOWER_X_ACCEL_DATA 
