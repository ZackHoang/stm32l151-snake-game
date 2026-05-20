#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// static int score = 0;
static uint8_t snake_pos = 50;

struct {
	uint8_t x;
	uint8_t y;
} health_pos;

void randomize_health() {
	health_pos.x = std::rand() % 129;
	health_pos.y = std::rand() % 65;
}

void draw_snake() {
	for (int i = snake_pos; i >= 0; i--) {
		view_render.drawPixel(i, 10, BLACK);
	}
	snake_pos++;
	for (int i = snake_pos; i >= 0; i--) {
		view_render.drawPixel(i, 10, WHITE);
	}
}

void task_draw_snake(ak_msg_t* msg) {
	switch (msg->sig) {
		case (CHANGE_POS): {
			draw_snake();
		}
	}
}

void render_game_screen()
{
	view_render.clear();
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