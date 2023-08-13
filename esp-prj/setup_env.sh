#!/bin/bash

if [[ $(whoami) != "esp" ]]; then
    echo "Error. Invalid user. Run script from inside the container"
    exit 1
fi

if [[ ! -d "$(pwd)/esp-idf" ]]; then
    git clone --recursive https://github.com/espressif/esp-idf.git
fi

$HOME/esp-idf/install.sh esp32
echo "source \$HOME/esp-idf/export.sh" >> $HOME/.bashrc
