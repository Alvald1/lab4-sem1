CFLAGS = -Wall -Wextra -Werror

ASAN = -fsanitize=address,undefined -g

REPORT_DIR = report_dir
LIB_DIR = lib
EXECUTABLE = bin

LDFLAGS = -lreadline

all: compile

compile: formating
	cc -c *.c $(CFLAGS) $(LDFLAGS)
	cc -c $(LIB_DIR)/*.c $(CFLAGS)
	cc *.o $(CFLAGS) -o $(EXECUTABLE)_clean $(LDFLAGS)
	rm *.o

debug: formating
	cc -c -g *.c $(CFLAGS) 
	cc -c -g $(LIB_DIR)/*.c $(CFLAGS) 
	cc *.o $(CFLAGS) -o $(EXECUTABLE)_debug $(LDFLAGS)
	rm *.o

asan: formating
	clang -c *.c $(CFLAGS) $(ASAN)
	clang -c $(LIB_DIR)/*.c $(CFLAGS) $(ASAN)
	clang *.o $(CFLAGS) $(ASAN) -o $(EXECUTABLE)_asan $(LDFLAGS)
	rm *.o

static: formating
	clang --analyze -Xanalyzer -analyzer-output=html -o $(REPORT_DIR) *.c
	clang --analyze -Xanalyzer -analyzer-output=html -o $(REPORT_DIR) $(LIB_DIR)/*.c

formating:
	clang-format *.c $(LIB_DIR)/*.c -i -style=webkit

clean:
	rm -f $(EXECUTABLE)* */*.html

help:
	@echo "Available targets:"
	@echo "  all      : Build the executable with default settings"
	@echo "  compile  : Build the executable"
	@echo "  debug    : Build the executable with debugging information"
	@echo "  asan     : Build the executable with AddressSanitizer"
	@echo "  static   : Run static analysis and generate HTML reports"
	@echo "  clean    : Remove generated files"
	@echo "  formating: Format source code using clang-format"
	@echo "  help     : Display this help message"
	
