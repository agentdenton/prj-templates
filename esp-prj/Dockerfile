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
    subversion \
    cmake \
    flex \
    bison \
    gperf \
    python3 \
    python3-pip \
    python3-venv \
    ninja-build \
    ccache \
    libffi-dev \
    libssl-dev \
    dfu-util \
    libusb-1.0-0 \
    usbutils

RUN useradd --shell=/bin/bash --create-home $USERNAME
RUN echo "$USERNAME ALL=(ALL) NOPASSWD: ALL" | tee -a /etc/sudoers

RUN locale-gen en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

# Enable man pages and help messages
RUN yes | unminimize

USER $USERNAME
WORKDIR /home/$USERNAME
