TARGET = personagens
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -Imodels -Idatabase -Iinterface

SRCS = main.c \
       models/adventure.c \
       models/inventory.c \
       models/item.c \
       database/table.c \
       database/adventure_table.c \
       database/inventory_table.c \
       database/item_table.c \
       interface/interface.c \
       interface/adventure_interface.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
