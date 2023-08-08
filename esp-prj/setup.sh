#!/bin/bash

set -e
set -u

IMG_NAME="esp_dev_img"
CONTAINER_NAME="esp_dev"

USERNAME="esp"
MOUNT_PATH="$(pwd)"

if [[ ! -d "$(pwd)/esp-idf" ]]; then
    git clone --recursive https://github.com/espressif/esp-idf.git
fi

# remove previously created images
if [[ -n $(docker ps -a | grep "$CONTAINER_NAME") ]]; then
    docker rm "$CONTAINER_NAME" || true
    docker rmi "$IMG_NAME" || true
fi

# create the image
docker build -t $IMG_NAME --build-arg USERNAME=$USERNAME .

# create the container
docker create -it --privileged \
    --mount type=bind,source="$MOUNT_PATH",target=/home/$USERNAME \
    --name $CONTAINER_NAME $IMG_NAME

docker start $CONTAINER_NAME

docker exec -u $USERNAME $CONTAINER_NAME \
    bash -c "esp-idf/install.sh esp32"

docker exec -u $USERNAME $CONTAINER_NAME \
    bash -c "echo source \$HOME/esp-idf/export.sh >> /home/$USERNAME/.bashrc"

docker stop $CONTAINER_NAME
