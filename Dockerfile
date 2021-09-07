FROM alpine

WORKDIR /app

COPY a.out .

CMD ["./a.out"]


