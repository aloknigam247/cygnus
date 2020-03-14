$(BIN)/clg: clg.c clg.tab.c
	gcc clg.c clg.tab.c -lfl -o $(BIN)/clg

clg.c: clg.l clg.tab.h
	flex -o clg.c clg.l

clg.tab.c: clg.y
	bison -d clg.y

clg.l:
	echo "clg.l"
