#
#  Configure:
#  source /opt/yocto/poky/1.3.2/environment-setup-core2-poky-linux
#
#OBJS specifies which files to compile as part of the project
OBJS = tube.cpp bird.cpp app.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = app

#This is the target that compiles our executable
all : $(OBJS)
	nasm -f elf buzzer.asm
	g++ -m32 $(OBJS) -o $(OBJ_NAME) buzzer.o -L/usr/local/lib -w -lallegro_image -lallegro -lserial -fopenmp 
	sudo ./$(OBJ_NAME)
