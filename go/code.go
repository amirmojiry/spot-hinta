package main

import (
    "encoding/json"
    "fmt"
    "net/http"
    "strconv"
    "time"
)

type EnergyData struct {
    PriceWithTax float64 `json:"PriceWithTax"`
    Rank         string  `json:"Rank"`
    DateTime     string  `json:"DateTime"`
}

func fetchHourData(lookForwardHours int) EnergyData {
    baseURL := "https://api.spot-hinta.fi"
    endpoint := fmt.Sprintf("/JustNow?lookForwardHours=%d&isHtmlRequest=true", lookForwardHours)
    url := baseURL + endpoint
    resp, _ := http.Get(url)
    defer resp.Body.Close()

    var data EnergyData
    json.NewDecoder(resp.Body).Decode(&data)
    return data
}

func main() {
    nextHours := 2
    energyPrices := make(map[string]map[string]string)

    for i := 0; i <= nextHours; i++ {
        data := fetchHourData(i)
        price := data.PriceWithTax * 100
        datetime, _ := time.Parse(time.RFC3339, data.DateTime)
        timeStr := datetime.Format("15:04")
        energyPrices[fmt.Sprintf("Hour %d", i)] = map[string]string{
            "Price": strconv.FormatFloat(price, 'f', 2, 64),
            "Time":  timeStr,
        }
    }

    for _, details := range energyPrices {
        fmt.Printf("Price at %s: %s snt/kWh\n", details["Time"], details["Price"])
    }
}
