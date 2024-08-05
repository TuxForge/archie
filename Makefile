CC = cc
src = archie.c
target = archie
all:
	$(target)
$(target): $(src)
	$(CC) -o $(target) $(src)
clean:
	rm -rf $(target)
