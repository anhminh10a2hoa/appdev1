OBJ = main.o screen.o sound.o comm.o
APPNAME = sound.out

# math library is used
$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm -lcurl

%.o : %.c
	gcc -c -o $@ $<

clean :
	rm $(APPNAME) $(OBJ)

tar :
	tar cf sound.tar *.c *.h makefile
