TAG := 2.42
TARBALL := glibc-$(TAG).tar.gz

$(TARBALL):
	@echo "downloading $(tarball)..."
	wget ftp://ftp.gnu.org/gnu/glibc/$(TARBALL)
	@if [ "$(cat $(tarball).md5)" != "$(md5sum $(tarball))" ]; then \
		echo "checksum of $(tarball) is invalid."; \
		exit 1; \
	fi

src: $(TARBALL)
	mkdir src
	tar xf $(TARBALL) -C src --strip-components=1

src/build: src
	mkdir src/build
	@(cd src/build && \
		CFLAGS="-I$(BUILD)/include" ../configure --prefix=$(BUILD))

build: src src/build
	$(MAKE) -C src/build build

install: build
	$(MAKE) -C src/build install

clean:
	rm -rf src $(TARBALL)