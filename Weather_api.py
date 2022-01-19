import pyowm

owm = pyowm.OWM('17eb5600d304a223ed026524e50a5a84')

city = 'Nicosia'

loc = owm.weather_manager().weather_at_place(city)

weather = loc.weather

temp = weather.temperature(unit='celsius')
humidity = weather.humidity
status = weather.detailed_status

cleaned_temp_data = int(temp['temp'])

print('The temperature today in', city, 'is', cleaned_temp_data, 'degrees celsius.')
print('The humidity today in', city, 'is', humidity, '%rh')
print('The day today will have', status, '.')

if 'rain' in status or 'thunderstorm' in status or 'drizzle' in status or 'snow' in status:
    print('Due to the weather today, there is no need of turning on the water pump.')
