FROM ubuntu:latest
LABEL authors="luke"

ENTRYPOINT ["top", "-b"]