FROM ubuntu:22.04

ARG USERNAME

# Set non-interactive frontend for apt-get to skip any user confirmations
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get clean && apt-get update

RUN apt-get install -y \
    locales \
    vim \
    sudo \
    make \
    help2man \
    unzip \
    git \
    wget \
    python3 \
    python3-pip \
    python3-venv \
    libusb-1.0-0-dev \
    usbutils \
    cmake \
    ninja-build \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    build-essential \
    automake \
    autoconf \
    texinfo \
    libtool \
    libftdi-dev \
    pkg-config \
    minicom \
    gdb-multiarch

RUN useradd --shell=/bin/bash --create-home $USERNAME
RUN echo "$USERNAME ALL=(ALL) NOPASSWD: ALL" | tee -a /etc/sudoers

RUN usermod -a -G dialout $USERNAME

RUN locale-gen en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8
ENV PICO_SDK_PATH="/home/$USERNAME/pico-sdk"

# Enable man pages and help messages
RUN yes | unminimize

USER $USERNAME
WORKDIR /home/$USERNAME
