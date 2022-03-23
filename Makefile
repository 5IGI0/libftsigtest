LIBFT_PATH ?= ../
CC = gcc
TESTS = ft_split ft_calloc ft_itoa

all: $(TESTS)

libcwrapper.dylib: common/inspect.c
	@echo "Compiling libc wrapper..."
	@gcc -dynamiclib ${<} -o ${@}

"${LIBFT_PATH}/libft.a":
	@echo "Compiling libft..."
	@make -C ${LIBFT_PATH}

${TESTS}: libcwrapper.dylib "${LIBFT_PATH}/libft.a"
	@gcc -o a.out "tests/test_${@}.c" -L"${LIBFT_PATH}" -lft -I"${LIBFT_PATH}"
	@DYLD_INSERT_LIBRARIES=libcwrapper.dylib ./a.out