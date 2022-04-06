#include <kipr/wombat.h>

void servoUp() // This function is executed last and is a work in progress for the lifting of the gate in the center of the board.
{
    int i = 0, armPos[2]={get_servo_position(0), get_servo_position(1)}, armThreshold[2]={750,1285};
    while(armPos[0]<=armThreshold[0] || armPos[1]<=armThreshold[1]) 
    {
        if(i>=2)		// This increments the position of two servos slowly, to maintain stability when lifting the gate.
            i=0;		// It does so as long as the servo positions do not match up with the specified thresholds.
		set_servo_position(i,armPos[i]);
        (i==0)?(armPos[i]+=100):(armPos[i]+=20);
        msleep(100);
        i++;			// The values by which the servos increment has been modified to lift the gate more easily.
        				// The threshold values have also been altered to maintain an optimal height for the arm.
    }
}

void reset(int version) // The reset function has two versions, one lifts the arm up to fit in the starting box at a postion such that it will not collide with the other creations.
{   
    enable_servo(0);
    enable_servo(1);
    int i = 0, arrPos, pos[4]={400,1480,0,1200}; 
    version==0?(arrPos=0):(arrPos=2); // This ternary operator allows the arrPos variable to begin at 0 or 2. Positions 0 and 1, versus 2 and 3, correspond to the two reset function versions.
    while(i < 2)
    {
        set_servo_position(i, pos[arrPos]);
     	i++;
        arrPos++;
    }
}
void turn(char turnDirec, int sleepTime) // This function turns the CreateBot, given the direction, right or left. It also requires the time between executions of the turn function, in milliseconds.
{
    reset(1);
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
void moveStraight(int distance, char direc) // This function is similar to the previous forward() function; however, it allows for moving backwards as well.
{
	set_create_distance(0);
    while (get_create_distance() > -1*distance && direc=='b') // This function allows the CreateBot to move backwards.
    {
        create_drive_direct(-200,-200);
    }
    while (get_create_distance() < distance && direc=='f') // This function allows the CreateBot to move forwards.
    {
        create_drive_direct(200,200);
    }
}
#define arrSize 2
void move() // This function allows for the the turn and drive patterns to be repeated consistently, storing the parameter values in arrays.
{
    create_connect();
    int i = 0, fwdArr[arrSize] = {770, 810}, direc[arrSize] = {'b', 'f'}, direction[1] = {'r'}, sleepArr[1] = {1900}; // These arrays store values which allow the CreateBot to move optimally. The values have been altered since the previous iteration, to better fit the changes made to the way the CreateBot approaches its goal.
    while(i<arrSize) //  This loops the functions to allow the CreateBot to turn and move forward for the specified amount of times.
	{
    	moveStraight(fwdArr[i], direc[i]);
        turn(direction[i], sleepArr[i]);
        i++;
        i==1?reset(1):0;
    }
    create_stop();
    create_disconnect();
}

int main() // This is the main function which executes the specified functions for the CreateBot to complete the given tasks.
{
    reset(0);
    move();
    servoUp();
    return 0;
}
