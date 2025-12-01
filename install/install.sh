#!/usr/bin/env bash

set -e

LOGOS_GIT_URL=https://gitlab.com/rmordechay1/logos
INSTALL_PREFIX="${INSTALL_PREFIX:-/usr/local}"
TEMP_DIR=$(mktemp -d)

cleanup() {
  echo "Cleaning up"
  rm -rf "$TEMP_DIR"
}

trap cleanup EXIT

detect_os() {
  if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
    WORKERS=$(nproc)
    LGS_LIB="lgslib.so"
  elif [ -f /etc/os-alpine ]; then
    OS="alpine"
    WORKERS=$(nproc)
    LGS_LIB="lgslib.so"
  elif [[ "$OSTYPE" = "darwin"* ]]; then
    OS="macos"
    WORKERS=$(sysctl -n hw.ncpu)
    LGS_LIB="lgslib.dylib"
  else
    echo "Operating system could not be detected."
    exit 1
  fi
}

install_debian() {
  apt-get update
  DEBIAN_FRONTEND=noninteractive apt-get install -y \
    curl git cmake clang-19 libclang-19-dev libclang-cpp19-dev
  update-alternatives --install /usr/bin/clang clang /usr/lib/llvm-19/bin/clang 100
  update-alternatives --install /usr/bin/clang++ clang++ /usr/lib/llvm-19/bin/clang++ 100
  update-alternatives --install /usr/bin/llc llc /usr/lib/llvm-19/bin/llc 100
}

install_alpine() {
  apk add curl git cmake make clang19
  ln -sf /usr/bin/clang-19 /usr/bin/cc
  ln -sf /usr/bin/clang++-19 /usr/bin/c++
}

install_macos() {
  echo "Installing for Mac..."
  brew install -y curl git cmake llvm@19
}

install_fedora() {
    dnf install -y curl git cmake clang19
}

install_dependencies() {
  echo "Installing dependencies for $OS..."
  case $OS in
    debian|ubuntu)
      install_debian;;
    fedora)
      install_fedora;;
    alpine)
      install_alpine;;
    macos)
      install_macos;;
    *)
      echo "Operating system is empty. Could not install dependencies."
      exit 1;;
  esac
}

install_logos() {
  echo "Installing Logos..."
  cd "$TEMP_DIR"
  git clone --depth 1 -b dev "$LOGOS_GIT_URL"
  cd logos

  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DLOGOS_RELEASE=ON
  cmake --build build -j"$WORKERS"
  cmake --install build

  if [[ "$OS" != "macos" ]]; then
    # Update shared library cache
    ldconfig /usr/local/lib 2>/dev/null || ldconfig
  fi
}

build_cblas() {
    git clone --depth 1 https://github.com/OpenMathLib/OpenBLAS.git
    make -C OpenBLAS CFLAGS="-O3 -Wno-uninitialized" > /dev/null
    cp OpenBLAS/libopenblas.a libcblas.a
    rm -rf OpenBLAS
}

detect_os
#install_dependencies
build_cblas
#install_logos

echo "Installation done."
echo "Files installed:"
echo "- $INSTALL_PREFIX/bin/lgs"
echo "- $INSTALL_PREFIX/lib/$LGS_LIB"
