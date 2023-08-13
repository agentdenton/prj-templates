#!/bin/bash

set -eu

IMG_NAME="zephyr_dev_img"
CONTAINER_NAME="zephyr_dev"

USERNAME="zephyr"
MOUNT_DIR="$PWD"

trap "echo 'Stopping...' && docker stop $CONTAINER_NAME" EXIT

# remove previously created images
if [[ -n $(docker ps -a | grep "$CONTAINER_NAME") ]]; then
    docker rm "$CONTAINER_NAME" || true
    docker rmi "$IMG_NAME" || true
fi

# create the image
docker build -t $IMG_NAME --build-arg USERNAME=$USERNAME .

docker create -it --privileged \
    --mount type=bind,source="$MOUNT_DIR",target=/home/$USERNAME \
    --name $CONTAINER_NAME $IMG_NAME

docker start $CONTAINER_NAME
docker exec -u $USERNAME $CONTAINER_NAME bash -c "./setup_env.sh"
docker stop $CONTAINER_NAME

rules="60-openocd.rules"
if [[ ! -e "/etc/udev/rules.d/$rules" ]]; then
    sudo cp $MOUNT_DIR/zephyr-sdk-0.16.1/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/$rules \
        /etc/udev/rules.d
    sudo udevadm control --reload
fi
