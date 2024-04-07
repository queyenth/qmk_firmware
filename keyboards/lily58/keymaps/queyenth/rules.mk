OLED_ENABLE= yes     # OLED display
RAW_ENABLE= yes

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/layer_state_reader.c \
	./lib/pomodoro.c \
	./lib/matrix_animation.c \
        #./lib/logo_reader.c \
        #./lib/rgb_state_reader.c \
        #./lib/keylogger.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/timelogger.c \
