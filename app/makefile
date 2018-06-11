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
	g++ $(OBJS) -L/usr/local/lib -w -lallegro_image -lallegro -lserial -fopenmp -o $(OBJ_NAME)
	sudo ./$(OBJ_NAME)
