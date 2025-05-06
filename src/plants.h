#pragma once

struct plant_type_t {
    float build_cost;       // per kW capacity
    float operating_cost;   // per kWh generated
    float default_capacity; // per kWh generated
};


// plants definition

static const char* plant_type_names[] = { "Hydroelectric Plant", "Thermal Coal Plant", "Thermal Gas Plant", "Nuclear Plant", "Photovoltaic Station", "Wind Park" };

const plant_type_t plant_types[] = {
    { 3083, 0.00645,  100000 },  // hydropower
    { 6625, 0.01860,  650000 },  // thermal coal USC 90%CCS
    { 1062, 0.00341, 1083000 },  // thermal gas combined cycle multishaft
    { 7030, 0.01700, 2156000 },  // nuclear
    { 1327, 0.00384,  150000 },  // solar photovoltaic with storage
    { 1718, 0.00314,  200000 }   // wind park
};

