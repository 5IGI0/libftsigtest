LIBFT_PATH ?= ../
TESTS = ft_split ft_calloc ft_itoa ft_strdup ft_substr ft_strjoin ft_strmapi
BONUSES = ft_lstnew ft_lstmap

mandatory: $(TESTS)

bonus: $(BONUSES)

all: mandatory bonus

libcwrapper.dylib: common/inspect.c
	@echo "Compiling libc wrapper..."
	@gcc -dynamiclib ${<} -o ${@}

compile_bonus:
	@make bonus -C ${LIBFT_PATH}

"${LIBFT_PATH}/libft.a":
	@echo "Compiling libft..."
	@make -C ${LIBFT_PATH}

${BONUSES}: compile_bonus

${TESTS} ${BONUSES}: libcwrapper.dylib "${LIBFT_PATH}/libft.a"
	@gcc -o a.out "tests/test_${@}.c" -L"${LIBFT_PATH}" -lft -I"${LIBFT_PATH}"
	@DYLD_INSERT_LIBRARIES=libcwrapper.dylib ./a.out