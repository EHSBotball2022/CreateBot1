#include <kipr/wombat.h>

void servoUp() // This function is executed last and is a work in progress for the lifting of the gate in the center of the board.
{
    enable_servo(0);
    enable_servo(1);
    int i = 0, armPos[2]={get_servo_position(0), get_servo_position(1)}, armThreshold[2]={730,1280}; 
    while(armPos[0]>=armThreshold[0] || armPos[1]<=armThreshold[1]) 
    {									// This increments the position of two servos slowly, to maintain stability when lifting the gate.
        if(i>=2)							// It does so as long as the servo positions do not match up with the specified thresholds.
            i=0;	
		set_servo_position(i,armPos[i]);
        (i==0)?(armPos[i]-=20):(armPos[i]+=30);
        msleep(100);
        i++;
    }
    disable_servo(0);
    disable_servo(1);
}
void reset() // This function resets the servo position such that it does not cross boundaries within the starting box.
{   
    int i = 0, pos[2] = {1070, 1070}; 
    while(i < 2)
    {
        set_servo_position(i, pos[i]);
     	i++;   
    }
}
void turn(char turnDirec, int sleepTime) // This function turns the CreateBot, given the direction, right or left. It also requires the time between executions of the turn function, in milliseconds.
{
    set_create_total_angle(0);
    while (get_create_total_angle() > -1 && turnDirec == 'r') // This loop allows the CreateBot to turn right.
    {
       	create_drive_direct(75,-75);
        msleep(sleepTime);
    }
    while (get_create_total_angle() < 1 && turnDirec == 'l') // This loop allows for the CreateBot to turn left.
    {
      	create_drive_direct(-75,75);
        msleep(sleepTime);
    }   
}
void forward(int distance) // This function moves the CreateBot forward, given a distance.
{
    set_create_distance(0);
    while (get_create_distance() < distance)
    {
        create_drive_direct(200,200);
    }
}
#define arrSize 2
void move() // This function allows for the the turn and drive patterns to be repeated consistently, storing the parameter values in arrays.
{
    create_connect();
    int i = 0, fwdArr[arrSize] = {800, 580}, direction[arrSize] = {'r', 'l'}, sleepArr[arrSize] = {4200, 2200}; // These arrays store values which allow the CreateBot to move optimally.
    while(i<arrSize) {			//  This loops the functions to allow the CreateBot to turn and move forward for the specified amount of times.
        turn(direction[i], sleepArr[i]);
    	forward(fwdArr[i]);
        i++;
        (i==1)?(reset()):(0);
    }
    create_stop();
    create_disconnect();
}

int main()
{  		// This is the main function which executes the specified functions for the CreateBot to complete the given tasks.
    reset();
    msleep(1000); 
    move();
    servoUp();
    return 0;
}
