#pragma once

#include "Utils.h"

#define MIN_THRESHOLD 0.001f

static const Vec2 TOP_PATH_POINTS[] = {
        {160.0f,  220.0f},
        {240.0f,  220.0f},
        {385.0f,  220.0f},
        {385.0f,  505.0f},
        {570.0f,  505.0f},
        {570.0f,  630.0f},
        {640.0f,  630.0f},
        {640.0f,  660.0f},
        {960.0f,  660.0f},
        {960.0f,  160.0f},
        {1000.0f, 160.0f},
        {1000.0f, 110.0f},
        {1055.0f, 110.0f},
        {1055.0f, 25.0f},
        {1410.0f, 25.0f},
        {1410.0f, 220.0f},
        {1180.0f, 220.0f},
        {1180.0f, 500.0f},
        {1205.0f, 500.0f},
        {1205.0f, 525.0f},
        {1440.0f, 525.0f},
        {1440.0f, 400.0f}
};
static const int TOP_PATH_LENGTH = 22;

static const Vec2 TOP_SPAWN_POINT = {
        .x = 165.0, .y = 0.0f
};

static const Vec2 LAKE_PATH_POINTS[] = {
        {325.0f,  505.0f},
        {385.0f,  505.0f},
        {570.0f,  505.0f},
        {570.0f,  630.0f},
        {640.0f,  630.0f},
        {640.0f,  660.0f},
        {960.0f,  660.0f},
        {960.0f,  160.0f},
        {1000.0f, 160.0f},
        {1000.0f, 110.0f},
        {1055.0f, 110.0f},
        {1055.0f, 25.0f},
        {1410.0f, 25.0f},
        {1410.0f, 220.0f},
        {1180.0f, 220.0f},
        {1180.0f, 500.0f},
        {1205.0f, 500.0f},
        {1205.0f, 525.0f},
        {1440.0f, 525.0f},
        {1440.0f, 400.0f}
};
static const int LAKE_PATH_LENGTH = 20;

static const Vec2 LAKE_SPAWN_POINT = {
        .x = 325.0f, .y = 900.0f
};

static const Vec2 BOTTOM_PATH_POINTS[] = {
        {1060.0f, 795.0f},
        {1060.0f, 700.0f},
        {960.0f,  700.0f},
        {960.0f,  660.0f},
        {960.0f,  160.0f},
        {1000.0f, 160.0f},
        {1000.0f, 110.0f},
        {1055.0f, 110.0f},
        {1055.0f, 25.0f},
        {1410.0f, 25.0f},
        {1410.0f, 220.0f},
        {1180.0f, 220.0f},
        {1180.0f, 500.0f},
        {1205.0f, 500.0f},
        {1205.0f, 525.0f},
        {1440.0f, 525.0f},
        {1440.0f, 400.0f}
};
static const int BOTTOM_PATH_LENGTH = 17;

static const Vec2 BOTTOM_SPAWN_POINT = {
        .x = 1600.0f, .y = 795.0f
};

static const Vec2 TOWER_LOCATIONS[] = {
        {450.0f, 350.0f},
        {705.0f, 500.0f},
        {1060.0f, 540.0f},
        {860.0f, 130.0f},
        {1280.0f, 350.0f}
};

static const Vec2 CAPITOL_LOCATION = {1440.0f,400.0f};

static const int HP = 5;
static const int SCREEN_WIDTH = 1600;
static const int SCREEN_HEIGHT = 900;
