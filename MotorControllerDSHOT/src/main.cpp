#include "mbed.h"
#include <DSHOT150.h>

DSHOT150 motor( p22 );

int main() //3d mode
{
    Timer t; 
    t.start();
    while (t.elapsed_time() < 10ms){

    } //I don't think this is strictly necessary but it feels nicer to have a small buffer
    t.stop();
    t.reset();

    t.start();
    while (t.elapsed_time() < 5s) {
            motor.special_cmd(0);     //disarms and stops (brakes) any motor rotation by setting throttle-type value to 0 (not 1048, which would be 0% throttle)
                                //step 1/2 of arming sequence is for ESC to read these 0s
    }
    t.stop();
    t.reset();

    int i;
    i = 0;

//telemetry must be true to save special_cmds, but must be false for throttle 0% to be not spinning (if tel is true, motor jerks at 3 hz at
//0% throttle). SHould be able to set tel true for special commanding, then set it false for spinning. It might be smart to include this directly in special command void.
/*
    motor.set_tel( false );      //we don't read telemetry, but the telemetry bit must be high for the special commands to save/go into effect

    while (i < 50)            //runs 1000 times
        {motor.special_cmd(0);  //special command 0 is all 0's except telemetry and check sum      
        i++;}                   //adds 1 to i every time another packet is sent

    i = 0;
    while (i < 2)               //probably only needs to be sent once but twice for good measure
        {motor.set_3d_on();     //makes sure esc is in 3d mode, which defines throttle-type values from 48 to 1047 as REVERSE,
        i++;}                   //1048 as 0 throttle (not braked, and still armed), and 1049 to 2048 as FORWARD

    i = 0;                    //resets the counter
    while (i < 2)                //again, probably only needs to be sent once but it can't hurt
        {motor.special_cmd(12);  //spcl cmd 12 saves the previous command (set_3d_on is just special_cmd(10))
        i++;}
*/    
    
    float thrust=0;

    while (thrust < .5){
      motor.throttle_3d(thrust += .05);
      ThisThread::sleep_for(1s); 
    }
  
    while (thrust > -.5){
      motor.throttle_3d(thrust -= .1);
      ThisThread::sleep_for(1s); 
    }
    
    while (thrust < 0){
      motor.throttle_3d(thrust += .1);
      ThisThread::sleep_for(1s); 
    }

    //Ensuring the motor stops
    motor.throttle_3d(0); 

    /*
    i = 0;          
    while (i < 500)
       {motor.throttle_3d(0);  
        i++;}


    i = 0;
    while (i < 500)
        {motor.throttle_3d(0.1);  
        i++;}

        i = 0;          
    while (i < 500)
       {motor.throttle_3d(0);  
        i++;}

    i = 0;
    while (i < 500)
        {motor.throttle_3d(-0.1);  
        i++;}

        i = 0;          
    while (i < 500)
       {motor.throttle_3d(0);  
        i++;}

    */
}        
/*
    i = 0;
    while (i < 5000)
        {motor.throttle_3d(0.05);  
        i++;}

        i = 0;          
    while (i < 5000)
       {motor.throttle_3d(0);  
        i++;}

    i = 0;
    while (i < 5000)
        {motor.throttle_3d(0.04);  
        i++;}

    i = 0;          
    while (i < 5000)
       {motor.throttle_3d(0);  
        i++;}

    i = 0;
    while (i < 5000)
        {motor.throttle_3d(0.03);  
        i++;}
   
        i = 0;          
    while (i < 5000)
       {motor.throttle_3d(0);  
        i++;}

    i = 0;
    while (i < 5000)
        {motor.throttle_3d(0.02);  
        i++;}

    i = 0;          
    while (i < 5000)
       {motor.throttle_3d(0);  
        i++;}

    i = 0;
    while (i < 5000)
        {motor.throttle_3d(0.01);  
        i++;}

}
*/