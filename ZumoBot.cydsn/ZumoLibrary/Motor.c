/**
 * @file    Motor.c
 * @brief   Basic methods for operating motor sensor. For more details, please refer to Motor.h file. 
 * @details included in Zumo shield
*/
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"


/**
* @brief    Starting motor sensors
* @details  
*/
void motor_start()
{
    PWM_Start();
}


/**
* @brief    Stopping motor sensors
* @details
*/
void motor_stop()
{
    PWM_Stop();
}


/**
* @brief    Moving motors forward
* @details  giveing same speed to each side of PWM to make motors go forward
* @param    uint8 speed : speed value
* @param    uint32 delay : delay time
*/
void motor_forward(uint8 speed ,uint32 delay)
{
    MotorDirLeft_Write(0);      // set LeftMotor forward mode
    MotorDirRight_Write(0);     // set RightMotor forward mode
    PWM_WriteCompare1(speed); 
    PWM_WriteCompare2(speed); 
    vTaskDelay(delay);
}
void motor_instant_left (uint8 speedL, uint8 speedR, uint32 delay)
{
        MotorDirLeft_Write(1);      // set LeftMotor backward mode
        MotorDirRight_Write(0);     // set RightMotor backward mode
        PWM_WriteCompare1(speedL);
        PWM_WriteCompare2(speedR);
        vTaskDelay(delay);
}
void motor_instant_right (uint8 speedL, uint8 speedR, uint32 delay)
{
        MotorDirLeft_Write(0);      // set LeftMotor backward mode
        MotorDirRight_Write(1);     // set RightMotor backward mode
        PWM_WriteCompare1(speedL);
        PWM_WriteCompare2(speedR);
        vTaskDelay(delay);
}
/**
* @brief    Moving motors to make a turn 
* @details  moving left when l_speed < r_speed or moving right when l_speed > r_speed
* @param    uint8 l_speed : left motor spee dvalue
* @param    uint8 r_speed : right motor speed value
* @param    uint32 delay : delay time
*/
void motor_turn(uint8 l_speed, uint8 r_speed, uint32 delay)
{
    PWM_WriteCompare1(l_speed); 
    PWM_WriteCompare2(r_speed); 
    vTaskDelay(delay);
}


/**
* @brief    Moving motors backward
* @details  setting backward mode to each motors and gives same speed to each side of PWM
* @param    uint8 speed : speed value
* @param    uint32 delay : delay time
*/
void motor_backward(uint8 speed,uint32 delay)
{
    MotorDirLeft_Write(1);      // set LeftMotor backward mode
    MotorDirRight_Write(1);     // set RightMotor backward mode
    PWM_WriteCompare1(speed); 
    PWM_WriteCompare2(speed); 
    vTaskDelay(delay);
}
TickType_t timeIR = 0, timeEnd = 0;

int maze[13][9] = { {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1,-1,-1,-1,-1,-1,-1,-1,-1} };
int row[3] = { 1,0,0 };
int col[3] = { 0,1,-1 };
int r = 0, c = 0, count = -1, timeDiff = 0;
bool check = false;
void maze_turn(int speedL, int speedR, uint32 delay) {
    if (speedL < 0) {
        MotorDirLeft_Write(1);
        speedL = -speedL;
    }
    if (speedR<0) {
        MotorDirRight_Write(1);
        speedR = -speedR;
    }
    PWM_WriteCompare1(speedL); 
    PWM_WriteCompare2(speedR); 
    vTaskDelay(delay);
}
void balance_move_dig(struct sensors_ dig) 
{
	int speed = 100, speedLarge = 100, speedSmall = -50;
	if (dig.l1 == 1 && dig.r1 == 1)
		motor_forward(speed, 15);
	else if (dig.l1 == 1 && dig.r1 == 0)
		maze_turn(speedSmall, speedLarge, 15);
	else if (dig.l1 == 0 && dig.r1 == 1)
		maze_turn(speedLarge, speedSmall, 15);
}
void balance_move_dig1(struct sensors_ dig, int c) //Makes robot goes to next intersection
{
	if ((c != 1) && (c != 7))
	{
		while (!((dig.l3 == 1) && (dig.r3 == 1))) {
			reflectance_digital(&dig);
			balance_move_dig(dig);
		}
		while (!((dig.l3 == 0) && (dig.r3 == 0))) {
			reflectance_digital(&dig);
			balance_move_dig(dig);
		}
	}
	else
	{
		if (c == 7)
		{
			while (!(dig.l3 == 1)) {
				reflectance_digital(&dig);
				balance_move_dig(dig);
			}
			while (!(dig.l3 == 0)) {
				reflectance_digital(&dig);
				balance_move_dig(dig);
			}
		}
		else
		{
			while (!(dig.r3 == 1)) {
				reflectance_digital(&dig);
				balance_move_dig(dig);
			}
			while (!(dig.r3 == 0)) {
				reflectance_digital(&dig);
				balance_move_dig(dig);
			}
		}
	}
	motor_forward(0, 0);
}
void balance_turn_dig(struct sensors_ dig, int direction, int left, int right)
{
	if (direction == 1)
	{
		do
		{
			reflectance_digital(&dig);
			maze_turn(left, -right, 5);
		} while ((dig.l1 == 1) || (dig.r1 == 1));
		do
		{
			reflectance_digital(&dig);
			maze_turn(left, -right, 15);
		} while (dig.l1 == 0);
		motor_forward(0, 0);
	}
	else if (direction == 2)
	{
		do
		{
			reflectance_digital(&dig);
			maze_turn(-right, left, 5);
		} while ((dig.l1 == 1) || (dig.r1 == 1));
		do
		{
			reflectance_digital(&dig);
			maze_turn(-right, left, 15);
		} while (dig.r1 == 0);
		motor_forward( 0, 0);
	}
	while (!((dig.l3 == 0) && (dig.r3 == 0)))
	{
		reflectance_digital(&dig);
		balance_move_dig(dig);
	}
	reflectance_digital(&dig);
	balance_move_dig(dig);
	motor_backward( 50, 50);
	motor_forward( 0, 0);
}
void checkobstacle(int *a) //Check whether there is a obstacle
{
	int p = 0;
	p = Ultra_GetDistance();
	if ((p < 18) && (p > 0)) {
		*a = -1;
	}
}

void initial() //Move robot to (0,0)
{
	uint8 button = 1; struct sensors_ dig; bool condition = false; int count = 0;
	reflectance_start(); motor_start(); IR_Start(); IR_flush();

	motor_forward(0, 0);
	do
	{
		button = SW1_Read();
		if (!button)
		{
			for (;;)
			{
				motor_forward( 50, 5);
				reflectance_digital(&dig);
				if ((dig.l3 == 1) && (dig.r3 == 1))
				{
					motor_forward( 0, 0);
					condition = true;
					break;
				}
			}
		}
	} while (condition == false);

	condition = false;
    print_mqtt("Zumo041/ready","maze");
	IR_wait();
    timeIR = xTaskGetTickCount();
    vTaskDelay(500);
    print_mqtt("Zumo041/start", "%d", timeIR);
	condition = !condition;

	do
	{
		reflectance_digital(&dig);
		balance_move_dig(dig);
		if ((dig.l3 == 1) && (dig.r3 == 1) && (condition == false))
		{
			condition = true;
		}
		if ((dig.l3 == 0) && (dig.r3 == 0) && (condition == true))
		{
			condition = false;
			count++;
		}
	} while (count != 2);

	motor_forward(0, 0);
}

void dfs(int r, int c, int direction) //Find the path
{
	struct sensors_ dig; reflectance_start();
	if (check == true) return;

	maze[r][c] = -1;

	print_mqtt("Zumo041/position", "%d %d", r, c - 4);

	switch (direction)
	{
	case 0:
		checkobstacle(&maze[r + row[direction]][c + col[direction]]);
		break;

	case 1:
		checkobstacle(&maze[r + row[direction]][c + col[direction]]);
		direction = 2; reflectance_digital(&dig); balance_turn_dig(dig, direction, 100, 75); direction = 0;
		checkobstacle(&maze[r + row[direction]][c + col[direction]]);
		break;

	case 2:
		checkobstacle(&maze[r + row[direction]][c + col[direction]]);
		direction = 1; reflectance_digital(&dig); balance_turn_dig(dig, direction, 100, 75); direction = 0;
		checkobstacle(&maze[r + row[direction]][c + col[direction]]);
		break;
	}
	if (r == 11)
	{
		motor_forward( 0, 0); check = true; movetomiddle(c);
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		if ((r + row[i] >= 0) && (r + row[i] <= 11) && (c + col[i] >= 0) && (c + col[i] <= 8) && (maze[r + row[i]][c + col[i]] != -1) && (check == false))
		{
			if (i != 0) {
				reflectance_digital(&dig);
				balance_turn_dig(dig, i, 100, 75);
				checkobstacle(&maze[r + row[i]][c + col[i]]);

				if (maze[r + row[i]][c + col[i]] != -1) {
					direction = i;
					reflectance_digital(&dig);
					balance_move_dig1(dig, c);
					dfs(r + row[i], c + col[i], direction);
				}
				else balance_turn_dig(dig, 2, 100, 95);
			}
			else
			{
				direction = i;
				reflectance_digital(&dig);
				balance_move_dig1(dig, c);
				dfs(r + row[i], c + col[i], direction);
			}
		}
	}
}

void movetomiddle(int c) //Move robot to (13,0)
{
	struct sensors_ dig; reflectance_start();
	if (c != 4)
	{
		if (c < 4)
		{
			reflectance_digital(&dig);
			balance_turn_dig(dig, 1, 100, 95);
			while (c != 4) {
				reflectance_digital(&dig);
				balance_move_dig1(dig, c);
                c++;
                print_mqtt("Zumo041/position", "11 %d", c - 4);
			}
			balance_turn_dig(dig, 2, 100, 95);
		}
		else
		{
			reflectance_digital(&dig);
			balance_turn_dig(dig, 2, 100, 95);
			while (c != 4) {
				reflectance_digital(&dig);
				balance_move_dig1(dig, c);
                c--;
                print_mqtt("Zumo041/position", "11 %d", c - 4);
			}
			balance_turn_dig(dig, 1, 100, 95);
		}
	}
}

void finish() //Move robot from (13,0) to the end
{
	motor_forward( 0, 0);
	struct sensors_ dig; bool black = false; int count = 0;
	reflectance_start();
    r=11;
	do
	{
		reflectance_digital(&dig);
		balance_move_dig(dig);
		if ((dig.l3 == 1) && (dig.r3 == 1) && (black == false))
		{
			black = true;
			count++;
            r++;
            print_mqtt("Zumo041/position", "%d %d", r, c - 4);
		}
		if ((dig.l3 == 0) && (dig.r3 == 0) && (black == true))
		{
			black = false;
		}
	} while (count != 2);

	motor_forward( 0, 0);
    timeEnd = xTaskGetTickCount();
    print_mqtt("Zumo041/stop", "%d", timeEnd);
    timeDiff = timeEnd - timeIR;
    print_mqtt("Zumo041/time", "%d", timeDiff);
}