
# HHKEngine

A rendering engine for the Classpad II fx-CP400. This can be used to make games, simulations and rendering shapes in 2D and 3D.

## Installation

Firstly, clone the project

```bash
git clone https://github.com/s3ansh33p/hhkengine
cd hhkengine
```
Make sure that you have python3 installed, then install the "Pillow" package
```bash
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade Pillow
```
To convert the textures for the classpad, run the following python scripts.
```bash
python3 ./convert_textures.py
python3 ./convert_fonts.py
```
To compile the program, make sure that you have the [Hollyhock-2 SDK](https://github.com/SnailMath/hollyhock-2) istalled, with newlib.

Once the SDK is installed, compile the program.
```bash
make hhk
```
If you want to recompile you can run the following command.
```bash
make clean && make hhk
```

## Features

- Tile system for games
- Collision detection for 2D entities / shapes
- Debug Menu for memory usage, entities, fps, keys and textures
- Event system to simplify handling inputs
- Save files
- Animated sprites / players
- Basic 3D rendering

## Documentation

Most .hpp and .py files contain documentation, though I'll create a wiki soon to give better and clearer documentation.

Feel free to join the [SnailMath Discord Server](https://discord.gg/k95AbVs7wv) if you need help with anything.

## License

This project is under [GPL-3](https://choosealicense.com/licenses/gpl-3.0/)


## Contributors

- [@s3ash33p](https://www.github.com/s3ash33p)
- [@InterChan](https://github.com/InterChan374)
- [@SnailMath](https://github.com/SnailMath/)
- [@DasHeiligeDoenerhuhn](https://github.com/DasHeiligeDoenerhuhn)
