#include <kipr/wombat.h>

// 34 in, turn, 20 in

void servoUp()
{
   	enable_servo(0);
    enable_servo(1);
    int i = 0, armPos[2]={get_servo_position(0), get_servo_position(1)}, armThreshold[2]={730,1280};
    while(armPos[0]>=armThreshold[0] || armPos[1]<=armThreshold[1]) 
    {
        if(i>=2)
            i=0;
		set_servo_position(i,armPos[i]);
        (i==0)?(armPos[i]-=20):(armPos[i]+=30);
        msleep(100);
        i++;
    }
    disable_servo(0);
    disable_servo(1);
}
// Claw for rings
/*reset();
    msleep(3000);
	int i = 0, servoOrder[3] = {1, 0, 2}, pos[3] = {1142, 1140, 315};
    while(i < 3)
    {
        enable_servo(servoOrder[i]);
        msleep(500);
        set_servo_position(servoOrder[i], pos[i]);
        i++;
    }*/
void reset()
{   
    int i = 0, pos[2] = {1070, 1070};
    while(i < 2)
    {
        set_servo_position(i, pos[i]);
     	i++;   
    }
}
void turn(char turnDirec, int sleepTime)
{
    set_create_total_angle(0);
    while (get_create_total_angle() > -1 && turnDirec == 'r')
    {
       	create_drive_direct(75,-75);
        msleep(sleepTime);
    }
    while (get_create_total_angle() < 1 && turnDirec == 'l')
    {
      	create_drive_direct(-75,75);
        msleep(sleepTime);
    }   
}
void forward(int distance)
{
	set_create_distance(0);
    while (get_create_distance() < distance)
    {
        create_drive_direct(200,200);
    }
}
#define arrSize 2
void move()
{
    create_connect();
    int i = 0, fwdArr[arrSize] = {800, 580}, direction[arrSize] = {'r', 'l'}, sleepArr[arrSize] = {4200, 2200}; 
    while(i<arrSize) {
        turn(direction[i], sleepArr[i]);
    	forward(fwdArr[i]);
        i++;
        (i==1)?(reset()):(0);
    }
    create_stop();
    create_disconnect();
}

int main()
{
    /*reset();
    msleep(1000);
    move();*/
    servoUp();
    return 0;
}
