#include "minigame2.h"

K_TIMER_DEFINE(secTimerMg2, NULL, NULL);

char *mg2Threads[mg2ThreadCount] = {"startbtn", "btnmatrix_in", "btnmatrix_out", "buzzers"};

void getMg2Threads(char ***names, unsigned *amount) {
	*names = mg2Threads;
	*amount = mg2ThreadCount;
}

#define MG2_ONELINERS 4
char oneLinersMG2[MG2_ONELINERS][32] = {
	"Simon Says: Drukop de        ",
	"lichtgevende    knoppen      ",
	"in de juiste    volgorde     ",
	"Druk op de      startknop!   "
};


void generateSequence(uint8_t *sequence,uint8_t size,uint8_t bits) {
	for (uint8_t i = 0; i < size; i++)	{
			uint8_t randomValue = 0;
			sys_rand_get(&randomValue, sizeof(randomValue));
			randomValue = randomValue & (bits);
			sequence[i] = randomValue;
			printk("random = sequence[%d]: %d\n",i,sequence[i]);
		}
}

void showButton(uint8_t btn)
{
	uint8_t data[4] = {0b00000000,0b00000000,0b00000000,0b00000000};
	switch (btn)
	{
	case 3:
	data[0] = 0b00001000;
		break;
	case 2:
	data[0] = 0b00000001;
		break;
	case 1:
	data[3] = 0b00001000;
		break;
	case 0:
	data[3] = 0b00000001;
		break;
	case 6:
	data[0] = 0b00001001;
	data[3] = 0b00001001;
		break;
	default:
		//should not reach
		break;
	}	
	btnmatrix_outSetMutexValue(data);
}

void showLevel(uint8_t level,uint8_t sequence[8]){
	for (uint8_t i = 0; i < level+1; i++)
	{
		
		showButton(sequence[i]);
		printk("sequence[%d]: %d\n",i,sequence[i]);
		k_timer_start(&secTimerMg2, K_MSEC(1000), K_NO_WAIT);
		while (!(k_timer_status_get(&secTimerMg2) > 0)){k_sleep(K_MSEC(1));}	
		showButton(5);
		k_timer_start(&secTimerMg2, K_MSEC(1000), K_NO_WAIT);
		while (!(k_timer_status_get(&secTimerMg2) > 0)){k_sleep(K_MSEC(1));}	
		
	}
	
	showButton(6);
	k_timer_start(&secTimerMg2, K_MSEC(1000), K_NO_WAIT);
	while (!(k_timer_status_get(&secTimerMg2) > 0)){k_sleep(K_MSEC(1));}	
	showButton(5);
}

uint8_t checkinput(bool* genValue,uint32_t* score, uint8_t level,uint8_t sequence[8])
{
	uint8_t *btnValues;
	uint8_t btnLevel = 0;
	bool buttonDetected = false;

	while(*genValue == true)
	{
		k_cpu_idle();
		
		btnValues = btnmatrix_inGetMutexValue();
		if(btnValues[15] && btnValues[12] && btnValues[3] && btnValues[0])
		{
			buttonDetected = false;
			showButton(5);
			if(btnLevel == level+1)
			{
				return 1;
				break;
			}
		}
		if((!btnValues[15] || !btnValues[12] || !btnValues[3] || !btnValues[0]) && buttonDetected == false)
		{
			buttonDetected = true;
			printk("sequence before %d \n",sequence[btnLevel]);
			switch (sequence[btnLevel])
			{
			case 3:
				if(btnValues[15] && btnValues[12] && btnValues[3] && !btnValues[0])
				{
					btnLevel++;
					printk("3 correct \n");
					showButton(3);
				}
				else
				{
					*genValue = false;
					*score -= 100;
					printk("3 incorrect \n");
					for (int i = 0; i < 16; i++)
					{
						printk("button once %d: %d\n",i,btnValues[i]);
					}
				}
				break;
			case 2:
				if(btnValues[15] && btnValues[12] && !btnValues[3] && btnValues[0])
				{
					btnLevel++;
					printk("2 correct \n");
					showButton(2);
				}
				else
				{
					*genValue = false;
					*score -= 100;
					printk("2 incorrect \n");
					for (int i = 0; i < 16; i++)
					{
						printk("button once %d: %d\n",i,btnValues[i]);
					}
				}
				break;
			case 1:
				if(btnValues[15] && !btnValues[12] && btnValues[3] && btnValues[0])
				{
					btnLevel++;
					printk("1 correct \n");
					showButton(1);
				}
				else
				{
					*genValue = false;
					*score -= 100;
					printk("1 incorrect \n");
					for (int i = 0; i < 16; i++)
					{
						printk("button once %d: %d\n",i,btnValues[i]);
					}
				}
				break;
			case 0:
				if(!btnValues[15] && btnValues[12] && btnValues[3] && btnValues[0])
				{
					btnLevel++;
					printk("0 correct \n");
					showButton(0);
				}
				else
				{
					*genValue = false;
					*score -= 100;
					printk("0 incorrect \n");
					for (int i = 0; i < 16; i++)
					{
						printk("button once %d: %d\n",i,btnValues[i]);
					}
				}
				break;
			}	
		}
	}
	return 0;
}

void showOnelinersMG2()
{
	bool done = false;
	//lcdEnable();
	lcdStringWrite("Druk op start");
	while (!done)
	{
		k_cpu_idle();
		
		if(startbuttonGet())
		{	
			startledSet(1);
		}
		else
		{
			startledSet(0);
			for (uint8_t i = 0; i < MG2_ONELINERS; i++)
			{
			lcdStringWrite(oneLinersMG2[i]);
			k_timer_start(&secTimerMg2, K_MSEC(3000), K_NO_WAIT);
			while (!(k_timer_status_get(&secTimerMg2) > 0)){k_sleep(K_MSEC(1));}	
			}
			startledSet(1);
			while (true)
			{
				k_cpu_idle();
				
				if(!startbuttonGet())
				{	
				done = true;
				break;
				}
			}
			
		}
	}
	startledSet(0);
	//lcdClear();
	//lcdDisable();
}

void circleTest()
{
	printk("Testing LED Circle");
	int8_t led_circle_data[8] = 	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 
		0b00000000, 0b00000000, 0b00000000, 0b00000000,};

	for(int j = 0; j < 8; j++)
	{
		for(int i = 0; i < 8; i++)
		{
			led_circle_data[i%8] = led_circle_data[i%8] << 1 | 1;
		}

		circleMatrixSet(led_circle_data);
		k_msleep(1000);
	}
	printk("End testing LED Circle");
}

// possible issue identified: without mutex it quickly turns on/off in sim
int buttonMatrixLEDTest()
{
	printk("Start button LED Test");
	lcdStringWrite("Button LED Matrix Test");
	uint8_t data[4] = {0b00000000,0b00000000,0b00000000,0b00000000};

	for(int i = 0; i < 16; i++)
	{
		data[i%4] = data[i%4] << 1 | 1;
		buttonMatrixSet(data);
		k_msleep(1000);
	}

	return 0;
}

int ledMatrixTest()
{
	printk("Start LED Matrix test");
	lcdStringWrite("Start LED Matrix test");
	int16_t data[16] = {0xFFFF};

	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			data[i] = data[i] << 1 | 1;
			ledMatrixSet(data);
			k_msleep(50);
		}
	}

	return 0;
}

int buttonMatrixPressTest()
{
	// TODO: fix this
	printk("Button Matrix test");
	lcdStringWrite("Button Matrix Test");
	int8_t buttonPressedCount = 0;
	uint8_t *btnValues;
	uint8_t data[4] = {0b00000000,0b00000000,0b00000000,0b00000000};

	while(buttonPressedCount < 16)
	{
		// k_cpu_idle(); // is this necessary?
		k_msleep(1000);
		btnValues = btnmatrix_inGetMutexValue();
		// lcdStringWrite(btnValues[0]);
		// data[0] |= btnValues[1];
		// btnmatrix_outSetMutexValue(data);
	}
	return 0;
}

// void circleTestMutex()
// {
// 	printk("Testing LED Circle");
// 	int8_t led_circle_data[8] = 	{0b00000000, 0b00000000, 0b00000000, 0b00000000, 
// 		0b00000000, 0b00000000, 0b00000000, 0b00000000,};

// 	for(int j = 0; j < 8; j++)
// 	{
// 		for(int i = 0; i < 8; i++)
// 		{
// 			led_circle_data[i%8] = led_circle_data[i%8] << 1 | 1;
// 		}

// 		circleMatrixSet(led_circle_data);
// 		k_msleep(1000);
// 	}
// 	printk("End testing LED Circle");
// }

// int buttonMatrixLEDTestMutex()
// {
// 	printk("Start button LED Test");
// 	lcdStringWrite("Button LED Matrix Test");
// 	uint8_t data[4] = {0b00000000,0b00000000,0b00000000,0b00000000};

// 	for(int i = 0; i < 16; i++ )
// 	{
// 		data[i%4] = data[i%4] << 1 | 1;
// 		btnmatrix_outSetMutexValue(data);
// 		k_msleep(1000);
// 	}

// 	return 0;
// }

int testAllInterface() {
	printk("Start testing all interfaces");
	
	// lcdTest();
	circleTest();
	buttonMatrixLEDTest();
	// abcStartLEDTest();
	ledMatrixTest();


	/// input required tests:
	// buttonMatrixPressTest();

// 	uint8_t startbuttonGetMutexValue();
// uint8_t* btnmatrix_inGetMutexValue();
// uint8_t* switchesGetMutexValue();
// int32_t potmeterGetMutexValue();
// uint8_t* abcbtnGetMutexValue();
// void buzzersSetMutexValue(uint8_t data[3]);
// void ledmatrixSetMutexValue(uint16_t data[16]);
// void ledcircleSetMutexValue(uint8_t data[8]);
// void sevensegSetMutexValue(char input[4],uint8_t dpPosition);

	return 0;
}

int playMg2() {
	uint32_t score = 1000;
	uint8_t sequence[8] = {0,0,0,0,0,0,0,0};
	uint8_t level = 0;
	bool genValue = false;

	k_cpu_idle(); // don't know if this helps but maybe

	printk("playMg2 entered");

	if(testAllInterface() != 0)
	{
		lcdStringWrite("Error!");
	}
	
	showOnelinersMG2();
	while (true)
	{
		k_cpu_idle();
		if(genValue == false)
		{
			level = 0;
			generateSequence(sequence,8,0b11);
			genValue = true;
		}
		
		k_timer_start(&secTimerMg2, K_MSEC(1000), K_NO_WAIT);
		while (!(k_timer_status_get(&secTimerMg2) > 0)){k_sleep(K_MSEC(1));}
		
		showLevel(level,sequence);
		level += checkinput(&genValue, &score, level, sequence);
		if(level == 8 || score == 0)
		{
			break;
		}
	}
	
	return (int)score;
}
