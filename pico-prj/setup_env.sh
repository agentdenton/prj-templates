#!/bin/bash

if [[ $(whoami) != "pico" ]]; then
    echo "Error. Invalid user. Run script from inside the container"
    exit 1
fi

if [[ ! -d "$HOME/pico-sdk" ]]; then
    git clone --recursive https://github.com/raspberrypi/pico-sdk.git \
        --branch master
fi

if [[ ! -d "$HOME/pico-examples" ]]; then
    git clone https://github.com/raspberrypi/pico-examples.git --branch master
fi

if [[ ! -d "$HOME/micropython" ]]; then
    git clone https://github.com/micropython/micropython.git --branch master
fi

if [[ ! -d "$HOME/openocd" ]]; then
    git clone https://github.com/raspberrypi/openocd.git --branch rp2040
fi

if [[ ! -d "$HOME/picoprobe" ]]; then
    git clone --recursive https://github.com/raspberrypi/picoprobe.git
fi

if [[ ! -d "$HOME/picotool" ]]; then
    git clone https://github.com/raspberrypi/picotool.git --branch master
fi

pushd openocd
    ./bootstrap
    ./configure --enable-ftdi
    make -j$(nproc)
    sudo make install
popd

pushd picoprobe
    mkdir -p build
    cd build
    cmake ..
    make -j$(nproc)
popd
