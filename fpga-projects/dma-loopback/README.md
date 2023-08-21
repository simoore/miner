# DMA Loop Back

This project follows this tutorial:
<https://www.hackster.io/whitney-knitter/introduction-to-using-axi-dma-in-embedded-linux-5264ec>

The part number is XC7Z007S-1CLG400. <https://digilent.com/reference/programmable-logic/cora-z7/start>

Diligent provides board files which allows you to select the board during project creation and provides configuration
for some of Xilinx's IP cores including the processing system. Download the board files from 
<https://github.com/Digilent/vivado-boards/tree/master> and copy the `new/board_files` directory into your 
vivado installation at `<Vivado installation path>/data/boards/board_files`. When using creating a block design, the 
`board` tab allows you insert preconfigured cores for this board that are defined in the board files.

## Windows Subsystem for Linux

<https://learn.microsoft.com/en-us/windows/wsl/install-manual>
<https://www.sitepoint.com/wsl2/>

You need to enable the following windows features: WSL and the virtual machine platform. Then I executed the following
commands to setup WSL version 2:

```bash
wsl --set-default-version 2
wsl --update
```

Use `wsl --list --online` to list available distributions then, for example to install Ubuntu 22.04, execute the 
following command to install a distribution:

```bash
wsl --install -d Ubuntu-22.04
```

You'll be asked to setup a username and password once installation in complete. You can see the installed distributions 
using `wsl -l -v` or in App & Features in Windows settings. You can uninstall a distro via App & Features. With only 
once distribution, you can launch a termain session using `wsl`.

## Installing Petalinux with WSL

