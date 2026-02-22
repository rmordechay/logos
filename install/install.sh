#!/usr/bin/env bash

set -e

LOGOS_GIT_URL=https://github.com/rmordechay/logos
INSTALL_PREFIX="${INSTALL_PREFIX:-/usr/local}"
TEMP_DIR=$(mktemp -d)

cleanup() {
  echo "Cleaning up"
  rm -rf "$TEMP_DIR"
}

trap cleanup EXIT

setup_installation() {
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
  DEBIAN_FRONTEND=noninteractive apt-get install -y curl git cmake clang-21 libclang-21-dev libclang-cpp21-dev
  update-alternatives --install /usr/bin/clang clang /usr/lib/llvm-21/bin/clang 100
  update-alternatives --install /usr/bin/clang++ clang++ /usr/lib/llvm-21/bin/clang++ 100
  update-alternatives --install /usr/bin/llc llc /usr/lib/llvm-21/bin/llc 100
}

install_alpine() {
  apk add curl git cmake make clang21
  ln -sf /usr/bin/clang-21 /usr/bin/cc
  ln -sf /usr/bin/clang++-21 /usr/bin/c++
}

install_macos() {
  echo "Installing for Mac..."
  brew install -y curl git cmake llvm@21
}

install_fedora() {
    dnf install -y curl git cmake clang21
}

install_cblas() {
    git clone --depth 1 https://github.com/OpenMathLib/OpenBLAS.git
    make -C OpenBLAS CFLAGS="-O3 -Wno-uninitialized" > /dev/null
    cp OpenBLAS/libopenblas.a libcblas.a
    rm -rf OpenBLAS
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
  echo "Installing cblas..."
  install_cblas
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

setup_installation
install_dependencies
install_logos

echo "Installation done."
echo "Files installed:"
echo "- $INSTALL_PREFIX/bin/lgs"
echo "- $INSTALL_PREFIX/lib/$LGS_LIB"
