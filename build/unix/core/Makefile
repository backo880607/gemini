######################################
#
#
######################################
  
#target you can change test to what you want
#共享库文件名，lib*.so
TARGET  := libcore.so

#自定义目录
DIR_HOME = ../../../code/core
DIR_SRC = ${DIR_HOME}/src
DIR_INC = -I${DIR_HOME}

DIR_THIRD = ../../../third_party
DIR_INC += -I${DIR_THIRD}/boost_1_66_0
DIR_INC += -I${DIR_HOME}/public
DIR_INC += -I${DIR_HOME}/include

#编译生成目录
DIR_BUILD = .
DIR_OBJ = ${DIR_BUILD}/objs
DIR_BIN = ${DIR_BUILD}/bin
DIR_LIB = ${DIR_BUILD}/libs

#compile and lib parameter
#编译参数
CC      := g++
LIBS    :=
LDFLAGS := -L$(DIR_LIB)/
DEFINES :=
INCLUDE := -I. ${DIR_INC}
CFLAGS  := -g -Wall -O3 -std=c++0x $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H
SHARE   := -fPIC -shared -o


#i think you should do anything here
#下面的基本上不需要做任何改动了
  
#source file
#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件
SRC  := $(foreach dir, ${DIR_SRC}, $(wildcard ${dir}/*.cpp))
OBJS = $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC}))
BIN_TARGET = ${DIR_BIN}/${TARGET}

${BIN_TARGET} : ${OBJS}
	$(CC) -fPIC -shared $(OBJS)  -o $@ -Wl,-Bstatic ${LDFLAGS} -Wl,-Bdynamic
${DIR_OBJ}/%.o : ${DIR_SRC}/%.cpp
	$(CC) -fPIC $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
