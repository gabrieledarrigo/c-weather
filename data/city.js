var fs = require('fs');

fs.readFile(__dirname + '/city.list.json', (err, data) => {
    if (err) {
        console.log(err);
    }

    const parsed = JSON.parse(data);
    const cities = [];

    parsed.data.forEach(element => {
        cities.push(element.name);
    });

    console.log(JSON.stringify(cities));
});