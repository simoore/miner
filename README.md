# Miner

This project implements a bitcoin miner on the Xilinx ZYNQ-7000.

The software writes a block to be mined into memory. The software adds the required padding before mining commences. A 
set of mining cores will read in the block and hash it. Each mining core writes it own nonce to the block header. A 
mining core can manage multiple SHA256 implementations and will process a range of nonce's in parallel.

<https://zipcpu.com/> is an excellent source for FPGA tutorials and articles.

## Aims

* Build a distribution using first Petalinux tools.
* Understand how to use device tree, create own drivers etc
* Have memory-mapped IO and DMA transfers to memory fro PL-PS communication

## WSL Ubuntu 22.03.3 Development Environment Setup

```bash
sudo apt update
sudo apt upgrade
sudo apt install build-essential lzop u-boot-tools net-tools bison flex libssl-dev libncurses5-dev
sudo apt install libncursesw5-dev unzip chrpath xz-utils minicom
```

Download the linux compiler `arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-linux-gnueabihf.tar.xz` from 
<https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads>. 

```bash
sudo tar -xf arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-linux-gnueabihf.tar.xz -C /opt
```

I add the following function to my `.bashrc`.

<https://superuser.com/questions/39751/add-directory-to-path-if-its-not-already-there>

```bash
pathadd() {
    if [ -d "$1" ] && [[ ":$PATH:" != *":$1:"* ]]; then
        PATH="${PATH:+"$PATH:"}$1"
    fi
}

pathadd /opt/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-linux-gnueabihf/bin
```

## Device Tree Documentation

<https://www.devicetree.org/>
<https://elinux.org/Device_Tree_What_It_Is>
<https://www.kernel.org/doc/Documentation/devicetree/usage-model.txt>

## Clang

Download a release from <https://github.com/llvm/llvm-project/releases>

C:\msys64\ucrt64\bin
C:\msys64\usr\bin
C:\Program Files (x86)\Arm GNU Toolchain arm-none-linux-gnueabihf\12.3 rel1\bin
C:\GNU_MCU_Eclipse\OpenOCD\xpack-openocd-0.11.0-1\bin
C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\12.3 rel1\bin