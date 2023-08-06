# CPP Miner

A simple C++ Bitcoin miner.

## Build Instructions

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G Ninja
ninja
```

## References

* [Using CMake and managing dependencies](https://edw.is/using-cmake/)
* [Descriptions of SHA-256, SHA-384, and SHA-512](https://eips.ethereum.org/assets/eip-2680/sha256-384-512.pdf)