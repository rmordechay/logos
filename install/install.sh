#!/usr/bin/env bash

set -e

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
  apt-get update > /dev/null 2>&1
  DEBIAN_FRONTEND=noninteractive \
    apt-get update && \
    apt-get install -y git cmake clang-19 libclang-19-dev libclang-cpp19-dev
  update-alternatives --install /usr/bin/clang clang /usr/lib/llvm-19/bin/clang 100 > /dev/null 2>&1
  update-alternatives --install /usr/bin/clang++ clang++ /usr/lib/llvm-19/bin/clang++ 100 > /dev/null 2>&1
  update-alternatives --install /usr/bin/llc llc /usr/lib/llvm-19/bin/llc 100 > /dev/null 2>&1
}

install_alpine() {
  apk add git cmake make clang19
  ln -sf /usr/bin/clang-19 /usr/bin/cc
  ln -sf /usr/bin/clang++-19 /usr/bin/c++
}

install_macos() {
  echo "Installing for Mac..."
  apt-get install -y git cmake llvm@19
}

install_fedora() {
    dnf install -y git cmake clang19
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
  git clone --depth 1 -b dev https://github.com/rmordechay/logos
  cd logos

  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DLOGOS_RELEASE=ON
  cmake --build build -j"$WORKERS"
  cmake --install build

  if [[ "$OS" != "macos" ]]; then
    # Update shared library cache
    ldconfig /usr/local/lib 2>/dev/null || ldconfig
  fi
}

detect_os
install_dependencies
install_logos

echo "Installation done."
echo "Files installed:"
echo "- $INSTALL_PREFIX/bin/lgs"
echo "- $INSTALL_PREFIX/lib/$LGS_LIB"
