#!/bin/bash

IMAGE_NAME=slowcat-build

docker build --progress plain --tag ${IMAGE_NAME} -f Dockerfile.musl .

id=$(docker create ${IMAGE_NAME})
mkdir -p dist
docker cp $id:/build/slowcat ./dist/
docker rm -v $id
