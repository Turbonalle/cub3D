# cub3D

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

Due to project constraints, compiling the game normally will give you a basic version, which won't be able to read all the maps. For an improved version that can run all the extra features we added, run this command instead:

`make bonus`
