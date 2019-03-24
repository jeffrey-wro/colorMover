#include "MyRio.h"
#include "I2C.h"
#include "Motor_Controller.h"
#include "Utils.h"
#include "Ultrasonic.h"

#include "jeffrey.h"


Jeffrey::Jeffrey(){	

}
Jeffrey::~Jeffrey(){

}

NiFpga_Status Jeffrey::init(NiFpga_Session* myrio_session){

	NiFpga_Status status = mc.init(myrio_session);
	mc.controllerEnable(DC);

	int volt = mc.readBatteryVoltage(1);
	printf("Battery: %.02fv\n\n", volt/100.0);

	return status;
}

void Jeffrey::reset(){
	Utils::waitFor(2);
	mc.controllerReset(DC);
}


void Jeffrey::moveForwardCM(int cm, int speed=100){

	int degree = WHEEL_DEGREE_CM * cm;
	int degree1 = degree+mc.readEncoderDegrees(DC, DC_1);
	int degree2 = -degree+mc.readEncoderDegrees(DC, DC_2);

	mc.setMotorDegrees(DC, speed, degree1, speed, degree2);

	//TODO maybe make a timeout
	while(mc.readEncoderDegrees(DC, DC_1) != degree1 ){
		Utils::waitForMicro(50000);
		printf("%d\n", degree1);
		printf("%ld\n\n", mc.readEncoderDegrees(DC, DC_1));
	}
	Utils::waitForMicro(50000);
	while(mc.readEncoderDegrees(DC, DC_2) != degree2 ){
		Utils::waitForMicro(50000);
		printf("%d\n", degree2);
		printf("%ld\n\n", mc.readEncoderDegrees(DC, DC_2));
	}

}

int Jeffrey::alignWithWall(int speed=25, float calib=0.75){
	float leftDistance;
    float rightDistance;

    while(1) {

        leftDistance = ultrasonic.getDistance(Ultrasonic::FRONT_RIGHT);
        rightDistance = ultrasonic.getDistance(Ultrasonic::FRONT_LEFT);

        if(leftDistance >= 400 || leftDistance <= 2 || rightDistance >= 400 || rightDistance <= 2 ){
        	
			mc.setMotorSpeeds(DC, 0, 0);
        	printf("One sensor is Out of range\n");

        }else if(leftDistance - calib > rightDistance){

        	printf("Turning right\n");
			mc.setMotorSpeeds(DC, speed, speed);

        }else  if(leftDistance < rightDistance - calib){

        	printf("Turning left\n");
			mc.setMotorSpeeds(DC, -speed, -speed);

        }else{
			
			mc.setMotorSpeeds(DC, 0, 0);
        	printf("Robot is perpendicular to the surface\n");

        }


		Utils::waitForMicro(100000);
    }
}
