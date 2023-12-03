# RTL Miner

The processing system writes a block to memory for hashing. This block is preceded by a descriptor that includes 
the size of the block, if processing has been finished, and a space to write the resulting hash. The processing system
also adds any padding required for hashing. Then the processor finds a hashing perpheral that is not busy and supplies 
the address of the descriptor and the hashing peripheral starts processing it. The processing system must poll to 
peripheral to see if it has finished.

Each hashing peripheral contains a AXI4-Lite slave iterface for the control registers, and a AXI4 master interface to
read the block from memory.

## TODOs

* Project Setup and build automation (cmake, tcl, or other)
* Testbench and error checking
* Test bench SHA256 

## VS Code Integration

I'm using the plugin [Verilog-HDL/SystemVerilog/Bluespec SystemVerilog](https://marketplace.visualstudio.com/items?itemName=mshr-h.VerilogHDL)
and I've set the linter to `xvlog`. For this to work I've added the `bin` and `lib` directory of my vivado installation
to the path.

## Links

### FPGA Development

* [Building a basic AXI Master](https://zipcpu.com/blog/2020/03/23/wbm2axisp.html)
* [Building a custom yet functional AXI-lite slave](https://zipcpu.com/blog/2019/01/12/demoaxilite.html)
* [WB2AXIP: Bus interconnects, bridges, and other components](https://github.com/ZipCPU/wb2axip)

### Bitcoint Mining

* [Understanding the Bitcoin Blockchain Header](https://medium.com/fcats-blockchain-incubator/understanding-the-bitcoin-blockchain-header-a2b0db06b515)

### SHA256 Algorithm

* [SHA256 Wikipedia](https://en.wikipedia.org/wiki/SHA-2)
* [SHA256 FPGA implementation](https://github.com/secworks/sha256)
* [Open-Source FPGA Bitcoin Miner](https://github.com/progranism/Open-Source-FPGA-Bitcoin-Miner)
* [US Secure Hash Algorithms (SHA and HMAC-SHA)](https://www.rfc-editor.org/rfc/rfc4634)
* [Descriptions of SHA-256, SHA-384, and SHA-512](https://eips.ethereum.org/assets/eip-2680/sha256-384-512.pdf)

### Project Setup Examples

* [Xilinx Vivado setup for source control](https://github.com/jhallen/vivado_setup)

### Verification

* [Chip Verify: UVM Tutorial](https://www.chipverify.com/uvm/uvm-tutorial)
