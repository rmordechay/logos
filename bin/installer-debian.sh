apt-get update &&  \
    DEBIAN_FRONTEND=noninteractive apt-get install -y  \
    git \
    cmake \
    clang-19 \
    llvm-19-dev \
    libclang-19-dev \
    libclang-cpp19-dev \
    curl \
    libzstd-dev \
    libedit-dev \
    zlib1g \
    zlib1g-dev \
    libcurlpp-dev

update-alternatives --install /usr/bin/clang clang /usr/lib/llvm-19/bin/clang 100
update-alternatives --install /usr/bin/clang++ clang++ /usr/lib/llvm-19/bin/clang++ 100

if [ ! -d "/tmp/logos" ]; then
  git clone -b dev https://github.com/rmordechay/logos /tmp/logos
fi

cd /tmp/logos
mkdir -p build
cd build
cmake ..
cmake --build . -j$(nproc)