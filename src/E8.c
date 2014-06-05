#include "pebble.h"
#include "conversion.h"
#include "constant_def.h"
/************************************************************************/
/* This is a Pebble Watchface inspired by the E8 Watch by Lexon.		*/
/* Made By Clement Guillou												*/
/*																		*/
/* Version : 1.3														*/
/* Version note : optimisations, use of rect instead of images			*/
/*																		*/
/* 2.2 SDK																*/
/*																		*/
/************************************************************************/

// HANDLER FOR BATTERY
static void handle_battery(BatteryChargeState charge_state) {
	uint8_t charge_value = charge_state.charge_percent;
	
	bool charging = charge_state.is_charging;
	
	if (charging == 0) {
		charge_round = ((charge_value - (charge_value%10))/10);
		layer_mark_dirty(bat_back_layer);
	}

	else
		charge_round = 11;
	layer_mark_dirty(bat_back_layer);
	
}

// TIME DISPLAY UPDATE CALLBACK
static void layer_update_callback(Layer *me, GContext *ctx) {
	
	int hour_t = conversion_from_time_to_hour();
	int min_t = conversion_from_time_to_minute();
	
	if (!clock_is_24h_style()) {
		if (hour_t >12) {
			hour_t = hour_t - 12;
		}
	}

	
	int ten_of_hour_t = convert_to_ten_of_hour(hour_t);
	int one_of_hour_t = convert_to_one_of_hour(hour_t);

	int ten_of_minute_t = convert_to_ten_of_minute(min_t);
	int one_of_minute_t = convert_to_one_of_minute(min_t);

	
	graphics_context_set_stroke_color	(ctx, GColorWhite);
	
	//TEN OF THE HOURS
	for (int itth = 0; itth < ten_of_hour_t; itth++) {
		graphics_draw_rect(ctx, (GRect) { .origin = {8, 148 - (itth*18) }, .size = { 24, 15 }});
		graphics_fill_rect(ctx, (GRect) { .origin = {8, 148 - (itth*18) }, .size = { 24, 15 }}, 0, GCornerNone);
	}
	
	//ONE OF THE HOURS
	for (int ioth = 0; ioth < one_of_hour_t; ioth++) {
		graphics_draw_rect(ctx, (GRect) { .origin = {36, 148 - (ioth*18) }, .size = { 24, 15 }});
		graphics_fill_rect(ctx, (GRect) { .origin = {36, 148 - (ioth*18) }, .size = { 24, 15 }}, 0, GCornerNone);
	}
	
	// TEN OF THE MINUTES
	for (int ittm = 0; ittm < ten_of_minute_t; ittm++) {
		graphics_draw_rect(ctx, (GRect) { .origin = {84, 148 - (ittm*18) }, .size = { 24, 15 }});
		graphics_fill_rect(ctx, (GRect) { .origin = {84, 148 - (ittm*18) }, .size = { 24, 15 }}, 0, GCornerNone);
	}
	
	// ONE OF THE MINUTES
	for (int iotm = 0; iotm <one_of_minute_t; iotm++) {
		graphics_draw_rect(ctx, (GRect) { .origin = {112, 148 - (iotm*18) }, .size = { 24, 15 }});
		graphics_fill_rect(ctx, (GRect) { .origin = {112, 148 - (iotm*18) }, .size = { 24, 15 }}, 0, GCornerNone);
	}
	
}
// BACKGROUND UPDATE CALLBACK
static void layer_update_callback_background(Layer *me, GContext *ctx) {

	GRect bounds = background_image->bounds;
	
	graphics_draw_bitmap_in_rect(ctx, background_image, (GRect) { .origin = { 0, 0 }, .size = bounds.size});
	
}
// BAT UPDATE CALLBACK
static void layer_update_callback_bat_back(Layer *me, GContext *ctx) {

	GRect bounds_bat_back = bat_back->bounds;
	
	if (charge_round == 11) {
		graphics_draw_bitmap_in_rect(ctx, bat_charging, (GRect) { .origin = { 10, 8 }, .size = bounds_bat_back.size });
		
	}
	
	else {
		graphics_draw_bitmap_in_rect(ctx, bat_back, (GRect) { .origin = { 10, 8 }, .size = bounds_bat_back.size });
		graphics_context_set_stroke_color(ctx, GColorBlack);
		graphics_context_set_fill_color(ctx, GColorWhite);
	
		graphics_fill_rect(ctx, GRect(13, 11, (int)(charge_round), 4), 0, GCornerNone);
	}
	
}

// HANDLER FOR TIME
static void handle_minute_tick(struct tm* tick_time, TimeUnits units_changed) {
	
	layer_mark_dirty(image_layer);
}

// INIT
void init(void) {
	
	window = window_create();
	window_stack_push(window, true);
	window_set_background_color(window, GColorBlack);
	
	Layer *window_layer = window_get_root_layer(window);
	
	GRect bounds = layer_get_frame(window_layer);

	
	time_layer = text_layer_create(bounds);
	layer_add_child(window_layer, text_layer_get_layer(time_layer));
	
	background_layer = layer_create(bounds);
	layer_set_update_proc(background_layer, layer_update_callback_background);
	layer_add_child(text_layer_get_layer(time_layer), background_layer);
	
	
	image_layer = layer_create(bounds);
	bat_back_layer = layer_create(bounds);
	
	
	layer_set_update_proc(image_layer, layer_update_callback);
	layer_add_child(background_layer, image_layer);
	
	layer_set_update_proc(bat_back_layer, layer_update_callback_bat_back);
	layer_add_child(window_layer, bat_back_layer);
	
	

	

	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	handle_minute_tick(current_time, SECOND_UNIT);
	tick_timer_service_subscribe(SECOND_UNIT, &handle_minute_tick);
	

	battery_state_service_subscribe(&handle_battery);

	background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
	bat_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT_BACK);
	bat_charging = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT_CHARGING);

	handle_battery(battery_state_service_peek());	
		
}

// DEINIT
void deinit(void) {
	
	tick_timer_service_unsubscribe();
	battery_state_service_unsubscribe();
	
	gbitmap_destroy(bat_back);
	gbitmap_destroy(bat_charging);
	
	
	layer_destroy(background_layer);
	layer_destroy(image_layer);
	layer_destroy(bat_back_layer);
	layer_destroy(bat_charging_layer);
	
	text_layer_destroy(time_layer);


    window_destroy(window);

}

// MAIN
int main(void) {
	srand(time(NULL));
	init();
	app_event_loop();
	deinit();
}
