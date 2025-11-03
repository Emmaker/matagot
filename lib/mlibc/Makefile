.PHONY: build install

ALL: build install

build:
	meson setup builddir -Dlinux_kernel_headers=$(BUILD)/include
	@(cd builddir && ninja)

install:
	@. ./install.sh	