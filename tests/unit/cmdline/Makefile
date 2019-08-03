CY_COMP := g++ -I /home/alok/Project/cygnus/include
OBJ_DIR := $(CYGNUS_HOME)/tests/unit/obj

all: $(OBJ_DIR) test

test: test.o $(OBJ_DIR)/cmdline.o 
	$(CY_COMP) -o $@ $^

test.o: test.cc test.h
	$(CY_COMP) -c $< -o $@

$(OBJ_DIR)/cmdline.o: /home/alok/Project/cygnus/src/cmdline.cc /home/alok/Project/cygnus/include/cmdline.h
	$(CY_COMP) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf test.o $(OBJ_DIR)/cmdline.o test
