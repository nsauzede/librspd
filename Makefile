TARGET=rspd
TARGET+=rspd2

CFLAGS:=-Wall -Werror -Wextra
CFLAGS+=-g
CFLAGS+=-O0

all: $(TARGET)

rspd: rspd.o librspd.h
	$(CC) -o $@ $< -pthread

clean:
	$(RM) $(TARGET) *.o

clobber: clean

mrproper: clobber
