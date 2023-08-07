# Blink LED Project

This project is based on the tutorial:
<https://redpitaya-knowledge-base.readthedocs.io/en/latest/learn_fpga/4_lessons/LedBlink.html>

I had a lot of trouble loading the bitstream. In turns out in the new version of REd Pitaya's OS image, the process
to load a new FPGA design has changed:

```bash
# V1 OS - this is the old method of loading the bitstream for reference.
cat led_blink.bit > /dev/xdevcfg

# V2 OS - first, generate the bitstream in the correct format on your development machine.
echo -n "all:{ ./led_blink.bit }" > led_blink.bif
bootgen -image led_blink.bif -arch zynq -process_bitstream bin -o led_blink.bit.bin -w

# Then load the bitstream on the FPGA
fpgautil -b led_blink.bit.bin
```