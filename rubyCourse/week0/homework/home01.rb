CURRENCY_RATE = {usd: 1.7408, eur: 1.9557, gbp: 2.6415, bgn: 1}

def convert_to_bgn(value, currency)
  rate = CURRENCY_RATE[currency]
  (value * rate).round(2)
end

def compare_prices(price_1, currency_1, price_2, currency_2)
  convert_to_bgn(price_1, currency_1) - convert_to_bgn(price_2, currency_2)
end