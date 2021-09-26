FROM alpine

WORKDIR /app

RUN apk --update add parallel && \
    apk --update add musl && \
    apk --update add build-base && \
    apk --update add curl

COPY . .

RUN g++ -O3 -std=c++11 -g -o sora main.cpp -L/opt/arrayfire/lib64 -laf -I/opt/arrayfire/include
CMD ["./start.sh"]
