.PHONY: build install clean

ALL: build install

build:
	meson setup builddir -Dlinux_kernel_headers=$(INCLUDE)
	@(cd builddir && ninja)

install:
	@. ./install.sh	

clean:
	rm -rf builddir