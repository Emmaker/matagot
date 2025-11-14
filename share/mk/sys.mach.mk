.ifnmake __<sys.mach.mk>__
__<sys.mach.mk>__: .NOTMAIN

TARGET?= ${MACHINE}
TARGET_ARCH?= ${MACHINE_ARCH}

.endif ## __<sys.mach.mk>__ ##
