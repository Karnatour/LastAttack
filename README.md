# Last Attack

**Last Attack** is a **Tower Defense** game available for both **Windows** and **Linux** platforms. The game is developed using **C** and built using **SDL2**, **SDL2_ttf**, **SDL2_image**, **SDL2_gfx**, and **tmx**. Below you'll find detailed instructions for building and running the game on both platforms.

## Gameplay info
- Tower cost: 5
- Tower upgrade cost: 10
- Each upgrade has 5 tiers
- Number of HP: 5
- Number of waves: 3

## Keybinds
- ESC: exit the game
- V: toggle tower range when you hover over them

---

## Dependencies

To build **Last Attack**, you will need the following libraries installed on your system:

- **SDL2**
- **SDL2_ttf**
- **SDL2_image**
- **SDL2_gfx**
- **tmx** (bundled for Linux; Windows requires installation)

### Windows

On **Windows**, you can use **vcpkg** to install the necessary libraries:

### Linux

On **Linux** (specifically tested on Ubuntu or WSL Ubuntu), install the required libraries:

```shell
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-gfx-dev
```

## 2. Clone or Extract the Game Source
Clone the repository or extract the game files from the source.

Navigate to the Game Directory.
Open a terminal and navigate to the project directory, then create a build directory:

```cmake
mkdir build
cd build
```

Run CMake to Generate Build Files:
Generate the build files using CMake:

```cmake
cmake ..
```

Build the Project:
Run the following command to compile the game:

```cmake
make
```

Run the Game:
After building the game, you can run it using:

```shell
./Last Attack
```