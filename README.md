# cub3D

You're trapped in a slimey dungeon, with only one goal - to escape in one piece!

This is a raycasting game inspired by the old Wolfenstein3D game. The world has seen so many first person shooters, though, so we took a non-violent approach. There are hungry slime monsters lurking around, but you have no weapons to take care of them. If only you had something to distract them with, so you can run past them.

<br>

### Goals

The goals of this project was to:
- create a raycasting game
- make an error-proof map parser
- enable the player to move and look around
<br><br>

Some of the extra features we added for fun:
- Collision detection
- Timer
- Built-in speedrun levels with locally stored records
- Health bar
- Slime monsters that will attack you if they see you
- Mushrooms you can pick up and throw to distract the slime monsters
- Doors and keys
- Pause menu
- Choice to look around with either left/right arrows or mouse
- Ability to set FOV
- Zoomable and movable minimap

<br>

### How to play

- W,S,A,D - move around
- Left/Right arrow - turn around
- P - toggle pause menu
- Esc - go back to previous menu

<br>

## Installation

### MacOS

Make sure you have **GLFW** and **CMake** installed on your system. If you don't, run the following command to install both (be aware that it may take some time):

`brew install glfw`

To clone the repository:

`git clone --recursive https://github.com/Turbonalle/cub3D.git`

To compile, navigate to the root of the repo and run:

`make`

Run the executable with the path to any of the maps as a parameter:

Ex.
`./cub3D assets/maps/showcase.cub`

Due to project constraints, compiling the game normally will give you a basic version, which won't be able to read all the maps. For an improved version that can run all the maps with every extra feature, run this command instead:

`make bonus`
