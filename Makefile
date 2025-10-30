export ROOT ?= $(shell pwd)
export DEPLOY ?= $(ROOT)/deploy
export BUILD ?= $(ROOT)/build

.PHONY: build install clean

ALL: build install

build:
	$(MAKE) -C linux build
	$(MAKE) -C lib build

install: build
	$(MAKE) -C linux install
	$(MAKE) -C lib install

clean:
	$(MAKE) -C linux clean
	$(MAKE) -C lib clean