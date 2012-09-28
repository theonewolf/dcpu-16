default:
	@clang dcpu.c \
		-o dcpu_test \
		-Wall \
		-Werror

clean:
	@rm -f dcpu_test
