#!/bin/bash

set -eu

if [[ $(whoami) != "zephyr" ]]; then
    echo "Error. Invalid user. Run script from inside the container"
    exit 1
fi

mkdir -p zephyrproject

python3 -m venv ~/zephyrproject/.venv
source ~/zephyrproject/.venv/bin/activate
pip install west
west init ~/zephyrproject

pushd ~/zephyrproject
west update
west zephyr-export
pip install -r ~/zephyrproject/zephyr/scripts/requirements.txt
popd

SDK_NAME="zephyr-sdk-0.16.1_linux-x86_64.tar.xz"
wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.1/$SDK_NAME
wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.1/sha256.sum | shasum --check --ignore-missing
tar xvf zephyr-sdk-0.16.1_linux-x86_64.tar.xz
pushd ${SDK_NAME%%_*} && yes | ./setup.sh && popd

rm -rf $SDK_NAME

echo "source \$HOME/zephyrproject/.venv/bin/activate" >> $HOME/.bashrc
