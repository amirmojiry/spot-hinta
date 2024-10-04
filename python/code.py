import requests
from datetime import datetime

base_url = "https://api.spot-hinta.fi"

def fetch_hour_data(look_forward_hours):
    endpoint = f"/JustNow?lookForwardHours={look_forward_hours}&isHtmlRequest=true"
    url = base_url + endpoint
    response = requests.get(url)
    if response.status_code != 200:
        print(f"Failed to fetch data for hour {look_forward_hours}: {response.status_code}")
        return None
    return response.json()

next_hours = 2

energy_prices = {}

for i in range(next_hours + 1):
    data = fetch_hour_data(i)
    if data:
        price = data.get('PriceWithTax', 0) * 100  # Convert to snt/kWh
        rank = data.get('Rank', 'N/A')
        datetime_str = data.get('DateTime', '')
        if datetime_str:
            date = datetime.fromisoformat(datetime_str)
            time_str = date.strftime("%H:%M")
        else:
            time_str = "N/A"

        energy_prices[f'Hour {i}'] = {
            'Price': f"{price:.2f}",
            'Time': time_str
        }

for hour, details in energy_prices.items():
    print(f"Price at {details['Time']}: {details['Price']} snt/kWh")
