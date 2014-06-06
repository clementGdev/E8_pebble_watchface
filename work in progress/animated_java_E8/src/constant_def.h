#ifndef CONSTANT_DEF_H
#define CONSTANT_DEF_H

static Window *window;

static Layer *image_layer;
static Layer *bat_back_layer;
static Layer *bat_charging_layer;
static Layer *animated_layer;

static InverterLayer *inverter_layer;
static Layer *inverter_root_layer;

static Layer *background_layer;

static GBitmap *background_image;
static TextLayer *time_layer;

static GBitmap *bat_back;
static GBitmap *bat_charging;
//static GBitmap *animated_rect;

bool inverted;

static int charge_round;

#endif
