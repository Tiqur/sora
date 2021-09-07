FROM alpine

WORKDIR /app

RUN apk --update add parallel && \
    apk --update add musl && \
    apk --update add build-base

COPY . .

RUN g++ -O3 main.cpp
CMD ["./start.sh"]
