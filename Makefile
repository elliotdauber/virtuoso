CC = g++ --std=c++11
CXXFLAGS = -O0 -Wall -g -Iincludes

VPATH = src
SRC = $(wildcard src/*.cc)

TARGET = virtuoso

all: $(TARGET)

$(TARGET): main.cc $(SRC)
			$(CC) $(CXXFLAGS) -o $(TARGET) main.cc $(SRC)

clean:
	$(RM) $(TARGET)