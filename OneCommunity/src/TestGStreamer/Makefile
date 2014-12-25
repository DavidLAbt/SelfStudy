CC=gcc
CPP=g++
INCLUDES=-I/Library/Frameworks/GStreamer.framework/Versions/1.0/Headers/
CFLAGS=-c -Wall $(INCLUDES)
CPPFLAGS=-c -Wall $(INCLUDES)
LDFLAGS=-L/Library/Frameworks/GStreamer.framework/Versions/1.0/lib/ -lgstreamer-1.0 -lglib-2.0 -lgobject-2.0 -lc++
SRC_DIR=./src/
BIN_DIR=./bin/


#SOURCES=               \
	$(SRC_DIR)ex4_1.cpp    				\
	$(SRC_DIR)ex4_2.cpp						\
	$(SRC_DIR)ex5_1.cpp						\
	$(SRC_DIR)ex5_5.cpp						\
	$(SRC_DIR)ex7_1.cpp						\
	$(SRC_DIR)ex10_1.cpp
#OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES:.c=.o))
#EXECUTABLES=$(patsubst %.cpp,%.o,$(SOURCES:.cpp=))

#all: $(SOURCES) $(EXECUTABLES)

clean:
	rm -r $(BIN_DIR)/*

%:
	
	$(CC) $(CPPFLAGS) $(SRC_DIR)$*.cpp  -o $(BIN_DIR)$*.o
	$(CC) $(LDFLAGS) $(BIN_DIR)$*.o -o $(BIN_DIR)$*
	
#$(EXECUTABLES): $(OBJECTS)
#	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

#.c.o:
#	$(CC) $(CFLAGS) $< -o $@

#.cpp.o:
#	$(CPP) $(CPPFLAGS) $< -o $@