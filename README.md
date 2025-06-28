# Delta Calculator (C++)

Simple C++ implementation of the Vega option Greek using the Black-Scholes model.

## Build

First, you need to install Quantlib. On Mac:

```bash
brew install quantlib
```

Make sure the `CMakeLists.txt` has the maching links for your system.

Then, compile with:

```bash
mkdir build
cd build
cmake ..
make
```

## Run

```bash
./delta_quantlib
```