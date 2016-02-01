#pragma once

#include "Arduino.h"
#include "KeyboardioHID.h"

// Buttons

#define KEY_MOUSE_BUTTON_LEFT    0x01
#define KEY_MOUSE_BUTTON_MIDDLE  0x02
#define KEY_MOUSE_BUTTON_RIGHT   0x04


// Warping commands

#define WARP_END 1
#define WARP_UP 2
#define WARP_DOWN 4
#define WARP_LEFT 8
#define WARP_RIGHT 16



// apparently, the mac discards 15% of the value space for mouse movement.
// need to test this on other platforms

#define MAX_WARP_WIDTH 32767
#define MAX_WARP_HEIGHT 32767

#define WARP_ABS_TOP 0
#define WARP_ABS_LEFT 0

// Mouse acceleration

// we want the whole s curve, not just the bit
// that's usually above the x and y axes;
#define ATAN_LIMIT 1.57079633
#define ACCELERATION_FLOOR 0.25
#define ACCELERATION_MULTIPLIER 5
#define  ACCELERATION_RUNWAY 5
// Climb speed is how fast we get to max speed
// 1 is "instant"
// 0.05 is just right
// 0.001 is insanely slow

#define ACCELERATION_CLIMB_SPEED  0.05


class MouseWrapper_ {
  public:
    MouseWrapper_(void);
    void move( int8_t x, int8_t y);
    void warp(uint8_t warp_cmd);
    void press_button(uint8_t button);
    void release_button(uint8_t button);

  private:
    double mouseActiveForCycles = 0;
    float carriedOverX = 0;
    float carriedOverY = 0;


    uint16_t next_width;
    uint16_t next_height;
    uint16_t section_top;
    uint16_t section_left;
    boolean is_warping = false;

    double acceleration (double cycles);
    void begin_warping();
    void end_warping();
    void warp_jump(long left, long top, long height, long width);

};
extern MouseWrapper_ MouseWrapper;