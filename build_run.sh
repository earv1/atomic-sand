#!/bin/bash
meson . builddir --buildtype=debug --reconfigure

ninja -C builddir && ./builddir/run_atomic_sand