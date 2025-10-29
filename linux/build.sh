TAG="v6.17"

if [ ! -f "$TAG.tar.gz" ]; then
    wget https://github.com/torvalds/linux/archive/refs/tags/$TAG.tar.gz

    if [ ! $(echo $TAG.tar.gz.md5) -eq $(md5sum $TAG.tar.gz) ]; then
        echo "Checksum of $TAG.tar.gz not valid"
        exit 1
    fi
fi
if [ ! -d "$TAG-src" ]; then
    mkdir $TAG-src
    tar -xf $TAG.tar.gz -C $TAG-src
fi

ln -sf $PWD/.config $PWD/$TAG-src/.config 
(cd $TAG-src && make && \
    make headers_install INSTALL_HDR_PATH=$BUILD)