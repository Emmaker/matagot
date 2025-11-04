TAG := v6.17
TARBALL := $(TAG).tar.gz

.PHONY: build install clean

ALL: build install

$(TARBALL):
	@echo "downloading $(TARBALL)..."
	wget https://github.com/torvalds/linux/archive/refs/tags/$(TARBALL)
	@if [ "$(shell cat $(TARBALL).md5)" != "$$(md5sum $(TARBALL))" ]; then \
		echo "checksum of $(TARBALL) is invalid."; \
		rm -f $(TARBALL); \
		exit 1; \
	fi

src: $(TARBALL)
	@if [ -d src ]; then rm -rf src; fi
	mkdir src
	tar xf $(TARBALL) -C src --strip-components=1

src/.config: src
	ln -sf $(shell pwd)/.config src/.config

build: src src/.config
	$(MAKE) -C src

install: build
	$(MAKE) -C src headers_install INSTALL_HDR_PATH=$(BUILD)
	cp -u src/vmlinux $(DEPLOY)/vmlinux

clean:
	rm -rf src $(TARBALL)