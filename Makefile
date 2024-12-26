NAME				= minitalk
CLIENT				= client
SERVER				= server
CLIENT_BONUS		= client_bonus
SERVER_BONUS		= server_bonus

BUILD_DIR			= build
CLIENT_SRC			= client.c
SERVER_SRC			= server.c
CLIENT_BONUS_SRC	= client_bonus.c
SERVER_BONUS_SRC	= server_bonus.c

RM					= rm -rf
CFLAGS				= -Wall -Wextra -Werror -Ift_printf/include
LDFLAGS				= -Lft_printf
LDLIBS				= -lftprintf

$(NAME): all

all: $(CLIENT) $(SERVER)

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT): $(BUILD_DIR)/$(CLIENT).o
	@make -C ft_printf
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(SERVER): $(BUILD_DIR)/$(SERVER).o
	@make -C ft_printf
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(CLIENT_BONUS): $(BUILD_DIR)/$(CLIENT_BONUS).o
	@make -C ft_printf
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(SERVER_BONUS): $(BUILD_DIR)/$(SERVER_BONUS).o
	@make -C ft_printf
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@make -C ft_printf clean
	$(RM) $(BUILD_DIR)

fclean: clean
	@make -C ft_printf fclean
	$(RM) $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
