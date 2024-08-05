CC = cc
target = archie
source = archie.c
prefix = /bin/
all: $(source)
	$(CC) -o $(target) $(source)
install: $(target)
	cp $(target) $(prefix)
