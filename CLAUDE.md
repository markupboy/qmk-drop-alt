# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview
This is a custom QMK keymap for the Drop ALT keyboard, featuring:
- Custom "Outrun Sunset" RGB lighting theme
- Two-layer 65% ANSI layout
- Custom RGB matrix effects defined in `rgb_matrix_user.inc`

## Build Commands
Build the firmware:
```bash
util/docker_build.sh massdrop/alt:markupboy
```

Alternative build using QMK CLI:
```bash
qmk compile -kb massdrop/alt -km markupboy
```

## Architecture
- **keymap.c**: Main keymap definition with 2 layers (base layer and function layer)
- **config.h**: Disables most default RGB matrix effects to optimize for custom effect
- **rgb_matrix_user.inc**: Custom RGB matrix effect implementation for "Outrun Sunset" theme
- **rules.mk**: Enables custom RGB matrix user effects

## Key Components
- Base layer (0): Standard QWERTY layout with Fn key access
- Function layer (1): F-keys, RGB controls, media keys, and system functions
- Custom RGB effect uses HSV color manipulation for different key zones
- Underglow gradient effect from cyan to magenta based on LED position

## Development Notes
- QMK firmware version 0.26.11 is required
- Uses podman/docker containerized build environment
- Custom RGB effect targets specific LED indices for themed lighting zones
- Flash firmware using QMK Toolbox after building