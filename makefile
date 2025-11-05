topdir!= pwd
incdir:= ${topdir}/include

.export topdir
.export incdir

################
#  linuxbuild  #
################
linuxtag:= v6.17
linuxtarball:= ${linuxtag}.tar.gz

${linuxtarball}:
	@echo "downloading ${linuxtarball}..."
	wget https://github.com/torvalds/linux/archive/refs/tags/${linuxtarball}
# Check the hash of the downloaded tarball against the locally saved hash
	@if [ "$$(cat ${linuxtarball}.md5)" != "$$(md5sum ${linuxtarball})" ]; then \
		echo "checksum of ${linuxtarball} is invalid."; \
		rm -f ${linuxtarball}; \
		exit 1; \
	fi

linux: ${linuxtarball}
	@if [ -d linux ]; then rm -rf linux/*; fi
	mkdir -p linux
	tar xf ${linuxtarball} -C linux --strip-components=1

linux/.config: linux
	ln -sf ${.CURDIR}/linuxconfig linux/.config

linuxbuild: linux linux/.config .PHONY
# Linux builds with GNU make, not BSD make, so we invoke gmake
	gmake -C linux
# Will install headers in ${topdir}/include
	gmake -C linux headers_install INSTALL_HDR_PATH=${topdir}	

###########
#  clean  #
###########
clean: .PHONY
	rm -rf ${linuxtarball} linux