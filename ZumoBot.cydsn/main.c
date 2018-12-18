/**
* @mainpage ZumoBot Project
* @brief    You can make your own ZumoBot with various sensors.
* @details  <br><br>
    <p>
    <B>General</B><br>
    You will use Pololu Zumo Shields for your robot project with CY8CKIT-059(PSoC 5LP) from Cypress semiconductor.This 
    library has basic methods of various sensors and communications so that you can make what you want with them. <br> 
    <br><br>
    </p>
    
    <p>
    <B>Sensors</B><br>
    &nbsp;Included: <br>
        &nbsp;&nbsp;&nbsp;&nbsp;LSM303D: Accelerometer & Magnetometer<br>
        &nbsp;&nbsp;&nbsp;&nbsp;L3GD20H: Gyroscope<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Reflectance sensor<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Motors
    &nbsp;Wii nunchuck<br>
    &nbsp;TSOP-2236: IR Receiver<br>
    &nbsp;HC-SR04: Ultrasonic sensor<br>
    &nbsp;APDS-9301: Ambient light sensor<br>
    &nbsp;IR LED <br><br><br>
    </p>
    
    <p>
    <B>Communication</B><br>
    I2C, UART, Serial<br>
    </p>
*/

#include <stdlib.h>
#include <project.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/

#if 0
// Hello World!
void zmain(void)
{
    printf("\nHello, World!\n");

    while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
 }   
#endif

#if 0
// Name and age
void zmain(void)
{
    char name[32];
    int age;
    
    
    printf("\n\n");
    
    printf("Enter your name: ");
    //fflush(stdout);
    scanf("%s", name);
    printf("Enter your age: ");
    //fflush(stdout);
    scanf("%d", &age);
    
    printf("You are [%s], age = %d\n", name, age);

    while(true)
    {
        BatteryLed_Write(!SW1_Read());
        vTaskDelay(100);
    }
 }   
#endif


#if 0
//battery level//
void zmain(void)
{
    ADC_Battery_Start();        

    int16 adcresult =0;
    float volts = 0.0;

    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

    for(;;)
    {
        char msg[80];
        ADC_Battery_StartConvert(); // start sampling
        if(ADC_Batetry_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for ADC converted value
            adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
            // convert value to Volts
            // you need to implement the conversion
            
            // Print both ADC results and converted value
            printf("%d %f\r\n",adcresult, volts);
        }
        vTaskDelay(500);
    }
 }   
#endif

#if 0
// button
void zmain(void)
{
    while(1) {
        printf("Press button within 5 seconds!\n");
        int i = 50;
        while(i > 0) {
            if(SW1_Read() == 0) {
                break;
            }
            vTaskDelay(100);
            --i;
        }
        if(i > 0) {
            printf("Good work\n");
            while(SW1_Read() == 0) vTaskDelay(10); // wait until button is released
        }
        else {
            printf("You didn't press the button\n");
        }
    }
}
#endif

#if 0
// button
void zmain(void)
{
    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
    
    bool led = false;
    
    for(;;)
    {
        // toggle led state when button is pressed
        if(SW1_Read() == 0) {
            led = !led;
            BatteryLed_Write(led);
            if(led) printf("Led is ON\n");
            else printf("Led is OFF\n");
            Beep(1000, 150);
            while(SW1_Read() == 0) vTaskDelay(10); // wait while button is being pressed
        }        
    }
 }   
#endif
/*week 2 */
#if 0 // assignment 1
    void zmain(void)
    {
        bool yes = SW1_Read();
        for(;;)
        {
            if (yes)
            {
               BatteryLed_Write(1); // Switch led on
               vTaskDelay(500);
               BatteryLed_Write(0);
               vTaskDelay(500);
               BatteryLed_Write(1);
               vTaskDelay(500);
               BatteryLed_Write(0);
               vTaskDelay(500);
               BatteryLed_Write(1);
               vTaskDelay(500);
               BatteryLed_Write(0);
               vTaskDelay(500);
               BatteryLed_Write(1);
               vTaskDelay(1500);
               BatteryLed_Write(0);
               vTaskDelay(500);
               BatteryLed_Write(1);
               vTaskDelay(1500);
               BatteryLed_Write(0);
               vTaskDelay(500);
               yes = 0;
            }
        }
    }
#endif

#if 0 //Assignment 2    
void zmain(void)
{
    int timediff, age;
    printf ("\nEnter your age: ");
    TickType_t timestart;
    timestart = xTaskGetTickCount();
    scanf ("%d", &age);
    TickType_t timeend;
    timeend = xTaskGetTickCount();
    timediff = timeend - timestart;
    
    if (age <= 21) 
    {
        if (timediff < 3000)
            printf ("Supper fast dude!"); 
            
        else if (timediff >= 3000 && timediff <= 5000)
            printf ("So mediocre.");
            
        else 
            printf ("My granny is faster than you!");
    }
    
    else if (age >= 22 && age <= 50)
    {
        if (timediff < 3000)
            printf ("Be quick or be dead");
            
        else if (timediff >= 3000 && timediff <= 5000)
            printf ("You are so average.");
            
        else 
            printf ("Have you been smoking something illegal?"); 
    }
    else if (age > 50)
    {
        if (timediff < 3000)
            printf ("Still going strong");
            
        else if (timediff >= 3000 && timediff <= 5000)
            printf ("You are doing ok for your age.");
            
        else 
            printf ("Do they still allow you to drive?");
    }
}
#endif


#if 0 //Assignment 3
void zmain(void)
{
    
    ADC_Battery_Start();
    ADC_Battery_StartConvert();
    double value_received;
    double voltage;
    bool state=0;
    bool pressed=0;
    printf("ADC TEST...\n");
    
    for(;;)
    {
        ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT);
        value_received=ADC_Battery_GetResult16();
        voltage=(5*value_received/4095)*1.5;
        printf("%f V\n",voltage);
        
        if (voltage >=4)
        {
            vTaskDelay(1000);
            if ( SW1_Read() ==0)
            {
                BatteryLed_Write(0);
                pressed = 0;
                
            }
            if (pressed == 0)
            {
                continue;
            }
        }
        pressed=1;
        BatteryLed_Write(state);
        vTaskDelay(500);
        state = !state;
    }
}
         
        
          
#endif
//week 3
//assignment 1
#if 0
//motor
void zmain(void)
{
    motor_start();              // enable motor controller
    

    vTaskDelay(3000);
    
    motor_forward(250,1500);     // moving forward
    motor_turn(200,5,450);  
    motor_forward(255,1100);
    motor_turn(200,5,450);
    motor_forward(240,1250);
    motor_turn(175,40,750);
    motor_forward(250,100);
    motor_turn(180,40,600);
    motor_forward(250,1000);
   
    //motor_turn(100,150,3000);
    //motor_turn(50,200,2000);     // turn
    //motor_backward(100,2000);    // moving backward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
    
    for(;;)
    {
    }
}
#endif

#if 0 //Assignment 2
//ultrasonic sensor//
void zmain(void)
{
    Ultra_Start();                          // Ultra Sonic Start function
    motor_start();
    
    
    
        
    while(1) {
    int d = Ultra_GetDistance();
    if (d<10){
         motor_forward(0,0);
        Beep(1000, 150);
        motor_backward(50,500);
        motor_turn(25,150,500);}
    
    motor_forward(100,0);
        
       
}   
}
#endif
//Assignment 3
#if 0
/* Example of how to use te Accelerometer!!!*/
void zmain(void)
{
    struct accData_ data;
    int initial_Value=0, new_Value=0, diffX=0;
    uint8_t dir =0;
    
    motor_start();
    motor_forward (0,0);
    
        if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
        
    for(;;)
    {
        motor_forward(255,0);
        LSM303D_Read_Acc(&data);
        initial_Value = data.accX;
        LSM303D_Read_Acc(&data);       
        new_Value= data.accX;
        diffX = new_Value - initial_Value;
        if (diffX >= 7000) {
           dir = rand() %2;
           motor_forward(0,0);
            motor_backward(100,500);
            if (dir ==0){
                motor_turn(190,40,600);
            }
            else{
                motor_turn(150,0,200);
            }
            motor_forward(200,0);
            
        }
    }
}
#endif 

#if 0
//IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    IR_Start();
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    bool led = false;
    // Toggle led when IR signal is received
    for(;;)
    {
        IR_wait();  // wait for IR command
        led = !led;
        BatteryLed_Write(led);
        if(led) printf("Led is ON\n");
        else printf("Led is OFF\n");
    }    
 }   
#endif



#if 0
//IR receiver - read raw data
void zmain(void)
{
    IR_Start();
    
    uint32_t IR_val; 
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    // print received IR pulses and their lengths
    for(;;)
    {
        if(IR_get(&IR_val, portMAX_DELAY)) {
            int l = IR_val & IR_SIGNAL_MASK; // get pulse length
            int b = 0;
            if((IR_val & IR_SIGNAL_HIGH) != 0) b = 1; // get pulse state (0/1)
            printf("%d %d\r\n",b, l);
        }
    }    
 }   
#endif

//Week4-Assignment 1
#if 0
//reflectance
void zmain(void)
{
    
    struct sensors_ dig;
    struct sensors_ ref;
    uint8 button=1;
    int count =0;
    bool white = 0;
    reflectance_start();
    motor_start ();
    IR_Start();
    IR_flush();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

   
   
for (;;)
  {    
    if ( SW1_Read()==0)
    {
    button= !button;
    vTaskDelay(200);
    }
    if (button==0)
    {
    reflectance_digital(&dig);
    reflectance_read(&ref);
    
    motor_forward (100,0);

    if ( white ==1 && (dig.r3== 1 && dig.l3==1) )
    { 
        
        white = 0;
        count ++;
    }
    else if (dig.r3==0 && dig.l3==0)
    { 
        white =1;    
    } 
    if (count==1)
    {
        motor_forward(0,0);
        IR_wait();
        count++;
    }
    if(count==5)
    {
        motor_forward(0,0);
        motor_stop();
    }
    }
  }
}

#endif

//Week4- assignemnt 2

#if 0
    
//reflectance
void zmain(void)
{
    
    struct sensors_ dig;
    struct sensors_ ref;
    uint8 button=1;
    int count =0;
    bool white = 0;
    reflectance_start();
    motor_start ();
    IR_Start();
    IR_flush();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

   
   
for (;;)
  {  
     //reflectance_digital(&dig);
     //reflectance_read(&ref); 
     //printf("left:%5d\n",ref.l3);
     //printf("right:%5d\n",ref.r3);
    if ( SW1_Read()==0)
    {
    button= !button;
    vTaskDelay(200);
    }
    if (button==0)
    {
    reflectance_digital(&dig);
    reflectance_read(&ref);
    
    motor_forward (100,0);

    if ( white ==1 && (dig.r3== 1 && dig.l3==1 ) )
    { 
        
        white = 0;
        count ++;
    }
    else if (dig.r3==0 && dig.l3==0 )
    { 
        white =1;    
    } 
    if (count==1)
    {
        motor_forward(0,0);
        IR_wait();
        count++;
    }
    if (ref.l1 >=22000 && ref.r1 >=22000){
        motor_forward(100,1);}
    else if (ref.l1<=22000 && ref.r1 >22000){
        motor_turn(150,10,1);}
    else if (ref.l1 >=22000 && ref.r1 <22000){
        motor_turn(10,150,1);}
    
    else if ( ref.l3 <=8000 && ref.r3 <=8000) 
    {
           if (count ==3)
        {
            
            while (!(ref.l1 > 11000 && ref.r1 > 11000 && ref.l2 < 11000 && ref.r2 < 11000 && ref.l3 < 11000 && ref.r3 < 11000))
            {
                reflectance_digital(&dig);
                
                motor_instant_left (100,100,10);
                if(dig.r3==0 && dig.r2==0 && dig.r1==1 && dig.l1==1 && dig.l2==0 && dig.l3==0)
                {   motor_forward(0,0);
                    break;
                }
            }
        }
        if (count ==4)
        {
            
            while (!(ref.l1 > 11000 && ref.r1 > 11000 && ref.l2 < 11000 && ref.r2 < 11000 && ref.l3 < 11000 && ref.r3 < 11000))
            {
                reflectance_digital(&dig);
                
                motor_instant_right (100,100,10);
                if(dig.r3==0 && dig.r2==0 && dig.r1==1 && dig.l1==1 && dig.l2==0 && dig.l3==0)
                {   motor_forward(0,0);
                    break;
                }
            }
        }
        if (count ==5)
        {
            
            while (!(ref.l1 > 11000 && ref.r1 > 11000 && ref.l2 < 11000 && ref.r2 < 11000 && ref.l3 < 11000 && ref.r3 < 11000))
            {
                reflectance_digital(&dig);
                
                motor_instant_right (100,100,10);
                if(dig.r3==0 && dig.r2==0 && dig.r1==1 && dig.l1==1 && dig.l2==0 && dig.l3==0)
                {   motor_forward(0,0);
                    break;
                }
            }
        }
        if (count == 6 && ref.r1<=22000 && ref.l1<=22000)
        {
            motor_stop();
        }
    }
    }
}
}
        
#endif

//week 4 - assignment 3
#if 0
//reflectance
void zmain(void)
{
    
    struct sensors_ dig;
    struct sensors_ ref;
    uint8 button=1;
    int count =0;
    bool white = 0;
    reflectance_start();
    motor_start ();
    IR_Start();
    IR_flush();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

   
   
for (;;)
  {    
    if ( SW1_Read()==0)
    {
    button= !button;
    vTaskDelay(200);
    }
    if (button==0)
    {
    reflectance_digital(&dig);
    reflectance_read(&ref);
    
    motor_forward (100,0);

    if ( white ==1 && (dig.r3== 1 && dig.l3==1) )
    { 
        
        white = 0;
        count ++;
    }
    else if (dig.r3==0 && dig.l3==0)
    { 
        white =1;    
    } 
    if (count==1)
    {
        motor_forward(0,0);
        IR_wait();
        count++;
    }
    if (ref.l1 >=22000 && ref.r1 >=22000){
        motor_forward(100,1);}
    else if (ref.l1<=22000 && ref.r1 >22000){
        motor_turn(150,10,1);}
    else if (ref.l1 >=22000 && ref.r1 <22000){
        motor_turn(10,150,1);}
   if (count==3)
    {
        motor_forward(0,0);
        motor_stop ();
    }
    }
    }
}

   #endif 
//Week5-Assignment1
 #if 0
void zmain(void)
{    
    RTC_Start(); // start real time clock
    int x,y;
      
    
    printf("enter the current hour:");
    scanf("%d",&x);
    printf("enter the current minute:");
    scanf("%d",&y);
    RTC_TIME_DATE now;
    // set current time
    now.Hour = x;
    now.Min = y;
   /* bool press = 0;*/
    RTC_WriteTime(&now); // write the time to real time clock

    for(;;)
    {
        if(SW1_Read() == 0) {
            // read the current time
            RTC_DisableInt(); /* Disable Interrupt of RTC Component */
            now = *RTC_ReadTime(); /* copy the current time to a local variable */
            RTC_EnableInt(); /* Enable Interrupt of RTC Component */

            // print the current time
            
            printf("%2d:%02d\n", now.Hour, now.Min);
            print_mqtt("Zumo041/output", "%2d:%02d", now.Hour, now.Min);
            // wait until button is released
            while(SW1_Read() == 1);
        }
        vTaskDelay(50);
    }
 }   
#endif

  //Week5-Assignment2
#if 0
//ultrasonic sensor//
void zmain(void)
{
    Ultra_Start();                          // Ultra Sonic Start function
    motor_start();
    uint8_t dir =0;
    
    
        
    while(1) {
    int d = Ultra_GetDistance();
    if (d<10){
        dir = rand() %2;
           motor_forward(0,0);
            motor_backward(100,500);
            if (dir ==0){
                motor_instant_right(150,150,300);
            print_mqtt("Zumo041/output", "robot turned right");
            }
            else{
                motor_instant_left(150,150,300);
            print_mqtt("Zumo041/output", "robot turned left");    
            }
    
    motor_forward(100,0);
    
        
       
}   
}
}
#endif
//Week5-Assignment3
#if 0
//reflectance
void zmain(void)
{
    
    struct sensors_ dig;
    struct sensors_ ref;
   /*uint8 button=1;*/
    TickType_t start=0;
    TickType_t end;
    int x;
    bool white = 0;
    reflectance_start();
    motor_start ();
    IR_Start();
    IR_flush();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

   
   
for (;;)
  {  
    start = end;
    
    reflectance_digital(&dig);
    reflectance_read(&ref);
    
    motor_forward (100,0);

    if ( white ==1 && (dig.r3== 1 && dig.l3==1) )
    { 
        white = 0;
        motor_forward(0,0);
        end = xTaskGetTickCount ();
        IR_wait();
        x=end-start;
        print_mqtt("Zumo041/output", "start %d", start);
        print_mqtt("Zumo041/output", "end number %d", end);
        print_mqtt("Zumo041/output", "lap number %d", x);
    }
    if ( dig.r3 == 0 && dig.l3 == 0)
    {
        white =1 ;
        
    }
     if (ref.l1 >=22000 && ref.r1 >=22000){
        motor_forward(100,1);}
    else if (ref.l1<=22000 && ref.r1 >22000){
        motor_turn(150,10,1);}
    else if (ref.l1 >=22000 && ref.r1 <22000){
        motor_turn(10,150,1);}
    
}
}
  #endif

//Robot wrestling
#if 01
struct sensors_ ref;
struct sensors_ dig;
struct accData_ data;
int count = 0,timeDiff = 0;
int currentValueX = 0, newValueX = 0, diffX = 0;
int currentValueY = 0, newValueY = 0, diffY = 0;
   
bool isHit = false;
bool isWhite = true;
bool isPressed = true;
    
TickType_t timeIR = 0, timeHit = 0, timeEnd = 0;
    
void checkHit(void) {
    LSM303D_Read_Acc(&data);
    currentValueX = data.accX;
    currentValueY = data.accY;
            
    LSM303D_Read_Acc(&data);
    newValueX = data.accX;
    newValueY = data.accY;
          
    diffX = currentValueX - newValueX;
    diffY = currentValueY - newValueY;
    
    if (isHit == false && diffX > 10000){
        isHit = true;
        timeHit = xTaskGetTickCount();
        print_mqtt("Zumo041/hit", "%d", timeHit);
    }
    else if (isHit == true && diffX <= 8000) {
        isHit = false;
    }
}
void checkBW(void) {
    reflectance_digital(&dig);
    if (isWhite == true && (dig.r3 == 1 || dig.l3 == 1)) {
        isWhite = false;
        count++;
        if (count == 1) {
            motor_forward(0,0);
            print_mqtt("Zumo041/ready","zumo");
            IR_wait();
            
            timeIR = xTaskGetTickCount();
            print_mqtt("Zumo041/start", "%d", timeIR);
        }
        else if (count > 1) {
            motor_forward(0,0);
            if (dig.r3 == 1) {
                motor_backward(255,50);
                motor_instant_left(255,200,300);
            }
            else if (dig.l3 == 1) {
                motor_backward(255,5);
                motor_instant_right(200,255,200);
            }
        }
    }
    else if (dig.l3 == 0 && dig.r3 == 0) {
        isWhite = true;
        if (count > 1) {
            checkHit();
        }
    }
}
void zmain(void) {
    motor_start();
    motor_forward(0,0);
    IR_Start();
    IR_flush();
    reflectance_start();
    reflectance_set_threshold(11000, 11000, 15000, 15000, 11000, 11000);
    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    for(;;){
        if (SW1_Read()== 0) {
            isPressed = !isPressed;
            vTaskDelay(500);
        }
        if(isPressed == false) {
            motor_forward(255,0);
              
            //reflectance_read(&ref);
            
            checkBW();
            if (SW1_Read()== 0){ 
                motor_forward(0,0);
                isPressed= !isPressed;
                timeEnd = xTaskGetTickCount();
                print_mqtt("Zumo041/stop", "%d", timeEnd);
                timeDiff= timeEnd - timeIR;
                print_mqtt("Zumo041/time", "%d", timeDiff);
                break;
            }
        }
    }    
}
#endif
//line follower
#if 0
//reflectance
void zmain(void)
{
    TickType_t timeIR=0;
    TickType_t timeEnd=0;
  
    int timeDiff;
    struct sensors_ dig;
    struct sensors_ ref;
    uint8 button=1;
    int count =0;
    bool white = 0;
    reflectance_start();
    motor_start ();
    IR_Start();
    IR_flush();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

   
   
for (;;)
  {    
  
    if ( SW1_Read()==0)
    {
    button= !button;
    vTaskDelay(200);
    }
    if (button==0)
    {
    reflectance_digital(&dig);
    reflectance_read(&ref);

    if ( white ==1 && (dig.r3== 1 && dig.l3==1) )
    {
        white = 0;
        count ++;
    }
    else if (dig.r3==0 && dig.l3==0)
    { 
        white =1;    
    } 
    if (count==1)
    {
        motor_forward(0,0);
        print_mqtt("Zumo041/ready", "line");
       
        IR_wait();
        timeIR=xTaskGetTickCount();
        print_mqtt("Zumo041/start","%d", timeIR);
        count++;
        
        
    }
    if (dig.l1==1&&dig.r1==1){
        motor_forward(250,10);}
    else if (dig.l1 ==0 && dig.r1 == 1){
        motor_turn(220,0,0);}
    else if (dig.l1 ==1 && dig.r1 == 0){
        motor_turn(0,220,0);}
    
   
    }
    if (count==4)
    {
        motor_forward(0,0);
        timeEnd=xTaskGetTickCount();
        print_mqtt("Zumo041/stop","%d", timeEnd);
        timeDiff = timeEnd - timeIR;
        print_mqtt("Zumo041/time","%d", timeDiff);
        motor_stop();
        break;
        
    }
    }
}
    


   #endif 

          


//maze
#if 00
void zmain(void)
{
	initial();
	Ultra_Start();
	dfs(0, 4, 0);
	finish();
}
#endif
#if 0
/* Example of how to use te Accelerometer!!!*/
void zmain(void)
{
    struct accData_ data;
    
    printf("Accelerometer test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    
    for(;;)
    {
        LSM303D_Read_Acc(&data);
        printf("%8d %8d %8d\n",data.accX, data.accY, data.accZ);
        vTaskDelay(50);
    }
 }   
#endif    

#if 0
/* Example of how to use te Accelerometer!!!*/
void zmain(void)
{
    struct accData_ data;
    
    printf("Accelerometer test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    
    for(;;)
    {
        LSM303D_Read_Acc(&data);
        printf("%8d %8d %8d\n",data.accX, data.accY, data.accZ);
        vTaskDelay(50);
    }
 }   
#endif    

#if 0
// MQTT test
void zmain(void)
{
    int ctr = 0;

    printf("\nBoot\n");
    send_mqtt("Zumo01/debug", "Boot");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 

    for(;;)
    {
        printf("Ctr: %d, Button: %d\n", ctr, SW1_Read());
        print_mqtt("Zumo01/debug", "Ctr: %d, Button: %d", ctr, SW1_Read());

        vTaskDelay(1000);
        ctr++;
    }
 }   
#endif


#if 00
void zmain(void)
{    
    struct accData_ data;
    struct sensors_ ref;
    struct sensors_ dig;
    
    printf("MQTT and sensor test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Accelerometer Ok...\n");
    }
    
    int ctr = 0;
    reflectance_start();
    for(;;)
    {
        LSM303D_Read_Acc(&data);
        // send data when we detect a hit and at 10 second intervals
        if(data.accX > 1500 || ++ctr > 1000) {
            printf("Acc: %8d %8d %8d\n",data.accX, data.accY, data.accZ);
            print_mqtt("Zumo01/acc", "%d,%d,%d", data.accX, data.accY, data.accZ);
            reflectance_read(&ref);
            printf("Ref: %8d %8d %8d %8d %8d %8d\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
            print_mqtt("Zumo01/ref", "%d,%d,%d,%d,%d,%d", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);
            reflectance_digital(&dig);
            printf("Dig: %8d %8d %8d %8d %8d %8d\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            print_mqtt("Zumo01/dig", "%d,%d,%d,%d,%d,%d", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            ctr = 0;
        }
        vTaskDelay(10);
    }
 }   

#endif

#if 0
void zmain(void)
{    
    RTC_Start(); // start real time clock
    
    RTC_TIME_DATE now;

    // set current time
    now.Hour = 12;
    now.Min = 34;
    now.Sec = 56;
    now.DayOfMonth = 25;
    now.Month = 9;
    now.Year = 2018;
    RTC_WriteTime(&now); // write the time to real time clock

    for(;;)
    {
        if(SW1_Read() == 0) {
            // read the current time
            RTC_DisableInt(); /* Disable Interrupt of RTC Component */
            now = *RTC_ReadTime(); /* copy the current time to a local variable */
            RTC_EnableInt(); /* Enable Interrupt of RTC Component */

            // print the current time
            printf("%2d:%02d.%02d\n", now.Hour, now.Min, now.Sec);
            
            // wait until button is released
            while(SW1_Read() == 0) vTaskDelay(50);
        }
        vTaskDelay(50);
    }
 }   
#endif

/* [] END OF FILE */
