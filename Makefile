CC = cc
CFLAGS = -Wall -Wextra -O2
TARGET = archie
INSTALL_DIR = /usr/bin

all: $(TARGET)

$(TARGET): archie.c
	$(CC) $(CFLAGS) -o $(TARGET) archie.c

install: $(TARGET)
	install -m 755 $(TARGET) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all install uninstall clean
