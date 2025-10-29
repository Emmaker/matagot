export ROOT ?= $(shell pwd)
export DEPLOY ?= $(ROOT)/deploy
export BUILD ?= $(ROOT)/build

.PHONY: linux

linux:
	@(cd linux && ./build.sh)

lib: linux
	$(MAKE) -C lib