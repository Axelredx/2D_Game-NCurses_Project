all:
	g++ main.cpp box.hpp box.cpp player.cpp player.hpp dataManager.cpp dataManager.hpp market.cpp market.hpp -lncurses -o main