CXX  = clang++ 
ARGS = -std=c++17
SRC  = *.cpp 

build := debug

ifeq ($(UNAME_S),Linux)
    BIN = ./bogosort.o 
else
	BIN = ./bogosort.exe 
endif
	
ifeq ($(build),release)
    ARGS += -O3
else
	ARGS += -g -O0 
endif

all:
	$(CXX) $(SRC) -o $(BIN) $(ARGS) 

clean:
	rm $(BIN)