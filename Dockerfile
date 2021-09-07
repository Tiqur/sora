FROM alpine

ARG THREADS
ENV THREADS = ${THREADS}

WORKDIR /app

RUN apk --update add parallel && \
    apk --update add musl

COPY a.out start.sh .

CMD ["./start.sh"]
