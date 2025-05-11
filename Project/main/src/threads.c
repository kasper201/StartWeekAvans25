#include "threads.h"

//#include <zephyr/kernel.h>

// Thread startupdelay
uint32_t Startupdelay = 120000;

// Define the threads
// Input threads
K_THREAD_DEFINE(tstartbutton_id, STACKSIZE, tstartbutton, NULL, NULL, NULL, TSTARTBUTTON_PRIORITY, 0,0);
K_THREAD_DEFINE(tgps_id, STACKSIZE, tgps, NULL, NULL, NULL, TGPS_PRIORITY, 0, 0);
K_THREAD_DEFINE(tgyro_id, STACKSIZE, tgyro, NULL, NULL, NULL, TGYRO_PRIORITY, 0, 0);
K_THREAD_DEFINE(tbtnmatrix_in_id, STACKSIZE, tbtnmatrix_in, NULL, NULL, NULL, TBTNMATRIX_IN_PRIORITY, 0, 0);
K_THREAD_DEFINE(tswitches_id, STACKSIZE, tswitches, NULL, NULL, NULL, TSWITCHES_PRIORITY, 0, 0);
K_THREAD_DEFINE(tpotmeter_id, STACKSIZE, tpotmeter, NULL, NULL, NULL, TPOTMETER_PRIORITY, 0, 0);
K_THREAD_DEFINE(tabcbtn_id, STACKSIZE, tabcbtn, NULL, NULL, NULL, TABCBTN_PRIORITY, 0, 0);
// Output threads
K_THREAD_DEFINE(tbtnmatrix_out_id, STACKSIZE, tbtnmatrix_out, NULL, NULL, NULL, TBTNMATRIX_OUT_PRIORITY, 0, 0);
K_THREAD_DEFINE(tbuzzers_id, STACKSIZE, tbuzzers, NULL, NULL, NULL, TBUZZERS_PRIORITY, 0, 0);
K_THREAD_DEFINE(tledmatrix_id, STACKSIZE, tledmatrix, NULL, NULL, NULL, TLEDMATRIX_PRIORITY, 0, 0);
K_THREAD_DEFINE(tledcircle_id, STACKSIZE, tledcircle, NULL, NULL, NULL, TLEDCIRCLE_PRIORITY, 0, 0);
K_THREAD_DEFINE(tsevenseg_id, STACKSIZE, tsevenseg, NULL, NULL, NULL, TSEVENSEG_PRIORITY, 0, 0);

// Mutex Defines + protected an unprotected variable

K_MUTEX_DEFINE(startbuttonMutex);// Mutex
uint8_t startbuttonMutexValue = 0; // MutexValue (Protected)
uint8_t startbuttonMutexValueRet = 0; // Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(gpsMutex); // Mutex
int64_t gpsMutexValue[2] = {0,0}; // MutexValue (Protected)
int64_t gpsMutexValueRet[2] = {0,0}; // Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(gyroMutex); // Mutex
int16_t gyroMutexMagnetoValue[3] = {0,0,0}; // MutexValue (Protected)
int16_t gyroMutexAccelValue[3] = {0,0,0}; // MutexValue (Protected)
int		gyroMutexRollValue = 0; // MutexValue (Protected)
int		gyroMutexPitchValue = 0; // MutexValue (Protected)
int		gyroMutexHeadingValue = 0; // MutexValue (Protected)
float	gyroMutexGyroValue[3] = {0,0,0}; // MutexValue (Protected)

int16_t gyroMutexMagnetoValueRet[3] = {0,0,0}; // Return value for mutexValue (Not protected)
int16_t gyroMutexAccelValueRet[3] = {0,0,0}; // Return value for mutexValue (Not protected)
int		gyroMutexRollValueRet = 0; // Return value for mutexValue (Not protected)
int		gyroMutexPitchValueRet = 0; // Return value for mutexValue (Not protected)
int		gyroMutexHeadingValueRet = 0; // Return value for mutexValue (Not protected)
float	gyroMutexGyroValueRet[3] = {0,0,0}; // Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(btnmatrix_inMutex);// Mutex
uint8_t btnmatrix_inMutexValue[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // MutexValue (Protected)
uint8_t btnmatrix_inMutexValueRet[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(switchsMutex); // Mutex
uint8_t switchsMutexValue[5] = {0,0,0,0,0};// MutexValue (Protected)
uint8_t switchsMutexValueRet[5] = {0,0,0,0,0};// Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(potmeterMutex); // Mutex
int32_t potmeterMutexValue = 0 ;// MutexValue (Protected)
int32_t potmeterMutexValueRet = 0 ;// Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(abcbtnMutex); // Mutex
uint8_t abcbtnMutexValue[3] = {0,0,0} ;// MutexValue (Protected)
uint8_t abcbtnMutexValueRet[3] = {0,0,0} ;// Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(btnmatrix_outMutex); // Mutex
uint8_t btnmatrix_outMutexValue[4] = {0,0,0,0}; // MutexValue (Protected)
uint8_t btnmatrix_outMutexValueOld[4] = {0,0,0,0}; // Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(buzzersMutex); // Mutex
uint8_t buzzersMutexValue[3] = {0,0,0} ;// MutexValue (Protected)
uint8_t buzzersMutexValueOld[3] = {0,0,0} ;// Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(ledmatrixMutex); // Mutex
int16_t ledmatrixMutexValue[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};// MutexValue (Protected)
int16_t ledmatrixMutexValueOld[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};// Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(ledcircleMutex); // Mutex
uint8_t ledcircleMutexValue[8] = {0,0,0,0,0,0,0,0} ;// MutexValue (Protected)
uint8_t ledcircleMutexValueOld[8] = {0,0,0,0,0,0,0,0} ;// Return value for mutexValue (Not protected)

K_MUTEX_DEFINE(sevensegMutex); // Mutex
char sevensegMutexValueInput[4] = "0000";// MutexValue (Protected)
uint8_t sevensegMutexValuedpPosition = 0 ;// MutexValue (Protected)
char sevensegMutexValueInputOld[4] = "0000" ;// Return value for mutexValue (Not protected)
uint8_t sevensegMutexValuedpPositionOld = 0 ;// MutexValue (Protected)

// Input thread and mutex functions

uint8_t startbuttonGetMutexValue()
{
	if (k_mutex_lock(&startbuttonMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		for (uint8_t i = 0; i < 16; i++)
		{
			startbuttonMutexValueRet = startbuttonMutexValue; //access protected value
		}
		k_mutex_unlock(&startbuttonMutex);	
	} 
	else 
	{
		printf("Cannot lock startbutton\n");
	}
	return startbuttonMutexValueRet; //Return unprotected value
}

void tstartbutton(void) {
	k_msleep(Startupdelay); //startup sleep for main thread
	uint8_t values = 0;// Value to decrease locking amount
	while (1) 
	{
		if(values != startbuttonGet()) 
		{
			values = startbuttonGet();
			k_mutex_lock(&startbuttonMutex, K_FOREVER); // wait forever until mutex is available
			startbuttonMutexValue = values;
			k_mutex_unlock(&startbuttonMutex);
		}
		k_msleep(1000);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

/**
* @brief Get the mutex value of the gps
* @returns the gpsMutexValue
*/
int64_t* gpsGetMutexValue()
{
    if (k_mutex_lock(&gpsMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
    {
        for (uint8_t i = 0; i < 2; i++)
        {
            gpsMutexValueRet[i] = gpsMutexValue[i]; //access protected value
        }
        k_mutex_unlock(&gpsMutex);
    }
    else
    {
        printf("Cannot lock gps\n");
    }
    return gpsMutexValueRet; //Return unprotected value
}

/**
* @brief Thread to get the gps data
*/
void tgps(void) {
	k_msleep(Startupdelay);
	int64_t values[2] = {0,0};// Value to decrease locking amount
	while (true)
	{
		if(values[0] != getLatitude() || values[1] != getLongitude())
        {
            values[0] = getLatitude();
			values[1] = getLongitude();
			k_mutex_lock(&gpsMutex, K_FOREVER); // wait forever until mutex is available
			gpsMutexValue[0] = values[0];
			gpsMutexValue[1] = values[1];
			k_mutex_unlock(&gpsMutex);
        }
        k_msleep(1000);
	}
}

int16_t *gyroGetMagnetoMutexValue()
{
	if (k_mutex_lock(&gyroMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			gyroMutexMagnetoValueRet[i] = gyroMutexMagnetoValue[i]; //access protected value
		}
		k_mutex_unlock(&gyroMutex);
	}
	else
	{
		printf("Cannot lock gyro\n");
	}
	return gyroMutexMagnetoValueRet; //Return unprotected value
}

int16_t *gyroGetAccelMutexValue()
{
	if (k_mutex_lock(&gyroMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			gyroMutexAccelValueRet[i] = gyroMutexAccelValue[i]; //access protected value
		}
		k_mutex_unlock(&gyroMutex);
	}
	else
	{
		printf("Cannot lock gyro\n");
	}
	return gyroMutexAccelValueRet; //Return unprotected value
}

int gyroGetRollMutexValue()
{
	if (k_mutex_lock(&gyroMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		gyroMutexRollValueRet = gyroMutexRollValue; //access protected value
		k_mutex_unlock(&gyroMutex);
	}
	else
	{
		printf("Cannot lock gyro\n");
	}
	return gyroMutexRollValueRet; //Return unprotected value
}

int gyroGetPitchMutexValue()
{
	if (k_mutex_lock(&gyroMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		gyroMutexPitchValueRet = gyroMutexPitchValue; //access protected value
		k_mutex_unlock(&gyroMutex);
	}
	else
	{
		printf("Cannot lock gyro\n");
	}
	return gyroMutexPitchValueRet; //Return unprotected value
}

int gyroGetHeadingMutexValue()
{
	if (k_mutex_lock(&gyroMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		gyroMutexHeadingValueRet = gyroMutexHeadingValue; //access protected value
		k_mutex_unlock(&gyroMutex);
	}
	else
	{
		printf("Cannot lock gyro\n");
	}
	return gyroMutexHeadingValueRet; //Return unprotected value
}

float *gyroGetMutexGyroValue()
{
	if (k_mutex_lock(&gyroMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			gyroMutexGyroValueRet[i] = gyroMutexGyroValue[i]; //access protected value
		}
		k_mutex_unlock(&gyroMutex);
	}
	else
	{
		printf("Cannot lock gyro\n");
	}
	return gyroMutexGyroValueRet; //Return unprotected value
}

void tgyro(void)
{
	uint8_t err = 0;
	k_msleep(Startupdelay);

	int16_t magneto[3] = {0, 0, 0};
	int16_t acceleration[3] = {0, 0, 0};
	float gyro[3] = {0, 0, 0};
	int values[3] = {0, 0, 0};

	int16_t prevMagneto[3] = {0, 0, 0};
	int16_t prevAccel[3] = {0, 0, 0};
	float prevGyro[3] = {0, 0, 0};
	int prevValues[3] = {0, 0, 0};

	while (true)
	{
		// Fetch sensor data
		err = magnetometer_get_magneto(magneto);
		if (err != 0)
			printf("Error in magnetometer_get_magneto: %d\n", err);

		err = gyroscope_get_acceleration(acceleration);
		if (err != 0)
			printf("Error in gyroscope_get_acceleration: %d\n", err);

		err = gyroscope_get_gyro(gyro);
		if (err != 0)
			printf("Error in gyroscope_get_gyro: %d\n", err);

		err = gyroscope_get_roll(&values[0]);
		if (err != 0)
			printf("Error in gyroscope_get_roll: %d\n", err);

		err = gyroscope_get_pitch(&values[1]);
		if (err != 0)
			printf("Error in gyroscope_get_pitch: %d\n", err);

		err = gyroCompass_get_heading(&values[2]);
		if (err != 0)
			printf("Error in gyroCompass_get_heading: %d\n", err);

		// Check for changes and update protected values
		bool updated = false;
		for (int i = 0; i < 3; i++)
		{
			if (magneto[i] != prevMagneto[i] || acceleration[i] != prevAccel[i] || gyro[i] != prevGyro[i] || values[i] != prevValues[i])
			{
				updated = true;
				prevMagneto[i] = magneto[i];
				prevAccel[i] = acceleration[i];
				prevGyro[i] = gyro[i];
				prevValues[i] = values[i];
			}
		}

		if (updated)
		{
			k_mutex_lock(&gyroMutex, K_FOREVER);
			memcpy(gyroMutexMagnetoValue, magneto, sizeof(magneto));
			memcpy(gyroMutexAccelValue, acceleration, sizeof(acceleration));
			memcpy(gyroMutexGyroValue, gyro, sizeof(gyro));
			gyroMutexRollValue = values[0];
			gyroMutexPitchValue = values[1];
			gyroMutexHeadingValue = values[2];
			k_mutex_unlock(&gyroMutex);
		}

		k_msleep(1000); // Adjust delay based on sensor requirements
	}
}

/**
* @brief Get the mutex value of the btnmatrix
*/
uint8_t *btnmatrix_inGetMutexValue()
{
	if (k_mutex_lock(&btnmatrix_inMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		for (uint8_t i = 0; i < 16; i++)
		{
			btnmatrix_inMutexValueRet[i] = btnmatrix_inMutexValue[i]; //access protected value
		}
		k_mutex_unlock(&btnmatrix_inMutex);
	} else
	{
		printf("Cannot lock btnmatrix_in\n");
	}
	return btnmatrix_inMutexValueRet; //Return unprotected value
}

/**
* @brief Thread to get the btnmatrix data
*/
void tbtnmatrix_in(void)
{
	k_msleep(Startupdelay); //startup sleep for main thread
	uint8_t values[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};// Value to decrease locking amount
	while (1) 
	{
		for (uint8_t i = 0; i < 16; i++)
		{
			if(values[i] != buttons4x4Get(i)) 
			{
				values[i] = buttons4x4Get(i);
				k_mutex_lock(&btnmatrix_inMutex, K_FOREVER); // wait forever until mutex is available
				btnmatrix_inMutexValue[i] = values[i];
				k_mutex_unlock(&btnmatrix_inMutex);
			}
		}
		k_msleep(10);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

uint8_t* switchesGetMutexValue()
{
	if (k_mutex_lock(&switchsMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		for (uint8_t i = 0; i < 5; i++)
		{
			switchsMutexValueRet[i] = switchsMutexValue[i]; //access protected value
		}
		k_mutex_unlock(&switchsMutex);	
	} 
	else 
	{
		printf("Cannot lock switchs\n");
	}
	return switchsMutexValueRet; //Return unprotected value
}

void tswitches(void) { 
	k_msleep(Startupdelay); //startup sleep for main thread
	uint8_t values[5] = {0,0,0,0,0};// Value to decrease locking amount
	while (1) 
	{
		for (uint8_t i = 0; i < 5; i++)
		{
			if(values[i] != switchesGet(i)) 
			{
				values[i] = switchesGet(i);
				k_mutex_lock(&switchsMutex, K_FOREVER); // wait forever until mutex is available
				switchsMutexValue[i] = values[i];
				k_mutex_unlock(&switchsMutex);
			}
		}
		k_msleep(10);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

int32_t potmeterGetMutexValue()
{
	if (k_mutex_lock(&potmeterMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		potmeterMutexValueRet = potmeterMutexValue; //access protected value
		k_mutex_unlock(&potmeterMutex);
	} 
	else 
	{
		printf("Cannot lock potmeter\n");
	}
	return potmeterMutexValueRet; //Return unprotected value
}

void tpotmeter(void) { 
	k_msleep(Startupdelay); //startup sleep for main thread
	//int32_t values = 0;// Value to decrease locking amount
	while (1) 
	{
		// if(values != potmeterGet()) 
		// {
		// 	values = potmeterGet();
		// 	k_mutex_lock(&potmeterMutex, K_FOREVER); // wait forever until mutex is available
		// 	potmeterMutexValue = values;
		// 	k_mutex_unlock(&potmeterMutex);
		// }
		k_msleep(10);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

uint8_t* abcbtnGetMutexValue()
{
	if (k_mutex_lock(&abcbtnMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			abcbtnMutexValueRet[i] = abcbtnMutexValue[i]; //access protected value
			
		}
		k_mutex_unlock(&abcbtnMutex);	
	} 
	else 
	{
		printf("Cannot lock abcbtn\n");
	}
	return abcbtnMutexValueRet; //Return unprotected value
}

void tabcbtn(void) { 
	k_msleep(Startupdelay); //startup sleep for main thread
	uint8_t values[3] = {0,0,0};// Value to decrease locking amount
	while (1) 
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			if(values[i] != abcbuttonsGet((char)97+i)) //conversion to ascii
			{
				values[i] = abcbuttonsGet((char)97+i); //conversion to ascii
				k_mutex_lock(&abcbtnMutex, K_FOREVER); // wait forever until mutex is available
				abcbtnMutexValue[i] = values[i];
				k_mutex_unlock(&abcbtnMutex);
			}
		}
		k_msleep(10);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

// Output thread and mutex functions
void btnmatrix_outSetMutexValue(uint8_t data[4])
{

	k_mutex_lock(&btnmatrix_outMutex, K_FOREVER);
	for (uint8_t i = 0; i < 4; i++)
	{
		btnmatrix_outMutexValue[i] = data[i]; //access protected value
		
	}
	k_mutex_unlock(&btnmatrix_outMutex);	

}

void tbtnmatrix_out(void) { 
	k_msleep(Startupdelay); //startup sleep for main thread
	while (1) 
	{
		if (k_mutex_lock(&btnmatrix_outMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
		{
			for (uint8_t i = 0; i < 4; i++)
			{
				btnmatrix_outMutexValueOld[i] = btnmatrix_outMutexValue[i];
			}
			k_mutex_unlock(&btnmatrix_outMutex);	
		} 
		buttonMatrixSet(btnmatrix_outMutexValueOld);
		//k_msleep(0);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

void buzzersSetMutexValue(uint8_t data[3])
{

	k_mutex_lock(&buzzersMutex, K_FOREVER);
	for (uint8_t i = 0; i < 3; i++)
	{
		buzzersMutexValue[i] = data[i]; //access protected value
		
	}
	k_mutex_unlock(&buzzersMutex);	

}

void tbuzzers(void) { 
	k_msleep(Startupdelay); //startup sleep for main thread
	while (1) 
	{
		if (k_mutex_lock(&buzzersMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
		{
			for (uint8_t i = 0; i < 3; i++)
			{
				buzzersMutexValueOld[i] = buzzersMutexValue[i];
			}
			k_mutex_unlock(&buzzersMutex);	
		} 
		//buzzersSet(btnmatrix_outMutexValueOld);
		k_msleep(10);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

void ledmatrixSetMutexValue(uint16_t data[16])
{
	k_mutex_lock(&ledmatrixMutex, K_FOREVER);
	for (uint8_t i = 0; i < 16; i++)
	{
		ledmatrixMutexValue[i] = data[i]; //access protected value
		
	}
	k_mutex_unlock(&ledmatrixMutex);	
}

void tledmatrix(void) { 
	k_msleep(Startupdelay); //startup sleep for main thread
	while (1) 
	{
		if (k_mutex_lock(&ledmatrixMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
		{
			for (uint8_t i = 0; i < 16; i++)
			{
				ledmatrixMutexValueOld[i] = ledmatrixMutexValue[i];
			}
			k_mutex_unlock(&ledmatrixMutex);	
		} 
		ledMatrixSet(ledmatrixMutexValueOld);
		// k_msleep(16);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

void ledcircleSetMutexValue(uint8_t data[8])
{
	k_mutex_lock(&ledcircleMutex, K_FOREVER);
	for (uint8_t i = 0; i < 8; i++)
	{
		ledcircleMutexValue[i] = data[i]; //access protected value
		
	}
	k_mutex_unlock(&ledcircleMutex);	
}

void tledcircle(void) { 
	k_msleep(Startupdelay); //startup sleep for main thread
	while (1) 
	{
		if (k_mutex_lock(&ledcircleMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
		{
			for (uint8_t i = 0; i < 8; i++)
			{
				ledcircleMutexValueOld[i] = ledcircleMutexValue[i];
			}
			k_mutex_unlock(&ledcircleMutex);	
		} 
		circleMatrixSet(ledcircleMutexValueOld);
		//k_msleep(16);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

void sevensegSetMutexValue(char input[4],uint8_t dpPosition)
{
	k_mutex_lock(&sevensegMutex, K_FOREVER);
	for (uint8_t i = 0; i < 4; i++)
	{
		sevensegMutexValueInput[i] = input[i]; //access protected value
	}
	sevensegMutexValuedpPosition = dpPosition ;//access protected value
	k_mutex_unlock(&sevensegMutex);	
}

void tsevenseg(void) { 
	k_msleep(Startupdelay); //startup sleep for main thread
	while (1) 
	{
		if (k_mutex_lock(&sevensegMutex, K_MSEC(100)) == 0) //Check if mutex is not locked by another thread
		{
			for (uint8_t i = 0; i < 4; i++)
			{
				sevensegMutexValueInputOld[i] = sevensegMutexValueInput[i];
			}
			sevensegMutexValuedpPositionOld = sevensegMutexValuedpPosition;
			k_mutex_unlock(&sevensegMutex);	
		} 
		sevenSegmentSet(sevensegMutexValueInputOld,sevensegMutexValuedpPositionOld);
		//k_msleep(16);	// This delay should depend on how frequently this sensor / actuator is read / written
	}
}

void enableThreads(char **names, unsigned amount) {
	for (int i = 0; i < amount; i++) {
		// Resume each desired thread
		printf("Enabling thread %s\n", names[i]);
		setThread(names[i], true);
	}
}

void disableThreads(char **names, unsigned amount) {
	for (int i = 0; i < amount; i++) {
		// Suspend each desired thread
		printf("Suspending thread %s\n", names[i]);
		setThread(names[i], false);
	}
}

void setThread(char* name, bool state) {
	if (strcmp(name, "startbtn") == 0) {
		extern const k_tid_t tstartbutton_id;
		state ? k_thread_resume(tstartbutton_id) : k_thread_suspend(tstartbutton_id);
		return;
	}
	if (strcmp(name, "btnmatrix_in") == 0) {
		extern const k_tid_t tbtnmatrix_in_id;
		state ? k_thread_resume(tbtnmatrix_in_id) : k_thread_suspend(tbtnmatrix_in_id);
		return;
	}
	if (strcmp(name, "switches") == 0) {
		extern const k_tid_t tswitches_id;
		state ? k_thread_resume(tswitches_id) : k_thread_suspend(tswitches_id);
		return;
	}
	if (strcmp(name, "potmeter") == 0) {
		extern const k_tid_t tpotmeter_id;
		state ? k_thread_resume(tpotmeter_id) : k_thread_suspend(tpotmeter_id);
		return;
	}
	if (strcmp(name, "abcbtn") == 0) {
		extern const k_tid_t tabcbtn_id;
		state ? k_thread_resume(tabcbtn_id) : k_thread_suspend(tabcbtn_id);
		return;
	}
	if (strcmp(name, "btnmatrix_out") == 0) {
		extern const k_tid_t tbtnmatrix_out_id;
		state ? k_thread_resume(tbtnmatrix_out_id) : k_thread_suspend(tbtnmatrix_out_id);
		return;
	}
	if (strcmp(name, "buzzers") == 0) {
		extern const k_tid_t tbuzzers_id;
		state ? k_thread_resume(tbuzzers_id) : k_thread_suspend(tbuzzers_id);
		return;
	}
	if (strcmp(name, "ledmatrix") == 0) {
		extern const k_tid_t tledmatrix_id;
		state ? k_thread_resume(tledmatrix_id) : k_thread_suspend(tledmatrix_id);
		return;
	}
	if (strcmp(name, "ledcircle") == 0) {
		extern const k_tid_t tledcircle_id;
		state ? k_thread_resume(tledcircle_id) : k_thread_suspend(tledcircle_id);
		return;
	}
	if (strcmp(name, "sevenseg") == 0) {
		extern const k_tid_t tsevenseg_id;
		state ? k_thread_resume(tsevenseg_id) : k_thread_suspend(tsevenseg_id);
		return;
	}
	if (strcmp(name, "gps") == 0) {
		extern const k_tid_t tgps_id;
		state ? k_thread_resume(tgps_id) : k_thread_suspend(tgps_id);
		return;
	}
	if (strcmp(name, "gyro") == 0) {
		extern const k_tid_t tgyro_id;
		state ? k_thread_resume(tgyro_id) : k_thread_suspend(tgyro_id);
		return;
	}
	printf("Unknown thread: %s\n", name);
}

void disableAllThreads() {
	k_thread_suspend(tstartbutton_id);
	k_thread_suspend(tbtnmatrix_in_id);
	k_thread_suspend(tswitches_id);
	k_thread_suspend(tpotmeter_id);
	k_thread_suspend(tabcbtn_id);
	k_thread_suspend(tbtnmatrix_out_id);
	k_thread_suspend(tbuzzers_id);
	k_thread_suspend(tledmatrix_id);
	k_thread_suspend(tledcircle_id);
	k_thread_suspend(tsevenseg_id);
}
