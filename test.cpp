#include <vector>
#include <iostream>

#include <stdio.h>

#include "MyRio.h"
#include "I2C.h"
#include "Motor_Controller.h"
#include "Utils.h"

#include "opencv2/core.hpp"

#include "ImageSender.h"
#include "Ultrasonic.h"


#include "state.h"
#include "jeffrey.h"


using namespace std;
using namespace cv;

extern NiFpga_Session myrio_session;
NiFpga_Status status;


int main(int argc, char **argv) {
	
	status = MyRio_Open();
	if (MyRio_IsNotSuccess(status)) {
		return status;
	}

	Jeffrey jeffrey;
	jeffrey.init(&myrio_session);
	

	StateFunc statefunc = startedState;
	statefunc = (StateFunc)(*statefunc)(&jeffrey);


	jeffrey.reset();
	status = MyRio_Close();

	return status;
}