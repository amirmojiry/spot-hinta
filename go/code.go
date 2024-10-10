package main

import (
    "encoding/json"
    "fmt"
    "net/http"
)

type EnergyData struct {
    PriceWithTax float64 `json:"PriceWithTax"`
    Rank         string  `json:"Rank"`
    DateTime     string  `json:"DateTime"`
}

func main() {
    baseURL := "https://api.spot-hinta.fi"
    nextHours := 2

    for i := 0; i <= nextHours; i++ {
        url := fmt.Sprintf("%s/JustNow?lookForwardHours=%d&isHtmlRequest=true", baseURL, i)
        resp, _ := http.Get(url)
        defer resp.Body.Close()

        var data EnergyData
        json.NewDecoder(resp.Body).Decode(&data)
        fmt.Println(data)
    }
}
