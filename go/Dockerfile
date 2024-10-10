FROM golang:1.20-alpine AS builder
RUN apk add --no-cache git
WORKDIR /app
COPY go.mod ./
RUN go mod tidy
RUN go mod download
COPY *.go ./
RUN go build -o app code.go

FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/app .
RUN apk add --no-cache libstdc++ libgcc
EXPOSE 8080
CMD ["./app"]
