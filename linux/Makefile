TAG := v6.17
TARBALL := $(TAG).tar.gz

.PHONY: build clean

ALL: build

$(TARBALL):
	@echo "downloading $(TARBALL)..."
	wget https://github.com/torvalds/linux/archive/refs/tags/$(TARBALL)
	@if [ "$(shell cat $(TARBALL).md5)" != "$$(md5sum $(TARBALL))" ]; then \
		echo "checksum of $(TARBALL) is invalid."; \
		rm -f $(TARBALL); \
		exit 1; \
	fi

src: $(TARBALL)
	mkdir src
	tar xf $(TARBALL) -C src --strip-components=1

src/.config: src
	ln -sf $(shell pwd)/.config src/.config

build: src src/.config
	$(MAKE) -C src
	$(MAKE) -C src headers_install INSTALL_HDR_PATH=$(BUILD)

clean:
	rm -rf src $(TARBALL)