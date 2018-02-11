# Cweather
![Cweather](https://media.giphy.com/media/xThtau7plauZ5RPQR2/giphy.gif)

### Description
CWeather is a C shell application that retrieve weather data from [https://openweathermap.org/](https://openweathermap.org/) public API.

### Dependencies
The application has two main dependencies:

1. [libcurl](https://curl.haxx.se/libcurl/) to make an HTTP call to the API and get the data in raw JSON format.  
2. [Jsmn](https://github.com/zserge/jsmn), a library used to parse the JSON intp a workable data structure.

While Jsmn is included into the project, under lib folder, libcurl is not, so be sure that you run the application on a 

### Build
CWeather is built with _gcc_ with a plain and simple _Makefile_; all generated objects files are placed into the _bin/_ folder and linked with the required dependencies.  
The executable *weather* is generated into the main folder.  

### How it works

When the user provide a city to the executable the CWeather application check its name against an archive of cities.
The archive is based on this list: [http://bulk.openweathermap.org/sample/](http://bulk.openweathermap.org/sample/) and is a JSON array containing over 200.000 locations.
The array is first decoded and then the provided city is searched through the archive.
If it doesn't exists CWeather stops the execution.
Otherwise the name is used to compose the url to query the API; for example in case the desired city to search for the weather conditions is Crema, then a url of this type is constructed:

```
http://api.openweathermap.org/data/2.5/weather?q=Crema
```

and used by curl to _GET_ the data, encoded in JSON format.
With no HTTP error the response is parsed, decoded and the weather data outputted to the terminal.

#### Flow chart

![cweather-flowchart](https://user-images.githubusercontent.com/1985555/35482518-fe469434-0436-11e8-8439-9017163830b0.png)


### Usage
Clone the repository, and then build the project:

```
c-weather$ make
```

Just run the *weather* executable specifying the name of a city:

```
c-weather$ ./weather Crema

--------------------------------------------------------
| Searching for current weather conditions in: Crema
--------------------------------------------------------

Coordinates
        Latitude: 9.69
        Longitude: 45.36
Weather
        Conditions: Fog
        Temperature: 4.95 °C
        Pressure: 1035 hPa
        Humidity: 87%

--------------------------------------------------------
```

If the name of the city which you are searching to obtain the weather conditions is composed by two ore more words, then wrap its name inside quotes:

```
c-weather$ ./weather "Los Angeles"
```
