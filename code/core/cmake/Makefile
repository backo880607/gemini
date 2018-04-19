######################################
#
#
######################################
  
#target you can change test to what you want
#共享库文件名，lib*.so
TARGET  := libcore.so
  
#compile and lib parameter
#编译参数
CC      := gcc
LIBS    :=
LDFLAGS := ../../libs
DEFINES :=
INCLUDE := -I. -I../../../../third_party/boost_1_66_0
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H
SHARE   := -fPIC -shared -o
DIR_SRC = ../../../../code/core/src
DIR_OBJ = ../../objs
DIR_BIN = ../../bin
  
#i think you should do anything here
#下面的基本上不需要做任何改动了
  
#source file
#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件
SOURCE  := $(wildcard ${DIR_SRC}/*.c) $(wildcard ${DIR_SRC}/*.cpp)
OBJS    := $(patsubst %.c,${DIR_OBJ}/%.o,$(patsubst %.cpp,${DIR_OBJ}/%.o,$(SOURCE)))
BIN_TARGET = ${DIR_BIN}/${TARGET}
  
.PHONY : everything objs clean veryclean rebuild
  
everything : $(TARGET)
  
all : $(TARGET)
  
objs : $(OBJS)
  
rebuild: veryclean everything
                
clean :
    find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
    
veryclean : clean
    rm -fr $(TARGET)
  
$(TARGET) : $(OBJS)
    $(CC) $(CXXFLAGS) $(SHARE) $@ $(OBJS) $(LDFLAGS) $(LIBS)