# Multi-Language Energy Prices Fetcher

This project consists of three services written in Python, Go, and C++.

Each service fetches energy prices from the [Spot Hinta API](https://api.spot-hinta.fi).



## Running Locally

### Python

```bash
pip install --upgrade pip
pip install -r requirements.txt
python server.py
```

Open your browser and navigate to `http://localhost:8080`. Use the buttons to run `code.py` or `simple_code.py`.

### Go

```bash
go mod init .
go build -o app code.go
go build -o simple_app simple_code.go
./app
./simple_app
```

### C++

Ensure `json.hpp` is Present. If not, download it:

```bash
wget https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp -O json.hpp
```

```bash
g++ code.cpp -o app -lcurl -std=c++11 -I.
g++ simple_code.cpp -o simple_app -lcurl -std=c++11 -I.
./app
./simple_app
```

## Using Docker

### Building Docker Images

```bash
docker build -t myapp-python ./python
```

### Running Docker Containers

```bash
docker run --rm -d -p 8080:8080 --name myapp-python myapp-python
```

  ```bash
  docker run --rm -e SCRIPT=code -p 8080:8080 --name myapp-go myapp-go
  ```

  ```bash
  docker run --rm -e SCRIPT=simple_code -p 8080:8080 --name myapp-go-simple myapp-go
  ```