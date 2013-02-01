#!/bin/sh
### bootstrap the build system after cloning #################

echo "Generating autotools build system files"
mkdir -p build/autoconf
autoreconf --install --force --warnings=gnu || exit 1
echo "Run ./configure, make, and make install"
