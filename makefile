# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Ilib

# Source files
SRCS = main.c server.c client.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = bao

# Default rule
all: generate_headers $(TARGET)

# Create lib folder if it doesn't exist
lib_dir:
	@mkdir -p lib

# Automatically generate .h files from .c files (except main.c)
generate_headers: lib_dir
	@echo "Generating header stubs..."
	@for src in $(SRCS); do \
		if [ "$$src" != "main.c" ]; then \
			hfile="lib/$${src%.c}.h"; \
			if [ ! -f $$hfile ]; then \
				echo "// Auto-generated header for $$src" > $$hfile; \
				grep -E '^[a-zA-Z0-9_]+[ \*]+[a-zA-Z0-9_]+\([^\)]*\);' $$src >> $$hfile 2>/dev/null || true; \
				echo "// End of header" >> $$hfile; \
				echo "Created $$hfile"; \
			fi; \
		fi; \
	done

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)
