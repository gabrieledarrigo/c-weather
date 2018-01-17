const fs = require('fs');

/**
 * Transform the json object with
 * all the cities in a more simple and parsalble array structure.
 * 
 * @param {object} err 
 * @param {object} data 
 */
const toJSONArray =  (err, data) => {
    if (err) {
        console.log(err);
    }

    const parsed = JSON.parse(data);
    const cities = [];

    parsed.data.forEach(element => {
        cities.push(element.name);
    });

    console.log(JSON.stringify(cities));
};


fs.readFile(__dirname + '/city.list.json', toJSONArray);