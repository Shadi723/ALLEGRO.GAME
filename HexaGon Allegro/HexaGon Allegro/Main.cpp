#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
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
	bool cell, check, wow, drawn;
	bool color[3];
	bool hammer;
};
struct cases
{
	int k1, k2, k3;
	int counter, level, star;
	bool d1, d2, d3, endcase;
};
bool done, doit, done_men, draww; 
bool moves[3];
bool des[3];
bool endcase = true;
static bool states = false;
static bool soundd = false, fiin = false;
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
ALLEGRO_FONT *font_number;
ALLEGRO_FONT *font_number1;
ALLEGRO_BITMAP* image;
ALLEGRO_BITMAP* back;
ALLEGRO_BITMAP* finish;
ALLEGRO_BITMAP* q1;
ALLEGRO_BITMAP* q2;
ALLEGRO_BITMAP* q3;
ALLEGRO_BITMAP* q4;
ALLEGRO_BITMAP* q5;
ALLEGRO_BITMAP* q6;
ALLEGRO_BITMAP* q9;
ALLEGRO_BITMAP* q10;
ALLEGRO_BITMAP* newgame;
ALLEGRO_BITMAP* star;
ALLEGRO_BITMAP* trash;
ALLEGRO_BITMAP* hammer;
ALLEGRO_BITMAP* hammer1;
ALLEGRO_SAMPLE* sound ;
ALLEGRO_SAMPLE_ID soundid;
ALLEGRO_SAMPLE* win;
ALLEGRO_SAMPLE* level1;
ALLEGRO_SAMPLE* click; 
ALLEGRO_SAMPLE* click_menu;
ALLEGRO_SAMPLE* end;
ALLEGRO_SAMPLE* pop;
ALLEGRO_SAMPLE* shoot;
ALLEGRO_SAMPLE* no_access;
static ALLEGRO_BITMAP* q[37];
static char score [10];
static int counter = 0;
int star_count;
int k1, k2, k3,level = 1,levsound = 1;
FILE *file;
FILE *score_file;
FILE *board_file;
FILE *ver_file;
FILE *inver_file;
static ele_pos  e1, e2, e3, er, board[37], borad_ver[37], board_ver_inv[37];
void save();
void init_resum();
void init();
void game_loop();
const ele_pos three_el[6][3] = { {{560,350},{855,350},{1145,350}},
								 {{560,350},{855,350},{1145,350}},
								 {{560,425},{855,425},{1150,425}} ,
							   	 {{560,355},{855,355},{1150,355}} ,
								 {{560,405},{855,405},{1150,405}} ,
								 {{560,370},{855,370},{1150,370}} };
void draw(ALLEGRO_MOUSE_STATE state);
void update_logic(ALLEGRO_EVENT event);
void user_input(ALLEGRO_EVENT event);
void check_good();
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
	font = al_load_ttf_font("AlexBrush-Regular.ttf", 35, 0);
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
		star_count = c.star;
	}
	fclose(score_file);
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
					for (int i = 0; i < 37; i++)
						printf("%d\n", board[i].cell);
					init_resum();
					for (int i = 0; i < 37; i++)
						printf("%d\n", board[i].cell);
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
			if(p)
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
	font = al_load_ttf_font("AlexBrush-Regular.ttf", 33, 0);
	font_number = al_load_ttf_font("pirulen rg.ttf", 70, 0);
	font_number1 = al_load_ttf_font("pirulen rg.ttf", 30, 0);
	image = al_load_bitmap("h.png");
	back = al_load_bitmap("background.png");
	q1 = al_load_bitmap("1.png");
	q2 = al_load_bitmap("2.png");
	q3 = al_load_bitmap("3.png");
	q4 = al_load_bitmap("4.png");
	q5 = al_load_bitmap("5.png");
	q6 = al_load_bitmap("6.png");
	q9 = al_load_bitmap("9.png");
	q10 = al_load_bitmap("10.png");
	finish = al_load_bitmap("finish.png");
	star = al_load_bitmap("star.png");
	trash = al_load_bitmap("trash.png");
	hammer = al_load_bitmap("hammer.png");
	hammer1 = al_load_bitmap("hammer1.png");
	al_reserve_samples(9);
	sound = al_load_sample("sound.wav");
	win = al_load_sample("win.wav");
	level1 = al_load_sample("level.wav");
	click = al_load_sample("click.wav");
	end = al_load_sample("end.wav");
	pop = al_load_sample("pop.wav");
	shoot = al_load_sample("shoot.wav");
	no_access = al_load_sample("no_access.wav");
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	done = false;
	moves[0] = false;
	moves[1] = false;
	moves[2] = false;
	draww = false;
	init_board();
	init_ver();
	doit = true;
	des[0] = true; des[1] = true; des[2] = true;
	srand(time(NULL));
	k1 = rand() % 4;
	k2 = rand() % 4;
	k3 = rand() % 4;
	e1 = three_el[k1][0];
	e2 = three_el[k2][1];
	e3 = three_el[k2][2];
	counter = 0;
	level = 1;
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
		board[i].color[0] = false;
		board[i].color[1] = false;
		board[i].color[2] = false;
		board[i].cell = false;
		board[i].check = false;
		board[i].wow = false;
		board[i].drawn = false;
		board[i].hammer = false;
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
		borad_ver[i].color[0] = false;
		borad_ver[i].color[1] = false;
		borad_ver[i].color[2] = false;
		borad_ver[i].cell = false;
		printf("( %d , %d )", borad_ver[i].x, borad_ver[i].y);
		if (i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32)
			printf("\n");
	}
	printf("\n----------------------------------\n");
	for (int i = 0; i < 37; i++) {
		board_ver_inv[i].color[0] = false;
		board_ver_inv[i].color[1] = false;
		board_ver_inv[i].color[2] = false;
		board_ver_inv[i].cell = false;
		printf("( %d , %d )", board_ver_inv[i].x, board_ver_inv[i].y);
		if (i == 3 || i == 8 || i == 14 || i == 21 || i == 27 || i == 32)
			printf("\n");
	}
}
void update_movement(ALLEGRO_EVENT event,int k,int case_color ,ele_pos e, int m, int d) {
	for (int i = 0; i < 37; i++)
	{
		if (k == 0)
		{
			if ((i < 2) || (i > 3 && i < 7) || (i > 8 && i < 13) || (i > 14 && i < 20) || (i > 21 && i < 26) || (i > 27 && i < 31) || (i > 32 && i < 35))
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 2].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i+1].color[case_color] = true;		board[i + 1].cell = true;
					board[i+2].color[case_color] = true;		board[i + 2].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;				borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 2].x == borad_ver[j].x) && (board[i + 2].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;				borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;			board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;			board_ver_inv[j].cell = true;
						}
						if ((board[i + 2].x == board_ver_inv[j].x) && (board[i + 2].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;			board_ver_inv[j].cell = true;
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
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 1].color[case_color] = true;		board[i + 1].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 2;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
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
					borad_ver[i].color[case_color] = true;			borad_ver[i].cell = true;
					borad_ver[i + 1].color[case_color] = true;		borad_ver[i + 1].cell = true;
					borad_ver[i + 2].color[case_color] = true;		borad_ver[i + 2].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
							board[j].color[case_color] = true;			board[j].cell = true;
						}
						if ((borad_ver[i + 1].x == board[j].x) && (borad_ver[i + 1].y == board[j].y)) {
							board[j].color[case_color] = true;			board[j].cell = true;
						}
						if ((borad_ver[i + 2].x == board[j].x) && (borad_ver[i + 2].y == board[j].y)) {
							board[j].color[case_color] = true;			board[j].cell = true;
						}
						if ((borad_ver[i].x == board_ver_inv[j].x) && (borad_ver[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;			board_ver_inv[j].cell = true;
						}
						if ((borad_ver[i + 1].x == board_ver_inv[j].x) && (borad_ver[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;			board_ver_inv[j].cell = true;
						}
						if ((borad_ver[i + 2].x == board_ver_inv[j].x) && (borad_ver[i + 2].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;			board_ver_inv[j].cell = true;
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
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 5].color[case_color] = true;		board[i + 5].cell = true;
					board[i + 10].color[case_color] = true;	board[i + 10].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 3 && i < 9)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 6].color[case_color] = true;		board[i + 6].cell = true;
					board[i + 12].color[case_color] = true;	board[i + 12].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;				borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;				borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;				borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;			board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;			board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;			board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 8 && i < 15)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 7].color[case_color] = true;		board[i + 7].cell = true;
					board[i + 13].color[case_color] = true;	board[i + 13].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 15 && i < 21)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 7].color[case_color] = true;		board[i + 7].cell = true;
					board[i + 12].color[case_color] = true;	board[i + 12].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 22 && i < 27)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 6].color[case_color] = true;		board[i + 6].cell = true;
					board[i + 10].color[case_color] = true;	board[i + 10].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 3;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
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
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 4].color[case_color] = true;		board[i + 4].cell = true;
					board[i + 5].color[case_color] = true;		board[i + 5].cell = true;
					board[i + 10].color[case_color] = true;	board[i + 10].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 4].x == borad_ver[j].x) && (board[i + 4].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 4].x == board_ver_inv[j].x) && (board[i + 4].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 3 && i < 9)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 5].color[case_color] = true;		board[i + 5].cell = true;
					board[i + 6].color[case_color] = true;		board[i + 6].cell = true;
					board[i + 12].color[case_color] = true;	board[i + 12].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 8 && i < 15)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 6].color[case_color] = true;		board[i + 6].cell = true;
					board[i + 7].color[case_color] = true;		board[i + 7].cell = true;
					board[i + 13].color[case_color] = true;	board[i + 13].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}

			if (i > 15 && i < 21)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 6].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 6].color[case_color] = true;		board[i + 6].cell = true;
					board[i + 7].color[case_color] = true;		board[i + 7].cell = true;
					board[i + 12].color[case_color] = true;	board[i + 12].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 22 && i < 27)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 5].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 5].color[case_color] = true;		board[i + 5].cell = true;
					board[i + 6].color[case_color] = true;		board[i + 6].cell = true;
					board[i + 10].color[case_color] = true;	board[i + 10].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 4;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
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
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 1].color[case_color] = true;		board[i + 1].cell = true;
					board[i + 5].color[case_color] = true;		board[i + 5].cell = true;
					board[i + 10].color[case_color] = true;	board[i + 10].cell = true;
					board[i + 11].color[case_color] = true;	board[i + 11].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 5].x == borad_ver[j].x) && (board[i + 5].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 5].x == board_ver_inv[j].x) && (board[i + 5].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 3 && i < 8)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 1].color[case_color] = true;		board[i + 1].cell = true;
					board[i + 6].color[case_color] = true;		board[i + 6].cell = true;
					board[i + 12].color[case_color] = true;	board[i + 12].cell = true;
					board[i + 13].color[case_color] = true;	board[i + 13].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 8 && i < 14)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 13].cell == false) && (board[i + 14].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 1].color[case_color] = true;		board[i + 1].cell = true;
					board[i + 7].color[case_color] = true;		board[i + 7].cell = true;
					board[i + 13].color[case_color] = true;	board[i + 13].cell = true;
					board[i + 14].color[case_color] = true;	board[i + 14].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 14].x == borad_ver[j].x) && (board[i + 14].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 14].x == board_ver_inv[j].x) && (board[i + 14].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 15 && i < 20)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 7].cell == false) && (board[i + 12].cell == false) && (board[i + 13].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 1].color[case_color] = true;		board[i + 1].cell = true;
					board[i + 7].color[case_color] = true;		board[i + 7].cell = true;
					board[i + 12].color[case_color] = true;	board[i + 12].cell = true;
					board[i + 13].color[case_color] = true;	board[i + 13].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 7].x == borad_ver[j].x) && (board[i + 7].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 12].x == borad_ver[j].x) && (board[i + 12].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i + 13].x == borad_ver[j].x) && (board[i + 13].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;			borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 7].x == board_ver_inv[j].x) && (board[i + 7].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 12].x == board_ver_inv[j].x) && (board[i + 12].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
						if ((board[i + 13].x == board_ver_inv[j].x) && (board[i + 13].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;		board_ver_inv[j].cell = true;
						}
					}
					check_good();
				}
			}
			if (i > 22 && i < 26)
			{
				if ((event.mouse.button & 1) && (board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 6].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false) && (e.x >= board[i].x) && (e.x <= board[i].x + 40) && (e.y >= board[i].y) && (e.y <= board[i].y + 40)) {
					board[i].color[case_color] = true;			board[i].cell = true;
					board[i + 1].color[case_color] = true;		board[i + 1].cell = true;
					board[i + 6].color[case_color] = true;		board[i + 6].cell = true;
					board[i + 10].color[case_color] = true;	board[i + 10].cell = true;
					board[i + 11].color[case_color] = true;	board[i + 11].cell = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					counter += 5;
					check_level();
					moves[m] = false;
					des[d] = false;
					for (int j = 0; j < 37; j++) {
						if ((board[i].x == borad_ver[j].x) && (board[i].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 1].x == borad_ver[j].x) && (board[i + 1].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 6].x == borad_ver[j].x) && (board[i + 6].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 10].x == borad_ver[j].x) && (board[i + 10].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i + 11].x == borad_ver[j].x) && (board[i + 11].y == borad_ver[j].y)) {
							borad_ver[j].color[case_color] = true;		borad_ver[j].cell = true;
						}
						if ((board[i].x == board_ver_inv[j].x) && (board[i].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 1].x == board_ver_inv[j].x) && (board[i + 1].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 6].x == board_ver_inv[j].x) && (board[i + 6].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 10].x == board_ver_inv[j].x) && (board[i + 10].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
						if ((board[i + 11].x == board_ver_inv[j].x) && (board[i + 11].y == board_ver_inv[j].y)) {
							board_ver_inv[j].color[case_color] = true;	board_ver_inv[j].cell = true;
						}
					}
				}
				check_good();
			}
		}
	}
}
void update_logic(ALLEGRO_EVENT event) {
	if (moves[0]) {
		update_movement(event, k1, 0, e1,0, 0);
	}
	else if (moves[1]) {
		update_movement(event, k2, 1, e2, 1, 1);
	}
	else if (moves[2]) {
		update_movement(event, k3, 2, e3, 2, 2);
	}
}
void user_input(ALLEGRO_EVENT event) {
		if (event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY || event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			er.x = event.mouse.x;
			er.y = event.mouse.y;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if ((( k1 == 0) || (k1==1) || (k1== 3) || (k1 == 5))&&(event.mouse.button & 1) && (event.mouse.x >= three_el[k1][0].x) && (event.mouse.x <= three_el[k1][0].x + 50) && (event.mouse.y >= three_el[k1][0].y) && (event.mouse.y <= three_el[k1][0].y + 50)) {
					moves[0] = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				}
			else if ((k1 == 2) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k1][0].x) && (event.mouse.x <= three_el[k1][0].x + 50) && (event.mouse.y >= three_el[k1][0].y) && (event.mouse.y <= three_el[k1][0].y + 50)) {
				moves[0] = true;
				al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if ((k1 == 4) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k1][0].x) && (event.mouse.x <= three_el[k1][0].x + 50) && (event.mouse.y >= three_el[k1][0].y) && (event.mouse.y <= three_el[k1][0].y + 50)) {
				moves[0] = true;
				al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if (((k2 == 0) || (k2 == 1) || (k2 == 3) || (k2 == 5)) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k2][1].x) && (event.mouse.x <= three_el[k2][1].x + 50) && (event.mouse.y >= three_el[k2][1].y) && (event.mouse.y <= three_el[k2][1].y + 50)) {
					moves[1] = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				}
			else if ((k2 == 2) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k2][1].x) && (event.mouse.x <= three_el[k2][1].x + 50) && (event.mouse.y >= three_el[k2][1].y) && (event.mouse.y <= three_el[k2][1].y + 50)) {
				moves[1] = true;
				al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if ((k2 == 4) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k2][1].x) && (event.mouse.x <= three_el[k2][1].x + 50) && (event.mouse.y >= three_el[k2][1].y ) && (event.mouse.y <= three_el[k2][1].y + 50)) {
				moves[1] = true;
				al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if (((k3 == 0) || (k3 == 1) || (k3 == 3) || (k3 == 5)) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k3][2].x) && (event.mouse.x <= three_el[k3][2].x + 50) && (event.mouse.y >= three_el[k3][2].y) && (event.mouse.y <= three_el[k3][2].y + 50)) {
					moves[2] = true;
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				}
			else if ((k3 == 2) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k3][2].x) && (event.mouse.x <= three_el[k3][2].x + 50) && (event.mouse.y >= three_el[k3][2].y) && (event.mouse.y <= three_el[k3][2].y + 50)) {
				moves[2] = true;
				al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if ((k3 == 4) && (event.mouse.button & 1) && (event.mouse.x >= three_el[k3][2].x) && (event.mouse.x <= three_el[k3][2].x + 50) && (event.mouse.y >= three_el[k3][2].y) && (event.mouse.y <= three_el[k3][2].y + 50)) {
				moves[2] = true;
				al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if (event.mouse.button & 2)
			{
				moves[0] = false;
				moves[1] = false;
				moves[2] = false;
			}
		}
		update_logic(event);
}
void help_good(ele_pos main_bo[37] ,int b_start, int b_end, int ver_st,int ver_end,ele_pos ini_board[37], ele_pos sec_board[37]) {
	for (int i = b_start; i < b_end; i++) {
		main_bo[i].wow = true;
		main_bo[i].color[0] = false;
		main_bo[i].color[1] = false;
		main_bo[i].color[2] = false;
		main_bo[i].cell = false;
		for (int k = 0; k < 37; k++) {
			if ((main_bo[i].x == ini_board[k].x) && (main_bo[i].y == ini_board[k].y))
			{
				ini_board[k].color[0] = false;
				ini_board[k].color[1] = false;
				ini_board[k].color[2] = false;
				ini_board[k].cell = false;
			}
			if ((main_bo[i].x == sec_board[k].x) && (main_bo[i].y == sec_board[k].y))
			{
				sec_board[k].color[0] = false;
				sec_board[k].color[1] = false;
				sec_board[k].color[2] = false;
				sec_board[k].cell = false;
			}
		}
	}
	for (int i = ver_st; i < ver_end; i++) {
		ini_board[i].color[0] = false;
		ini_board[i].color[1] = false;
		ini_board[i].color[2] = false;
		ini_board[i].cell = false;
		for (int k = 0; k < 37; k++) {
			if ((ini_board[i].x == main_bo[k].x) && (ini_board[i].y == main_bo[k].y))
			{
				main_bo[k].wow = true;
				main_bo[k].color[0] = false;
				main_bo[k].color[1] = false;
				main_bo[k].color[2] = false;
				main_bo[k].cell = false;
			}
			if ((ini_board[i].x == sec_board[k].x) && (ini_board[i].y == sec_board[k].y))
			{
				sec_board[k].color[0] = false;
				sec_board[k].color[1] = false;
				sec_board[k].color[2] = false;
				sec_board[k].cell = false;
			}
		}
	}
}
void help_good_ver(ele_pos main_bo[37], int b_start, int b_end, int ver_st, int ver_end, ele_pos ini_board[37],ele_pos sec_board[37]) {
	for (int i = b_start; i < b_end; i++) {
		main_bo[i].color[0] = false;
		main_bo[i].color[1] = false;
		main_bo[i].color[2] = false;
		main_bo[i].cell = false;
		for (int k = 0; k < 37; k++) {
			if ((main_bo[i].x == ini_board[k].x) && (main_bo[i].y == ini_board[k].y)) {
				ini_board[k].wow = true;
				ini_board[k].color[0] = false;
				ini_board[k].color[1] = false;
				ini_board[k].color[2] = false;
				ini_board[k].cell = false;
			}
		}
		for (int k = 0; k < 37; k++) {
			if ((main_bo[i].x == sec_board[k].x) && (main_bo[i].y == sec_board[k].y)) {
				sec_board[k].color[0] = false;
				sec_board[k].color[1] = false;
				sec_board[k].color[2] = false;
				sec_board[k].cell = false;
			}
		}
	}
	for (int i = ver_st; i < ver_end; i++) {
		ini_board[i].color[0] = false;
		ini_board[i].color[1] = false;
		ini_board[i].color[2] = false;
		ini_board[i].cell = false;
		ini_board[i].wow = true;
		for (int k = 0; k < 37; k++) {
			if ((ini_board[i].x == sec_board[k].x) && (ini_board[i].y == sec_board[k].y)) {
				sec_board[k].color[0] = false;
				sec_board[k].color[1] = false;
				sec_board[k].color[2] = false;
				sec_board[k].cell = false;
			}
			if ((ini_board[i].x == main_bo[k].x) && (ini_board[i].y == main_bo[k].y)) {
				main_bo[k].color[0] = false;
				main_bo[k].color[1] = false;
				main_bo[k].color[2] = false;
				main_bo[k].cell = false;
			}
		}
	}
}
void help_good1(ele_pos main_bo[37], int b_start, int b_end, ele_pos ini_board[37], ele_pos sec_board[37]) {
	for (int i = b_start; i < b_end; i++) {
		main_bo[i].color[0] = false;
		main_bo[i].color[1] = false;
		main_bo[i].color[2] = false;
		main_bo[i].cell = false;
		main_bo[i].wow = true;
		for (int k = 0; k < 37; k++) {
			if ((main_bo[i].x == ini_board[k].x) && (main_bo[i].y == ini_board[k].y)) {
				ini_board[k].color[0] = false;
				ini_board[k].color[1] = false;
				ini_board[k].color[2] = false;
				ini_board[k].cell = false;
			}
		}
		for (int k = 0; k < 37; k++) {
			if ((main_bo[i].x == sec_board[k].x) && (main_bo[i].y == sec_board[k].y)) {
				sec_board[k].color[0] = false;
				sec_board[k].color[1] = false;
				sec_board[k].color[2] = false;
				sec_board[k].cell = false;
			}
		}
	}
}
void help_good2(ele_pos main_bo[37], int b_start, int b_end,ele_pos ini_board[37], ele_pos sec_board[37]) {
	for (int i = b_start; i < b_end; i++) {
		main_bo[i].color[0] = false;
		main_bo[i].color[1] = false;
		main_bo[i].color[2] = false;
		main_bo[i].cell = false;
		for (int k = 0; k < 37; k++) {
			if ((main_bo[i].x == ini_board[k].x) && (main_bo[i].y == ini_board[k].y)) {
				ini_board[k].wow = true;
				ini_board[k].color[0] = false;
				ini_board[k].color[1] = false;
				ini_board[k].color[2] = false;
				ini_board[k].cell = false;
			}
			if ((main_bo[i].x == sec_board[k].x) && (main_bo[i].y == sec_board[k].y)) {
				sec_board[k].color[0] = false;
				sec_board[k].color[1] = false;
				sec_board[k].color[2] = false;
				sec_board[k].cell = false;
			}
		}
	}
}
void is_good_optimal() {
	int i = 0;
	int temp_board[7] = { 0 };
	int temp_ver[7] = { 0 };
	int temp_inv[7] = { 0 };
	while (i < 4)
	{
		if (board[i].cell) {
			temp_board[0]++;
		}
		if (borad_ver[i].cell) {
			temp_ver[0]++;
		}
		if (board_ver_inv[i].cell) {
			temp_inv[0]++;
		}
		i++;
	}
	while (i > 3 && i < 9)
	{
		if (board[i].cell) {
			temp_board[1]++;
		}
		if (borad_ver[i].cell) {
			temp_ver[1]++;
		}
		if (board_ver_inv[i].cell) {
			temp_inv[1]++;
		}
		i++;
	}
	while (i > 8 && i < 15)
	{
		if (board[i].cell) {
			temp_board[2]++;
		}
		if (borad_ver[i].cell) {
			temp_ver[2]++;
		}
		if (board_ver_inv[i].cell) {
			temp_inv[2]++;
		}
		i++;
	}
	while (i > 14 && i < 22)
	{
		if (board[i].cell) {
			temp_board[3]++;
		}
		if (borad_ver[i].cell) {
			temp_ver[3]++;
		}
		if (board_ver_inv[i].cell) {
			temp_inv[3]++;
		}
		i++;
	}
	while (i > 21 && i < 28)
	{
		if (board[i].cell) {
			temp_board[4]++;
		}
		if (borad_ver[i].cell) {
			temp_ver[4]++;
		}
		if (board_ver_inv[i].cell) {
			temp_inv[4]++;
		}
		i++;
	}
	while (i > 27 && i < 33)
	{
		if (board[i].cell) {
			temp_board[5]++;
		}
		if (borad_ver[i].cell) {
			temp_ver[5]++;
		}
		if (board_ver_inv[i].cell) {
			temp_inv[5]++;
		}
		i++;
	}
	while (i > 32 && i < 37)
	{
		if (board[i].cell) {
			temp_board[6]++;
		}
		if (borad_ver[i].cell) {
			temp_ver[6]++;
		}
		if (board_ver_inv[i].cell) {
			temp_inv[6]++;
		}
		i++;
	}
	if ((temp_ver[0] == 4) && (temp_inv[0] == 4) && (temp_board[3] == 7)) {
		for (int j = 0; j < 4; j++) {
			borad_ver[j].color[0] = false;	board_ver_inv[j].color[0] = false;
			borad_ver[j].color[1] = false;	board_ver_inv[j].color[1] = false;
			borad_ver[j].color[2] = false;	board_ver_inv[j].color[2] = false;
			borad_ver[j].cell = false;	board_ver_inv[j].cell = false;
			for (int k = 0; k < 37; k++) {
				if ((borad_ver[j].x == board[k].x) && (borad_ver[j].y == board[k].y))
					board[k].wow = true;
				if ((board_ver_inv[j].x == board[k].x) && (board_ver_inv[j].y == board[k].y))
					board[k].wow = true;
			}
		}
		for (int j = 15; j < 22; j++) {
			board[j].color[0] = false;
			board[j].color[1] = false;
			board[j].color[2] = false;
			board[j].cell = false;
			board[j].wow = true;
		}
		draww = true;
		temp_inv[0] = 0;
		temp_ver[0] = 0;
		temp_board[3] = 0;
		counter += 15;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if ((temp_ver[6] == 4) && (temp_inv[6] == 4) && (temp_board[3] == 7)) {
		for (int j = 0; j < 4; j++) {
			borad_ver[j + 33].color[0] = false;	board_ver_inv[j + 33].color[0] = false;
			borad_ver[j + 33].color[1] = false;	board_ver_inv[j + 33].color[1] = false;
			borad_ver[j + 33].color[2] = false;	board_ver_inv[j + 33].color[2] = false;
			borad_ver[j + 33].cell = false;	board_ver_inv[j + 33].cell = false;
			for (int k = 0; k < 37; k++) {
				if ((borad_ver[j + 33].x == board[k].x) && (borad_ver[j + 33].y == board[k].y))
					board[k].wow = true;
				if ((board_ver_inv[j + 33].x == board[k].x) && (board_ver_inv[j + 33].y == board[k].y))
					board[k].wow = true;
			}
		}
		for (int j = 15; j < 22; j++) {
			board[j].color[0] = false;
			board[j].color[1] = false;
			board[j].color[2] = false;
			board[j].cell = false;
			board[j].wow = true;
		}
		draww = true;
		temp_inv[6] = 0;
		temp_ver[6] = 0;
		temp_board[3] = 0;
		counter += 15;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
/////////////////////////
	if (temp_board[0] == 4) {
		if (temp_ver[0] == 4) {
			help_good(board, 0, 4, 0, 4, borad_ver, board_ver_inv);
			draww = true;
			temp_board[0] = 0;
			temp_ver[0] = 0;
			counter += 8;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_ver[1] == 5) {
			help_good(board, 0, 4, 4, 9, borad_ver, board_ver_inv);
			temp_board[0] = 0;
			temp_ver[1] = 0;
			counter += 9;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_ver[2] == 6) {
			help_good(board, 0, 4, 9, 15, borad_ver, board_ver_inv);
			temp_board[0] = 0;
			temp_ver[2] = 0;
			counter += 10;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_ver[3] == 7) {
			help_good(board, 0, 4, 15, 22, borad_ver, board_ver_inv);
			temp_board[0] = 0;
			temp_ver[3] = 0;
			counter += 11;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_inv[3] == 7) {
			help_good(board, 0, 4, 15, 22, board_ver_inv, borad_ver);
			draww = true;
			temp_board[0] = 0;
			temp_inv[3] = 0;
			counter += 11;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_inv[4] == 6) {
			help_good(board, 0, 4, 22, 28, board_ver_inv, borad_ver);
			temp_board[0] = 0;
			temp_inv[4] = 0;
			counter += 10;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_inv[5] == 5) {
			help_good(board, 0, 4, 28, 33,board_ver_inv, borad_ver);
			temp_board[0] = 0;
			temp_inv[5] = 0;
			counter += 9;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_inv[6] == 4) {
			help_good(board, 0, 4, 33, 37,board_ver_inv, borad_ver);
			temp_board[0] = 0;
			temp_inv[6] = 0;
			counter += 8;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
	}
	if (temp_board[6] == 4) {
		if (temp_inv[0] == 4) {
			help_good(board, 33, 37, 0, 4, board_ver_inv, borad_ver);
			draww = true;
			temp_board[6] = 0;
			temp_inv[0] = 0;
			counter += 8;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_inv[1] == 5) {
			help_good(board, 33, 37, 4, 9, board_ver_inv, borad_ver);
			temp_board[6] = 0;
			temp_inv[1] = 0;
			counter += 9;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_inv[2] == 6) {
			help_good(board, 33, 37, 9, 15, board_ver_inv, borad_ver);
			temp_board[6] = 0;
			temp_inv[2] = 0;
			counter += 10;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_inv[3] == 7) {
			help_good(board, 33, 37, 15, 22, board_ver_inv, borad_ver);
			temp_board[6] = 0;
			temp_inv[3] = 0;
			counter += 11;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_ver[3] == 7) {
			help_good(board, 33, 37, 15, 22, borad_ver, board_ver_inv);
			draww = true;
			temp_board[6] = 0;
			temp_ver[3] = 0;
			counter += 11;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_ver[4] == 6) {
			help_good(board, 33, 37, 22, 28, borad_ver, board_ver_inv);
			temp_board[6] = 0;
			temp_ver[4] = 0;
			counter += 10;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_ver[5] == 5) {
			help_good(board, 33, 37, 28, 33, borad_ver, board_ver_inv);
			temp_board[6] = 0;
			temp_ver[5] = 0;
			counter += 9;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_ver[6] == 4) {
			help_good(board, 33, 37, 33, 37, borad_ver, board_ver_inv);
			temp_board[6] = 0;
			temp_ver[6] = 0;
			counter += 8;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
	}
////////////////////////
	if (temp_ver[0] == 4) {
		if (temp_board[1] == 5) {
			help_good_ver(borad_ver, 0, 4, 4, 9, board, board_ver_inv);
			temp_board[1] = 0;
			temp_ver[0] = 0;
			counter += 9;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_board[2] == 6) {
			help_good_ver(borad_ver, 0, 4, 9, 15, board, board_ver_inv);
			temp_board[1] = 0;
			temp_ver[0] = 0;
			counter += 10;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_board[3] == 7) {
			help_good_ver(borad_ver, 0, 4, 15, 22, board, board_ver_inv);
			temp_board[1] = 0;
			temp_ver[0] = 0;
			counter += 11;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
	}
	if (temp_inv[6] == 4) {
		if (temp_board[1] == 5) {
			help_good_ver(board_ver_inv, 33, 37, 4, 9, board, borad_ver);
			temp_board[1] = 0;
			temp_inv[6] = 0;
			counter += 9;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_board[2] == 6) {
			help_good_ver(board_ver_inv, 33, 37, 9, 15, board, borad_ver);
			temp_board[2] = 0;
			temp_inv[6] = 0;
			counter += 10;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_board[3] == 7) {
			help_good_ver(board_ver_inv, 33, 37, 15, 22, board, borad_ver);
			temp_board[3] = 0;
			temp_inv[6] = 0;
			counter += 11;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
	}
////////////////////////
	if (temp_inv[0] == 4) {
		if (temp_board[3] == 7) {
			help_good_ver(board_ver_inv, 0, 4, 15, 22, board, borad_ver);
			draww = true;
			temp_board[3] = 0;
			temp_inv[0] = 0;
			counter += 11;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_board[4] == 6) {
			help_good_ver(board_ver_inv, 0, 4, 22, 28, board, borad_ver);
			temp_board[4] = 0;
			temp_inv[0] = 0;
			counter += 10;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_board[5] == 5) {
			help_good_ver(board_ver_inv, 0, 4, 28, 33, board, borad_ver);
			temp_board[5] = 0;
			temp_inv[0] = 0;
			counter += 9;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
	}
	if (temp_ver[6] == 4) {
		if (temp_board[3] == 7) {
			help_good_ver(borad_ver, 0, 4, 15, 22, board, board_ver_inv);
			draww = true;
			temp_board[3] = 0;
			temp_ver[0] = 0;
			counter += 11;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_board[4] == 6) {
			help_good_ver(borad_ver, 0, 4, 22, 28, board, board_ver_inv);
			temp_board[4] = 0;
			temp_ver[0] = 0;
			counter += 10;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
		if (temp_board[5] == 5) {
			help_good_ver(borad_ver, 0, 4, 28, 33, board, board_ver_inv);
			temp_board[5] = 0;
			temp_ver[0] = 0;
			counter += 9;
			al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			check_level();
		}
	}
////////////////////////
	if (temp_board[3] == 7 && temp_ver[0]!=4 && temp_inv[6] != 4 && temp_ver[6] != 4 && temp_inv[0] != 4) {
		help_good1(board, 15, 22,borad_ver,board_ver_inv);
		temp_board[3] = 0;
		counter += 7;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_ver[3] == 7 && temp_board[0] != 4 && temp_board[6] != 4) {
		help_good2(borad_ver, 15, 22,board,board_ver_inv);
		temp_ver[3] = 0;
		counter += 7;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_inv[3] == 7 && temp_board[0] != 4 && temp_board[6] != 4) {
		help_good2(board_ver_inv, 15, 22, board,borad_ver);
		temp_inv[3] = 0;
		counter += 7;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
///////////////////////
	if (temp_board[2] == 6 && temp_ver[0] != 4 && temp_inv[6] != 4) {
		help_good1(board, 9, 15, borad_ver, board_ver_inv);
		temp_board[2] = 0;
		counter += 6;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_ver[2] == 6 && temp_board[0] != 4) {
		help_good2(borad_ver, 9, 15, board, board_ver_inv);
		temp_ver[2] = 0;
		counter += 6;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_inv[2] == 6 && temp_board[6] != 4) {
		help_good2(board_ver_inv, 9, 15, board, borad_ver);
		temp_inv[2] = 0;
		counter += 6;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
///////////////////////
	if (temp_board[4] == 6 && temp_ver[6] != 4 && temp_inv[0] != 4) {
		help_good1(board, 22, 28, borad_ver, board_ver_inv);
		temp_board[4] = 0;
		counter += 6;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_ver[4] == 6 && temp_board[0] != 4) {
		help_good2(borad_ver, 22, 28, board, board_ver_inv);
		temp_ver[4] = 0;
		counter += 6;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_inv[4] == 6 && temp_board[6] != 4) {
		help_good2(board_ver_inv, 22, 28, board, borad_ver);
		temp_inv[4] = 0;
		counter += 6;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
///////////////////////
	if (temp_board[1] == 5 && temp_ver[0] != 4 && temp_inv[6] != 4) {
		help_good1(board, 4, 9, borad_ver, board_ver_inv);
		temp_board[1] = 0;
		counter += 5;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_ver[1] == 5 && temp_board[0] != 4) {
		help_good2(borad_ver, 4, 9, board, board_ver_inv);
		temp_ver[1] = 0;
		counter += 5;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_inv[1] == 5 && temp_board[6] != 4) {
		help_good2(board_ver_inv, 4, 9, board, borad_ver);
		temp_inv[1] = 0;
		counter += 5;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
///////////////////////
	if (temp_board[5] == 5 && temp_ver[6] != 4 && temp_inv[0] != 4) {
		help_good1(board, 28, 33, borad_ver, board_ver_inv);
		temp_board[5] = 0;
		counter += 5;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_ver[5] == 5 && temp_board[0] != 4) {
		help_good2(borad_ver, 28, 33, board,board_ver_inv);
		temp_ver[5] = 0;
		counter += 5;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_inv[5] == 5 && temp_board[6] != 4) {
		help_good2(board_ver_inv, 28, 33, board, borad_ver);
		temp_inv[5] = 0;
		counter += 5;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	///////////////////////
	if (temp_board[0] == 4 && temp_ver[0] != 4 && temp_inv[6] != 4) {
		help_good1(board, 0, 4, borad_ver, board_ver_inv);
		temp_board[0] = 0;
		counter += 4;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_ver[0] == 4 && temp_board[0] != 4) {
		help_good2(borad_ver, 0, 4, board, board_ver_inv);
		temp_ver[0] = 0;
		counter += 4;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_inv[0] == 4 && temp_board[6] != 4) {
		help_good2(board_ver_inv, 0, 4, board, borad_ver);
		temp_inv[0] = 0;
		counter += 4;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	///////////////////////
	if (temp_board[6] == 4 && temp_ver[6] != 4 && temp_inv[0] != 4) {
		help_good1(board, 33, 37, borad_ver, board_ver_inv);
		temp_board[6] = 0;
		counter += 4;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_ver[6] == 4 && temp_board[0] != 4) {
		help_good2(borad_ver, 33, 37, board, board_ver_inv);
		temp_ver[6] = 0;
		counter += 4;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}
	if (temp_inv[6] == 4 && temp_board[6] != 4) {
		help_good2(board_ver_inv, 33, 37, board, borad_ver);
		temp_inv[6] = 0;
		counter += 4;
		al_play_sample(win, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		check_level();
	}



	///////////////////////
	for (int i = 0; i < 37; i++) {
		if (board[i].cell == false) {
			board[i].color[0] = false;
			board[i].color[1] = false;
			board[i].color[2] = false;
			board[i].drawn = false;
		}
	}
	/*for (int i = 0; i < 37; i++) {
		if (borad_ver[i].cell == false) {
			borad_ver[i].color[0] = false;
			borad_ver[i].color[1] = false;
			borad_ver[i].color[2] = false;
			for (int j = 0; j < 37; j++) {
				if ((borad_ver[i].x == board[j].x) && (borad_ver[i].y == board[j].y)) {
					board[j].color[0] = false;
					board[j].color[1] = false;
					board[j].color[2] = false;
					board[j].cell = false;
					board[j].drawn = false;
				}
				if ((borad_ver[i].x == board_ver_inv[j].x) && (borad_ver[i].y == board_ver_inv[j].y)) {
					board_ver_inv[j].color[0] = false;
					board_ver_inv[j].color[1] = false;
					board_ver_inv[j].color[2] = false;
					board_ver_inv[j].cell = false;
				}
			}
		}
	}
	for (int i = 0; i < 37; i++) {
		if (board_ver_inv[i].cell == false) {
			board_ver_inv[i].color[0] = false;
			board_ver_inv[i].color[1] = false;
			board_ver_inv[i].color[2] = false;
			for (int j = 0; j < 37; j++) {
				if ((board_ver_inv[i].x == board[j].x) && (board_ver_inv[i].y == board[j].y)) {
					board[j].color[0] = false;
					board[j].color[1] = false;
					board[j].color[2] = false;
					board[j].cell = false;
					board[j].drawn = false;
				}
				if ((board_ver_inv[i].x == borad_ver[j].x) && (board_ver_inv[i].y == borad_ver[j].y)) {
					borad_ver[j].color[0] = false;
					borad_ver[j].color[1] = false;
					borad_ver[j].color[2] = false;
					borad_ver[j].cell = false;
				}
			}
		}
	}*/
}
void check_good() {
	is_good_optimal();
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
			if (i < 3)
			{
				if ((board[i].cell == false) && (board[i + 1].cell == false) && (board[i + 5].cell == false) && (board[i + 10].cell == false) && (board[i + 11].cell == false))
				{
					temp = true;
				}
			}
			if (i > 3 && i < 8)
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
void check_help(ALLEGRO_MOUSE_STATE state) {
	save();
	if (soundd) {
		al_play_sample(end, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		soundd = false;
	}
	if (fiin) {
		al_draw_bitmap(finish, 0, 0, 0);
		al_draw_textf(font_number1, al_map_rgb(153, 102, 0), 720, 260, 0, "%s", score);
		al_draw_textf(font_number, al_map_rgb(153, 102, 0), 680, 100, 0, "%d", counter);
		al_draw_textf(font_number1, al_map_rgb(153, 102, 0), 710, 360, 0, "%d", counter/2);
		al_flip_display();
	}
	if ((state.buttons & 1) && (state.x >= 500) && (state.x <= 560) && (state.y >= 470) && (state.y <= 540)) {
		done = true;
		done_men = false;
		fiin = false;
		shutdown();
		init_menu();
		game_menu();
	}
	if ((state.buttons & 1) && (state.x >= 750) && (state.y >= 460) && (state.x <= 820) && (state.y <= 520)) {
		fiin = false;
		done = true;
		shutdown();
		done = false;
		init();
		al_play_sample(sound, 0.4, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
		game_loop();
	}
}
void check_end() {
	endcase = false;
	if (!des[0] && des[1] && des[2]) {
		if (!check_end_case(k2) && !check_end_case(k3))
		{
			endcase = true;
			soundd = true;
			fiin = true;
			star_count += (counter / 2);
			save();
		}

	}
	else if (!des[0] && !des[1] && des[2])
	{
		if (!check_end_case(k3))
		{
			endcase = true;
			soundd = true;
			fiin = true;
			star_count = star_count + (counter / 2);
			save();
		}
	}
	else if (!des[0] && des[1] && !des[2])
	{
		if (!check_end_case(k2))
		{
			endcase = true;
			soundd = true;
			fiin = true;
			star_count = star_count + (counter / 2);
			save();
		}
	}
	else if (des[0] && des[1] && !des[2])
	{
		if (!check_end_case(k1) && !check_end_case(k2))
		{
			endcase = true;
			soundd = true;
			fiin = true;
			star_count = star_count + (counter / 2);
			save();
		}
	}
	else if (des[0] && !des[1] && des[2])
	{
		if (!check_end_case(k1) && !check_end_case(k3))
		{
			endcase = true;
			soundd = true;
			fiin = true;
			star_count = star_count + (counter / 2);
			save();
		}
	}
	else if (des[0] && !des[1] && !des[2])
	{
		if (!check_end_case(k1))
		{
			endcase = true;
			soundd = true;
			fiin = true;
			star_count = star_count + (counter / 2);
			save();
		}
	}
	else if (des[0] && des[1] && des[2])
	{
		if (!check_end_case(k1) && !check_end_case(k2) && !check_end_case(k3))
		{
			endcase = true;
			soundd = true;
			fiin = true;
			star_count = star_count + (counter / 2);
			save();
		}
	}
}
void high_score() {
	int temp = -1;
	char i[10];
	file = fopen("HighScore.txt", "r");
	fgets(i,10,file);
	fclose(file);
	temp = atoi(i);
	if (counter > temp)
	{
		file = fopen("HighScore.txt", "w");
		sprintf(i, "%d", counter);
		fputs(i,file);
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
void draw_shape(int k, ele_pos e, int r,int g,int b) {
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
					al_draw_tinted_bitmap(q[i], al_map_rgb(r,g,b), board[i].x - 20, board[i].y, 0);
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
					al_draw_tinted_bitmap(q[i], al_map_rgb(r,g,b), board[i].x - 20, board[i].y, 0);
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
					al_draw_tinted_bitmap(q[i], al_map_rgb(r,g,b), board[i].x - 20, board[i].y, 0);
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
					al_draw_tinted_bitmap(q[i], al_map_rgb(r,g,b), board[i].x - 20, board[i].y, 0);
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
					al_draw_tinted_bitmap(q[i], al_map_rgb(r,g,b), board[i].x - 20, board[i].y, 0);
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
					al_draw_tinted_bitmap(q[i], al_map_rgb(r,g,b), board[i].x - 20, board[i].y, 0);
				}
			}
		}
	}
}
void draw(ALLEGRO_MOUSE_STATE state) {

	if (!des[0] && !des[1] && !des[2])
		doit = true;
	else
		doit = false;
	if (al_mouse_button_down(&state, 1)) {
		al_rest(0.08);
		if ((state.buttons & 1) && (state.x >= 640) && (state.x <= 670) && (state.y >= 20) && (state.y <= 70) && (star_count > 100))
		{
			star_count -= 100;
			doit = true;
			al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}
		if ((state.buttons & 1) && (state.x >= 640) && (state.x <= 670) && (state.y >= 20) && (state.y <= 70) && (star_count < 100))
			al_play_sample(no_access, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
	}
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
		des[0] = true; des[1] = true; des[2] = true;
		doit = false;
	}
	if (moves[0] && !moves[1] && !moves[2])
		e1 = er;
	else
		e1 = three_el[k1][0];
	if (moves[1] && !moves[0] && !moves[2])
		e2 = er;
	else
		e2 = three_el[k2][1];
	if (moves[2] && !moves[1] && !moves[0])
		e3 = er;
	else
		e3 = three_el[k3][2];
	al_draw_bitmap(back, 0, 0, 0);
	al_draw_bitmap(image, 50, 50, 0);
	al_draw_bitmap(star, 1200, 40, 0);
	al_draw_tinted_bitmap(trash, al_map_rgb(176, 82, 249), 650, 20, 0);
	al_draw_tinted_bitmap(hammer1, al_map_rgb(176,82,249), 720, 20, 0);
	al_draw_textf(font, al_map_rgb(153, 102, 0), 50, 10, 0, "SCORE: %d", counter);
	al_draw_textf(font, al_map_rgb(153, 102, 0), 1200, 10, 0, "LEVEL: %d", level);
	al_draw_textf(font, al_map_rgb(153, 102, 0), 1260, 50, 0, "%d", star_count);
		for (int i = 0; i < 37; i++) {
			board[i].check = false;
		}
		///////////start
		if (moves[0]) {
			draw_shape(k1, e1, 255, 105, 97);

		}
		else if (moves[1]) {
			draw_shape(k2, e2, 252, 247, 97);
		}
		else if (moves[2]) {
			draw_shape(k3, e3, 203, 153, 201);
		}
		//////////end
		if (des[0]) {
			switch (k1)
			{
			case 0:
				al_draw_tinted_bitmap(q1, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
				break;
			case 1:
				al_draw_tinted_bitmap(q2, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
				break;
			case 2:
				al_draw_tinted_bitmap(q3, al_map_rgb(255, 0, 0), e1.x, e1.y-70, 0);
				break;
			case 3:
				al_draw_tinted_bitmap(q4, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
				break;
			case 4:
				al_draw_tinted_bitmap(q5, al_map_rgb(255, 0, 0), e1.x, e1.y-35, 0);
				break;
			case 5:
				al_draw_tinted_bitmap(q6, al_map_rgb(255, 0, 0), e1.x, e1.y, 0);
				break;
			default:
				break;
			}
		}
		if (des[1]) {
			switch (k2)
			{
			case 0:
				al_draw_tinted_bitmap(q1, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
				break;
			case 1:
				al_draw_tinted_bitmap(q2, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
				break;
			case 2:
				al_draw_tinted_bitmap(q3, al_map_rgb(255, 255, 0), e2.x, e2.y-70, 0);
				break;
			case 3:
				al_draw_tinted_bitmap(q4, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
				break;
			case 4:
				al_draw_tinted_bitmap(q5, al_map_rgb(255, 255, 0), e2.x, e2.y-35, 0);
				break;
			case 5:
				al_draw_tinted_bitmap(q6, al_map_rgb(255, 255, 0), e2.x, e2.y, 0);
				break;
			default:
				break;
			}
		}
		if (des[2]) {
			switch (k3)
			{
			case 0:
				al_draw_tinted_bitmap(q1, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
				break;
			case 1:
				al_draw_tinted_bitmap(q2, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
				break;
			case 2:
				al_draw_tinted_bitmap(q3, al_map_rgb(255, 0, 255), e3.x, e3.y-70, 0);
				break;
			case 3:
				al_draw_tinted_bitmap(q4, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
				break;
			case 4:
				al_draw_tinted_bitmap(q5, al_map_rgb(255, 0, 255), e3.x, e3.y-35, 0);
				break;
			case 5:
				al_draw_tinted_bitmap(q6, al_map_rgb(255, 0, 255), e3.x, e3.y, 0);
				break;
			default:
				break;
			}
		}
		for (int i = 0; i < 37; i++) {
			if (board[i].color[0] && !board[i].color[1] && !board[i].color[2] && board[i].drawn) {
				q[i] = q9;
				al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 0), board[i].x - 20, board[i].y, 0);
			}
			else if (board[i].color[1] && !board[i].color[0] && !board[i].color[2] && board[i].drawn) {
				q[i] = q9;
				al_draw_tinted_bitmap(q[i], al_map_rgb(255, 255, 0), board[i].x - 20, board[i].y, 0);
			}
			else if (board[i].color[2] && !board[i].color[0] && !board[i].color[1] && board[i].drawn) {
				q[i] = q9;
				al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 255), board[i].x - 20, board[i].y, 0);
			}
		}
		for (int i = 0; i < 37; i++) {
			if (board[i].color[0] && !board[i].color[1] && !board[i].color[2] && !board[i].drawn) {
				q[i] = q9;
				al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 0), board[i].x - 20, board[i].y , 0);
				al_flip_display();
				al_play_sample(pop, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				al_rest(0.16);
				board[i].drawn = true;
			}
			else if (board[i].color[1] && !board[i].color[0] && !board[i].color[2] && !board[i].drawn) {
				q[i] = q9;
				al_draw_tinted_bitmap(q[i], al_map_rgb(255, 255, 0), board[i].x - 20, board[i].y, 0);
				al_flip_display();
				al_play_sample(pop, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				al_rest(0.16);
				board[i].drawn = true;
			}
			else if (board[i].color[2] && !board[i].color[0] && !board[i].color[1] && !board[i].drawn) {
				q[i] = q9;
				al_draw_tinted_bitmap(q[i], al_map_rgb(255, 0, 255), board[i].x - 20, board[i].y , 0);
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
				al_rest(0.15);
				board[j].wow = false;
			}
		}
		if (al_mouse_button_down(&state, 1)) {
			if ((state.buttons & 1) && (state.x >= 720) && (state.x <= 750) && (state.y >= 20) && (state.y <= 70))
			{
				al_rest(0.08);
				states = !states;
				printf("States = %d \n", states);
				if ((star_count > 100) && states) {
					al_play_sample(click, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					for (int i = 0; i < 37; i++) {
						if (board[i].cell)
						{
							board[i].hammer = true;
						}
					}
				}
				else {
					al_play_sample(no_access, 0.25, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					for (int i = 0; i < 37; i++) {
						board[i].hammer = false;
					}
				}
			}
		}
		else if (star_count < 100) {
			for (int i = 0; i < 37; i++) {
				board[i].hammer = false;
			}
		}
		for (int i = 0; i < 37; i++) {
			if (board[i].hammer)
			{
				al_draw_bitmap(hammer, board[i].x, board[i].y+8, 0);
			}
		}
		for (int i = 0; i < 37; i++) {
			if ((star_count > 100 ) && (state.buttons & 1 ) && board[i].hammer && board[i].cell && states && (state.x >= board[i].x) && (state.x <= board[i].x + 40) && (state.y >= board[i].y) && (state.y <= board[i].y + 40))
			{
				star_count -= 100;
				board[i].cell = false;
				board[i].color[0] = false;
				board[i].color[1] = false;
				board[i].color[2] = false;
				board[i].wow = true;
				board[i].hammer = false;
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
			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);

			if (!soundd && !fiin) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				high_score();
				draw(state);
				al_flip_display();
				//al_draw_textf(font, al_map_rgb(153, 102, 0), 850, 150, 0, "HIGH SCORE: %s", score);
				//ALLEGRO_MOUSE_STATE state;
				//al_get_mouse_state(&state);
				/*	if (state.buttons & 1) {
						// Primary (e.g. left) mouse button is held.
						printf("Mouse position: (%d, %d)--", state.x, state.y);
					}
					if (state.buttons & 2) {
						// Secondary (e.g. right) mouse button is held.
					}
					if (state.buttons & 4) {
						// Tertiary (e.g. middle) mouse button is held.
					}*/
				draww = false;
				check_end();
			}
			else 
			{
				draw(state);
				moves[0] = true;
				moves[1] = true;
				moves[2] = true;
				check_help(state);
			}
		}
	}
}
void save() {
	cases c = { k1,k2,k3,counter,level,star_count,des[0],des[1],des[2],endcase };

	board_file = fopen("board.dat", "w");
	fwrite(&board, sizeof(board), 1, board_file);
	fclose(board_file);

	ver_file = fopen("ver_board.dat", "w");
	fwrite(&borad_ver, sizeof(borad_ver), 1, ver_file);
	fclose(ver_file);

	inver_file = fopen("inver_board.dat", "w");
	fwrite(&board_ver_inv, sizeof(borad_ver), 1, inver_file);
	fclose(inver_file);

	score_file = fopen("score.dat", "w");
	fwrite(&c, sizeof(cases), 1, score_file);
	fclose(score_file);

}
void init_resum() {
	done_men = false;
	cases c;
	ele_pos pos[37];
	int i = 0;
	board_file = fopen("board.dat", "r");
	fread(&pos, sizeof(pos), 1, board_file);
	for (int i = 0; i < 37;i++)
		board[i] = pos[i];
	fclose(board_file);

	ver_file = fopen("ver_board.dat", "r");
	fread(&pos, sizeof(pos), 1, ver_file);
	for (int i = 0; i < 37; i++)
		borad_ver[i] = pos[i];
	fclose(ver_file);

	inver_file = fopen("inver_board.dat", "r");
	fread(&pos, sizeof(pos), 1, inver_file);
	for (int i = 0; i < 37; i++)
		board_ver_inv[i] = pos[i];
	fclose(inver_file);

	score_file = fopen("score.dat", "r");
	fread(&c, sizeof(cases), 1, score_file);
	k1 = c.k1;
	k2 = c.k2;
	k3 = c.k3;
	des[0] = c.d1;
	des[1] = c.d2;
	des[2] = c.d3;
	counter = c.counter;
	level = c.level;
	endcase = c.endcase;
	star_count = c.star;
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
}