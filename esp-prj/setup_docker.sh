#!/bin/bash

set -eu

IMG_NAME="esp_dev_img"
CONTAINER_NAME="esp_dev"

USERNAME="esp"
MOUNT_DIR="$PWD"

trap "echo 'Stopping...' && docker stop $CONTAINER_NAME" EXIT

# remove previously created images
if [[ -n $(docker ps -a | grep "$CONTAINER_NAME") ]]; then
    docker rm "$CONTAINER_NAME" || true
    docker rmi "$IMG_NAME" || true
fi

# create the image
docker build -t $IMG_NAME --build-arg USERNAME=$USERNAME .

# create the container
docker create -it --privileged \
    --mount type=bind,source="$MOUNT_DIR",target=/home/$USERNAME \
    --name $CONTAINER_NAME $IMG_NAME

docker start $CONTAINER_NAME
docker exec -u $USERNAME $CONTAINER_NAME bash -c "./setup_env.sh"
docker stop $CONTAINER_NAME
