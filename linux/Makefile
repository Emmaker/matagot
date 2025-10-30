TAG := v6.17
TARBALL := $(TAG).tar.gz

ALL: build

$(TARBALL):
	@echo "downloading $(tarball)..."
	wget https://github.com/torvalds/linux/archive/refs/tags/$(tarball)
	@if [ "$(cat $(tarball).md5)" != "$(md5sum $(tarball))" ]; then \
		echo "checksum of $(tarball) is invalid."; \
		exit 1; \
	fi

src: $(TARBALL)
	mkdir src
	tar xf $(TARBALL) -C src --strip-components=1

src/.config: src
	ln -sf $(shell pwd)/.config src/.config

build: src src/.config
	$(MAKE) -C src

install: build
	$(MAKE) -C src headers_install INSTALL_HDR_PATH=$(DEPLOY)

clean:
	rm -rf src $(TARBALL)