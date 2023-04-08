#!/bin/bash

if [ -z "$1" ]; then
    echo "provide the username as a the first and only argument"
    exit 1
else
    USERNAME=$1
fi

DOCKER_BUILDKIT=1 docker build --network host \
    --build-arg USER=$USERNAME \
    --build-arg UID=$(id -u) \
    --build-arg GID=$(id -g) \
    --tag devel-dothis:bullseye .
