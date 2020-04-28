.PHONY: default

default: $(OBJ_DIR)/lang $(OBJ_DIR)/lang/c-bison.o $(OBJ_DIR)/lang/c-flex.o
	$(CPP_COMPILER) -o $(EXE) $(shell find $(OBJ_DIR) -name "*.o")

$(OBJ_DIR)/lang:
	$Qmkdir -p $@

$(OBJ_DIR)/lang/c-bison.o: c-bison.c
	gcc -c -o $@ $^

$(OBJ_DIR)/lang/c-flex.o: c-flex.c c-bison.h
	gcc -c -o $@ $<

c-bison.c: c.y
	bison --defines=c-bison.h -o $@ $^

c-flex.c: c.l
	flex -o $@ $^

c.y c.l: c.cyl
	cygnus -l c.cyl
