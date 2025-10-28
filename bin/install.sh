set -e

detect_os() {
  if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
  elif [ -f /etc/os-alpine ]; then
    OS="alpine"
  elif [[ "$OSTYPE" = "darwin"* ]]; then
    OS="macos"
  else
    echo "Operating system could not be detected."
    exit 1
  fi
}

install_debian() {
  apt-get update &&  \
      DEBIAN_FRONTEND=noninteractive apt-get install -y  \
      cmake \
      clang-19 \
      llvm-19-dev \
      libclang-19-dev \
      libclang-cpp19-dev \
      libzstd-dev \
      libedit-dev \
      zlib1g \
      zlib1g-dev \
      libcurlpp-dev
}

install_alpine() {
  apk add git cmake make clang19 llvm19-dev curl curl-dev libxml2-dev
  ln -sf /usr/bin/clang-19 /usr/bin/clang
  ln -sf /usr/bin/clang++-19 /usr/bin/clang++
  ln -sf /usr/bin/clang-19 /usr/bin/cc
  ln -sf /usr/bin/clang++-19 /usr/bin/c++
}

install_macos() {
  echo "Installing for Mac..."
}

build_logos() {
  git clone --depth 1 https://github.com/rmordechay/logos
  cd logos
  make build
}

detect_os
echo "$OS"
echo "Installing dependencies"

case $OS in
  debian)
    install_debian
    ;;
  alpine)
    install_alpine
    ;;
  macos)
    install_macos
    ;;
  *)
    echo "Operating system could not be detected."
    exit 1
    ;;
esac
