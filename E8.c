// E8.c


#include "pebble.h"

// This is a Pebble Watchface inspired by the E8 Watch by Lexon.
// Made By Clement Guillou

static Window *window;

static Layer *image_layer;
static Layer *bat_back_layer;
static Layer *bat_charging_layer;

static Layer *background_layer;

static GBitmap *background_image;
static TextLayer *time_layer;

static GBitmap *image0;
static GBitmap *image1;
static GBitmap *image2;
static GBitmap *image3;
static GBitmap *image4;
static GBitmap *image5;
static GBitmap *image6;
static GBitmap *image7;
static GBitmap *image8;
static GBitmap *image9;
static GBitmap *bat_back;
static GBitmap *bat_charging;

static int charge_round;
// Get the hour
int conversion_from_time_to_hour(void) {
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	int hour = t->tm_hour;
	return hour;
}
// Get the minutes
int conversion_from_time_to_minute(void) {
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	int minute = t->tm_min;
	return minute;
}
// Get the ten of the hour
int convert_to_ten_of_hour(int h){
	int ten_of_hour;
	int one_of_h = h % 10;
	ten_of_hour = h - one_of_h;
	ten_of_hour = ten_of_hour / 10;
	return ten_of_hour;
}
// Get the one of the hour
int convert_to_one_of_hour(int h){
	int one_of_hour = h % 10;
	return one_of_hour;
}
// Get the ten of the minutes
int convert_to_ten_of_minute(int m){
	int ten_of_minute;
	int one_of_min = m % 10;
	ten_of_minute = m - one_of_min;
	ten_of_minute = ten_of_minute / 10;
	return ten_of_minute;
}
// Get the one of the minutes
int convert_to_one_of_minute(int m){
	int one_of_minute = m % 10;
	return one_of_minute;
}
// Battery Handle Routine
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
// Layer update
static void layer_update_callback(Layer *me, GContext *ctx) {

	GRect bounds0 = image0->bounds;
	GRect bounds9 = image9->bounds;
	
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

	// TEN OF HOUR
	switch (ten_of_hour_t) {
		case 0:
			graphics_draw_bitmap_in_rect(ctx, image0, (GRect) { .origin = { 7, 130 }, .size = bounds0.size});
			break;
			
		case 1:
			graphics_draw_bitmap_in_rect(ctx, image1, (GRect) { .origin = { 7, 130 }, .size = bounds0.size});
			break;
			
		case 2:
			graphics_draw_bitmap_in_rect(ctx, image2, (GRect) { .origin = { 7, 130 }, .size = bounds0.size});
			break;
		default:
			break;
	}
	// ONE OF HOUR
	switch (one_of_hour_t) {
		case 0:
			graphics_draw_bitmap_in_rect(ctx, image0, (GRect) { .origin = { 35, 130 }, .size = bounds0.size});
			break;
			
		case 1:
			graphics_draw_bitmap_in_rect(ctx, image1, (GRect) { .origin = { 35, 130 }, .size = bounds0.size});
			break;
			
		case 2:
			graphics_draw_bitmap_in_rect(ctx, image2, (GRect) { .origin = { 35, 130 }, .size = bounds0.size});
			break;
			
		case 3:
			graphics_draw_bitmap_in_rect(ctx, image3, (GRect) { .origin = { 35, 3 }, .size = bounds9.size});
			break;
			
		case 4:
			graphics_draw_bitmap_in_rect(ctx, image4, (GRect) { .origin = { 35, 3 }, .size = bounds9.size});
			break;
			
		case 5:
			graphics_draw_bitmap_in_rect(ctx, image5, (GRect) { .origin = { 35, 3 }, .size = bounds9.size});
			break;
			
		case 6:
			graphics_draw_bitmap_in_rect(ctx, image6, (GRect) { .origin = { 35, 3 }, .size = bounds9.size});
			break;
			
		case 7:
			graphics_draw_bitmap_in_rect(ctx, image7, (GRect) { .origin = { 35, 3 }, .size = bounds9.size});
			break;
			
		case 8:
			graphics_draw_bitmap_in_rect(ctx, image8, (GRect) { .origin = { 35, 3 }, .size = bounds9.size});
			break;
			
		case 9:
			graphics_draw_bitmap_in_rect(ctx, image9, (GRect) { .origin = { 35, 3 }, .size = bounds9.size});
			break;
		
		default:
			break;
	}
	// TEN OF MINUTE
	switch (ten_of_minute_t) {
		case 0:
			graphics_draw_bitmap_in_rect(ctx, image0, (GRect) { .origin = { 83, 130 }, .size = bounds0.size});
			break;
			
		case 1:
			graphics_draw_bitmap_in_rect(ctx, image1, (GRect) { .origin = { 83, 130 }, .size = bounds0.size});
			break;
			
		case 2:
			graphics_draw_bitmap_in_rect(ctx, image2, (GRect) { .origin = { 83, 130 }, .size = bounds0.size});
			break;
			
		case 3:
			graphics_draw_bitmap_in_rect(ctx, image3, (GRect) { .origin = { 83, 3 }, .size = bounds9.size});
			break;
			
		case 4:
			graphics_draw_bitmap_in_rect(ctx, image4, (GRect) { .origin = { 83, 3 }, .size = bounds9.size});
			break;
			
		case 5:
			graphics_draw_bitmap_in_rect(ctx, image5, (GRect) { .origin = { 83, 3 }, .size = bounds9.size});
			break;
		default:
			break;
	}
	// ONE OF MINUTE
	switch (one_of_minute_t) {
		case 0:
			graphics_draw_bitmap_in_rect(ctx, image0, (GRect) { .origin = { 111, 130 }, .size = bounds0.size});
			break;
			
		case 1:
			graphics_draw_bitmap_in_rect(ctx, image1, (GRect) { .origin = { 111, 130 }, .size = bounds0.size});
			break;
			
		case 2:
			graphics_draw_bitmap_in_rect(ctx, image2, (GRect) { .origin = { 111, 130 }, .size = bounds0.size});
			break;
			
		case 3:
			graphics_draw_bitmap_in_rect(ctx, image3, (GRect) { .origin = { 111, 3 }, .size = bounds9.size});
			break;
			
		case 4:
			graphics_draw_bitmap_in_rect(ctx, image4, (GRect) { .origin = { 111, 3 }, .size = bounds9.size});
			break;
			
		case 5:
			graphics_draw_bitmap_in_rect(ctx, image5, (GRect) { .origin = { 111, 3 }, .size = bounds9.size});
			break;
			
		case 6:
			graphics_draw_bitmap_in_rect(ctx, image6, (GRect) { .origin = { 111, 3 }, .size = bounds9.size});
			break;
			
		case 7:
			graphics_draw_bitmap_in_rect(ctx, image7, (GRect) { .origin = { 111, 3 }, .size = bounds9.size});
			break;
			
		case 8:
			graphics_draw_bitmap_in_rect(ctx, image8, (GRect) { .origin = { 111, 3 }, .size = bounds9.size});
			break;
			
		case 9:
			graphics_draw_bitmap_in_rect(ctx, image9, (GRect) { .origin = { 111, 3 }, .size = bounds9.size});
			break;
		default:
			break;
	}
}
// background update
static void layer_update_callback_background(Layer *me, GContext *ctx) {
	GRect bounds = background_image->bounds;
	graphics_draw_bitmap_in_rect(ctx, background_image, (GRect) { .origin = { 0, 0 }, .size = bounds.size});
}
// battery display update
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
void init(void)
{
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

	image0 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_0);
	image1 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_1);
	image2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_2);
	image3 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_3);
	image4 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_4);
	image5 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_5);
	image6 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_6);
	image7 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_7);
	image8 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_8);
	image9 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_COLUMN_9);
	background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
	bat_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT_BACK);
	bat_charging = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT_CHARGING);

	handle_battery(battery_state_service_peek());	
		
}

// DEINIT
void deinit(void) {
	
	tick_timer_service_unsubscribe();
	battery_state_service_unsubscribe();
	
	gbitmap_destroy(image0);
	gbitmap_destroy(image1);
	gbitmap_destroy(image2);
	gbitmap_destroy(image3);
	gbitmap_destroy(image4);
	gbitmap_destroy(image5);
	gbitmap_destroy(image6);
	gbitmap_destroy(image7);
	gbitmap_destroy(image8);
	gbitmap_destroy(image9);
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