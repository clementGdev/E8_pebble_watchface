/************************************************************************/
/* This is a Pebble Watchface inspired by the E8 Watch by Lexon.		*/
/* Made By Clement Guillou												*/
/* Date : 6/6/14														*/
/*																		*/
/* Version : 1.3														*/
/* Version note : optimisations, use of rect instead of images			*/
/*																		*/
/* 2.2 SDK																*/
/************************************************************************/

#include "pebble.h"
#include "constant_def.h"
#include "conversion.h"

#define KEY_INVERT 0
#define	KEY_BATTERY 1


static int battery;
static int flag = 0;
static int flag2 = 0;

void on_animation_stopped(Animation *anim, bool finished, void *context)
{
    //Free the memory used by the Animation
    property_animation_destroy((PropertyAnimation*) anim);
	flag2 = 1;
}

void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration, int delay)
{
    //Declare animation
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, start, finish);
	
    //Set characteristics
    animation_set_duration((Animation*) anim, duration);
    animation_set_delay((Animation*) anim, delay);
	
    //Set stopped handler to free memory
    AnimationHandlers handlers = {
        //The reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);
	
    //Start animation!
    animation_schedule((Animation*) anim);
}

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
	
	if (flag2 == 0) {
		if (one_of_minute_t != 0) {
			one_of_minute_t = one_of_minute_t - 1;
		}
		else if (ten_of_minute_t != 0) {
			ten_of_minute_t = ten_of_minute_t -1;
		}
		else if (one_of_hour_t != 0) {
			one_of_hour_t = one_of_hour_t -1;
		}
		else if (ten_of_hour_t != 0) {
			ten_of_hour_t = ten_of_hour_t -1;
		}
		
	}
	
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

// ANIMATION
static void layer_update_callback_animated(Layer *me, GContext *ctx) {
	
	graphics_context_set_stroke_color	(ctx, GColorWhite);
	graphics_draw_rect(ctx, (GRect) { .origin = {0, 0 }, .size = { 24, 15 }});
	graphics_fill_rect(ctx, (GRect) { .origin = {0, 0 }, .size = { 24, 15 }}, 0, GCornerNone);

	
}

static void layer_update_callback_background(Layer *me, GContext *ctx) {

	GRect bounds = background_image->bounds;
	
	graphics_draw_bitmap_in_rect(ctx, background_image, (GRect) { .origin = { 0, 0 }, .size = bounds.size});
	
}

static void layer_update_callback_bat_back(Layer *me, GContext *ctx) {

	GRect bounds_bat_back = bat_back->bounds;
	if (battery == 1) {
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
	
	else if (battery == 2) {
		if (charge_round == 11) {
			graphics_draw_bitmap_in_rect(ctx, bat_charging, (GRect) { .origin = { 10, 8 }, .size = bounds_bat_back.size });
			
		}
		
		else if (charge_round <= 2) {
			graphics_draw_bitmap_in_rect(ctx, bat_back, (GRect) { .origin = { 10, 8 }, .size = bounds_bat_back.size });
			graphics_context_set_stroke_color(ctx, GColorBlack);
			graphics_context_set_fill_color(ctx, GColorWhite);
			
			graphics_fill_rect(ctx, GRect(13, 11, (int)(charge_round), 4), 0, GCornerNone);
		}
	}
	
	else if (battery == 3) {
		if (charge_round == 11) {
			graphics_draw_bitmap_in_rect(ctx, bat_charging, (GRect) { .origin = { 10, 8 }, .size = bounds_bat_back.size });
			
		}
	}
	
	
	if (inverted == true) {
		inverter_root_layer = inverter_layer_get_layer(inverter_layer);
		layer_add_child(bat_back_layer, inverter_root_layer);
	}
	else layer_remove_child_layers(bat_back_layer);

	
}



// HANDLER FOR TIME
static void handle_minute_tick(struct tm* tick_time, TimeUnits units_changed) {
	
	int seconds_anim = tick_time->tm_sec;
	int minutes_anim = tick_time->tm_min;
	int hour_anim = tick_time->tm_hour;
	
	int ten_of_hour_anim = convert_to_ten_of_hour(hour_anim);
	int one_of_hour_anim = convert_to_one_of_hour(hour_anim);
	
	int ten_of_minute_anim = convert_to_ten_of_minute(minutes_anim);
	int one_of_minute_anim = convert_to_one_of_minute(minutes_anim);

	
	APP_LOG(APP_LOG_LEVEL_DEBUG," one of hours = %d", one_of_hour_anim);

	
   // if(seconds_anim == 59)
    //{

		
		if (one_of_minute_anim == 0) {
			
			if (ten_of_minute_anim == 0) {
				
				if (one_of_hour_anim == 0) {
					
					
					if (flag == 1) {
						// Slide from the top on ten of hour column
						GRect start = GRect(8, -30, 144, 168);
						GRect finish = GRect(8, 148 - ((ten_of_hour_anim - 1)*18), 144, 168);
						animate_layer(animated_layer, &start, &finish, 600, 0);
					}
					else {
						flag = 1;

					}
				}
				else {
					
					if (flag == 1) {
						//Slide from the top on one of hour column
						GRect start = GRect(36, -30, 144, 168);
						GRect finish = GRect(36, 148 - ((one_of_hour_anim - 3)*18), 144, 168);
						animate_layer(animated_layer, &start, &finish, 600, 0);
					}
					else {
						flag = 1;

					}
				
				}
			}
			
			else {
				if (flag == 1) {
					//Slide from the top on ten of minutes
					GRect start = GRect(84, -30, 144, 168);
					GRect finish = GRect(84, 148 - ((ten_of_minute_anim - 1)*18), 144, 168);
					animate_layer(animated_layer, &start, &finish, 600, 0);
				}
				else {
					flag = 1;

				}
			
			}
		}
		
		else {
			if (flag == 1) {
				//Slide from the top on one of minutes
				GRect start = GRect(112, -30, 144, 168);
				GRect finish = GRect(112, 148 - ((one_of_minute_anim - 1)*18), 144, 168);
				animate_layer(animated_layer, &start, &finish, 450, 0);
			}
			else {
				flag = 1;

			}
        
		}

	


	flag2 = 0;

		layer_mark_dirty(animated_layer);

	
}

static void in_recv_handler(DictionaryIterator *iterator, void *context)
{
	
	//Get Tuple
	Tuple *t = dict_read_first(iterator);
	while(t)
	{
		switch(t->key)
		{
			case KEY_INVERT:
				//It's the KEY_INVERT key
				if(strcmp(t->value->cstring, "on") == 0)
				{
					layer_mark_dirty(bat_back_layer);
					persist_write_bool(KEY_INVERT, true);
					inverted = true;
				}
				else if(strcmp(t->value->cstring, "off") == 0)
				{
					layer_mark_dirty(bat_back_layer);
					persist_write_bool(KEY_INVERT, false);
					inverted = false;
				}
				break;
			case KEY_BATTERY:
				//It's the KEY_BATTERY key
				if(strcmp(t->value->cstring, "on") == 0)
				{
					layer_mark_dirty(bat_back_layer);
					persist_write_bool(KEY_BATTERY, true);
					battery = 1;
				}
				else if(strcmp(t->value->cstring, "low") == 0)
				{
					layer_mark_dirty(bat_back_layer);
					persist_write_bool(KEY_BATTERY, false);
					battery = 2;
				}
				
				else if(strcmp(t->value->cstring, "off") == 0)
				{
					layer_mark_dirty(bat_back_layer);
					persist_write_int(KEY_BATTERY, 3);
					battery = 3;
				}
				break;

		}
		t = dict_read_next(iterator);
	}
}

void init(void)
{
	
	window = window_create();
	window_stack_push(window, true);
	window_set_background_color(window, GColorBlack);
	
	inverted = persist_read_bool(KEY_INVERT);
	battery = persist_read_int(KEY_BATTERY);
	
	Layer *window_layer = window_get_root_layer(window);
	
	GRect bounds = layer_get_frame(window_layer);

	
	time_layer = text_layer_create(bounds);
	layer_add_child(window_layer, text_layer_get_layer(time_layer));
	
	background_layer = layer_create(bounds);
	layer_set_update_proc(background_layer, layer_update_callback_background);
	layer_add_child(text_layer_get_layer(time_layer), background_layer);
	
	
	image_layer = layer_create(bounds);
	bat_back_layer = layer_create(bounds);
	animated_layer = layer_create((GRect) { .origin = {0, -30 }, .size = { 160, 190 }});
	
	
	layer_set_update_proc(animated_layer, layer_update_callback_animated);
	layer_add_child(image_layer, animated_layer);
	
	layer_set_update_proc(image_layer, layer_update_callback);
	layer_add_child(background_layer, image_layer);
	
	layer_set_update_proc(bat_back_layer, layer_update_callback_bat_back);
	layer_add_child(window_layer, bat_back_layer);

	
	
	
	app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
		

	inverter_layer = inverter_layer_create(bounds);
	
	layer_add_child(background_layer, animated_layer);

	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	handle_minute_tick(current_time, MINUTE_UNIT);
	tick_timer_service_subscribe(MINUTE_UNIT, &handle_minute_tick);
	

	battery_state_service_subscribe(&handle_battery);
	
	background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
	bat_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT_BACK);
	bat_charging = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT_CHARGING);

	handle_battery(battery_state_service_peek());

	
		
}


void deinit(void) {
	
	tick_timer_service_unsubscribe();
	battery_state_service_unsubscribe();
	
	gbitmap_destroy(bat_back);
	gbitmap_destroy(bat_charging);
	
	layer_destroy(animated_layer);
	inverter_layer_destroy(inverter_layer);
	layer_destroy(inverter_root_layer);
	layer_destroy(background_layer);
	layer_destroy(image_layer);
	layer_destroy(bat_back_layer);
	layer_destroy(bat_charging_layer);
	
	text_layer_destroy(time_layer);


    window_destroy(window);

}


int main(void) {
	srand(time(NULL));
	init();
	app_event_loop();
	deinit();
}
