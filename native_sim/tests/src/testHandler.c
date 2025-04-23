#include "testHandler.h"

uint8_t lcdTest()
{
	uint8_t err = 0;
	printk("Enable LCD backlight");
	err |= lcdEnable();
	k_msleep(1000);
	printk("Test LCD Write");
	err |= lcdStringWrite("Test LCD Write");
	k_msleep(1000);
	printk("Clear LCD");
	err |= lcdClear();

    if(err != 0)
    {
        printk("LCD ERROR!!!!\n")
    }

	return err;
}

uint8_t circleTest()
{
    uint8_t err = 0;
	printk("Testing LED Circle");
	int8_t led_circle_data[8] = 	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 
		0b00000000, 0b00000000, 0b00000000, 0b00000000,};

	for(int j = 0; j < 8; j++)
	{
		for(int i = 0; i < 8; i++)
		{
			led_circle_data[i%8] = led_circle_data[i%8] << 1 | 1;
		}

		err |= circleMatrixSet(led_circle_data);
		k_msleep(1000);
	}
	
    if(err != 0)
    {
        printk("LED Circle error!!\n");
        lcdStringWrite("LED Circle ERROR!");
    }

    printk("End testing LED Circle\n");


    return err;
}

uint8_t buttonMatrixLEDTest()
{
    uint8_t err = 0;
	printk("Start button LED Matrix Test\n");
	lcdStringWrite("Button LED Matrix Test");
	uint8_t data[4] = {0b00000000,0b00000000,0b00000000,0b00000000};

	for(int i = 0; i < 16; i++)
	{
		data[i%4] = data[i%4] << 1 | 1;
		err |= buttonMatrixSet(data);
		k_msleep(500);
	}

    for(int i = 0; i < 16; i++)
	{
		data[i%4] = data[i%4] << 1;
		err |= buttonMatrixSet(data);
		k_msleep(500);
	}

    printk("End button LED Matrix Test\n");

    if(err != 0)
    {
        printk("Button LED error!!\n");
        lcdStringWrite("BUTTON LED ERROR!");
    }

	return err;
}

uint8_t abcStartLEDTest()
{
	printk("ABC & Start button LED test\n");
	lcdStringWrite("ABC & Start button LED test");
	uint8_t err = 0;
	
	err |= abcledsSet('a', HIGH);
	k_msleep(1000);
	err |= abcledsSet('b', HIGH);
	k_msleep(1000);
	err |= abcledsSet('c', HIGH);
	k_msleep(1000);
	err |= abcledsSet('a', LOW);
	k_msleep(1000);
	err |= abcledsSet('b', LOW);
	k_msleep(1000);
	err |= abcledsSet('c', LOW);
	k_msleep(1000);

	err |= startledSet(HIGH);
	k_msleep(1000);
	err |= startledSet(LOW);
	k_msleep(1000);

	return 0;
}

uint8_t ledMatrixTest()
{
	printk("Start LED Matrix test\n");
	lcdStringWrite("Start LED Matrix test");
	int16_t data[16] = {0x0000};

	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			data[i] = data[i] << 1 | 1;
			ledMatrixSet(data);
			k_msleep(25);
		}
	}
    for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			data[i] = data[i] << 1;
			ledMatrixSet(data);
			k_msleep(25);
		}
	}

	return 0;
}

uint8_t sevenSegmentTest()
{
    printk("Start Seven Segment Display Test\n");
    uint8_t err = 0;

    char data[4] = "5223";
    err |= sevenSegmentSet(data, 0); // Since the second number doesn't seem to be used in the sim, is it just displaying the decimal point?
    k_msleep(1000);

    return err;
}

#ifndef CONFIG_BOARD_NATIVE_SIM
uint8_t buzzerTest()
{
    printk("Buzzer test\n");
    lcdStringWrite("Buzzer test");
    uint8_t err = 0;

    int freqArray[3][3] = { // should play the 'A minor' chord
        {440,440,440},
        {0,523,523},
        {0,0,659}
    }; 

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            err |= buzzerSetPwm(j, freqArray[j][i]);
        }
        k_msleep(1000); // make a frequency last approximately 1s
    }
    return err;
}

uint8_t gpsTest()
{
    int64_t latitude = 0;
    int64_t longitude = 0;
    long double distance = 0;
    long double angle = 0;
    printk("gpsTest\n");
    lcdStringWrite("GPS Test");
    
    // get all data
    // getGnssData(); // possibly necessary for time determining but currently not relevant since same data gets used by all the other tested functions

    latitude = getLatitude();
    longitude = getLongitude();
    distance = getDistanceMeters(LAT_LOC_A, LON_LOC_A, LAT_LOC_B, LON_LOC_B);
    angle = getAngle(LAT_LOC_A, LON_LOC_A, LAT_LOC_B, LON_LOC_B);

    // long double nanoDegToLdDeg(int64_t);

    printk("Lat:%lld\n", latitude);
    printk("Long:%lld\n", longitude);
    printk("Distance %Lf", distance);
    printk("Angle:%Lf", angle);

    return 0;
}

// TODO: Fixx the unholy amount of data parsing, casting and safety issues
uint8_t gyroCompassTest()
{
    uint8_t err[2] = {0};
    uint16_t magnetoData[3] = {0};
    uint16_t acceleration[3] = {0};
    float gyro[3] = {0};
    int roll = 0;
    int pitch = 0;
    int heading = 0;

    char tempText[32];

    // magnometer
    printk("Testing Magneto\n");
    lcdStringWrite("Testing Magneto");
    err[0] |= magnetometer_init();
    k_msleep(1000); // wait 1s to be safe
    err[0] |= magnetometer_get_magneto(magnetoData);

    for (int i = 0; i < 3; i++)
    {
        sprintf(tempText, "Magneto %i Data: %i", i, magnetoData[i]);
        printk(tempText);
        lcdStringWrite(tempText);
        k_msleep(1000);
    }
    
    // gyro
    printk("Testing Gyro\n");
    lcdStringWrite("Testing Gyro");
    
    err[1] |= gyroscope_init();

    err[1] |= gyroscope_get_acceleration(acceleration);
    err[1] |= gyroscope_get_gyro(gyro);
    err[1] |= gyroscope_get_roll(&roll);
    err[1] |= gyroscope_get_pitch(&pitch);
    err[1] |= gyroCompass_get_heading(&heading);

    err[0] |= magnetometer_exit();
    err[1] |= gyroscope_exit();

    for(int i = 0; i < 3; i++)
    {
        sprintf(tempText, "Acceleration %i: %i",i, acceleration[i]);
        printk(tempText);
        lcdStringWrite(tempText);
    }

    for(int i = 0; i < 3; i++)
    {
        sprintf(tempText, "Gyro %i: %f",i, gyro[i]);
        printk(tempText);
        lcdStringWrite(tempText);
    }

    sprintf(tempText, "Roll: %i", roll);
    printk(tempText);
    lcdStringWrite(tempText);

    sprintf(tempText, "Pitch: %i", pitch);
    printk(tempText);
    lcdStringWrite(tempText);

    sprintf(tempText, "Heading: %i", heading);
    printk(tempText);
    lcdStringWrite(tempText);

    if(err[0] != 0)
    {
        sprintf(tempText, "Magneto Error: %i", err[0]);
        printk(tempText);
        lcdStringWrite(tempText);        
    }

    if(err[1] != 0)
    {
        sprintf(tempText, "Gyro Error: %i", err[1]);
        printk(tempText);
        lcdStringWrite(tempText);        
    }
    
    return err[0] || err[1];
}

#endif

// TODO: Fix that this doesn't generate an unholy amount of warnings
uint8_t buttonMatrixPressTest()
{
	printk("Button Matrix test\n");
	lcdStringWrite("Button Matrix Test");
	uint8_t buttonPressedCount = 0;
    uint8_t buttonVal = 0;
    uint8_t i = 0;
    bool prevButtonVal[16] = {0};
    uint8_t data[4] = {0b00000000,0b00000000,0b00000000,0b00000000};

	while(buttonPressedCount < 16)
	{
		buttonVal = buttons4x4Get(i);
        if(buttonVal == 2) // trying to access non existent button
            return 1; 

        else if((buttonVal == 1)) // if button is pressed
        {
            if(!prevButtonVal[i]) // ignore if was previously already pressed
            {
                buttonPressedCount++;
                prevButtonVal[i] = 1;
                lcdStringWrite("Button Pressed");
                printk("Button %i Pressed\n", i);
                printk("buttonVal: %i\n", prevButtonVal[i]);                
                // the next part assumes that the matrix LEDs succeded in their test.
                if(i < 4)
                    data[0] = data[0] |= 1 << i%4;
                else if(i < 8)
                    data[1] = data[1] |= 1 << i%4;
                else if(i < 12)
                    data[2] = data[2] |= 1 << i%4;
                else
                    data[3] = data[3] |= 1 << i%4;
                buttonMatrixSet(data);

                k_msleep(1000);
                lcdClear();

            }
        }
        else // button not pressed
        {
            prevButtonVal[i] = 0;
            if(i < 4)
                data[0] = data[0] &= !(1 << i%4);
            else if(i < 8)
                data[1] = data[1] &= !(1 << i%4);
            else if(i < 12)
                data[2] = data[2] &= !(1 << i%4);
            else
                data[3] = data[3] &= !(1 << i%4);
            buttonMatrixSet(data);
        }

        i++;
        i %= 16;
        k_msleep(1); // sleep to allow pressing in sim
	}
	return 0;
}

uint8_t switchTest()
{
    uint8_t switchesFlipped = 0;
    uint8_t switchVal[5] = {0};
    uint8_t prevSwitchVal[5] = {0};
    uint8_t i = 0;

    while(switchesFlipped < 5)
    {
        i++;
        i %= 5;
        switchVal[i] = switchesGet(i);
        if(switchVal[i] == 1)
        {
            if(!prevSwitchVal[i])
            {
                switchesFlipped++;
                printk("Switch %i Flipped\n", i);
                lcdStringWrite("Switch flipped");
                k_msleep(1000);
                prevSwitchVal[i] = 1;
                lcdClear();
            }
        }
        else if(switchVal[i] == 2) // happens when the switch is in the middle state which does not exist and thus is invalid
        {   
            printk("INVALID SWITCH VALUE\n");
            lcdStringWrite("INVALID SWITCH VAL");
            return 1;
        }
        else
            prevSwitchVal[i] = 0;
        k_msleep(1); // sleep to allow flipping in sim
        
    }
    return 0;
}

uint8_t abcStartButtonTest()
{
    printk("ABC And Start button test\n");
    lcdStringWrite("ABC Start Button Test");
    uint8_t buttonsPressed = 0;
    uint8_t buttonVal[4] = {0};
    uint8_t prevButtonVal[4] = {0};
    

    while(buttonsPressed < 4)
    {
        buttonVal[0] = abcbuttonsGet('a');
        buttonVal[1] = abcbuttonsGet('b');
        buttonVal[2] = abcbuttonsGet('c');
        buttonVal[3] = startbuttonGet();

        for(int i = 0; i < 4; i++)
        {
            if(buttonVal[i] == 2) // does not recognise button
            {
                printk("ABC or Start Button (%i) Not recognised\n", i);
                lcdStringWrite("Button not recognised");
                return 2;
            }
            else if(buttonVal[i] == 1)
            {
                if(!prevButtonVal[i])
                {
                    buttonsPressed++;
                    prevButtonVal[i] = 1;
                    printk("Button %i pressed\n", i);
                    lcdStringWrite("Button pressed");
                    k_msleep(1000);
                    lcdClear();
                }
            }
            else
            {
                prevButtonVal[i] = 0;
            }
        }
        k_msleep(1); // sleep to allow flipping in sim
    }
    return 0;
}

/**
 * @brief handles all tests
 * @return returns 0 if no errors otherwise there was an error
 */
uint8_t handleTests()
{
    printk("Start testing all interfaces\n");
    k_msleep(1000);
    uint8_t err = 0;

    disableAllThreads(); // make sure that threads are disabled
    
    err |= lcdTest();
    err |= circleTest();
    err |= buttonMatrixLEDTest();
    err |= abcStartLEDTest();
    err |= ledMatrixTest();
    err |= sevenSegmentTest();

    // Hardware specific tests that won't build if called on sim (TODO: FIX ME!)
#ifndef CONFIG_BOARD_NATIVE_SIM
    err |= buzzerTest();
    err |= gpsTest();
    err |= gyroCompassTest();
#endif    

    /// input required tests:
    err |= buttonMatrixPressTest();
    err |= switchTest();
    err |= abcStartButtonTest();
    // err |= potMeterTest(); // NO DRIVER FOUND

    return err;
}