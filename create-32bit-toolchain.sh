#!/usr/bin/env sh

export TARGET=i386-elf
export PREFIX=/usr/local/i386-elf-gcc
export PATH="$PREFIX/bin:$PATH"

mkdir -p ~/src
cd ~/src

# Binutils
wget https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.xz
tar -xf binutils-2.41.tar.xz
mkdir build-binutils && cd build-binutils
../binutils-2.41/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j$(sysctl -n hw.ncpu)
make install
cd ..

# GCC
wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.xz
tar -xf gcc-13.2.0.tar.xz
mkdir build-gcc && cd build-gcc
../gcc-13.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j$(sysctl -n hw.ncpu)
make all-target-libgcc -j$(sysctl -n hw.ncpu)
make install-gcc
make install-target-libgcc
