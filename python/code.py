import requests

base_url = "https://api.spot-hinta.fi"
next_hours = 2

for i in range(next_hours + 1):
    url = f"{base_url}/JustNow?lookForwardHours={i}&isHtmlRequest=true"
    response = requests.get(url)
    data = response.json()
    print(data)
