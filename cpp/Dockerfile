# Dockerfile
FROM alpine:latest AS builder
RUN apk add --no-cache g++ curl-dev wget
WORKDIR /app
COPY *.cpp ./
RUN mkdir -p nlohmann
RUN wget https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp -O json.hpp
RUN g++ code.cpp -o app -lcurl -std=c++11
RUN g++ simple_code.cpp -o simple_app -lcurl -std=c++11
COPY dispatcher.sh ./
RUN chmod +x dispatcher.sh

FROM alpine:latest
WORKDIR /app
COPY --from=builder /app/app .
COPY --from=builder /app/simple_app .
COPY --from=builder /app/dispatcher.sh .
RUN apk add --no-cache libcurl libstdc++ libgcc
EXPOSE 8080
ENV SCRIPT=code
CMD ["./dispatcher.sh"]
