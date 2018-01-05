TARGET = main

#directory
BIN = bin
SRC = src
INC = inc






#source file
SOURCE = $(wildcard $(SRC)/*.cpp)
#object file
OBJECT = $(patsubst %,$(BIN)/%,$(notdir $(SOURCE:.cpp=.o)))

CFLAGS = -std=c++11 -Wall


$(BIN)/$(TARGET) : $(OBJECT)
	g++ $(CFLAGS) -o $@ $^ -levent -lpthread -lprussdrv

$(BIN)/%.o : $(SRC)/%.cpp
	g++ $(CFLAGS) -I $(INC) -c $< -o $@ -levent



.PHONY : run
run : $(BIN)/$(TARGET)
	$(BIN)/$(TARGET)



.PHONY : clean
clean :
	rm $(BIN)/*



.PHONY : help
help :
	@echo "src: $(SOURCE)"
	@echo "obj: $(OBJECT)"