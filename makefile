OBJS	= main.o state.o jeffrey.o
SOURCE	= main.cpp state.cpp jeffrey.cpp
OUT	= colorMover.out

TOBJS	= test.o state.o jeffrey.o
TSOURCE	= test.cpp state.cpp jeffrey.cpp
TOUT	= colorMoverTest.out


HEADER	= 
CC		= /usr/local/oecore-x86_64/sysroots/x86_64-nilrtsdk-linux/usr/bin/arm-nilrt-linux-gnueabi/arm-nilrt-linux-gnueabi-g++ 
CFLAGS	= --sysroot=/usr/local/oecore-x86_64/sysroots/cortexa9-vfpv3-nilrt-linux-gnueabi -std=c++11 -pthread
INCLUDE = -I../imageSender/imageSender -I../ultrasonic/ultrasonic/ -I../opencvLib/include/opencv4/ -I../myrio/myrio -I../myrio/myrio/csupport -I"/usr/local/oecore-x86_64/sysroots/cortexa9-vfpv3-nilrt-linux-gnueabi/usr/include" -I"/usr/local/oecore-x86_64/sysroots/cortexa9-vfpv3-nilrt-linux-gnueabi/usr/include/c++/4.9.2/arm-nilrt-linux-gnueabi" 
FLAGS	= -g -c -Wall -DMyRio_1900 -O0 -g3 -Wall -std=gnu++11 -fmessage-length=0 -mfpu=vfpv3 -mfloat-abi=softfp
LFLAGS 	= -L../imageSender/imageSender -L../ultrasonic/ultrasonic -L../opencvLib/lib/opencv -L/usr/lib/opencv -L../myrio/myrio -L../myrio/myrio/csupport -lultrasonic -limagesender -lcsupport -lmyrio -limagesender -ldl -lopencv_calib3d -lopencv_core -lopencv_dnn -lopencv_features2d -lopencv_flann -lopencv_gapi -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_videoio

all: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -g $(OBJS) -o $(OUT)  $(LFLAGS)

test: $(TOBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -g $(TOBJS) -o $(TOUT)  $(LFLAGS)



main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(FLAGS) main.cpp

state.o: state.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(FLAGS) state.cpp

jeffrey.o: jeffrey.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(FLAGS) jeffrey.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(FLAGS) test.cpp



clean:
	rm -f $(OBJS) $(OUT) $(TOBJS) $(TOUT)

