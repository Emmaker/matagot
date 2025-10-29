TAG="2.42"


if [ ! -f "glibc-$TAG.tar.gz" ]; then
    wget ftp://ftp.gnu.org/gnu/glibc/glibc-$TAG.tar.gz

    if [ ! $(echo $glibc-TAG.tar.gz.md5) -eq $(md5sum glibc-$TAG.tar.gz) ]; then
        echo "Checksum of glibc-$TAG.tar.gz not valid"
        exit 1
    fi
fi
if [ ! -d "$TAG-src" ]; then
    mkdir $TAG-src
    tar -xf glibc-$TAG.tar.gz -C $TAG-src
fi