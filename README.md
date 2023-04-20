# Pong

Simple game of Pong developed to practice the usage of SDL2. The ultimate goal is to make the game multiplayer using the Enet library (or some other similar library)

# Build

To build the project, you must first install the SDL2 and the SDL2_ttf libraries. Also, the [Peepo](https://www.dafont.com/peepo.font) font was used to display de score of the game. 

After the necessary libraries and fonts have been installed, you can run the following command to build the project: g++ main.cpp -o Pong -I/opt/homebrew/Cellar/sdl2/2.26.4/include -L/opt/homebrew/Cellar/sdl2/2.26.4/lib -L/opt/homebrew/Cellar/sdl2_ttf/2.20.2/lib -lSDL2 -lSDL2_ttf
