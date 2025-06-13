#include "minigame3.h"

K_TIMER_DEFINE(timerMg3, NULL, NULL);
LOG_MODULE_REGISTER(mg_3);

char *mg3Threads[mg3ThreadCount] = {"startbtn", "btnmatrix_in", "btnmatrix_out", "ledmatrix"};

void getMg3Threads(char ***names, unsigned *amount) {
	*names = mg3Threads;
	*amount = mg3ThreadCount;
}

#define MG3_ONELINERS 3
char oneLinersMG3[MG3_ONELINERS][32] = {
	"Kopieer de vorm! ",
	"Maak de ledmatrix vorm na",
	"op de knoppenmatrix"
};

void generate_shape(uint8_t random_shape[4]){
	for(int i = 0; i < 4; i++){
		random_shape[i] = sys_rand32_get() % 16;
	}
}

static void wait_till_game_start(){
	lcdStringWrite("Druk op start");
	startledSet(1);

	while(startbuttonGet()){
		native_loop();
	}
	startledSet(0);
}

int playMg3() {
	uint8_t btnmatrix_off[4] = {0};
	uint8_t random_shape[4] = {0};
	uint8_t player_shape[4] = {0};
	uint8_t *player_input;
	uint16_t led_matrix_shape[16] = {0};
	uint16_t led_matrix_off[16] = {0};
	uint32_t score = 0;

	for (int i = 0; i < MG3_MAX_PLAY_COUNT; i++)
	{
		uint32_t remaining_time = 0;
		bool shapes_match = 0;
		show_oneliners(oneLinersMG3, MG3_ONELINERS);
		lcdEnable();
		wait_till_game_start();

		generate_shape(random_shape);
		btnmatrix_to_ledmatrix(random_shape, led_matrix_shape);
		ledmatrixSetMutexValue(led_matrix_shape);

		k_timer_start(&timerMg3, K_MSEC(10000), K_NO_WAIT);

		while (!shapes_match) {
			native_loop();
			memset(player_shape, 0, sizeof(player_shape));
			player_input = btnmatrix_inGetMutexValue();

			btnmatrix_in_to_out(player_input, player_shape);

			btnmatrix_outSetMutexValue(player_shape);
			if(memcmp(player_shape, random_shape, sizeof(random_shape)) == 0){
				LOG_INF("Shapes match\n");
				remaining_time = k_timer_remaining_get(&timerMg3);
				shapes_match = 1;
			}
		}

		btnmatrix_outSetMutexValue(btnmatrix_off);
		ledmatrixSetMutexValue(led_matrix_off);

		if(remaining_time > 0){
			score += (remaining_time) / MG3_MAX_PLAY_COUNT;
		}

		if(score >= 1000){
			score = 1000;
		}
	}

	LOG_INF("Score: %d\n", score);
	lcdDisable();
	k_msleep(20);

	return (int)score;
}