CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
SOURCES = my_malloc.c 
TARGET = my_malloc
CC = gcc

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^
.PHONY:
	fclean

fclean:
	@rm -f $(OBJECTS) $(TARGET)