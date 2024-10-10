from http.server import BaseHTTPRequestHandler, HTTPServer
import subprocess
import urllib.parse as urlparse
import html

HOST_NAME = '0.0.0.0'
PORT_NUMBER = 8080

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        with open('index.html', 'rb') as f:
            content = f.read()
        self.send_response(200)
        self.send_header('Content-Type', 'text/html')
        self.end_headers()
        self.wfile.write(content)

    def do_POST(self):
        content_length = int(self.headers.get('Content-Length', 0))
        post_data = self.rfile.read(content_length).decode()
        parsed_data = urlparse.parse_qs(post_data)
        script = parsed_data.get('script', [None])[0]

        if script == 'code.py':
            output = subprocess.check_output(['python3', 'code.py'], text=True)
        else:
            output = 'No valid script specified.'

        safe_output = html.escape(output)
        response = f'<pre>{safe_output}</pre>'

        self.send_response(200)
        self.send_header('Content-Type', 'text/html')
        self.end_headers()
        self.wfile.write(response.encode())

if __name__ == '__main__':
    server = HTTPServer((HOST_NAME, PORT_NUMBER), MyHandler)
    server.serve_forever()