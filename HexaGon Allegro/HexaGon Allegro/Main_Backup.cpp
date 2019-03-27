/*#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct ele_pos {
	int x, y;
	bool c1, c2, c3, cell, check, wow, drawn;
};
struct cases
{
	int k1, k2, k3;
	int counter, level;
	bool d1, d2, d3, endcase;
};

bool done, move1, move2, move3, d1, d2, d3, doit, done_men, draww;
bool endcase = true;
ALLEGRO_EVENT_QUEUE* event_queue_menu;
ALLEGRO_TIMER* timer_menu;
ALLEGRO_DISPLAY* display_menu;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_BITMAP* image_menu;
ALLEGRO_BITMAP* play;
ALLEGRO_BITMAP* resum;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;
ALLEGRO_FONT *font;
ALLEGRO_BITMAP* image;
ALLEGRO_BITMAP* q1;
ALLEGRO_BITMAP* q2;
ALLEGRO_BITMAP* q3;
ALLEGRO_BITMAP* q4;
ALLEGRO_BITMAP* q5;
ALLEGRO_BITMAP* q6;
ALLEGRO_BITMAP* q9;
ALLEGRO_BITMAP* q10;
ALLEGRO_BITMAP* newgame;
ALLEGRO_SAMPLE* sound;
ALLEGRO_SAMPLE_ID soundid;
ALLEGRO_SAMPLE* win;
ALLEGRO_SAMPLE* level1;
ALLEGRO_SAMPLE* click;
ALLEGRO_SAMPLE* click_menu;
ALLEGRO_SAMPLE* end;
ALLEGRO_SAMPLE* pop;
ALLEGRO_SAMPLE* shoot;
static ALLEGRO_BITMAP* q[37];
static char score[10];
static int counter = 0;
int k1, k2, k3, level = 1, levsound = 1;
FILE *file;
FILE *score_file;
FILE *board_file;
static ele_pos  e1, e2, e3, er, board[37], borad_ver[37], board_ver_inv[37];
void save();
void init_resum();
void init();
void game_loop();
const ele_pos three_el[6][3] = { { { 560,350 },{ 855,350 },{ 1145,350 } },
{ { 560,350 },{ 855,350 },{ 1145,350 } },
{ { 560,425 },{ 855,425 },{ 1150,425 } } ,
{ { 560,355 },{ 855,355 },{ 1150,355 } } ,
{ { 560,405 },{ 855,405 },{ 1150,405 } } ,
{ { 560,370 },{ 855,370 },{ 1150,370 } } };
void draw();
void update_logic(ALLEGRO_EVENT event);
void user_input(ALLEGRO_EVENT event);
void check_good();
void is_good();
void is_good_ver();
void is_good_ver_inv();
void is_good_tr();
void init_ver();
void init_board();
void check_level();
void check_end();
bool check_end_case(int k);
bool check_endk1();
bool check_endk2();
bool check_endk3();
void shutdown();
void shutdown_menu();
void high_score();

void abort_game(const char* message)
{
	printf("%s \n", message);
	fclose(file);
	exit(1);
}
void init_menu(void)
{
	if (!al_init())
		abort_game("Failed to initialize allegro");

	if (!al_install_keyboard())
		abort_game("Failed to install keyboard");

	if (!al_install_mouse())
		abort_game("Failed to install keyboard");

	timer_menu = al_create_timer(1.0 / 60);
	if (!timer_menu)
		abort_game("Failed to create timer");

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display_menu = al_create_display(800, 566);
	al_set_window_title(display_menu, "HEXAGON MAIN");
	if (!display_menu)
		abort_game("Failed to create display");

	event_queue_menu = al_create_event_queue();
	if (!event_queue_menu)
		abort_game("Failed to create event queue");
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	font = al_load_ttf_font("pirulen rg.ttf", 35, 0);
	al_reserve_samples(1);
	click_menu = al_load_sample("click_menu.wav");
	image_menu = al_load_bitmap("NEW.png");
	play = al_load_bitmap("play.png");
	resum = al_load_bitmap("resum.png");
	al_register_event_source(event_queue_menu, al_get_keyboard_event_source());
	al_register_event_source(event_queue_menu, al_get_timer_event_source(timer_menu));
	al_register_event_source(event_queue_menu, al_get_display_event_source(display_menu));
	al_register_event_source(event_queue_menu, al_get_mouse_event_source());
	cases c;
	score_file = fopen("score.dat", "r");
	if (score_file) {
		fread(&c, sizeof(cases), 1, score_file);
		fclose(score_file);
		endcase = c.endcase;
	}
	else
		endcase = true;
	done = true;

}
void game_menu(void)
{
	bool redraw = true, p = false, p1 = false;
	al_start_timer(timer_menu);

	while (!done_men) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue_menu, &event);
		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
			//	update_logic(event);
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done_men = true;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done_men = true;
			}

			//get_user_input();		

		}
		if (event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY || event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			if ((event.mouse.x >= 320) && (event.mouse.x <= 470) && (event.mouse.y >= 360) && (event.mouse.y <= 405))
			{
				p = true;
			}
			else if (done && !endcase && (event.mouse.x >= 320) && (event.mouse.x <= 470) && (event.mouse.y >= 460) && (event.mouse.y <= 505))
			{
				p1 = true;
			}
			else
			{
				p = false;
				p1 = false;
			}
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if ((event.mouse.x >= 320) && (event.mouse.x <= 470) && (event.mouse.y >= 360) && (event.mouse.y <= 405))
			{
				p = true;
				if (event.mouse.button & 1)
				{
					al_play_sample(click_menu, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					done_men = true;
					shutdown_menu();
					init();
					al_play_sample(sound, 0.4, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
					game_loop();
				}
			}
			else if (done && !endcase && (event.mouse.x >= 320) && (event.mouse.x <= 470) && (event.mouse.y >= 460) && (event.mouse.y <= 505))
			{
				p1 = true;
				if (event.mouse.button & 1)
				{
					al_play_sample(click_menu, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					done_men = true;
					shutdown_menu();
					init();
					init_resum();
					al_play_sample(sound, 0.4, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
					game_loop();
				}
			}
			else
			{
				p = false;
				p1 = false;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue_menu)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(image_menu, 0, 0, 0);
			if (p)
				al_draw_tinted_bitmap(play, al_map_rgb(0, 255, 0), 320, 350, 0);
			else
				al_draw_bitmap(play, 320, 350, 0);
			if (p1 && !endcase)
				al_draw_tinted_bitmap(resum, al_map_rgb(0, 255, 0), 320, 450, 0);
			else if (!endcase)
				al_draw_bitmap(resum, 320, 450, 0);
			al_flip_display();
		}
	}
}


void init(void)
{
	if (!al_init())
		abort_game("Failed to initialize allegro");

	if (!al_install_keyboard())
		abort_game("Failed to install keyboard");

	if (!al_install_mouse())
		abort_game("Failed to install keyboard");

	timer = al_create_timer(1.0 / 60);
	if (!timer)
		abort_game("Failed to create timer");

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(1400, 600);
	al_set_window_title(display, "HEXAGON");
	if (!display)
		abort_game("Failed to create display");

	event_queue = al_create_event_queue();
	if (!event_queue)
		abort_game("Failed to create event queue");
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	font = al_load_ttf_font("pirulen rg.ttf", 22, 0);
	image = al_load_bitmap("h.bmp");
	q1 = al_load_bitmap("1.png");
	q2 = al_load_bitmap("2.png");
	q3 = al_load_bitmap("3.png");
	q4 = al_load_bitmap("4.png");
	q5 = al_load_bitmap("5.png");
	q6 = al_load_bitmap("6.png");
	q9 = al_load_bitmap("9.png");
	q10 = al_load_bitmap("10.png");
	newgame = al_load_bitmap("New.png");
	al_reserve_samples(8);
	sound = al_load_sample("sound.wav");
	win = al_load_sample("win.wav");
	level1 = al_load_sample("level.wav");
	click = al_load_sample("click.wav");
	end = al_load_sample("end.wav");
	pop = al_load_sample("pop.wav");
	shoot = al_load_sample("shoot.wav");
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	done = false;
	move1 = false;
	move2 = false;
	move3 = false;
	draww = false;
	init_board();
	init_ver();
	doit = true;
	d1 = true; d2 = true; d3 = true;
	srand(time(NULL));
	k1 = rand() % 4;
	k2 = rand() % 4;
	k3 = rand() % 4;
	e1 = three_el[k1][0];
	e2 = three_el[k2][1];
	e3 = three_el[k2][2];
	counter = 0;
}
void init_board() {
	for (int i = 0; i < 37; i++) {
		if (i < 4) {
			board[i].x = 100;
		}
		else if (i>3 && i < 9) {
			board[i].x = 160;
		}
		else if (i > 8 && i < 15) {
			board[i].x = 220;
		}
		else if (i > 14 && i < 22) {
			board[i].x = 280;
		}
		else if (i > 21 && i < 28) {
			board[i].x = 340;
		}
		else if (i > 27 && i < 33) {
			board[i].x = 400;
		}
		else if (i > 32 && i < 37) {
			board[i].x = 460;
		}
	}
	for (int i = 0; i < 37; i++) {
		if (i < 4) {
			if (i == 0) {
				board[0].y = 160;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i>3 && i < 9) {
			if (i == 4) {
				board[4].y = 125;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 8 && i < 15) {
			if (i == 9) {
				board[9].y = 90;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 14 && i < 22) {
			if (i == 15) {
				board[15].y = 55;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 21 && i < 28) {
			if (i == 22) {
				board[22].y = 90;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 27 && i < 33) {
			if (i == 28) {
				board[28].y = 125;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 32 && i < 37) {
			if (i == 33) {
				board[33].y = 160;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
	}
	printf("----------------------------------\n");
	for (int i = 0; i < 37; i++) {
		board[i].c1 = false;
		board[i].c2 = false;
		board[i].c3 = false;
		board[i].cell = false;
		board[i].check = false;
		board[i].wow = false;
		board[i].drawn = false;
		printf("( %d , %d )", board[i].x, board[i].y);
		if (i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32)
			printf("\n");
	}

}
void init_ver() {

	// Inverse Ver
	for (int i = 0; i < 37; i++) {
		if (i < 4) {
			if (i == 0) {
				board_ver_inv[0].x = 280;
				board_ver_inv[0].y = 55;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i>3 && i < 9) {
			if (i == 4) {
				board_ver_inv[4].x = 220;
				board_ver_inv[4].y = 90;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 8 && i < 15) {
			if (i == 9) {
				board_ver_inv[9].x = 160;
				board_ver_inv[9].y = 125;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 14 && i < 22) {
			if (i == 15) {
				board_ver_inv[15].x = 100;
				board_ver_inv[15].y = 160;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 21 && i < 28) {
			if (i == 22) {
				board_ver_inv[22].x = 100;
				board_ver_inv[22].y = 230;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 27 && i < 33) {
			if (i == 28) {
				board_ver_inv[28].x = 100;
				board_ver_inv[28].y = 300;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 32 && i < 37) {
			if (i == 33) {
				board_ver_inv[33].x = 100;
				board_ver_inv[33].y = 370;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
	}
	// Board Ver
	for (int i = 0; i < 37; i++) {
		if (i < 4) {
			if (i == 0) {
				borad_ver[0].x = 100;
				borad_ver[0].y = 160;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i>3 && i < 9) {
			if (i == 4) {
				borad_ver[4].x = 100;
				borad_ver[4].y = 230;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 8 && i < 15) {
			if (i == 9) {
				borad_ver[9].x = 100;
				borad_ver[9].y = 300;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 14 && i < 22) {
			if (i == 15) {
				borad_ver[15].x = 100;
				borad_ver[15].y = 370;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 21 && i < 28) {
			if (i == 22) {
				borad_ver[22].x = 160;
				borad_ver[22].y = 405;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 27 && i < 33) {
			if (i == 28) {
				borad_ver[28].x = 220;
				borad_ver[28].y = 440;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 32 && i < 37) {
			if (i == 33) {
				borad_ver[33].x = 280;
				borad_ver[33].y = 475;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
	}
	printf("\n----------------------------------\n");
	for (int i = 0; i < 37; i++) {
		borad_ver[i].c1 = false;
		borad_ver[i].c2 = false;
		borad_ver[i].c3 = false;
		borad_ver[i].cell = false;
		printf("( %d , %d )", borad_ver[i].x, borad_ver[i].y);
		if (i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32)
			printf("\n");
	}
	printf("\n----------------------------------\n");
	for (int i = 0; i < 37; i++) {
		board_ver_inv[i].c1 = false;
		board_ver_inv[i].c2 = false;
		board_ver_inv[i].c3 = false;
		board_ver_inv[i].cell = false;
		printf("( %d , %d )", board_ver_inv[i].x, board_ver_inv[i].y);
		if (i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32)
			printf("\n");
	}
}
void update_logic(ALLEGRO_EVENT event) {
	if (move1) {
		for (int i = 0; i < 37; i++)
		{
			if (k1 == 0)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 2].c1 = true;		board[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 2].x == borad_ver[j].x) && (board[i + 2].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 2].x == board_ver_inv[j].x) && (board[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k1 == 1)
			{
				if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 2;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k1 == 2)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e1.x >= borad_ver[i].x) && (e1.x <= borad_ver[i].x + 40) && (e1.y >= borad_ver[i].y) && (e1.y <= borad_ver[i].y + 40)) {
						borad_ver[i].c1 = true;			borad_ver[i].cell = true;
						borad_ver[i + 1].c1 = true;		borad_ver[i + 1].cell = true;
						borad_ver[i + 2].c1 = true;		borad_ver[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						d1 = false;
						move1 = false;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].c1 = true;			board[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].c1 = true;			board[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].c1 = true;			board[j].cell = true;
							}
							if ((borad_ver[i].x == board_ver_inv[j].x) && (borad_ver[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board_ver_inv[j].x) && (borad_ver[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board_ver_inv[j].x) && (borad_ver[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k1 == 3)
			{
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

			}
			else if (k1 == 4) {
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 4].c1 = true;		board[i + 4].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 4].x == borad_ver[j].x) && (board[i + 4].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 4].x == board_ver_inv[j].x) && (board[i + 4].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k1 == 5) {
				if (i < 3)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						board[i + 11].c1 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 8)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 14)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						board[i + 14].c1 = true;	board[i + 14].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 14].x == borad_ver[j].x) && (board[i + 14].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 14].x == board_ver_inv[j].x) && (board[i + 14].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 20)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 26)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						board[i + 11].c1 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
					}
					check_good();
				}
			}
		}
	}
	else if (move2) {
		for (int i = 0; i < 37; i++)
		{
			if (k2 == 0)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 2].c2 = true;		board[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 2].x == borad_ver[j].x) && (board[i + 2].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 2].x == board_ver_inv[j].x) && (board[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k2 == 1)
			{
				if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 2;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k2 == 2)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e2.x >= borad_ver[i].x) && (e2.x <= borad_ver[i].x + 40) && (e2.y >= borad_ver[i].y) && (e2.y <= borad_ver[i].y + 40)) {
						borad_ver[i].c2 = true;			borad_ver[i].cell = true;
						borad_ver[i + 1].c2 = true;		borad_ver[i + 1].cell = true;
						borad_ver[i + 2].c2 = true;		borad_ver[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						d2 = false;
						move2 = false;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].c2 = true;		board[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].c2 = true;		board[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].c2 = true;		board[j].cell = true;
							}
							if ((borad_ver[i].x == board_ver_inv[j].x) && (borad_ver[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board_ver_inv[j].x) && (borad_ver[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board_ver_inv[j].x) && (borad_ver[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k2 == 3)
			{
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 12].c2 = true;		board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

			}
			else if (k2 == 4) {
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 4].c2 = true;		board[i + 4].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 4].x == borad_ver[j].x) && (board[i + 4].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 4].x == board_ver_inv[j].x) && (board[i + 4].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k2 == 5) {
				if (i < 3)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						board[i + 11].c2 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 8)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 14)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						board[i + 14].c2 = true;	board[i + 14].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 14].x == borad_ver[j].x) && (board[i + 14].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 14].x == board_ver_inv[j].x) && (board[i + 14].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 20)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 26)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						board[i + 11].c2 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
		}
	}
	else if (move3) {
		for (int i = 0; i < 37; i++)
		{
			if (k3 == 0)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 2].c3 = true;		board[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 2].x == borad_ver[j].x) && (board[i + 2].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 2].x == board_ver_inv[j].x) && (board[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k3 == 1)
			{
				if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 2;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k3 == 2)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e3.x >= borad_ver[i].x) && (e3.x <= borad_ver[i].x + 40) && (e3.y >= borad_ver[i].y) && (e3.y <= borad_ver[i].y + 40)) {
						borad_ver[i].c3 = true;			borad_ver[i].cell = true;
						borad_ver[i + 1].c3 = true;		borad_ver[i + 1].cell = true;
						borad_ver[i + 2].c3 = true;		borad_ver[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						d3 = false;
						move3 = false;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].c3 = true;			board[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].c3 = true;			board[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].c3 = true;			board[j].cell = true;
							}
							if ((borad_ver[i].x == board_ver_inv[j].x) && (borad_ver[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board_ver_inv[j].x) && (borad_ver[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board_ver_inv[j].x) && (borad_ver[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k3 == 3)
			{
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;				borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

			}
			else if (k3 == 4) {
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 4].c3 = true;		board[i + 4].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 4].x == borad_ver[j].x) && (board[i + 4].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 4].x == board_ver_inv[j].x) && (board[i + 4].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k3 == 5) {
				if (i < 3)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						board[i + 11].c3 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 8)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 14)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						board[i + 14].c3 = true;	board[i + 14].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 14].x == borad_ver[j].x) && (board[i + 14].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 14].x == board_ver_inv[j].x) && (board[i + 14].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 20)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 26)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						board[i + 11].c3 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
		}
	}
}

void user_input(ALLEGRO_EVENT event) {
	if (event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY || event.type == ALLEGRO_EVENT_MOUSE_AXES) {
		er.x = event.mouse.x;
		er.y = event.mouse.y;
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (((k1 == 0) || (k1 == 1) || (k1 == 3) || (k1 == 5)) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k1][0].x) && (event.mouse.x <= three_el[k1][0].x + 50) && (event.mouse.y >= three_el[k1][0].y) && (event.mouse.y <= three_el[k1][0].y + 50)) {
			move1 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k1 == 2) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k1][0].x) && (event.mouse.x <= three_el[k1][0].x + 50) && (event.mouse.y >= three_el[k1][0].y) && (event.mouse.y <= three_el[k1][0].y + 50)) {
			move1 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k1 == 4) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k1][0].x) && (event.mouse.x <= three_el[k1][0].x + 50) && (event.mouse.y >= three_el[k1][0].y) && (event.mouse.y <= three_el[k1][0].y + 50)) {
			move1 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if (((k2 == 0) || (k2 == 1) || (k2 == 3) || (k2 == 5)) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k2][1].x) && (event.mouse.x <= three_el[k2][1].x + 50) && (event.mouse.y >= three_el[k2][1].y) && (event.mouse.y <= three_el[k2][1].y + 50)) {
			move2 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k2 == 2) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k2][1].x) && (event.mouse.x <= three_el[k2][1].x + 50) && (event.mouse.y >= three_el[k2][1].y) && (event.mouse.y <= three_el[k2][1].y + 50)) {
			move2 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k2 == 4) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k2][1].x) && (event.mouse.x <= three_el[k2][1].x + 50) && (event.mouse.y >= three_el[k2][1].y) && (event.mouse.y <= three_el[k2][1].y + 50)) {
			move2 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if (((k3 == 0) || (k3 == 1) || (k3 == 3) || (k3 == 5)) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k3][2].x) && (event.mouse.x <= three_el[k3][2].x + 50) && (event.mouse.y >= three_el[k3][2].y) && (event.mouse.y <= three_el[k3][2].y + 50)) {
			move3 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k3 == 2) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k3][2].x) && (event.mouse.x <= three_el[k3][2].x + 50) && (event.mouse.y >= three_el[k3][2].y) && (event.mouse.y <= three_el[k3][2].y + 50)) {
			move3 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k3 == 4) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k3][2].x) && (event.mouse.x <= three_el[k3][2].x + 50) && (event.mouse.y >= three_el[k3][2].y) && (event.mouse.y <= three_el[k3][2].y + 50)) {
			move3 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if (event.mouse.button & 2)
		{
			move1 = false;
			move2 = false;
			move3 = false;
		}
	}
	update_logic(event);
}
void is_good() {
	int i = 0;
	int temp[7] = { 0 };
	for (int i = 0; i < 37; i++) {
		if (board[i].cell == false) {
			board[i].c1 = false;
			board[i].c2 = false;
			board[i].c3 = false;
			board[i].drawn = false;
		}
	}
	while (i < 4)
	{
		if (board[i].cell) {
			temp[0]++;
		}
		i++;
	}
	while (i > 3 && i < 9)
	{
		if (board[i].cell) {
			temp[1]++;
		}
		i++;
	}
	while (i > 8 && i < 15)
	{
		if (board[i].cell) {
			temp[2]++;
		}
		i++;
	}
	while (i > 14 && i < 22)
	{
		if (board[i].cell) {
			temp[3]++;
		}
		i++;
	}
	while (i > 21 && i < 28)
	{
		if (board[i].cell) {
			temp[4]++;
		}
		i++;
	}
	while (i > 27 && i < 33)
	{
		if (board[i].cell) {
			temp[5]++;
		}
		i++;
	}
	while (i > 32 && i < 37)
	{
		if (board[i].cell) {
			temp[6]++;
		}
		i++;
	}
	if (temp[0] == 4) {
		for (int j = 0; j < 4; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
				{
					borad_ver[k].cell = false;
				}
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
				{
					board_ver_inv[k].cell = false;
				}
			}
		}
		draww = true;
		temp[0] = 0;
		counter += 4;
		//al_stop_sample(&soundid);
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp[1] == 5) {
		for (int j = 4; j < 9; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[1] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[2] == 6) {
		for (int j = 9; j < 15; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[2] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[3] == 7) {
		for (int j = 15; j < 22; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;;
		temp[3] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 7;
		check_level();
	}
	if (temp[4] == 6) {
		for (int j = 22; j < 28; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[4] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[5] == 5) {
		for (int j = 28; j < 33; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[5] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[6] == 4) {
		for (int j = 33; j < 37; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[6] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}
}
void is_good_ver() {
	int i = 0;
	int temp[7] = { 0 };
	while (i < 4)
	{
		if (borad_ver[i].cell) {
			temp[0]++;
		}
		i++;
	}
	while (i > 3 && i < 9)
	{
		if (borad_ver[i].cell) {
			temp[1]++;
		}
		i++;
	}
	while (i > 8 && i < 15)
	{
		if (borad_ver[i].cell) {
			temp[2]++;
		}
		i++;
	}
	while (i > 14 && i < 22)
	{
		if (borad_ver[i].cell) {
			temp[3]++;
		}
		i++;
	}
	while (i > 21 && i < 28)
	{
		if (borad_ver[i].cell) {
			temp[4]++;
		}
		i++;
	}
	while (i > 27 && i < 33)
	{
		if (borad_ver[i].cell) {
			temp[5]++;
		}
		i++;
	}
	while (i > 32 && i < 37)
	{
		if (borad_ver[i].cell) {
			temp[6]++;
		}
		i++;
	}
	if (temp[0] == 4) {
		for (int j = 0; j < 4; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[0] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}
	if (temp[1] == 5) {
		for (int j = 4; j < 9; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[1] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[2] == 6) {
		for (int j = 9; j < 15; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[2] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[3] == 7) {
		for (int j = 15; j < 22; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[3] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 7;
		check_level();
	}
	if (temp[4] == 6) {
		for (int j = 22; j < 28; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[4] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[5] == 5) {
		for (int j = 28; j < 33; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[5] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[6] == 4) {
		for (int j = 33; j < 37; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[6] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}
}
void is_good_ver_inv() {
	int i = 0;
	int temp[7] = { 0 };
	while (i < 4)
	{
		if (board_ver_inv[i].cell) {
			temp[0]++;
		}
		i++;
	}
	while (i > 3 && i < 9)
	{
		if (board_ver_inv[i].cell) {
			temp[1]++;
		}
		i++;
	}
	while (i > 8 && i < 15)
	{
		if (board_ver_inv[i].cell) {
			temp[2]++;
		}
		i++;
	}
	while (i > 14 && i < 22)
	{
		if (board_ver_inv[i].cell) {
			temp[3]++;
		}
		i++;
	}
	while (i > 21 && i < 28)
	{
		if (board_ver_inv[i].cell) {
			temp[4]++;
		}
		i++;
	}
	while (i > 27 && i < 33)
	{
		if (board_ver_inv[i].cell) {
			temp[5]++;
		}
		i++;
	}
	while (i > 32 && i < 37)
	{
		if (board_ver_inv[i].cell) {
			temp[6]++;
		}
		i++;
	}
	if (temp[0] == 4) {
		for (int j = 0; j < 4; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[0] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}
	if (temp[1] == 5) {
		for (int j = 4; j < 9; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[1] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[2] == 6) {
		for (int j = 9; j < 15; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[2] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[3] == 7) {
		for (int j = 15; j < 22; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww == true;
		temp[3] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 7;
		check_level();
	}
	if (temp[4] == 6) {
		for (int j = 22; j < 28; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[4] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[5] == 5) {
		for (int j = 28; j < 33; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[5] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[6] == 4) {
		for (int j = 33; j < 37; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[6] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}

}
void is_good_tr() {
	int temp1[6] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		if (borad_ver[i].cell && board_ver_inv[i].cell)
		{
			temp1[0]++;
		}
		if (borad_ver[i].cell && board[i].cell)
		{
			temp1[1]++;
		}
		if (board_ver_inv[i + 33].cell && board[i].cell)
		{
			temp1[2]++;
		}
		if (board_ver_inv[i].cell && board[i + 33].cell)
		{
			temp1[3]++;
		}
		if (borad_ver[i + 33].cell && board[i + 33].cell)
		{
			temp1[4]++;
		}
		if (borad_ver[i + 33].cell && board_ver_inv[i + 33].cell)
		{
			temp1[5]++;
		}
	}
	if (temp1[0] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board_ver_inv[i].c1 = false;
			board_ver_inv[i].c2 = false;
			board_ver_inv[i].c3 = false;
			board_ver_inv[i].cell = false;
			borad_ver[i].c1 = false;
			borad_ver[i].c2 = false;
			borad_ver[i].c3 = false;
			borad_ver[i].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[i].x == board[k].x) && (borad_ver[i].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[i].x == board[k].x) && (board_ver_inv[i].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[i].x == board_ver_inv[k].x) && (borad_ver[i].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board_ver_inv[i].x == borad_ver[k].x) && (board_ver_inv[i].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp1[0] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[1] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board[i].c1 = false;
			board[i].c2 = false;
			board[i].c3 = false;
			board[i].cell = false;
			board[i].wow = true;
			borad_ver[i].c1 = false;
			borad_ver[i].c2 = false;
			borad_ver[i].c3 = false;
			borad_ver[i].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[i].x == board_ver_inv[k].x) && (borad_ver[i].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board[i].x == board_ver_inv[k].x) && (board[i].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((borad_ver[i].x == board[k].x) && (borad_ver[i].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board[i].x == borad_ver[k].x) && (board[i].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp1[1] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[2] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board[i].c1 = false;
			board[i].c2 = false;
			board[i].c3 = false;
			board[i].cell = false;
			board[i].wow = true;
			board_ver_inv[i + 33].c1 = false;
			board_ver_inv[i + 33].c2 = false;
			board_ver_inv[i + 33].c3 = false;
			board_ver_inv[i + 33].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[i + 33].x == borad_ver[k].x) && (board_ver_inv[i + 33].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[i].x == borad_ver[k].x) && (board[i].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board_ver_inv[i + 33].x == board[k].x) && (board_ver_inv[i + 33].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board[i].x == board_ver_inv[k].x) && (board[i].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp1[2] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[3] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board[i + 33].c1 = false;
			board[i + 33].c2 = false;
			board[i + 33].c3 = false;
			board[i + 33].cell = false;
			board[i + 33].wow = true;
			board_ver_inv[i].c1 = false;
			board_ver_inv[i].c2 = false;
			board_ver_inv[i].c3 = false;
			board_ver_inv[i].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[i + 33].x == borad_ver[k].x) && (board[i + 33].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board_ver_inv[i].x == borad_ver[k].x) && (board_ver_inv[i].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[i + 33].x == board_ver_inv[k].x) && (board[i + 33].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board_ver_inv[i].x == board[k].x) && (board_ver_inv[i].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
			}
		}
		draww = true;
		temp1[3] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[4] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board[i + 33].c1 = false;
			board[i + 33].c2 = false;
			board[i + 33].c3 = false;
			board[i + 33].cell = false;
			board[i + 33].wow = true;
			borad_ver[i + 33].c1 = false;
			borad_ver[i + 33].c2 = false;
			borad_ver[i + 33].c3 = false;
			borad_ver[i + 33].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[i + 33].x == board_ver_inv[k].x) && (board[i + 33].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((borad_ver[i + 33].x == board_ver_inv[k].x) && (borad_ver[i + 33].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board[i + 33].x == borad_ver[k].x) && (board[i + 33].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((borad_ver[i + 33].x == board[k].x) && (borad_ver[i + 33].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
			}
		}
		draww = true;
		temp1[4] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[5] == 4) {
		for (int i = 0; i < 4; i++)
		{
			board_ver_inv[i + 33].c1 = false;
			board_ver_inv[i + 33].c2 = false;
			board_ver_inv[i + 33].c3 = false;
			board_ver_inv[i + 33].cell = false;
			borad_ver[i + 33].c1 = false;
			borad_ver[i + 33].c2 = false;
			borad_ver[i + 33].c3 = false;
			borad_ver[i + 33].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[i + 33].x == board[k].x) && (board_ver_inv[i + 33].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[i + 33].x == board[k].x) && (borad_ver[i + 33].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[i + 33].x == board_ver_inv[k].x) && (borad_ver[i + 33].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board_ver_inv[i + 33].x == borad_ver[k].x) && (board_ver_inv[i + 33].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp1[5] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
}
void check_good() {
	is_good_tr();
	is_good_ver_inv();
	is_good_ver();
	is_good();
}
bool check_end_case(int k) {
	bool temp = false;
	for (int i = 0; i < 37; i++)
	{
		if (k == 0)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k == 1)
		{
			if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k == 2)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k == 3)
		{
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}

		}
		else if (k == 4) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}

			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k == 5) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 14)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 20)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 26)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
		}
	}
	return temp;
}
bool check_endk1() {
	bool temp = false;
	for (int i = 0; i < 37; i++)
	{
		if (k1 == 0)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k1 == 1)
		{
			if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k1 == 2)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k1 == 3)
		{
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}

		}
		else if (k1 == 4) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}

			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k1 == 5) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 14)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 20)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 26)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
		}
	}
	return temp;
}
bool check_endk2() {
	bool temp = false;
	for (int i = 0; i < 37; i++)
	{
		if (k2 == 0)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k2 == 1)
		{
			if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k2 == 2)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k2 == 3)
		{
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}

		}
		else if (k2 == 4) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}

			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k2 == 5) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 14)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 20)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 26)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
		}
	}
	return temp;
}
bool check_endk3() {
	bool temp = false;
	for (int i = 0; i < 37; i++)
	{
		if (k3 == 0)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k3 == 1)
		{
			if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k3 == 2)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k3 == 3)
		{
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}

		}
		else if (k3 == 4) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}

			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k3 == 5) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 14)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 20)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 26)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
		}
	}
	return temp;
}
void check_end() {
	endcase = false;
	if (!d1 && d2 && d3) {
		if (!check_end_case(k2) && !check_end_case(k3))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "Your Score", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}

	}
	else if (!d1 && !d2 && d3)
	{
		if (!check_end_case(k3))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (!d1 && d2 && !d3)
	{
		if (!check_end_case(k2))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (d1 && d2 && !d3)
	{
		if (!check_end_case(k1) && !check_end_case(k2))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (d1 && !d2 && d3)
	{
		if (!check_end_case(k1) && !check_end_case(k3))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (d1 && !d2 && !d3)
	{
		if (!check_end_case(k1))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (d1 && d2 && d3)
	{
		if (!check_end_case(k1) && !check_end_case(k2) && !check_end_case(k3))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();
		}
	}
}
void high_score() {
	int temp = -1;
	char i[10];
	file = fopen("HighScore.txt", "r");
	fgets(i, 10, file);
	fclose(file);
	temp = atoi(i);
	if (counter > temp)
	{
		file = fopen("HighScore.txt", "w");
		sprintf(i, "%d", counter);
		fputs(i, file);
		fclose(file);
	}
	file = fopen("HighScore.txt", "r");
	fgets(score, 10, file);
	fclose(file);
}
void shutdown(void)
{
	if (done) {
		if (event_queue)
			al_destroy_event_queue(event_queue);
		if (timer) {
			al_destroy_timer(timer);
		}
		if (display)
			al_destroy_display(display);
		if (sound)
			al_destroy_sample(sound);
	}
}
void shutdown_menu(void)
{
	if (done_men) {
		if (event_queue_menu)
			al_destroy_event_queue(event_queue_menu);
		if (timer_menu) {
			al_destroy_timer(timer_menu);
		}
		if (display_menu)
			al_destroy_display(display_menu);
	}
}
void draw() {
	if (!d1 && !d2 && !d3)
		doit = true;
	else
		doit = false;

	if (doit)
	{
		srand(time(NULL));
		if (level == 1) {
			k1 = rand() % 4;
			k2 = rand() % 4;
			k3 = rand() % 4;
		}
		else {
			k1 = rand() % 4 + 2;
			k2 = rand() % 4 + 2;
			k3 = rand() % 4 + 2;
		}
		d1 = true; d2 = true; d3 = true;
		doit = false;
	}
	if (move1 && !move2 && !move3)
		e1 = er;
	else
		e1 = three_el[k1][0];
	if (move2 && !move1 && !move3)
		e2 = er;
	else
		e2 = three_el[k2][1];
	if (move3 && !move2 && !move1)
		e3 = er;
	else
		e3 = three_el[k3][2];
	al_draw_bitmap(image, 50, 50, 0);
	for (int i = 0; i < 37; i++) {
		board[i].check = false;
	}
	///////////start
	if (move1) {
		for (int i = 0; i < 37; i++)
		{
			if (k1 == 0)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 1].check = true;				board[i + 2].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 1].check = false;				board[i + 2].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k1 == 1)
			{
				if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;				board[i + 1].check = true;
					}
					else
					{
						board[i].check = false;				board[i + 1].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k1 == 2)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e1.x >= borad_ver[i].x) && (e1.x <= borad_ver[i].x + 40) && (e1.y >= borad_ver[i].y) && (e1.y <= borad_ver[i].y + 40)) {
						borad_ver[i].check = true;				borad_ver[i + 1].check = true;				borad_ver[i + 2].check = true;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].check = true;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].check = true;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].check = true;
							}
						}
					}
					else
					{
						borad_ver[i].check = false;				borad_ver[i + 1].check = false;				borad_ver[i + 2].check = false;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].check = false;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].check = false;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].check = false;
							}
						}
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k1 == 3)
			{
				if (i < 4)
				{
					if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 5].check = true;			board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 5].check = false;			board[i + 10].check = false;
					}
				}
				if (i > 3 && i < 9)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 6].check = true;			board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 6].check = false;			board[i + 12].check = false;
					}
				}
				if (i > 8 && i < 15)
				{
					if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 7].check = true;			board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 7].check = false;			board[i + 13].check = false;
					}
				}
				if (i > 15 && i < 21)
				{
					if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 7].check = true;			board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 7].check = false;			board[i + 12].check = false;
					}
				}
				if (i > 22 && i < 27)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 6].check = true;			board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 6].check = false;			board[i + 10].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
					}
				}

			}
			else if (k1 == 4) {
				if (i < 4)
				{
					if ((board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 4].check = true;			board[i + 5].check = true;			board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 4].check = false;			board[i + 5].check = false;			board[i + 10].check = false;
					}
				}
				if (i > 3 && i < 9)
				{
					if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 5].check = true;			board[i + 6].check = true;			board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 5].check = false;			board[i + 6].check = false;			board[i + 12].check = false;
					}
				}
				if (i > 8 && i < 15)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 6].check = true;			board[i + 7].check = true;			board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 6].check = false;			board[i + 7].check = false;			board[i + 13].check = false;
					}
				}

				if (i > 15 && i < 21)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 6].check = true;			board[i + 7].check = true;			board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 6].check = false;			board[i + 7].check = false;			board[i + 12].check = false;
					}
				}
				if (i > 22 && i < 27)
				{
					if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;			board[i + 5].check = true;			board[i + 6].check = true;			board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;			board[i + 5].check = false;			board[i + 6].check = false;			board[i + 10].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k1 == 5) {
				if (i < 3)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 5].check = true;	board[i + 10].check = true;	board[i + 11].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 5].check = false;	board[i + 10].check = false; board[i + 11].check = false;
					}
				}
				if (i > 3 && i < 8)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 6].check = true;	board[i + 12].check = true;	board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 6].check = false;	board[i + 12].check = false; board[i + 13].check = false;
					}
				}
				if (i > 8 && i < 14)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 7].check = true;	board[i + 13].check = true;	board[i + 14].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 7].check = false;	board[i + 13].check = false; board[i + 14].check = false;
					}
				}
				if (i > 15 && i < 20)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 7].check = true;	board[i + 12].check = true;	board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 7].check = false;	board[i + 12].check = false; board[i + 13].check = false;
					}
				}
				if (i > 22 && i < 26)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 6].check = true;	board[i + 10].check = true;	board[i + 11].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 6].check = false;	board[i + 10].check = false; board[i + 11].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
		}

	}
	else if (move2) {
		for (int i = 0; i < 37; i++)
		{
			if (k2 == 0)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 1].check = true;		board[i + 2].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 1].check = false;		board[i + 2].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(252, 247, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k2 == 1)
			{
				if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 1].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 1].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(252, 247, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k2 == 2)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e2.x >= borad_ver[i].x) && (e2.x <= borad_ver[i].x + 40) && (e2.y >= borad_ver[i].y) && (e2.y <= borad_ver[i].y + 40)) {
						borad_ver[i].check = true;		borad_ver[i + 1].check = true;		borad_ver[i + 2].check = true;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].check = true;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].check = true;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].check = true;
							}
						}
					}
					else
					{
						borad_ver[i].check = false;		borad_ver[i + 1].check = false;		borad_ver[i + 2].check = false;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].check = false;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].check = false;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].check = false;
							}
						}
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(252, 247, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k2 == 3)
			{
				if (i < 4)
				{
					if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 5].check = true;		board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 5].check = false;		board[i + 10].check = false;
					}
				}
				if (i > 3 && i < 9)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 6].check = true;		board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 6].check = false;		board[i + 12].check = false;
					}
				}
				if (i > 8 && i < 15)
				{
					if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 7].check = true;		board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 7].check = false;		board[i + 13].check = false;
					}
				}
				if (i > 15 && i < 21)
				{
					if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 7].check = true;		board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 7].check = false;		board[i + 12].check = false;
					}
				}
				if (i > 22 && i < 27)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 6].check = true;		board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 6].check = false;		board[i + 10].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(252, 247, 97), board[i].x - 20, board[i].y, 0);
					}
				}

			}
			else if (k2 == 4) {
				if (i < 4)
				{
					if ((board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 4].check = true;		board[i + 5].check = true;		board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 4].check = false;		board[i + 5].check = false;		board[i + 10].check = false;
					}
				}
				if (i > 3 && i < 9)
				{
					if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 5].check = true;		board[i + 6].check = true;		board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 5].check = false;		board[i + 6].check = false;		board[i + 12].check = false;
					}
				}
				if (i > 8 && i < 15)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 6].check = true;		board[i + 7].check = true;		board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 6].check = false;		board[i + 7].check = false;		board[i + 13].check = false;
					}
				}

				if (i > 15 && i < 21)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 6].check = true;		board[i + 7].check = true;		board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 6].check = false;		board[i + 7].check = false;		board[i + 12].check = false;
					}
				}
				if (i > 22 && i < 27)
				{
					if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 5].check = true;		board[i + 6].check = true;		board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 5].check = false;		board[i + 6].check = false;		board[i + 10].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(252, 247, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k2 == 5) {
				if (i < 3)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 5].check = true;	board[i + 10].check = true;	board[i + 11].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 5].check = false;	board[i + 10].check = false;	board[i + 11].check = false;
					}
				}
				if (i > 3 && i < 8)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 6].check = true;	board[i + 12].check = true;	board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 6].check = false;	board[i + 12].check = false;	board[i + 13].check = false;
					}
				}
				if (i > 8 && i < 14)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 7].check = true;	board[i + 13].check = true;	board[i + 14].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 7].check = false;	board[i + 13].check = false;	board[i + 14].check = false;
					}
				}
				if (i > 15 && i < 20)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 7].check = true;	board[i + 12].check = true;	board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 7].check = false;	board[i + 12].check = false;	board[i + 13].check = false;
					}
				}
				if (i > 22 && i < 26)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 6].check = true;	board[i + 10].check = true;	board[i + 11].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 6].check = false;	board[i + 10].check = false;	board[i + 11].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(252, 247, 97), board[i].x - 20, board[i].y, 0);
					}
				}
			}
		}

	}
	else if (move3) {
		for (int i = 0; i < 37; i++)
		{
			if (k3 == 0)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 1].check = true;		board[i + 2].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 1].check = false;		board[i + 2].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(203, 153, 201), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k3 == 1)
			{
				if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 1].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 1].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(203, 153, 201), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k3 == 2)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e3.x >= borad_ver[i].x) && (e3.x <= borad_ver[i].x + 40) && (e3.y >= borad_ver[i].y) && (e3.y <= borad_ver[i].y + 40)) {
						borad_ver[i].check = true;		borad_ver[i + 1].check = true;		borad_ver[i + 2].check = true;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].check = true;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].check = true;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].check = true;
							}
						}
					}
					else
					{
						borad_ver[i].check = false;		borad_ver[i + 1].check = false;		borad_ver[i + 2].check = false;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].check = false;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].check = false;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].check = false;
							}
						}
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(203, 153, 201), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k3 == 3)
			{
				if (i < 4)
				{
					if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 5].check = true;		board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 5].check = false;		board[i + 10].check = false;
					}
				}
				if (i > 3 && i < 9)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 6].check = true;		board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 6].check = false;		board[i + 12].check = false;
					}
				}
				if (i > 8 && i < 15)
				{
					if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 7].check = true;		board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 7].check = false;		board[i + 13].check = false;
					}
				}
				if (i > 15 && i < 21)
				{
					if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 7].check = true;		board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 7].check = false;		board[i + 12].check = false;
					}
				}
				if (i > 22 && i < 27)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;		board[i + 6].check = true;		board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;		board[i + 6].check = false;		board[i + 10].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(203, 153, 201), board[i].x - 20, board[i].y, 0);
					}
				}

			}
			else if (k3 == 4) {
				if (i < 4)
				{
					if ((board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 4].check = true;	board[i + 5].check = true;	board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 4].check = false;	board[i + 5].check = false;	board[i + 10].check = false;
					}
				}
				if (i > 3 && i < 9)
				{
					if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 5].check = true;	board[i + 6].check = true;	board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 5].check = false;	board[i + 6].check = false;	board[i + 12].check = false;
					}
				}
				if (i > 8 && i < 15)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 6].check = true;	board[i + 7].check = true;	board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 6].check = false;	board[i + 7].check = false;	board[i + 13].check = false;
					}
				}

				if (i > 15 && i < 21)
				{
					if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 6].check = true;	board[i + 7].check = true;	board[i + 12].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 6].check = false;	board[i + 7].check = false;	board[i + 12].check = false;
					}
				}
				if (i > 22 && i < 27)
				{
					if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 5].check = true;	board[i + 6].check = true;	board[i + 10].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 5].check = false;	board[i + 6].check = false;	board[i + 10].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(203, 153, 201), board[i].x - 20, board[i].y, 0);
					}
				}
			}
			else if (k3 == 5) {
				if (i < 3)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 5].check = true;	board[i + 10].check = true;	board[i + 11].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 5].check = false;	board[i + 10].check = false;	board[i + 11].check = false;
					}
				}
				if (i > 3 && i < 8)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 6].check = true;	board[i + 12].check = true;	board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 6].check = false;	board[i + 12].check = false;	board[i + 13].check = false;
					}
				}
				if (i > 8 && i < 14)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 7].check = true;	board[i + 13].check = true;	board[i + 14].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 7].check = false;	board[i + 13].check = false;	board[i + 14].check = false;
					}
				}
				if (i > 15 && i < 20)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 7].check = true;	board[i + 12].check = true;	board[i + 13].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 7].check = false;	board[i + 12].check = false;	board[i + 13].check = false;
					}
				}
				if (i > 22 && i < 26)
				{
					if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].check = true;	board[i + 1].check = true;	board[i + 6].check = true;	board[i + 10].check = true;	board[i + 11].check = true;
					}
					else
					{
						board[i].check = false;	board[i + 1].check = false;	board[i + 6].check = false;	board[i + 10].check = false;	board[i + 11].check = false;
					}
				}
				for (int i = 0; i < 37; i++) {
					if (board[i].check) {
						q[i] = q9;
						al_draw_tinted_bitmap(q[i], al_map_rgb(203, 153, 201), board[i].x - 20, board[i].y, 0);
					}
				}
			}
		}

	}
	//////////end
	if (d1) {
		switch (k1)
		{
		case 0:
			al_draw_tinted_bitmap(q1, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
			break;
		case 1:
			al_draw_tinted_bitmap(q2, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
			break;
		case 2:
			al_draw_tinted_bitmap(q3, al_map_rgb(255, 0, 0), e1.x, e1.y - 70, 0);
			break;
		case 3:
			al_draw_tinted_bitmap(q4, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
			break;
		case 4:
			al_draw_tinted_bitmap(q5, al_map_rgb(255, 0, 0), e1.x, e1.y - 35, 0);
			break;
		case 5:
			al_draw_tinted_bitmap(q6, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
			break;
		default:
			break;
		}
	}
	if (d2) {
		switch (k2)
		{
		case 0:
			al_draw_tinted_bitmap(q1, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
			break;
		case 1:
			al_draw_tinted_bitmap(q2, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
			break;
		case 2:
			al_draw_tinted_bitmap(q3, al_map_rgb(255, 255, 0), e2.x, e2.y - 70, 0);
			break;
		case 3:
			al_draw_tinted_bitmap(q4, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
			break;
		case 4:
			al_draw_tinted_bitmap(q5, al_map_rgb(255, 255, 0), e2.x, e2.y - 35, 0);
			break;
		case 5:
			al_draw_tinted_bitmap(q6, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
			break;
		default:
			break;
		}
	}
	if (d3) {
		switch (k3)
		{
		case 0:
			al_draw_tinted_bitmap(q1, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
			break;
		case 1:
			al_draw_tinted_bitmap(q2, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
			break;
		case 2:
			al_draw_tinted_bitmap(q3, al_map_rgb(255, 0, 255), e3.x, e3.y - 70, 0);
			break;
		case 3:
			al_draw_tinted_bitmap(q4, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
			break;
		case 4:
			al_draw_tinted_bitmap(q5, al_map_rgb(255, 0, 255), e3.x, e3.y - 35, 0);
			break;
		case 5:
			al_draw_tinted_bitmap(q6, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < 37; i++) {
		if (board[i].c1 && !board[i].c2 && !board[i].c3 && board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 0), board[i].x - 20, board[i].y, 0);
		}
		else if (board[i].c2 && !board[i].c1 && !board[i].c3 && board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 255, 0), board[i].x - 20, board[i].y, 0);
		}
		else if (board[i].c3 && !board[i].c1 && !board[i].c2 && board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 255), board[i].x - 20, board[i].y, 0);
		}
	}
	for (int i = 0; i < 37; i++) {
		if (board[i].c1 && !board[i].c2 && !board[i].c3 && !board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 0), board[i].x - 20, board[i].y, 0);
			al_flip_display();
			al_play_sample(pop, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			al_rest(0.16);
			board[i].drawn = true;
		}
		else if (board[i].c2 && !board[i].c1 && !board[i].c3 && !board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 255, 0), board[i].x - 20, board[i].y, 0);
			al_flip_display();
			al_play_sample(pop, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			al_rest(0.16);
			board[i].drawn = true;
		}
		else if (board[i].c3 && !board[i].c1 && !board[i].c2 && !board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 255), board[i].x - 20, board[i].y, 0);
			al_flip_display();
			al_play_sample(pop, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			al_rest(0.16);
			board[i].drawn = true;
		}
	}
	for (int j = 0; j < 37; j++) {
		if (board[j].wow) {
			q[j] = q10;
			al_draw_bitmap(q[j], board[j].x - 20, board[j].y, 0);
			al_flip_display();
			al_play_sample(shoot, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			al_rest(0.1);
		}
	}
}
void check_level() {
	if (counter > 100)
	{
		level = 2;
		levsound++;
		while (levsound == 2)
		{
			al_play_sample(level1, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			levsound++;
		}
	}
}
void game_loop(void)
{
	bool redraw = true;
	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
			shutdown();
			save();
			done_men = false;
			init_menu();
			game_menu();
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			check_end();
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
				shutdown();
				save();
				done_men = false;
				init_menu();
				game_menu();
			}
		}
		user_input(event);
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			high_score();
			al_draw_textf(font, al_map_rgb(255, 255, 255), 850, 10, 0, "SCORE: %d", counter);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 850, 80, 0, "LEVEL: %d", level);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 850, 150, 0, "HIGH SCORE: %s", score);
			draw();
			/*	ALLEGRO_MOUSE_STATE state;

			al_get_mouse_state(&state);
			if (state.buttons & 1) {
			// Primary (e.g. left) mouse button is held.
			printf("Mouse position: (%d, %d)--", state.x, state.y);
			}
			if (state.buttons & 2) {
			// Secondary (e.g. right) mouse button is held.
			}
			if (state.buttons & 4) {
			// Tertiary (e.g. middle) mouse button is held.
			}
			al_flip_display();
			if (draww == true) {
				al_rest(0.15);
				for (int i = 0; i < 37; i++)
					board[i].wow = false;
			}
			draww = false;
			check_end();

		}
	}
}
void save() {
	if (done)
	{
		cases c = { k1,k2,k3,counter,level,d1,d2,d3,endcase };
		board_file = fopen("board.dat", "w");
		fwrite(&board, sizeof(board), 1, board_file);
		fclose(board_file);
		score_file = fopen("score.dat", "w");
		fwrite(&c, sizeof(cases), 1, score_file);
		fclose(score_file);
	}
}
void init_resum() {
	done_men = false;
	cases c;
	ele_pos pos[37];
	int i = 0;
	board_file = fopen("board.dat", "r");
	fread(&pos, sizeof(pos), 1, board_file);
	for (int i = 0; i < 37; i++)
		board[i] = pos[i];
	fclose(board_file);
	score_file = fopen("score.dat", "r");
	fread(&c, sizeof(cases), 1, score_file);
	k1 = c.k1;
	k2 = c.k2;
	k3 = c.k3;
	d1 = c.d1;
	d2 = c.d2;
	d3 = c.d3;
	counter = c.counter;
	level = c.level;
	endcase = c.endcase;
	fclose(score_file);
}



#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct ele_pos {
	int x, y;
	bool c1, c2, c3, cell, check, wow, drawn;
};
struct cases
{
	int k1, k2, k3;
	int counter, level;
	bool d1, d2, d3, endcase;
};

bool done, move1, move2, move3, d1, d2, d3, doit, done_men, draww;
bool endcase = true;
ALLEGRO_EVENT_QUEUE* event_queue_menu;
ALLEGRO_TIMER* timer_menu;
ALLEGRO_DISPLAY* display_menu;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_BITMAP* image_menu;
ALLEGRO_BITMAP* play;
ALLEGRO_BITMAP* resum;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;
ALLEGRO_FONT *font;
ALLEGRO_BITMAP* image;
ALLEGRO_BITMAP* q1;
ALLEGRO_BITMAP* q2;
ALLEGRO_BITMAP* q3;
ALLEGRO_BITMAP* q4;
ALLEGRO_BITMAP* q5;
ALLEGRO_BITMAP* q6;
ALLEGRO_BITMAP* q9;
ALLEGRO_BITMAP* q10;
ALLEGRO_BITMAP* newgame;
ALLEGRO_SAMPLE* sound;
ALLEGRO_SAMPLE_ID soundid;
ALLEGRO_SAMPLE* win;
ALLEGRO_SAMPLE* level1;
ALLEGRO_SAMPLE* click;
ALLEGRO_SAMPLE* click_menu;
ALLEGRO_SAMPLE* end;
ALLEGRO_SAMPLE* pop;
ALLEGRO_SAMPLE* shoot;
static ALLEGRO_BITMAP* q[37];
static char score[10];
static int counter = 0;
int k1, k2, k3, level = 1, levsound = 1;
FILE *file;
FILE *score_file;
FILE *board_file;
static ele_pos  e1, e2, e3, er, board[37], borad_ver[37], board_ver_inv[37];
void save();
void init_resum();
void init();
void game_loop();
const ele_pos three_el[6][3] = { { { 560,350 },{ 855,350 },{ 1145,350 } },
{ { 560,350 },{ 855,350 },{ 1145,350 } },
{ { 560,425 },{ 855,425 },{ 1150,425 } } ,
{ { 560,355 },{ 855,355 },{ 1150,355 } } ,
{ { 560,405 },{ 855,405 },{ 1150,405 } } ,
{ { 560,370 },{ 855,370 },{ 1150,370 } } };
void draw();
void update_logic(ALLEGRO_EVENT event);
void user_input(ALLEGRO_EVENT event);
void check_good();
void is_good();
void is_good_ver();
void is_good_ver_inv();
void is_good_tr();
void init_ver();
void init_board();
void check_level();
void check_end();
bool check_end_case(int k);
void shutdown();
void shutdown_menu();
void high_score();

void abort_game(const char* message)
{
	printf("%s \n", message);
	fclose(file);
	exit(1);
}
void init_menu(void)
{
	if (!al_init())
		abort_game("Failed to initialize allegro");

	if (!al_install_keyboard())
		abort_game("Failed to install keyboard");

	if (!al_install_mouse())
		abort_game("Failed to install keyboard");

	timer_menu = al_create_timer(1.0 / 60);
	if (!timer_menu)
		abort_game("Failed to create timer");

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display_menu = al_create_display(800, 566);
	al_set_window_title(display_menu, "HEXAGON MAIN");
	if (!display_menu)
		abort_game("Failed to create display");

	event_queue_menu = al_create_event_queue();
	if (!event_queue_menu)
		abort_game("Failed to create event queue");
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	font = al_load_ttf_font("pirulen rg.ttf", 35, 0);
	al_reserve_samples(1);
	click_menu = al_load_sample("click_menu.wav");
	image_menu = al_load_bitmap("NEW.png");
	play = al_load_bitmap("play.png");
	resum = al_load_bitmap("resum.png");
	al_register_event_source(event_queue_menu, al_get_keyboard_event_source());
	al_register_event_source(event_queue_menu, al_get_timer_event_source(timer_menu));
	al_register_event_source(event_queue_menu, al_get_display_event_source(display_menu));
	al_register_event_source(event_queue_menu, al_get_mouse_event_source());
	cases c;
	score_file = fopen("score.dat", "r");
	if (score_file) {
		fread(&c, sizeof(cases), 1, score_file);
		fclose(score_file);
		endcase = c.endcase;
	}
	else
		endcase = true;
	done = true;

}
void game_menu(void)
{
	bool redraw = true, p = false, p1 = false;
	al_start_timer(timer_menu);

	while (!done_men) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue_menu, &event);
		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
			//	update_logic(event);
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done_men = true;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done_men = true;
			}

			//get_user_input();		

		}
		if (event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY || event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			if ((event.mouse.x >= 320) && (event.mouse.x <= 470) && (event.mouse.y >= 360) && (event.mouse.y <= 405))
			{
				p = true;
			}
			else if (done && !endcase && (event.mouse.x >= 320) && (event.mouse.x <= 470) && (event.mouse.y >= 460) && (event.mouse.y <= 505))
			{
				p1 = true;
			}
			else
			{
				p = false;
				p1 = false;
			}
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if ((event.mouse.x >= 320) && (event.mouse.x <= 470) && (event.mouse.y >= 360) && (event.mouse.y <= 405))
			{
				p = true;
				if (event.mouse.button & 1)
				{
					al_play_sample(click_menu, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					done_men = true;
					shutdown_menu();
					init();
					al_play_sample(sound, 0.4, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
					game_loop();
				}
			}
			else if (done && !endcase && (event.mouse.x >= 320) && (event.mouse.x <= 470) && (event.mouse.y >= 460) && (event.mouse.y <= 505))
			{
				p1 = true;
				if (event.mouse.button & 1)
				{
					al_play_sample(click_menu, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					done_men = true;
					shutdown_menu();
					init();
					init_resum();
					al_play_sample(sound, 0.4, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
					game_loop();
				}
			}
			else
			{
				p = false;
				p1 = false;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue_menu)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(image_menu, 0, 0, 0);
			if (p)
				al_draw_tinted_bitmap(play, al_map_rgb(0, 255, 0), 320, 350, 0);
			else
				al_draw_bitmap(play, 320, 350, 0);
			if (p1 && !endcase)
				al_draw_tinted_bitmap(resum, al_map_rgb(0, 255, 0), 320, 450, 0);
			else if (!endcase)
				al_draw_bitmap(resum, 320, 450, 0);
			al_flip_display();
		}
	}
}


void init(void)
{
	if (!al_init())
		abort_game("Failed to initialize allegro");

	if (!al_install_keyboard())
		abort_game("Failed to install keyboard");

	if (!al_install_mouse())
		abort_game("Failed to install keyboard");

	timer = al_create_timer(1.0 / 60);
	if (!timer)
		abort_game("Failed to create timer");

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(1400, 600);
	al_set_window_title(display, "HEXAGON");
	if (!display)
		abort_game("Failed to create display");

	event_queue = al_create_event_queue();
	if (!event_queue)
		abort_game("Failed to create event queue");
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	font = al_load_ttf_font("pirulen rg.ttf", 22, 0);
	image = al_load_bitmap("h.bmp");
	q1 = al_load_bitmap("1.png");
	q2 = al_load_bitmap("2.png");
	q3 = al_load_bitmap("3.png");
	q4 = al_load_bitmap("4.png");
	q5 = al_load_bitmap("5.png");
	q6 = al_load_bitmap("6.png");
	q9 = al_load_bitmap("9.png");
	q10 = al_load_bitmap("10.png");
	newgame = al_load_bitmap("New.png");
	al_reserve_samples(8);
	sound = al_load_sample("sound.wav");
	win = al_load_sample("win.wav");
	level1 = al_load_sample("level.wav");
	click = al_load_sample("click.wav");
	end = al_load_sample("end.wav");
	pop = al_load_sample("pop.wav");
	shoot = al_load_sample("shoot.wav");
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	done = false;
	move1 = false;
	move2 = false;
	move3 = false;
	draww = false;
	init_board();
	init_ver();
	doit = true;
	d1 = true; d2 = true; d3 = true;
	srand(time(NULL));
	k1 = rand() % 4;
	k2 = rand() % 4;
	k3 = rand() % 4;
	e1 = three_el[k1][0];
	e2 = three_el[k2][1];
	e3 = three_el[k2][2];
	counter = 0;
}
void init_board() {
	for (int i = 0; i < 37; i++) {
		if (i < 4) {
			board[i].x = 100;
		}
		else if (i>3 && i < 9) {
			board[i].x = 160;
		}
		else if (i > 8 && i < 15) {
			board[i].x = 220;
		}
		else if (i > 14 && i < 22) {
			board[i].x = 280;
		}
		else if (i > 21 && i < 28) {
			board[i].x = 340;
		}
		else if (i > 27 && i < 33) {
			board[i].x = 400;
		}
		else if (i > 32 && i < 37) {
			board[i].x = 460;
		}
	}
	for (int i = 0; i < 37; i++) {
		if (i < 4) {
			if (i == 0) {
				board[0].y = 160;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i>3 && i < 9) {
			if (i == 4) {
				board[4].y = 125;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 8 && i < 15) {
			if (i == 9) {
				board[9].y = 90;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 14 && i < 22) {
			if (i == 15) {
				board[15].y = 55;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 21 && i < 28) {
			if (i == 22) {
				board[22].y = 90;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 27 && i < 33) {
			if (i == 28) {
				board[28].y = 125;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
		else if (i > 32 && i < 37) {
			if (i == 33) {
				board[33].y = 160;
			}
			else
				board[i].y = board[i - 1].y + 70;
		}
	}
	printf("----------------------------------\n");
	for (int i = 0; i < 37; i++) {
		board[i].c1 = false;
		board[i].c2 = false;
		board[i].c3 = false;
		board[i].cell = false;
		board[i].check = false;
		board[i].wow = false;
		board[i].drawn = false;
		printf("( %d , %d )", board[i].x, board[i].y);
		if (i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32)
			printf("\n");
	}

}
void init_ver() {

	// Inverse Ver
	for (int i = 0; i < 37; i++) {
		if (i < 4) {
			if (i == 0) {
				board_ver_inv[0].x = 280;
				board_ver_inv[0].y = 55;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i>3 && i < 9) {
			if (i == 4) {
				board_ver_inv[4].x = 220;
				board_ver_inv[4].y = 90;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 8 && i < 15) {
			if (i == 9) {
				board_ver_inv[9].x = 160;
				board_ver_inv[9].y = 125;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 14 && i < 22) {
			if (i == 15) {
				board_ver_inv[15].x = 100;
				board_ver_inv[15].y = 160;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 21 && i < 28) {
			if (i == 22) {
				board_ver_inv[22].x = 100;
				board_ver_inv[22].y = 230;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 27 && i < 33) {
			if (i == 28) {
				board_ver_inv[28].x = 100;
				board_ver_inv[28].y = 300;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
		else if (i > 32 && i < 37) {
			if (i == 33) {
				board_ver_inv[33].x = 100;
				board_ver_inv[33].y = 370;
			}
			else {
				board_ver_inv[i].x = board_ver_inv[i - 1].x + 60;
				board_ver_inv[i].y = board_ver_inv[i - 1].y + 35;
			}
		}
	}
	// Board Ver
	for (int i = 0; i < 37; i++) {
		if (i < 4) {
			if (i == 0) {
				borad_ver[0].x = 100;
				borad_ver[0].y = 160;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i>3 && i < 9) {
			if (i == 4) {
				borad_ver[4].x = 100;
				borad_ver[4].y = 230;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 8 && i < 15) {
			if (i == 9) {
				borad_ver[9].x = 100;
				borad_ver[9].y = 300;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 14 && i < 22) {
			if (i == 15) {
				borad_ver[15].x = 100;
				borad_ver[15].y = 370;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 21 && i < 28) {
			if (i == 22) {
				borad_ver[22].x = 160;
				borad_ver[22].y = 405;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 27 && i < 33) {
			if (i == 28) {
				borad_ver[28].x = 220;
				borad_ver[28].y = 440;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
		else if (i > 32 && i < 37) {
			if (i == 33) {
				borad_ver[33].x = 280;
				borad_ver[33].y = 475;
			}
			else {
				borad_ver[i].x = borad_ver[i - 1].x + 60;
				borad_ver[i].y = borad_ver[i - 1].y - 35;
			}
		}
	}
	printf("\n----------------------------------\n");
	for (int i = 0; i < 37; i++) {
		borad_ver[i].c1 = false;
		borad_ver[i].c2 = false;
		borad_ver[i].c3 = false;
		borad_ver[i].cell = false;
		printf("( %d , %d )", borad_ver[i].x, borad_ver[i].y);
		if (i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32)
			printf("\n");
	}
	printf("\n----------------------------------\n");
	for (int i = 0; i < 37; i++) {
		board_ver_inv[i].c1 = false;
		board_ver_inv[i].c2 = false;
		board_ver_inv[i].c3 = false;
		board_ver_inv[i].cell = false;
		printf("( %d , %d )", board_ver_inv[i].x, board_ver_inv[i].y);
		if (i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32)
			printf("\n");
	}
}
void update_movement(ALLEGRO_EVENT event, int k, int case_color, ele_pos e, bool move) {
	for (int i = 0; i < 37; i++)
	{
		if (k == 0)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 1].c1 = true;		board[i + 1].cell = true;
					board[i + 2].c1 = true;		board[i + 2].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;				borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 2].x == borad_ver[j].x) && (board[i + 2].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;				borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
						}
						if ((board[i + 2].x == board_ver_inv[j].x) && (board[i + 2].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
		}
		else if (k == 1)
		{
			if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 1].c1 = true;		board[i + 1].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 2;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
		}
		else if (k == 2)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((event.mouse.button & 1) && (borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e.x >= borad_ver[i].x) && (e.x <= borad_ver[i].x + 40) && (e.y >= borad_ver[i].y) && (e.y <= borad_ver[i].y + 40)) {
					borad_ver[i].c1 = true;			borad_ver[i].cell = true;
					borad_ver[i + 1].c1 = true;		borad_ver[i + 1].cell = true;
					borad_ver[i + 2].c1 = true;		borad_ver[i + 2].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					d1 = false;
					move = false;
					for (int j = 0; j < 37; j++) {
						if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
							board[j].c1 = true;			board[j].cell = true;
						}
						if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
							board[j].c1 = true;			board[j].cell = true;
						}
						if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
							board[j].c1 = true;			board[j].cell = true;
						}
						if ((borad_ver[i].x == board_ver_inv[j].x) && (borad_ver[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
						}
						if ((borad_ver[i + 1].x == board_ver_inv[j].x) && (borad_ver[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
						}
						if ((borad_ver[i + 2].x == board_ver_inv[j].x) && (borad_ver[i + 2].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
		}
		else if (k == 3)
		{
			if (i < 4)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 5].c1 = true;		board[i + 5].cell = true;
					board[i + 10].c1 = true;	board[i + 10].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 3 && i < 9)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 6].c1 = true;		board[i + 6].cell = true;
					board[i + 12].c1 = true;	board[i + 12].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;				borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;				borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;				borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 8 && i < 15)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 7].c1 = true;		board[i + 7].cell = true;
					board[i + 13].c1 = true;	board[i + 13].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 15 && i < 21)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 7].c1 = true;		board[i + 7].cell = true;
					board[i + 12].c1 = true;	board[i + 12].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 22 && i < 27)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 6].c1 = true;		board[i + 6].cell = true;
					board[i + 10].c1 = true;	board[i + 10].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}

		}
		else if (k == 4) {
			if (i < 4)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 4].c1 = true;		board[i + 4].cell = true;
					board[i + 5].c1 = true;		board[i + 5].cell = true;
					board[i + 10].c1 = true;	board[i + 10].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 4].x == borad_ver[j].x) && (board[i + 4].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 4].x == board_ver_inv[j].x) && (board[i + 4].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 3 && i < 9)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 5].c1 = true;		board[i + 5].cell = true;
					board[i + 6].c1 = true;		board[i + 6].cell = true;
					board[i + 12].c1 = true;	board[i + 12].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 8 && i < 15)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 6].c1 = true;		board[i + 6].cell = true;
					board[i + 7].c1 = true;		board[i + 7].cell = true;
					board[i + 13].c1 = true;	board[i + 13].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}

			if (i > 15 && i < 21)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 6].c1 = true;		board[i + 6].cell = true;
					board[i + 7].c1 = true;		board[i + 7].cell = true;
					board[i + 12].c1 = true;	board[i + 12].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 22 && i < 27)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 5].c1 = true;		board[i + 5].cell = true;
					board[i + 6].c1 = true;		board[i + 6].cell = true;
					board[i + 10].c1 = true;	board[i + 10].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
		}
		else if (k == 5) {
			if (i < 3)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 1].c1 = true;		board[i + 1].cell = true;
					board[i + 5].c1 = true;		board[i + 5].cell = true;
					board[i + 10].c1 = true;	board[i + 10].cell = true;
					board[i + 11].c1 = true;	board[i + 11].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 3 && i < 8)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 1].c1 = true;		board[i + 1].cell = true;
					board[i + 6].c1 = true;		board[i + 6].cell = true;
					board[i + 12].c1 = true;	board[i + 12].cell = true;
					board[i + 13].c1 = true;	board[i + 13].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 8 && i < 14)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 1].c1 = true;		board[i + 1].cell = true;
					board[i + 7].c1 = true;		board[i + 7].cell = true;
					board[i + 13].c1 = true;	board[i + 13].cell = true;
					board[i + 14].c1 = true;	board[i + 14].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 14].x == borad_ver[j].x) && (board[i + 14].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 14].x == board_ver_inv[j].x) && (board[i + 14].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 15 && i < 20)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 1].c1 = true;		board[i + 1].cell = true;
					board[i + 7].c1 = true;		board[i + 7].cell = true;
					board[i + 12].c1 = true;	board[i + 12].cell = true;
					board[i + 13].c1 = true;	board[i + 13].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 22 && i < 26)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].c1 = true;			board[i].cell = true;
					board[i + 1].c1 = true;		board[i + 1].cell = true;
					board[i + 6].c1 = true;		board[i + 6].cell = true;
					board[i + 10].c1 = true;	board[i + 10].cell = true;
					board[i + 11].c1 = true;	board[i + 11].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					move = false;
					d1 = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
							borad_ver[j].c1 = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
							board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
						}
					}
				}
				check_good();
			}
		}
	}
}
void update_logic(ALLEGRO_EVENT event) {
	if (move1) {
		for (int i = 0; i < 37; i++)
		{
			if (k1 == 0)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 2].c1 = true;		board[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 2].x == borad_ver[j].x) && (board[i + 2].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 2].x == board_ver_inv[j].x) && (board[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k1 == 1)
			{
				if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 2;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k1 == 2)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e1.x >= borad_ver[i].x) && (e1.x <= borad_ver[i].x + 40) && (e1.y >= borad_ver[i].y) && (e1.y <= borad_ver[i].y + 40)) {
						borad_ver[i].c1 = true;			borad_ver[i].cell = true;
						borad_ver[i + 1].c1 = true;		borad_ver[i + 1].cell = true;
						borad_ver[i + 2].c1 = true;		borad_ver[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						d1 = false;
						move1 = false;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].c1 = true;			board[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].c1 = true;			board[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].c1 = true;			board[j].cell = true;
							}
							if ((borad_ver[i].x == board_ver_inv[j].x) && (borad_ver[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board_ver_inv[j].x) && (borad_ver[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board_ver_inv[j].x) && (borad_ver[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k1 == 3)
			{
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;				borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

			}
			else if (k1 == 4) {
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 4].c1 = true;		board[i + 4].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 4].x == borad_ver[j].x) && (board[i + 4].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 4].x == board_ver_inv[j].x) && (board[i + 4].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k1 == 5) {
				if (i < 3)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 5].c1 = true;		board[i + 5].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						board[i + 11].c1 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 8)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 14)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						board[i + 14].c1 = true;	board[i + 14].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 14].x == borad_ver[j].x) && (board[i + 14].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 14].x == board_ver_inv[j].x) && (board[i + 14].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 20)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 7].c1 = true;		board[i + 7].cell = true;
						board[i + 12].c1 = true;	board[i + 12].cell = true;
						board[i + 13].c1 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 26)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e1.x >= board[i].x) && (e1.x <= board[i].x + 40) && (e1.y >= board[i].y) && (e1.y <= board[i].y + 40)) {
						board[i].c1 = true;			board[i].cell = true;
						board[i + 1].c1 = true;		board[i + 1].cell = true;
						board[i + 6].c1 = true;		board[i + 6].cell = true;
						board[i + 10].c1 = true;	board[i + 10].cell = true;
						board[i + 11].c1 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move1 = false;
						d1 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c1 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c1 = true;	board_ver_inv[j].cell = true;
							}
						}
					}
					check_good();
				}
			}
		}
	}
	else if (move2) {
		for (int i = 0; i < 37; i++)
		{
			if (k2 == 0)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 2].c2 = true;		board[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 2].x == borad_ver[j].x) && (board[i + 2].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 2].x == board_ver_inv[j].x) && (board[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k2 == 1)
			{
				if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 2;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;	board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k2 == 2)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e2.x >= borad_ver[i].x) && (e2.x <= borad_ver[i].x + 40) && (e2.y >= borad_ver[i].y) && (e2.y <= borad_ver[i].y + 40)) {
						borad_ver[i].c2 = true;			borad_ver[i].cell = true;
						borad_ver[i + 1].c2 = true;		borad_ver[i + 1].cell = true;
						borad_ver[i + 2].c2 = true;		borad_ver[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						d2 = false;
						move2 = false;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].c2 = true;		board[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].c2 = true;		board[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].c2 = true;		board[j].cell = true;
							}
							if ((borad_ver[i].x == board_ver_inv[j].x) && (borad_ver[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board_ver_inv[j].x) && (borad_ver[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board_ver_inv[j].x) && (borad_ver[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k2 == 3)
			{
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 12].c2 = true;		board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

			}
			else if (k2 == 4) {
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 4].c2 = true;		board[i + 4].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 4].x == borad_ver[j].x) && (board[i + 4].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 4].x == board_ver_inv[j].x) && (board[i + 4].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							else if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							else if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							else if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k2 == 5) {
				if (i < 3)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 5].c2 = true;		board[i + 5].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						board[i + 11].c2 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 8)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 14)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						board[i + 14].c2 = true;	board[i + 14].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 14].x == borad_ver[j].x) && (board[i + 14].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 14].x == board_ver_inv[j].x) && (board[i + 14].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 20)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 7].c2 = true;		board[i + 7].cell = true;
						board[i + 12].c2 = true;	board[i + 12].cell = true;
						board[i + 13].c2 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 26)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e2.x >= board[i].x) && (e2.x <= board[i].x + 40) && (e2.y >= board[i].y) && (e2.y <= board[i].y + 40)) {
						board[i].c2 = true;			board[i].cell = true;
						board[i + 1].c2 = true;		board[i + 1].cell = true;
						board[i + 6].c2 = true;		board[i + 6].cell = true;
						board[i + 10].c2 = true;	board[i + 10].cell = true;
						board[i + 11].c2 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move2 = false;
						d2 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c2 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c2 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
		}
	}
	else if (move3) {
		for (int i = 0; i < 37; i++)
		{
			if (k3 == 0)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 2].c3 = true;		board[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 2].x == borad_ver[j].x) && (board[i + 2].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 2].x == board_ver_inv[j].x) && (board[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k3 == 1)
			{
				if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 2;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k3 == 2)
			{
				if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
				{
					if ((event.mouse.button & 1) && (borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e3.x >= borad_ver[i].x) && (e3.x <= borad_ver[i].x + 40) && (e3.y >= borad_ver[i].y) && (e3.y <= borad_ver[i].y + 40)) {
						borad_ver[i].c3 = true;			borad_ver[i].cell = true;
						borad_ver[i + 1].c3 = true;		borad_ver[i + 1].cell = true;
						borad_ver[i + 2].c3 = true;		borad_ver[i + 2].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						d3 = false;
						move3 = false;
						for (int j = 0; j < 37; j++) {
							if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
								board[j].c3 = true;			board[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
								board[j].c3 = true;			board[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
								board[j].c3 = true;			board[j].cell = true;
							}
							if ((borad_ver[i].x == board_ver_inv[j].x) && (borad_ver[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 1].x == board_ver_inv[j].x) && (borad_ver[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((borad_ver[i + 2].x == board_ver_inv[j].x) && (borad_ver[i + 2].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k3 == 3)
			{
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;				borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;				borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 3;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

			}
			else if (k3 == 4) {
				if (i < 4)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 4].c3 = true;		board[i + 4].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 4].x == borad_ver[j].x) && (board[i + 4].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 4].x == board_ver_inv[j].x) && (board[i + 4].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 9)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 15)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}

				if (i > 15 && i < 21)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 27)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 4;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
			else if (k3 == 5) {
				if (i < 3)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 5].c3 = true;		board[i + 5].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						board[i + 11].c3 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 3 && i < 8)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 8 && i < 14)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						board[i + 14].c3 = true;	board[i + 14].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i + 14].x == borad_ver[j].x) && (board[i + 14].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;		borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
							if ((board[i + 14].x == board_ver_inv[j].x) && (board[i + 14].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;		board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 15 && i < 20)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 7].c3 = true;		board[i + 7].cell = true;
						board[i + 12].c3 = true;	board[i + 12].cell = true;
						board[i + 13].c3 = true;	board[i + 13].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
				if (i > 22 && i < 26)
				{
					if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e3.x >= board[i].x) && (e3.x <= board[i].x + 40) && (e3.y >= board[i].y) && (e3.y <= board[i].y + 40)) {
						board[i].c3 = true;			board[i].cell = true;
						board[i + 1].c3 = true;		board[i + 1].cell = true;
						board[i + 6].c3 = true;		board[i + 6].cell = true;
						board[i + 10].c3 = true;	board[i + 10].cell = true;
						board[i + 11].c3 = true;	board[i + 11].cell = true;
						al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						counter += 5;
						check_level();
						move3 = false;
						d3 = false;
						for (int j = 0; j < 37; j++) {
							if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
								borad_ver[j].c3 = true;			borad_ver[j].cell = true;
							}
							if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
							if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
								board_ver_inv[j].c3 = true;			board_ver_inv[j].cell = true;
							}
						}
						check_good();
					}
				}
			}
		}
	}
}

void user_input(ALLEGRO_EVENT event) {
	if (event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY || event.type == ALLEGRO_EVENT_MOUSE_AXES) {
		er.x = event.mouse.x;
		er.y = event.mouse.y;
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (((k1 == 0) || (k1 == 1) || (k1 == 3) || (k1 == 5)) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k1][0].x) && (event.mouse.x <= three_el[k1][0].x + 50) && (event.mouse.y >= three_el[k1][0].y) && (event.mouse.y <= three_el[k1][0].y + 50)) {
			move1 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k1 == 2) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k1][0].x) && (event.mouse.x <= three_el[k1][0].x + 50) && (event.mouse.y >= three_el[k1][0].y) && (event.mouse.y <= three_el[k1][0].y + 50)) {
			move1 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k1 == 4) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k1][0].x) && (event.mouse.x <= three_el[k1][0].x + 50) && (event.mouse.y >= three_el[k1][0].y) && (event.mouse.y <= three_el[k1][0].y + 50)) {
			move1 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if (((k2 == 0) || (k2 == 1) || (k2 == 3) || (k2 == 5)) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k2][1].x) && (event.mouse.x <= three_el[k2][1].x + 50) && (event.mouse.y >= three_el[k2][1].y) && (event.mouse.y <= three_el[k2][1].y + 50)) {
			move2 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k2 == 2) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k2][1].x) && (event.mouse.x <= three_el[k2][1].x + 50) && (event.mouse.y >= three_el[k2][1].y) && (event.mouse.y <= three_el[k2][1].y + 50)) {
			move2 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k2 == 4) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k2][1].x) && (event.mouse.x <= three_el[k2][1].x + 50) && (event.mouse.y >= three_el[k2][1].y) && (event.mouse.y <= three_el[k2][1].y + 50)) {
			move2 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if (((k3 == 0) || (k3 == 1) || (k3 == 3) || (k3 == 5)) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k3][2].x) && (event.mouse.x <= three_el[k3][2].x + 50) && (event.mouse.y >= three_el[k3][2].y) && (event.mouse.y <= three_el[k3][2].y + 50)) {
			move3 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k3 == 2) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k3][2].x) && (event.mouse.x <= three_el[k3][2].x + 50) && (event.mouse.y >= three_el[k3][2].y) && (event.mouse.y <= three_el[k3][2].y + 50)) {
			move3 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if ((k3 == 4) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k3][2].x) && (event.mouse.x <= three_el[k3][2].x + 50) && (event.mouse.y >= three_el[k3][2].y) && (event.mouse.y <= three_el[k3][2].y + 50)) {
			move3 = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		else if (event.mouse.button & 2)
		{
			move1 = false;
			move2 = false;
			move3 = false;
		}
	}
	update_logic(event);
}
void is_good() {
	int i = 0;
	int temp[7] = { 0 };
	for (int i = 0; i < 37; i++) {
		if (board[i].cell == false) {
			board[i].c1 = false;
			board[i].c2 = false;
			board[i].c3 = false;
			board[i].drawn = false;
		}
	}
	while (i < 4)
	{
		if (board[i].cell) {
			temp[0]++;
		}
		i++;
	}
	while (i > 3 && i < 9)
	{
		if (board[i].cell) {
			temp[1]++;
		}
		i++;
	}
	while (i > 8 && i < 15)
	{
		if (board[i].cell) {
			temp[2]++;
		}
		i++;
	}
	while (i > 14 && i < 22)
	{
		if (board[i].cell) {
			temp[3]++;
		}
		i++;
	}
	while (i > 21 && i < 28)
	{
		if (board[i].cell) {
			temp[4]++;
		}
		i++;
	}
	while (i > 27 && i < 33)
	{
		if (board[i].cell) {
			temp[5]++;
		}
		i++;
	}
	while (i > 32 && i < 37)
	{
		if (board[i].cell) {
			temp[6]++;
		}
		i++;
	}
	if (temp[0] == 4) {
		for (int j = 0; j < 4; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
				{
					borad_ver[k].cell = false;
				}
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
				{
					board_ver_inv[k].cell = false;
				}
			}
		}
		draww = true;
		temp[0] = 0;
		counter += 4;
		//al_stop_sample(&soundid);
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp[1] == 5) {
		for (int j = 4; j < 9; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[1] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[2] == 6) {
		for (int j = 9; j < 15; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[2] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[3] == 7) {
		for (int j = 15; j < 22; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;;
		temp[3] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 7;
		check_level();
	}
	if (temp[4] == 6) {
		for (int j = 22; j < 28; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[4] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[5] == 5) {
		for (int j = 28; j < 33; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[5] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[6] == 4) {
		for (int j = 33; j < 37; j++) {
			board[j].wow = true;
			board[j].c1 = false;
			board[j].c2 = false;
			board[j].c3 = false;
			board[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[6] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}
}
void is_good_ver() {
	int i = 0;
	int temp[7] = { 0 };
	while (i < 4)
	{
		if (borad_ver[i].cell) {
			temp[0]++;
		}
		i++;
	}
	while (i > 3 && i < 9)
	{
		if (borad_ver[i].cell) {
			temp[1]++;
		}
		i++;
	}
	while (i > 8 && i < 15)
	{
		if (borad_ver[i].cell) {
			temp[2]++;
		}
		i++;
	}
	while (i > 14 && i < 22)
	{
		if (borad_ver[i].cell) {
			temp[3]++;
		}
		i++;
	}
	while (i > 21 && i < 28)
	{
		if (borad_ver[i].cell) {
			temp[4]++;
		}
		i++;
	}
	while (i > 27 && i < 33)
	{
		if (borad_ver[i].cell) {
			temp[5]++;
		}
		i++;
	}
	while (i > 32 && i < 37)
	{
		if (borad_ver[i].cell) {
			temp[6]++;
		}
		i++;
	}
	if (temp[0] == 4) {
		for (int j = 0; j < 4; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[0] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}
	if (temp[1] == 5) {
		for (int j = 4; j < 9; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[1] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[2] == 6) {
		for (int j = 9; j < 15; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[2] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[3] == 7) {
		for (int j = 15; j < 22; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[3] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 7;
		check_level();
	}
	if (temp[4] == 6) {
		for (int j = 22; j < 28; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[4] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[5] == 5) {
		for (int j = 28; j < 33; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[5] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[6] == 4) {
		for (int j = 33; j < 37; j++) {

			borad_ver[j].c1 = false;
			borad_ver[j].c2 = false;
			borad_ver[j].c3 = false;
			borad_ver[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp[6] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}
}
void is_good_ver_inv() {
	int i = 0;
	int temp[7] = { 0 };
	while (i < 4)
	{
		if (board_ver_inv[i].cell) {
			temp[0]++;
		}
		i++;
	}
	while (i > 3 && i < 9)
	{
		if (board_ver_inv[i].cell) {
			temp[1]++;
		}
		i++;
	}
	while (i > 8 && i < 15)
	{
		if (board_ver_inv[i].cell) {
			temp[2]++;
		}
		i++;
	}
	while (i > 14 && i < 22)
	{
		if (board_ver_inv[i].cell) {
			temp[3]++;
		}
		i++;
	}
	while (i > 21 && i < 28)
	{
		if (board_ver_inv[i].cell) {
			temp[4]++;
		}
		i++;
	}
	while (i > 27 && i < 33)
	{
		if (board_ver_inv[i].cell) {
			temp[5]++;
		}
		i++;
	}
	while (i > 32 && i < 37)
	{
		if (board_ver_inv[i].cell) {
			temp[6]++;
		}
		i++;
	}
	if (temp[0] == 4) {
		for (int j = 0; j < 4; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[0] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}
	if (temp[1] == 5) {
		for (int j = 4; j < 9; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[1] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[2] == 6) {
		for (int j = 9; j < 15; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[2] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[3] == 7) {
		for (int j = 15; j < 22; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww == true;
		temp[3] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 7;
		check_level();
	}
	if (temp[4] == 6) {
		for (int j = 22; j < 28; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[4] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 6;
		check_level();
	}
	if (temp[5] == 5) {
		for (int j = 28; j < 33; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[5] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 5;
		check_level();
	}
	if (temp[6] == 4) {
		for (int j = 33; j < 37; j++) {

			board_ver_inv[j].c1 = false;
			board_ver_inv[j].c2 = false;
			board_ver_inv[j].c3 = false;
			board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp[6] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 4;
		check_level();
	}

}
void is_good_tr() {
	int temp1[6] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		if (borad_ver[i].cell && board_ver_inv[i].cell)
		{
			temp1[0]++;
		}
		if (borad_ver[i].cell && board[i].cell)
		{
			temp1[1]++;
		}
		if (board_ver_inv[i + 33].cell && board[i].cell)
		{
			temp1[2]++;
		}
		if (board_ver_inv[i].cell && board[i + 33].cell)
		{
			temp1[3]++;
		}
		if (borad_ver[i + 33].cell && board[i + 33].cell)
		{
			temp1[4]++;
		}
		if (borad_ver[i + 33].cell && board_ver_inv[i + 33].cell)
		{
			temp1[5]++;
		}
	}
	if (temp1[0] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board_ver_inv[i].c1 = false;
			board_ver_inv[i].c2 = false;
			board_ver_inv[i].c3 = false;
			board_ver_inv[i].cell = false;
			borad_ver[i].c1 = false;
			borad_ver[i].c2 = false;
			borad_ver[i].c3 = false;
			borad_ver[i].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[i].x == board[k].x) && (borad_ver[i].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board_ver_inv[i].x == board[k].x) && (board_ver_inv[i].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[i].x == board_ver_inv[k].x) && (borad_ver[i].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board_ver_inv[i].x == borad_ver[k].x) && (board_ver_inv[i].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp1[0] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[1] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board[i].c1 = false;
			board[i].c2 = false;
			board[i].c3 = false;
			board[i].cell = false;
			board[i].wow = true;
			borad_ver[i].c1 = false;
			borad_ver[i].c2 = false;
			borad_ver[i].c3 = false;
			borad_ver[i].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((borad_ver[i].x == board_ver_inv[k].x) && (borad_ver[i].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board[i].x == board_ver_inv[k].x) && (board[i].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((borad_ver[i].x == board[k].x) && (borad_ver[i].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board[i].x == borad_ver[k].x) && (board[i].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp1[1] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[2] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board[i].c1 = false;
			board[i].c2 = false;
			board[i].c3 = false;
			board[i].cell = false;
			board[i].wow = true;
			board_ver_inv[i + 33].c1 = false;
			board_ver_inv[i + 33].c2 = false;
			board_ver_inv[i + 33].c3 = false;
			board_ver_inv[i + 33].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[i + 33].x == borad_ver[k].x) && (board_ver_inv[i + 33].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[i].x == borad_ver[k].x) && (board[i].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board_ver_inv[i + 33].x == board[k].x) && (board_ver_inv[i + 33].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((board[i].x == board_ver_inv[k].x) && (board[i].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
			}
		}
		draww = true;
		temp1[2] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[3] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board[i + 33].c1 = false;
			board[i + 33].c2 = false;
			board[i + 33].c3 = false;
			board[i + 33].cell = false;
			board[i + 33].wow = true;
			board_ver_inv[i].c1 = false;
			board_ver_inv[i].c2 = false;
			board_ver_inv[i].c3 = false;
			board_ver_inv[i].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[i + 33].x == borad_ver[k].x) && (board[i + 33].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board_ver_inv[i].x == borad_ver[k].x) && (board_ver_inv[i].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((board[i + 33].x == board_ver_inv[k].x) && (board[i + 33].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board_ver_inv[i].x == board[k].x) && (board_ver_inv[i].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
			}
		}
		draww = true;
		temp1[3] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[4] == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			board[i + 33].c1 = false;
			board[i + 33].c2 = false;
			board[i + 33].c3 = false;
			board[i + 33].cell = false;
			board[i + 33].wow = true;
			borad_ver[i + 33].c1 = false;
			borad_ver[i + 33].c2 = false;
			borad_ver[i + 33].c3 = false;
			borad_ver[i + 33].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board[i + 33].x == board_ver_inv[k].x) && (board[i + 33].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((borad_ver[i + 33].x == board_ver_inv[k].x) && (borad_ver[i + 33].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board[i + 33].x == borad_ver[k].x) && (board[i + 33].y == borad_ver[k].y))
					borad_ver[k].cell = false;
				if ((borad_ver[i + 33].x == board[k].x) && (borad_ver[i + 33].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
			}
		}
		draww = true;
		temp1[4] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
	if (temp1[5] == 4) {
		for (int i = 0; i < 4; i++)
		{
			board_ver_inv[i + 33].c1 = false;
			board_ver_inv[i + 33].c2 = false;
			board_ver_inv[i + 33].c3 = false;
			board_ver_inv[i + 33].cell = false;
			borad_ver[i + 33].c1 = false;
			borad_ver[i + 33].c2 = false;
			borad_ver[i + 33].c3 = false;
			borad_ver[i + 33].cell = false;
			for (int k = 0; k < 37; k++)
			{
				if ((board_ver_inv[i + 33].x == board[k].x) && (board_ver_inv[i + 33].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[i + 33].x == board[k].x) && (borad_ver[i + 33].y == board[k].y)) {
					board[k].cell = false;
					board[k].wow = true;
				}
				if ((borad_ver[i + 33].x == board_ver_inv[k].x) && (borad_ver[i + 33].y == board_ver_inv[k].y))
					board_ver_inv[k].cell = false;
				if ((board_ver_inv[i + 33].x == borad_ver[k].x) && (board_ver_inv[i + 33].y == borad_ver[k].y))
					borad_ver[k].cell = false;
			}
		}
		draww = true;
		temp1[5] = 0;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		counter += 8;
		check_level();
	}
}
void check_good() {
	is_good_tr();
	is_good_ver_inv();
	is_good_ver();
	is_good();
}
bool check_end_case(int k) {
	bool temp = false;
	for (int i = 0; i < 37; i++)
	{
		if (k == 0)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k == 1)
		{
			if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k == 2)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k == 3)
		{
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}

		}
		else if (k == 4) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}

			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false))
				{
					temp = true;
				}
			}
		}
		else if (k == 5) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 8 && i < 14)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false))
				{
					temp = true;
				}
			}
			if (i > 15 && i < 20)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false))
				{
					temp = true;
				}
			}
			if (i > 22 && i < 26)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
		}
	}
	return temp;
}
void check_end() {
	endcase = false;
	if (!d1 && d2 && d3) {
		if (!check_end_case(k2) && !check_end_case(k3))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "Your Score", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}

	}
	else if (!d1 && !d2 && d3)
	{
		if (!check_end_case(k3))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (!d1 && d2 && !d3)
	{
		if (!check_end_case(k2))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (d1 && d2 && !d3)
	{
		if (!check_end_case(k1) && !check_end_case(k2))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (d1 && !d2 && d3)
	{
		if (!check_end_case(k1) && !check_end_case(k3))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (d1 && !d2 && !d3)
	{
		if (!check_end_case(k1))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();

		}
	}
	else if (d1 && d2 && d3)
	{
		if (!check_end_case(k1) && !check_end_case(k2) && !check_end_case(k3))
		{
			al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			int i = al_show_native_message_box(display, "Game End", "You Finished :D", "You reached dead end", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			done = true;
			done_men = false;
			endcase = true;
			save();
			shutdown();
			init_menu();
			game_menu();
		}
	}
}
void high_score() {
	int temp = -1;
	char i[10];
	file = fopen("HighScore.txt", "r");
	fgets(i, 10, file);
	fclose(file);
	temp = atoi(i);
	if (counter > temp)
	{
		file = fopen("HighScore.txt", "w");
		sprintf(i, "%d", counter);
		fputs(i, file);
		fclose(file);
	}
	file = fopen("HighScore.txt", "r");
	fgets(score, 10, file);
	fclose(file);
}
void shutdown(void)
{
	if (done) {
		if (event_queue)
			al_destroy_event_queue(event_queue);
		if (timer) {
			al_destroy_timer(timer);
		}
		if (display)
			al_destroy_display(display);
		if (sound)
			al_destroy_sample(sound);
	}
}
void shutdown_menu(void)
{
	if (done_men) {
		if (event_queue_menu)
			al_destroy_event_queue(event_queue_menu);
		if (timer_menu) {
			al_destroy_timer(timer_menu);
		}
		if (display_menu)
			al_destroy_display(display_menu);
	}
}
void draw_shape(int k, ele_pos e) {
	for (int i = 0; i < 37; i++)
	{
		if (k == 0)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 1].check = true;				board[i + 2].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 1].check = false;				board[i + 2].check = false;
				}
			}
			for (int i = 0; i < 37; i++) {
				if (board[i].check) {
					q[i] = q9;
					al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
				}
			}
		}
		else if (k == 1)
		{
			if ((i < 3) || (i > 3 && i < 8) || (i > 8 && i < 14) || (i > 14 && i < 21) || (i > 21 && i < 27) || (i > 27 && i < 32) || (i > 32 && i < 36))
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;				board[i + 1].check = true;
				}
				else
				{
					board[i].check = false;				board[i + 1].check = false;
				}
			}
			for (int i = 0; i < 37; i++) {
				if (board[i].check) {
					q[i] = q9;
					al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
				}
			}
		}
		else if (k == 2)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((borad_ver[i].cell == false) && (borad_ver[i + 1].cell == false) && (borad_ver[i + 2].cell == false) && (e.x >= borad_ver[i].x) && (e.x <= borad_ver[i].x + 40) && (e.y >= borad_ver[i].y) && (e.y <= borad_ver[i].y + 40)) {
					borad_ver[i].check = true;				borad_ver[i + 1].check = true;				borad_ver[i + 2].check = true;
					for (int j = 0; j < 37; j++) {
						if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
							board[j].check = true;
						}
						if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
							board[j].check = true;
						}
						if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
							board[j].check = true;
						}
					}
				}
				else
				{
					borad_ver[i].check = false;				borad_ver[i + 1].check = false;				borad_ver[i + 2].check = false;
					for (int j = 0; j < 37; j++) {
						if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
							board[j].check = false;
						}
						if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
							board[j].check = false;
						}
						if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
							board[j].check = false;
						}
					}
				}
			}
			for (int i = 0; i < 37; i++) {
				if (board[i].check) {
					q[i] = q9;
					al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
				}
			}
		}
		else if (k == 3)
		{
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 5].check = true;			board[i + 10].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 5].check = false;			board[i + 10].check = false;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 6].check = true;			board[i + 12].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 6].check = false;			board[i + 12].check = false;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 7].check = true;			board[i + 13].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 7].check = false;			board[i + 13].check = false;
				}
			}
			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 7].check = true;			board[i + 12].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 7].check = false;			board[i + 12].check = false;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 6].check = true;			board[i + 10].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 6].check = false;			board[i + 10].check = false;
				}
			}
			for (int i = 0; i < 37; i++) {
				if (board[i].check) {
					q[i] = q9;
					al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
				}
			}

		}
		else if (k == 4) {
			if (i < 4)
			{
				if ((board[i].cell == false) && (board[i + 4].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 4].check = true;			board[i + 5].check = true;			board[i + 10].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 4].check = false;			board[i + 5].check = false;			board[i + 10].check = false;
				}
			}
			if (i > 3 && i < 9)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 5].check = true;			board[i + 6].check = true;			board[i + 12].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 5].check = false;			board[i + 6].check = false;			board[i + 12].check = false;
				}
			}
			if (i > 8 && i < 15)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 6].check = true;			board[i + 7].check = true;			board[i + 13].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 6].check = false;			board[i + 7].check = false;			board[i + 13].check = false;
				}
			}

			if (i > 15 && i < 21)
			{
				if ((board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 6].check = true;			board[i + 7].check = true;			board[i + 12].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 6].check = false;			board[i + 7].check = false;			board[i + 12].check = false;
				}
			}
			if (i > 22 && i < 27)
			{
				if ((board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;			board[i + 5].check = true;			board[i + 6].check = true;			board[i + 10].check = true;
				}
				else
				{
					board[i].check = false;			board[i + 5].check = false;			board[i + 6].check = false;			board[i + 10].check = false;
				}
			}
			for (int i = 0; i < 37; i++) {
				if (board[i].check) {
					q[i] = q9;
					al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
				}
			}
		}
		else if (k == 5) {
			if (i < 3)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;	board[i + 1].check = true;	board[i + 5].check = true;	board[i + 10].check = true;	board[i + 11].check = true;
				}
				else
				{
					board[i].check = false;	board[i + 1].check = false;	board[i + 5].check = false;	board[i + 10].check = false; board[i + 11].check = false;
				}
			}
			if (i > 3 && i < 8)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;	board[i + 1].check = true;	board[i + 6].check = true;	board[i + 12].check = true;	board[i + 13].check = true;
				}
				else
				{
					board[i].check = false;	board[i + 1].check = false;	board[i + 6].check = false;	board[i + 12].check = false; board[i + 13].check = false;
				}
			}
			if (i > 8 && i < 14)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;	board[i + 1].check = true;	board[i + 7].check = true;	board[i + 13].check = true;	board[i + 14].check = true;
				}
				else
				{
					board[i].check = false;	board[i + 1].check = false;	board[i + 7].check = false;	board[i + 13].check = false; board[i + 14].check = false;
				}
			}
			if (i > 15 && i < 20)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;	board[i + 1].check = true;	board[i + 7].check = true;	board[i + 12].check = true;	board[i + 13].check = true;
				}
				else
				{
					board[i].check = false;	board[i + 1].check = false;	board[i + 7].check = false;	board[i + 12].check = false; board[i + 13].check = false;
				}
			}
			if (i > 22 && i < 26)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].check = true;	board[i + 1].check = true;	board[i + 6].check = true;	board[i + 10].check = true;	board[i + 11].check = true;
				}
				else
				{
					board[i].check = false;	board[i + 1].check = false;	board[i + 6].check = false;	board[i + 10].check = false; board[i + 11].check = false;
				}
			}
			for (int i = 0; i < 37; i++) {
				if (board[i].check) {
					q[i] = q9;
					al_draw_tinted_bitmap(q[i], al_map_rgb(255, 105, 97), board[i].x - 20, board[i].y, 0);
				}
			}
		}
	}
}
void draw() {
	if (!d1 && !d2 && !d3)
		doit = true;
	else
		doit = false;

	if (doit)
	{
		srand(time(NULL));
		if (level == 1) {
			k1 = rand() % 4;
			k2 = rand() % 4;
			k3 = rand() % 4;
		}
		else {
			k1 = rand() % 4 + 2;
			k2 = rand() % 4 + 2;
			k3 = rand() % 4 + 2;
		}
		d1 = true; d2 = true; d3 = true;
		doit = false;
	}
	if (move1 && !move2 && !move3)
		e1 = er;
	else
		e1 = three_el[k1][0];
	if (move2 && !move1 && !move3)
		e2 = er;
	else
		e2 = three_el[k2][1];
	if (move3 && !move2 && !move1)
		e3 = er;
	else
		e3 = three_el[k3][2];
	al_draw_bitmap(image, 50, 50, 0);
	for (int i = 0; i < 37; i++) {
		board[i].check = false;
	}
	///////////start
	if (move1) {
		draw_shape(k1, e1);

	}
	else if (move2) {
		draw_shape(k2, e2);
	}
	else if (move3) {
		draw_shape(k3, e3);
	}
	//////////end
	if (d1) {
		switch (k1)
		{
		case 0:
			al_draw_tinted_bitmap(q1, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
			break;
		case 1:
			al_draw_tinted_bitmap(q2, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
			break;
		case 2:
			al_draw_tinted_bitmap(q3, al_map_rgb(255, 0, 0), e1.x, e1.y - 70, 0);
			break;
		case 3:
			al_draw_tinted_bitmap(q4, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
			break;
		case 4:
			al_draw_tinted_bitmap(q5, al_map_rgb(255, 0, 0), e1.x, e1.y - 35, 0);
			break;
		case 5:
			al_draw_tinted_bitmap(q6, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
			break;
		default:
			break;
		}
	}
	if (d2) {
		switch (k2)
		{
		case 0:
			al_draw_tinted_bitmap(q1, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
			break;
		case 1:
			al_draw_tinted_bitmap(q2, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
			break;
		case 2:
			al_draw_tinted_bitmap(q3, al_map_rgb(255, 255, 0), e2.x, e2.y - 70, 0);
			break;
		case 3:
			al_draw_tinted_bitmap(q4, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
			break;
		case 4:
			al_draw_tinted_bitmap(q5, al_map_rgb(255, 255, 0), e2.x, e2.y - 35, 0);
			break;
		case 5:
			al_draw_tinted_bitmap(q6, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
			break;
		default:
			break;
		}
	}
	if (d3) {
		switch (k3)
		{
		case 0:
			al_draw_tinted_bitmap(q1, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
			break;
		case 1:
			al_draw_tinted_bitmap(q2, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
			break;
		case 2:
			al_draw_tinted_bitmap(q3, al_map_rgb(255, 0, 255), e3.x, e3.y - 70, 0);
			break;
		case 3:
			al_draw_tinted_bitmap(q4, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
			break;
		case 4:
			al_draw_tinted_bitmap(q5, al_map_rgb(255, 0, 255), e3.x, e3.y - 35, 0);
			break;
		case 5:
			al_draw_tinted_bitmap(q6, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < 37; i++) {
		if (board[i].c1 && !board[i].c2 && !board[i].c3 && board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 0), board[i].x - 20, board[i].y, 0);
		}
		else if (board[i].c2 && !board[i].c1 && !board[i].c3 && board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 255, 0), board[i].x - 20, board[i].y, 0);
		}
		else if (board[i].c3 && !board[i].c1 && !board[i].c2 && board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 255), board[i].x - 20, board[i].y, 0);
		}
	}
	for (int i = 0; i < 37; i++) {
		if (board[i].c1 && !board[i].c2 && !board[i].c3 && !board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 0), board[i].x - 20, board[i].y, 0);
			al_flip_display();
			al_play_sample(pop, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			al_rest(0.16);
			board[i].drawn = true;
		}
		else if (board[i].c2 && !board[i].c1 && !board[i].c3 && !board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 255, 0), board[i].x - 20, board[i].y, 0);
			al_flip_display();
			al_play_sample(pop, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			al_rest(0.16);
			board[i].drawn = true;
		}
		else if (board[i].c3 && !board[i].c1 && !board[i].c2 && !board[i].drawn) {
			q[i] = q9;
			al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 255), board[i].x - 20, board[i].y, 0);
			al_flip_display();
			al_play_sample(pop, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			al_rest(0.16);
			board[i].drawn = true;
		}
	}
	for (int j = 0; j < 37; j++) {
		if (board[j].wow) {
			q[j] = q10;
			al_draw_bitmap(q[j], board[j].x - 20, board[j].y, 0);
			al_flip_display();
			al_play_sample(shoot, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			al_rest(0.1);
		}
	}
}
void check_level() {
	if (counter > 100)
	{
		level = 2;
		levsound++;
		while (levsound == 2)
		{
			al_play_sample(level1, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			levsound++;
		}
	}
}
void game_loop(void)
{
	bool redraw = true;
	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
			shutdown();
			save();
			done_men = false;
			init_menu();
			game_menu();
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			check_end();
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
				shutdown();
				save();
				done_men = false;
				init_menu();
				game_menu();
			}
		}
		user_input(event);
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			high_score();
			al_draw_textf(font, al_map_rgb(255, 255, 255), 850, 10, 0, "SCORE: %d", counter);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 850, 80, 0, "LEVEL: %d", level);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 850, 150, 0, "HIGH SCORE: %s", score);
			draw();
				ALLEGRO_MOUSE_STATE state;

			al_get_mouse_state(&state);
			if (state.buttons & 1) {
			// Primary (e.g. left) mouse button is held.
			printf("Mouse position: (%d, %d)--", state.x, state.y);
			}
			if (state.buttons & 2) {
			// Secondary (e.g. right) mouse button is held.
			}
			if (state.buttons & 4) {
			// Tertiary (e.g. middle) mouse button is held.
			}
			al_flip_display();
			if (draww == true) {
				al_rest(0.15);
				for (int i = 0; i < 37; i++)
					board[i].wow = false;
			}
			draww = false;
			check_end();

		}
	}
}
void save() {
	if (done)
	{
		cases c = { k1,k2,k3,counter,level,d1,d2,d3,endcase };
		board_file = fopen("board.dat", "w");
		fwrite(&board, sizeof(board), 1, board_file);
		fclose(board_file);
		score_file = fopen("score.dat", "w");
		fwrite(&c, sizeof(cases), 1, score_file);
		fclose(score_file);
	}
}
void init_resum() {
	done_men = false;
	cases c;
	ele_pos pos[37];
	int i = 0;
	board_file = fopen("board.dat", "r");
	fread(&pos, sizeof(pos), 1, board_file);
	for (int i = 0; i < 37; i++)
		board[i] = pos[i];
	fclose(board_file);
	score_file = fopen("score.dat", "r");
	fread(&c, sizeof(cases), 1, score_file);
	k1 = c.k1;
	k2 = c.k2;
	k3 = c.k3;
	d1 = c.d1;
	d2 = c.d2;
	d3 = c.d3;
	counter = c.counter;
	level = c.level;
	endcase = c.endcase;
	fclose(score_file);
}

int main(int argc, char* argv[])
{
	//init();
	init_menu();
	game_menu();
	//al_play_sample(sound, 0.1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &soundid);
	//game_loop();
	//shutdown_menu();
	//system("pause");
}*/

/*void is_good() {
int i = 0;
int temp[7] = {0};
for (int i = 0; i < 37; i++) {
if (board[i].cell == false) {
board[i].color[0] = false;
board[i].color[1] = false;
board[i].color[2] = false;
board[i].drawn = false;
}
}
while (i < 4)
{
if (board[i].cell) {
temp[0]++;
}
i++;
}
while (i > 3 &&  i < 9)
{
if (board[i].cell) {
temp[1]++;
}
i++;
}
while (i > 8 && i < 15)
{
if (board[i].cell) {
temp[2]++;
}
i++;
}
while (i > 14 && i < 22)
{
if (board[i].cell) {
temp[3]++;
}
i++;
}
while (i > 21 && i < 28)
{
if (board[i].cell) {
temp[4]++;
}
i++;
}
while (i > 27 && i < 33)
{
if (board[i].cell) {
temp[5]++;
}
i++;
}
while (i > 32 && i < 37)
{
if (board[i].cell) {
temp[6]++;
}
i++;
}
if (temp[0] == 4) {
for (int j = 0; j < 4; j++) {
board[j].wow = true;
board[j].color[0] = false;
board[j].color[1] = false;
board[j].color[2] = false;
board[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
{
borad_ver[k].cell = false;
}
if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
{
board_ver_inv[k].cell = false;
}
}
}
draww = true;
temp[0] = 0;
counter += 4;
//al_stop_sample(&soundid);
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
check_level();
}
if (temp[1] == 5) {
for (int j = 4; j < 9; j++) {
board[j].wow = true;
board[j].color[0] = false;
board[j].color[1] = false;
board[j].color[2] = false;
board[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[1] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 5;
check_level();
}
if (temp[2] == 6) {
for (int j = 9; j < 15; j++) {
board[j].wow = true;
board[j].color[0] = false;
board[j].color[1] = false;
board[j].color[2] = false;
board[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[2] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 6;
check_level();
}
if (temp[3] == 7) {
for (int j = 15; j < 22; j++) {
board[j].wow = true;
board[j].color[0] = false;
board[j].color[1] = false;
board[j].color[2] = false;
board[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;;
temp[3] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 7;
check_level();
}
if (temp[4] == 6) {
for (int j = 22; j < 28; j++) {
board[j].wow = true;
board[j].color[0] = false;
board[j].color[1] = false;
board[j].color[2] = false;
board[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[4] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 6;
check_level();
}
if (temp[5] == 5) {
for (int j = 28; j < 33; j++) {
board[j].wow = true;
board[j].color[0] = false;
board[j].color[1] = false;
board[j].color[2] = false;
board[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[5] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 5;
check_level();
}
if (temp[6] == 4) {
for (int j = 33; j < 37; j++) {
board[j].wow = true;
board[j].color[0] = false;
board[j].color[1] = false;
board[j].color[2] = false;
board[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board[j].x == borad_ver[k].x) && (board[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board[j].x == board_ver_inv[k].x) && (board[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[6] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 4;
check_level();
}
}
void is_good_ver() {
int i = 0;
int temp[7] = { 0 };
while (i < 4)
{
if (borad_ver[i].cell) {
temp[0]++;
}
i++;
}
while (i > 3 && i < 9)
{
if (borad_ver[i].cell) {
temp[1]++;
}
i++;
}
while (i > 8 && i < 15)
{
if (borad_ver[i].cell) {
temp[2]++;
}
i++;
}
while (i > 14 && i < 22)
{
if (borad_ver[i].cell) {
temp[3]++;
}
i++;
}
while (i > 21 && i < 28)
{
if (borad_ver[i].cell) {
temp[4]++;
}
i++;
}
while (i > 27 && i < 33)
{
if (borad_ver[i].cell) {
temp[5]++;
}
i++;
}
while (i > 32 && i < 37)
{
if (borad_ver[i].cell) {
temp[6]++;
}
i++;
}
if (temp[0] == 4) {
for (int j = 0; j < 4; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[0] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 4;
check_level();
}
if (temp[1] == 5) {
for (int j = 4; j < 9; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[1] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 5;
check_level();
}
if (temp[2] == 6) {
for (int j = 9; j < 15; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[2] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 6;
check_level();
}
if (temp[3] == 7) {
for (int j = 15; j < 22; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[3] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 7;
check_level();
}
if (temp[4] == 6) {
for (int j = 22; j < 28; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[4] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 6;
check_level();
}
if (temp[5] == 5) {
for (int j = 28; j < 33; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[5] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 5;
check_level();
}
if (temp[6] == 4) {
for (int j = 33; j < 37; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp[6] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 4;
check_level();
}
}
void is_good_ver_inv() {
int i = 0;
int temp[7] = { 0 };
while (i < 4)
{
if (board_ver_inv[i].cell) {
temp[0]++;
}
i++;
}
while (i > 3 && i < 9)
{
if (board_ver_inv[i].cell) {
temp[1]++;
}
i++;
}
while (i > 8 && i < 15)
{
if (board_ver_inv[i].cell) {
temp[2]++;
}
i++;
}
while (i > 14 && i < 22)
{
if (board_ver_inv[i].cell) {
temp[3]++;
}
i++;
}
while (i > 21 && i < 28)
{
if (board_ver_inv[i].cell) {
temp[4]++;
}
i++;
}
while (i > 27 && i < 33)
{
if (board_ver_inv[i].cell) {
temp[5]++;
}
i++;
}
while (i > 32 && i < 37)
{
if (board_ver_inv[i].cell) {
temp[6]++;
}
i++;
}
if (temp[0] == 4) {
for (int j = 0; j < 4; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp[0] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 4;
check_level();
}
if (temp[1] == 5) {
for (int j = 4; j < 9; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp[1] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 5;
check_level();
}
if (temp[2] == 6) {
for (int j = 9; j < 15; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp[2] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 6;
check_level();
}
if (temp[3] == 7) {
for (int j = 15; j < 22; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww == true;
temp[3] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 7;
check_level();
}
if (temp[4] == 6) {
for (int j = 22; j < 28; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp[4] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 6;
check_level();
}
if (temp[5] == 5) {
for (int j = 28; j < 33; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp[5] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 5;
check_level();
}
if (temp[6] == 4) {
for (int j = 33; j < 37; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp[6] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 4;
check_level();
}

}
void is_good_tr() {
int temp2[6] = { 0 };
int temp3[6] = { 0 };
int temp4[6] = { 0 };
if (board[0].cell && board[1].cell &&board[2].cell &&board[3].cell) {
for (int i = 4; i < 22; i++) {
if (borad_ver[i].cell && i < 9)
temp2[0]++;
if (borad_ver[i].cell && i > 8 && i < 15)
temp2[1]++;
if (borad_ver[i].cell && i > 14 && i < 22)
temp2[2]++;
}
for (int i = 15; i < 37; i++) {
if (board_ver_inv[i].cell && i < 9)
temp2[3]++;
if (board_ver_inv[i].cell && i > 8 && i < 15)
temp2[4]++;
if (board_ver_inv[i].cell && i > 14 && i < 22)
temp2[5]++;
}
}
if (board[33].cell && board[34].cell &&board[35].cell &&board[36].cell) {
for (int i = 4; i < 22; i++) {
if (board_ver_inv[i].cell && i < 9)
temp3[0]++;
if (board_ver_inv[i].cell && i > 8 && i < 15)
temp3[1]++;
if (board_ver_inv[i].cell && i > 14 && i < 22)
temp3[2]++;
}
for (int i = 15; i < 37; i++) {
if (borad_ver[i].cell && i < 9)
temp3[3]++;
if (borad_ver[i].cell && i > 8 && i < 15)
temp3[4]++;
if (borad_ver[i].cell && i > 14 && i < 22)
temp3[5]++;
}
}
if (temp2[0] == 5 || temp2[1] == 6 || temp2[2] == 7 || temp2[3] == 7 || temp2[4] == 6 || temp2[5] == 5) {
for (int i = 0; i < 4; i++) {
board[i].wow = true;
board[i].cell = false;
board[i].color[0] = false;
board[i].color[1] = false;
board[i].color[2] = false;
}
if (temp2[0] == 5) {
for (int j = 4; j < 9; j++) {
borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp2[0] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 9;
check_level();
}
if (temp2[1] == 6) {
for (int j = 9; j < 15; j++) {
borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp2[1] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 10;
check_level();
}
if (temp2[2] == 7) {
for (int j = 15; j < 22; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp2[2] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 11;
check_level();
}
if (temp2[3] == 7) {
for (int j = 15; j < 22; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp2[3] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 11;
check_level();
}
if (temp2[4] == 6) {
for (int j = 22; j < 28; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp2[4] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 10;
check_level();
}
if (temp2[5] == 5) {
for (int j = 28; j < 33; j++) {
board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp2[5] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 9;
check_level();
}
}
if (temp3[0] == 5 || temp3[1] == 6 || temp3[2] == 7 || temp3[3] == 7 || temp3[4] == 6 || temp3[5] == 5) {
for (int i = 33; i < 37; i++) {
board[i].wow = true;
board[i].cell = false;
board[i].color[0] = false;
board[i].color[1] = false;
board[i].color[2] = false;
}
if (temp3[0] == 5) {
for (int j = 4; j < 9; j++) {
board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp3[0] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 9;
check_level();
}
if (temp3[1] == 6) {
for (int j = 9; j < 15; j++) {
board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp3[1] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 10;
check_level();
}
if (temp3[2] == 7) {
for (int j = 15; j < 22; j++) {

board_ver_inv[j].color[0] = false;
board_ver_inv[j].color[1] = false;
board_ver_inv[j].color[2] = false;
board_ver_inv[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[j].x == borad_ver[k].x) && (board_ver_inv[j].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp3[2] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 11;
check_level();
}
if (temp3[3] == 7) {
for (int j = 15; j < 22; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp3[3] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 11;
check_level();
}
if (temp3[4] == 6) {
for (int j = 22; j < 28; j++) {

borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp3[4] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 10;
check_level();
}
if (temp3[5] == 5) {
for (int j = 28; j < 33; j++) {
borad_ver[j].color[0] = false;
borad_ver[j].color[1] = false;
borad_ver[j].color[2] = false;
borad_ver[j].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y)) {
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[j].x == board_ver_inv[k].x) && (borad_ver[j].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp3[5] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 9;
check_level();
}
}
int temp1[6] = { 0 };
for (int i = 0; i < 4; i++)
{
if (borad_ver[i].cell && board_ver_inv[i].cell)
{
temp1[0]++;
}
if (borad_ver[i].cell && board[i].cell)
{
temp1[1]++;
}
if (board_ver_inv[i+33].cell && board[i].cell)
{
temp1[2]++;
}
if (board_ver_inv[i].cell && board[i+33].cell)
{
temp1[3]++;
}
if (borad_ver[i+33].cell && board[i+33].cell)
{
temp1[4]++;
}
if (borad_ver[i + 33].cell && board_ver_inv[i + 33].cell)
{
temp1[5]++;
}
}
if (temp1[0] == 4)
{
for (int i = 0; i < 4; i++)
{
board_ver_inv[i].color[0] = false;
board_ver_inv[i].color[1] = false;
board_ver_inv[i].color[2] = false;
board_ver_inv[i].cell = false;
borad_ver[i].color[0] = false;
borad_ver[i].color[1] = false;
borad_ver[i].color[2] = false;
borad_ver[i].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[i].x == board[k].x) && (borad_ver[i].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board_ver_inv[i].x == board[k].x) && (board_ver_inv[i].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[i].x == board_ver_inv[k].x) && (borad_ver[i].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
if ((board_ver_inv[i].x == borad_ver[k].x) && (board_ver_inv[i].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp1[0] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 8;
check_level();
}
if (temp1[1] == 4)
{
for (int i = 0; i < 4; i++)
{
board[i].color[0] = false;
board[i].color[1] = false;
board[i].color[2] = false;
board[i].cell = false;
board[i].wow = true;
borad_ver[i].color[0] = false;
borad_ver[i].color[1] = false;
borad_ver[i].color[2] = false;
borad_ver[i].cell = false;
for (int k = 0; k < 37; k++)
{
if ((borad_ver[i].x == board_ver_inv[k].x) && (borad_ver[i].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
if ((board[i].x == board_ver_inv[k].x) && (board[i].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
if ((borad_ver[i].x == board[k].x) && (borad_ver[i].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board[i].x == borad_ver[k].x) && (board[i].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp1[1] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 8;
check_level();
}
if (temp1[2] == 4)
{
for (int i = 0; i < 4; i++)
{
board[i].color[0] = false;
board[i].color[1] = false;
board[i].color[2] = false;
board[i].cell = false;
board[i].wow = true;
board_ver_inv[i+33].color[0] = false;
board_ver_inv[i+33].color[1] = false;
board_ver_inv[i+33].color[2] = false;
board_ver_inv[i+33].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[i+33].x == borad_ver[k].x) && (board_ver_inv[i+33].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board[i].x == borad_ver[k].x) && (board[i].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board_ver_inv[i+33].x == board[k].x) && (board_ver_inv[i+33].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((board[i].x == board_ver_inv[k].x) && (board[i].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
}
}
draww = true;
temp1[2] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 8;
check_level();
}
if (temp1[3] == 4)
{
for (int i = 0; i < 4; i++)
{
board[i+33].color[0] = false;
board[i+33].color[1] = false;
board[i+33].color[2] = false;
board[i+33].cell = false;
board[i + 33].wow = true;
board_ver_inv[i].color[0] = false;
board_ver_inv[i].color[1] = false;
board_ver_inv[i].color[2] = false;
board_ver_inv[i].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board[i+33].x == borad_ver[k].x) && (board[i+33].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board_ver_inv[i].x == borad_ver[k].x) && (board_ver_inv[i].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((board[i+33].x == board_ver_inv[k].x) && (board[i+33].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
if ((board_ver_inv[i].x == board[k].x) && (board_ver_inv[i].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
}
}
draww = true;
temp1[3] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 8;
check_level();
}
if (temp1[4] == 4)
{
for (int i = 0; i < 4; i++)
{
board[i + 33].color[0] = false;
board[i + 33].color[1] = false;
board[i + 33].color[2] = false;
board[i + 33].cell = false;
board[i + 33].wow = true;
borad_ver[i + 33].color[0] = false;
borad_ver[i + 33].color[1] = false;
borad_ver[i + 33].color[2] = false;
borad_ver[i + 33].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board[i + 33].x == board_ver_inv[k].x) && (board[i + 33].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
if ((borad_ver[i+33].x == board_ver_inv[k].x) && (borad_ver[i+33].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
if ((board[i + 33].x == borad_ver[k].x) && (board[i + 33].y == borad_ver[k].y))
borad_ver[k].cell = false;
if ((borad_ver[i+33].x == board[k].x) && (borad_ver[i+33].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
}
}
draww = true;
temp1[4] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 8;
check_level();
}
if (temp1[5] == 4) {
for (int i = 0; i < 4; i++)
{
board_ver_inv[i + 33].color[0] = false;
board_ver_inv[i + 33].color[1] = false;
board_ver_inv[i + 33].color[2] = false;
board_ver_inv[i + 33].cell = false;
borad_ver[i + 33].color[0] = false;
borad_ver[i + 33].color[1] = false;
borad_ver[i + 33].color[2] = false;
borad_ver[i + 33].cell = false;
for (int k = 0; k < 37; k++)
{
if ((board_ver_inv[i + 33].x == board[k].x) && (board_ver_inv[i + 33].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[i + 33].x == board[k].x) && (borad_ver[i + 33].y == board[k].y)){
board[k].cell = false;
board[k].wow = true;
}
if ((borad_ver[i + 33].x == board_ver_inv[k].x) && (borad_ver[i + 33].y == board_ver_inv[k].y))
board_ver_inv[k].cell = false;
if ((board_ver_inv[i + 33].x == borad_ver[k].x) && (board_ver_inv[i + 33].y == borad_ver[k].y))
borad_ver[k].cell = false;
}
}
draww = true;
temp1[5] = 0;
al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
counter += 8;
check_level();
}
}*/