weather: all

all: main check_json_string get_weather_data parse_json print_weather_data read_file search_city jsmn.a
	gcc -Wall bin/main.o bin/check_json_string.o bin/read_file.o bin/get_weather_data.o bin/parse_json.o bin/print_weather_data.o bin/search_city.o -lcurl lib/libjsmn.a -o weather

main:
	gcc -Wall -c main.c -o bin/main.o

check_json_string:
	gcc -Wall -c src/check_json_string.c -o bin/check_json_string.o

get_weather_data:
	gcc -Wall -c src/get_weather_data.c -o bin/get_weather_data.o

parse_json:
	gcc -Wall -c src/parse_json.c -o bin/parse_json.o

print_weather_data:
	gcc -Wall -c src/print_weather_data.c -o bin/print_weather_data.o	

read_file:
	gcc -Wall -c src/read_file.c -o bin/read_file.o

search_city:	
	gcc -Wall -c src/search_city.c -o bin/search_city.o

jsmn.a:
	gcc -Wall -c lib/jsmn.c -o lib/libjsmn.a

clean:
	rm bin/*o
