# cub3D

## Installation

### MacOS

Make sure you have **GLFW** and **CMake** installed on your system. If you don't, run the following command to install both (be aware that it may take some time):

`brew install glfw`

To clone the repository:

`git clone --recursive https://github.com/Turbonalle/cub3D.git`

To compile, navigate to the root of the repo and run:

`make`


## About

Cub3d is a 42 project, designed to introduce students to the interesting world of raycasting. The task is to build a very minimal version of the old Wolfenstein3D game. The only requirements are:

- the program has to take in a .cub file (containing wall textures, floor and ceiling color, and the map) as an argument
- to parse the .cub file in a specific way
- draw a world based on the player position and direction using raycasting
- add the ability to move (WSAD) and rotate (LEFT/RIGHT) player

To earn bonus points, the following features were supposed to be added:

- wall collisions
- a minimap
- doors that can open and close
- animated sprite
- ability to rotate player with mouse

We felt like this was a perfect project to get creative and go beyond the scope of what the subject asks for. Hence, this game was born. The escape from a slimy dungeon, with ravenous blobs (don't let the cuteness fool you) hungry for your flesh. In addition to the basic and bonus requirements, we also added the following features:

### Goal

First things first, who wants to wander endlessly aroung in a dungeon, without any hope of escape? A goal had to be added. In order to escape, you need to reach the the portal that takes you outside. You'll recognize it from the sparkling stars in a midnight sky.

### Speedrunning

Running through a random level found in the map folder wasn't enough, so we added speedrunning levels, in order to give the player a challenge and add more replayability to the game. The scores will be saved in a leaderboard, and will be carried across local gaming sessions.

### Enemies

As stated earlier, there will be hungry blobs of slime who will hunt you if they see you.

### Health

If you get hit by an enemy, you'll lose a heart. Once out of hearts, it's game over for you. Normally you'll have three hearts, but in speedrunning levels you only get one!

### Distractions
