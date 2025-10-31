export ROOT ?= $(shell pwd)
export DEPLOY ?= $(ROOT)/deploy
export BUILD ?= $(ROOT)/build

.PHONY: build clean

ALL: build

build:
	$(MAKE) -C linux
	$(MAKE) -C lib

clean:
	$(MAKE) -C linux clean
	$(MAKE) -C lib clean