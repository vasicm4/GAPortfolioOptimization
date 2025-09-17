import yfinance as yf
import pandas as pd
import datetime

tech_tickers = [
    "AAPL",  # Apple
    "MSFT",  # Microsoft
    "GOOGL", # Alphabet (Class A)
    "AMZN",  # Amazon
    "TSLA",  # Tesla
    "META",  # Meta Platforms
    "NVDA",  # NVIDIA
    "AMD",   # Advanced Micro Devices
    "INTC",  # Intel
    "IBM",   # IBM
    "ORCL",  # Oracle
    "CSCO",  # Cisco
    "ADBE",  # Adobe
    "SAP",   # SAP SE
    "CRM",   # Salesforce
    "QCOM",  # Qualcomm
    "SHOP",  # Shopify
    "NFLX",  # Netflix
    "PYPL",  # PayPal
    "UBER"   # Uber Technologies
]

dfs = []

for ticker in tech_tickers:
    data = yf.Ticker(ticker).history(start = datetime.datetime(2025, 1, 1), end = datetime.datetime(2025, 9, 1))
    df = pd.DataFrame(data.reset_index())
    df.rename(columns={"Close":ticker}, inplace=True)
    dfs.append(df.loc[:, ["Date", ticker]])

merged = dfs[0]

for i in range(1, len(dfs)):
    merged = pd.merge(merged, dfs[i], on='Date', how='inner')

merged.to_csv("data.csv", index = False)