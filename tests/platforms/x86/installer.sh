#!/usr/bin/env bash

setup-alpine -q
apk add git cmake make
apk add clang19 llvm19-dev curl curl-dev libxml2-dev
ln -sf /usr/bin/clang-19 /usr/bin/clang
ln -sf /usr/bin/clang++-19 /usr/bin/clang++
ln -sf /usr/bin/clang-19 /usr/bin/cc
ln -sf /usr/bin/clang++-19 /usr/bin/c++
git clone -b dev https://github.com/rmordechay/logos