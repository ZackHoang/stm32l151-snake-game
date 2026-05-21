#include "game.h"
#include <math.h>

// static int score = 0;
static uint8_t snake_pos = 50;
static uint8_t snake_length = 50;

struct {
	uint8_t x;
	uint8_t y;
} health_pos;

void render_game_over() {
	view_render.drawBitmap(8, 6, image_cry_dolph_bits, 55, 32, WHITE);
}

view_dynamic_t dyn_view_scr_game_over = {
		{
				.item_type = ITEM_TYPE_DYNAMIC,
		},
		render_game_over,
};

view_screen_t scr_game_over = {
		&dyn_view_scr_game_over,
		ITEM_NULL,
		ITEM_NULL,
		.focus_item = 0,
};

void randomize_health() {
	health_pos.x = rand() % 129;
	health_pos.y = rand() % 65;
}

void draw_snake() {
	if (snake_pos > 128) {
		SCREEN_TRAN(task_game_over, &scr_game_over);
	}
	for (int i = snake_pos; i >= snake_pos - snake_length; i--) {
		view_render.drawPixel(i, 10, BLACK);
	}
	snake_pos += 5;
	for (int i = snake_pos; i >= snake_pos - snake_length; i--) {
		view_render.drawPixel(i, 10, WHITE);
	}
}

void task_draw_snake(ak_msg_t* msg) {
	switch (msg->sig) {
		case (CHANGE_POS): {
			view_render_screen(&scr_game);
		}
	}
}

void render_game_screen()
{
	draw_snake();
	timer_set(TASK_UPDATE_POS, CHANGE_POS, 1000, TIMER_PERIODIC);
	view_render.drawBitmap(20, 50, image_health, health_pos.x, health_pos.y, WHITE);
}

view_dynamic_t dyn_view_scr_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	render_game_screen,
};

view_screen_t scr_game = {
	&dyn_view_scr_game,
	ITEM_NULL,
	ITEM_NULL,
	.focus_item = 0,
};



void task_game(ak_msg_t* msg) {}

void task_game_over(ak_msg_t* msg) {
	switch (msg->sig)
	{
	case GAME_OVER:
		view_render_screen(&scr_game_over);
		break;

	default:
		break;
	}
}