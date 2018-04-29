BOOSTDIR=../

DIR_INC = .
DIR_SRC = .
DIR_OBJ = ./objs
DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJS = $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC}))
OBJS += $(wildcard ../common/objs/*.o)
OBJS += $(wildcard ../license/objs/*.o)
OBJS += $(wildcard ../network/objs/*.o)

TARGET = main
BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++
CFLAGS += -g -Wall -std=c++0x -I${BOOSTDIR}
LDFLAGS += -L$(BOOSTDIR)/lib -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options


${BIN_TARGET} : ${OBJS}
	$(CC) $(OBJS)  -o $@ -Wl,-Bstatic ${LDFLAGS} -Wl,-Bdynamic

${DIR_OBJ}/%.o : ${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY : clean
clean :
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
