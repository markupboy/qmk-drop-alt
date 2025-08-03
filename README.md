# qmk-drop-alt :keyboard:

This is a custom QMK keymap and lighting firmware for Drop ALT keyboards.

## Usage

- Clone the (`qmk_firmware`)[https://github.com/qmk/qmk_firmware] locally.

  `git clone --recurse-submodules git@github.com:qmk/qmk_firmware.git`

- Check out the 0.26.11 tag

  `git checkout 0.26.11`

- Clone this repository into `qmk_firmware/keyboards/massdrop/alt/keymaps/markupboy`

  `git clone git@github.com:markupboy/qmk-drop-alt ./keyboards/massdrop/alt/keymaps/markupboy`

- [Install, initialize, and start podman](https://podman.io/docs/installation)
- Build the firmware with:

  `util/docker_build.sh massdrop/alt:markupboy`

- Flash to keyboard with [QMK Toolbox](https://github.com/qmk/qmk_toolbox)

## LED Matrix Themes

### Outrun Sunset

![Outrun](https://raw.githubusercontent.com/AndrewJo/qmk-drop-alt/master/outrun-sunset.svg)
