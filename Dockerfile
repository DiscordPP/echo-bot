FROM lballabio/boost:1.73.0-focal
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt upgrade -y && apt install -y git cmake build-essential libssl-dev libcrypto++-dev libcurl4-openssl-dev
WORKDIR /echo-bot
COPY . .
RUN git submodule update --init --recursive
RUN mkdir build && cd build && cmake .. && make
CMD ["./build/echo_bot"]
