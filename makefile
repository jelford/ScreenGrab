all:
	g++ -o ScreenGrab -lX11 `pkg-config --cflags --libs cairo` main.cpp
