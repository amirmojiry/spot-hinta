FROM golang:1.20-alpine AS builder
RUN apk add --no-cache git
WORKDIR /app
COPY go.mod ./
RUN go mod tidy
RUN go mod download
COPY *.go ./
RUN go build -o app code.go
RUN go build -o simple_app simple_code.go
COPY dispatcher.sh ./
RUN chmod +x dispatcher.sh

FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/app .
COPY --from=builder /app/simple_app .
COPY --from=builder /app/dispatcher.sh .
ENV SCRIPT=code
CMD ["sh", "./dispatcher.sh"]