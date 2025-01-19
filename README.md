# How to Clone and Build the Project

## Project Description
R-Type is a third-year Epitech project focused on developing a multiplayer shoot-'em-up game inspired by the classic R-Type arcade game.

## Prerequisites
Before you start, ensure your system has the following installed:
- **Git**
- **CMake**
- **Make**
- **FreeType library**

### Installing FreeType
- On **Ubuntu/Debian**: `sudo apt-get install libfreetype6-dev`
- On **Fedora**: `sudo dnf install freetype-devel`
- On **Arch Linux**: `sudo pacman -S freetype2`

---

## Steps to Clone and Build the Project

1. **Clone the repository**:
   ```bash
   git clone git@github.com:M0ugou-club/R-Type.git
   cd R-Type
   ```

2. **Install prerequisites**:
   Ensure that the required libraries and tools mentioned above are installed.

3. **Update submodules**:
   ```bash
   git submodule update --init --recursive
   ```

4. **Create a build directory**:
   ```bash
   mkdir build
   cd build
   ```

5. **Run CMake**:
   ```bash
   cmake ..
   ```

6. **Build the project**:
   ```bash
   make
   ```

## Documentation

[User documentation (Click)](https://m0ugou-club.github.io/R-Type/mdbook/book/index.html)

[Technical documentation (Click)](https://m0ugou-club.github.io/R-Type/doxygen/html/)

Network documentation :

    ```bash
    cat docs/RFC.txt
    ```

#Credits

- [Xer0ce](https://github.com/Xer0ce)
- [felixlvu](https://github.com/felixlvu)
- [albe2](https://github.com/albe2)
- [antonincmp](https://github.com/antonincmp)
- [Klaiveft](https://github.com/Klaiveft)
