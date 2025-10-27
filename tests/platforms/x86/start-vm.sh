#!/usr/bin/env bash

if [ ! -f linux-x86.qcow2 ]; then
  echo "Disk image not found. Creating and running installer."
  qemu-img create -f qcow2 linux-x86.qcow2 10G
  qemu-system-x86_64 \
    -machine accel=tcg \
    -cpu max \
    -m 6G \
    -drive file=linux-x86.qcow2,format=qcow2 \
    -cdrom alpine-x86_64.iso \
    -boot d \
    -net nic -net user \
    -nographic
  echo ""
  echo "Installation complete. Run ./start-vm.sh again to boot your system."
  exit 0
fi

echo "Booting existing system..."
qemu-system-x86_64 \
    -machine accel=tcg \
    -cpu max \
    -m 6G \
    -drive file=linux-x86.qcow2,format=qcow2 \
    -net nic -net user \
    -nographic