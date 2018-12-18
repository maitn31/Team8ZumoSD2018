/**
 * @file    Motor.h
 * @brief   Motor header file
 * @details If you want to use Motor methods, Include Motor.h file.
*/
#ifndef MOTOR_H_ 
#define MOTOR_H_ 

#include "project.h"
#include "Reflectance.h"
#include <stdio.h>
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
#include <stdbool.h>
#include "IR.h"
#include "Ultra.h"
void motor_start(); // start motor PWM timers
void motor_stop();  // stop motor PWM timers

/* moving forward */
void motor_forward(uint8 speed,uint32 delay);

/* moving left when l_speed < r_speed or moving right when l_speed > r_speed */
void motor_turn(uint8 l_speed, uint8 r_speed, uint32 delay);

/* moving backward */
void motor_backward(uint8 speed,uint32 delay);
void motor_instant_left (uint8 speedL, uint8 speedR, uint32 delay);
void motor_instant_right (uint8 speedL, uint8 speedR, uint32 delay);
void movetomiddle(int c);
void balance_move_dig(struct sensors_ dig);
void balance_move_dig1(struct sensors_ dig, int c);
void balance_turn_dig(struct sensors_ dig, int direction, int left, int right);
void checkobstacle(int *a);
void dfs(int r, int c, int direction);
void initial();
void movetomiddle(int c);
void finish();
#endif
/* moving left when l_speed < r_speed or moving right when l_speed > r_speed */
void maze_turn(int speedL, int speedR, uint32 delay);