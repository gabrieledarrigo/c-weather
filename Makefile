weather: all

all: main check_json_string get_weather_data parse_json read_file search_city
	gcc -Wall bin/main.o bin/check_json_string.o bin/read_file.o bin/get_weather_data.o bin/parse_json.o bin/search_city.o -lcurl lib/libjsmn.a -o weather

main:
	gcc -Wall -c main.c -o bin/main.o

check_json_string:
	gcc -Wall -c src/check_json_string.c -o bin/check_json_string.o

get_weather_data:
	gcc -Wall -c src/get_weather_data.c -o bin/get_weather_data.o

parse_json:
	gcc -Wall -c src/parse_json.c -o bin/parse_json.o

read_file:
	gcc -Wall -c src/read_file.c -o bin/read_file.o

search_city:	
	gcc -Wall -c src/search_city.c -o bin/search_city.o

clean:
	rm bin/*o