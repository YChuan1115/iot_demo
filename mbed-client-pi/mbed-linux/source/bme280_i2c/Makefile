CC=gcc
INC=-I./ -I./include
CFLAG=-lpthread
DEBUG=-DMYDEBUG

debug:
	$(CC) ./src/*.c ./*.c -o app $(INC) $(CFLAG) $(DEBUG)

app:
	$(CC) ./src/*.c ./*.c -o app $(INC) $(CFLAG)

clean:
	rm app
