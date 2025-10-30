.PHONY: build install clean

ALL: build install

build:
	$(MAKE) -C glibc build

install: build
	$(MAKE) -C glibc install

clean:
	$(MAKE) -C glibc clean