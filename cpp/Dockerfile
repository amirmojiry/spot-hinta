FROM alpine:latest AS builder
RUN apk add --no-cache g++ curl-dev wget
WORKDIR /app
COPY *.cpp ./ 
RUN mkdir -p nlohmann
RUN wget https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp -O json.hpp
RUN g++ code.cpp -o app -lcurl -std=c++11

FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/app .
RUN apk add --no-cache libcurl libstdc++ libgcc
EXPOSE 8080
CMD ["./app"]