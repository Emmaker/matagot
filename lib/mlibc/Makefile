TAG := v6.3.1
TARBALL := $(TAG).tar.gz

.PHONY: build

ALL: build

$(TARBALL):
	@echo "downloading $(TARBALL)..."
	wget https://github.com/managarm/mlibc/archive/refs/tags/$(TARBALL)
	@if [ "$(shell cat $(TARBALL).md5)" != "$$(md5sum $(TARBALL))" ]; then \
		echo "checksum of $(TARBALL) is invalid."; \
		rm -f $(TARBALL); \
		exit 1; \
	fi

src: $(TARBALL)
	mkdir src
	tar xf $(TARBALL) -C src --strip-components=1

src/builddir:
	@(cd src && meson setup builddir \
		-Dlinux_kernel_headers=$(BUILD)/include)

build: src src/builddir
	@(cd src/builddir && ninja)

# Files will be temporarily held in inst/ before moving to build/ and deploy/
	@if [ ! -d inst ]; then mkdir inst; fi
	@(cd src/builddir && meson install \
		--destdir $(shell pwd)/inst)

clean:
	rm -rf src $(TARBALL)