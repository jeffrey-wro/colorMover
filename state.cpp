#include <stdio.h>

#include "Motor_Controller.h"
#include "jeffrey.h"
#include "state.h"

void* startedState(Jeffrey* jeffrey){

	printf("startedState\n");
	fflush(stdout);

	//move 36cm to be out of the box and 10cm to maneuver
	jeffrey->moveForwardCM(36+10, 150);

	return (void *)outOfBox;
}

void* outOfBox(Jeffrey* jeffrey){

	printf("outOfBox\n");
	fflush(stdout);

	//align perpendicular with wall
	jeffrey->alignWithWall(25, 0.75);

	return (void *)stoppedState;
}

void* stoppedState(Jeffrey* jeffrey){

	printf("stoppedState\n");
	fflush(stdout);

	if(false){
		return NULL; //Next state
	}

	if(false){
		return NULL; //Next state
	}

	return (void *)stoppedState;
}