TOPDIR!= pwd
INCDIR:= ${TOPDIR}/include

.export TOPDIR
.export INCDIR

# These values can be replaced in the shell for cross-compilation
# EXAMPLE: bmake linuxbuild TARGET_ARCH=aarch64
TARGET?= ${MACHINE}
TARGET_ARCH?= ${MACHINE_ARCH}

.export TARGET
.export TARGET_ARCH

# Add arg to override the system makefile directory
MAKE+= -m${TOPDIR}/share/mk

##############
#  all/info  #
##############
all: info allnoinfo .PHONY
allnoinfo: linuxbuild libbuild .PHONY

info: .PHONY
	@echo
	@echo "BUILDING FOR MACHINE: ${TARGET}"
	@echo "BUILDING FOR ARCHITECTURE: ${TARGET_ARCH}"
	@echo

################
#  linuxbuild  #
################
LINUXTAG:= v6.17
LINUXTARBALL:= ${LINUXTAG}.tar.gz

${LINUXTARBALL}:
	@echo "downloading ${LINUXTARBALL}..."
	wget https://github.com/torvalds/linux/archive/refs/tags/${LINUXTARBALL}
# Check the hash of the downloaded tarball against the locally saved hash
	@if [ "$$(cat ${LINUXTARBALL}.md5)" != "$$(md5sum ${LINUXTARBALL})" ]; then \
		echo "checksum of ${LINUXTARBALL} is invalid."; \
		rm -f ${LINUXTARBALL}; \
		exit 1; \
	fi

linux: ${LINUXTARBALL}
	@if [ -d linux ]; then rm -rf linux/*; fi
	mkdir -p linux
	tar xf ${LINUXTARBALL} -C linux --strip-components=1

linux/.config: linux
	ln -sf ${.CURDIR}/linuxconfig linux/.config

linuxbuild: linux linux/.config .PHONY
# Linux builds with GNU make, not BSD make, so we invoke gmake
	gmake -C linux \
		ARCH=${TARGET}
# Will install headers in ${TOPDIR}/include
	gmake -C linux headers_install INSTALL_HDR_PATH=${TOPDIR}	

##############
#  libbuild  #
##############
libbuild: .PHONY
	${MAKE} -C lib

###########
#  clean  #
###########
clean: .PHONY
	rm -rf ${LINUXTARBALL} linux
	@(cd include && git clean -fX)

	${MAKE} -C lib clean