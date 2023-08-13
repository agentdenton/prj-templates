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
    wget \
    libusb-1.0-0-dev \
    usbutils \
    ninja-build \
    libftdi-dev \
    minicom \
    software-properties-common \
    lsb-release \
    autoconf \
    automake \
    bison \
    build-essential \
    ca-certificates \
    cargo \
    ccache \
    chrpath \
    cmake \
    cpio \
    device-tree-compiler \
    dfu-util \
    diffstat \
    dos2unix \
    doxygen \
    file \
    flex \
    g++ \
    gawk \
    gcc \
    gcovr \
    git \
    git-core \
    gnupg \
    gperf \
    gtk-sharp2 \
    help2man \
    iproute2 \
    lcov \
    libcairo2-dev \
    libglib2.0-dev \
    libgtk2.0-0 \
    liblocale-gettext-perl \
    libncurses5-dev \
    libpcap-dev \
    libpopt0 \
    libsdl1.2-dev \
    libsdl2-dev \
    libssl-dev \
    libtool \
    libtool-bin \
    net-tools \
    openssh-client \
    parallel \
    pkg-config \
    python3-dev \
    python3-pip \
    python3-ply \
    python3-venv \
    python3-setuptools \
    python-is-python3 \
    qemu \
    rsync \
    socat \
    srecord \
    texinfo \
    unzip \
    valgrind \
    ovmf \
    xz-utils \
    thrift-compiler

RUN useradd --shell=/bin/bash --create-home $USERNAME
RUN echo "$USERNAME ALL=(ALL) NOPASSWD: ALL" | tee -a /etc/sudoers

RUN usermod -a -G dialout $USERNAME

RUN locale-gen en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8
ENV ZEPHYR_BASE=/home/$USERNAME/zephyrproject/zephyr

# Enable man pages and help messages
RUN yes | unminimize

USER $USERNAME
WORKDIR /home/$USERNAME
