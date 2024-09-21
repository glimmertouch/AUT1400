#ifndef Q3_H
#define Q3_H

#include <queue>

namespace q3 {
struct Flight
{
	std::string flight_number;
	size_t duration;
	size_t connections;
	size_t connection_times;
	size_t price;
	bool operator<(const Flight& f) const {
		size_t this_value = duration + connection_times + 3*price;
		size_t f_value = f.duration + f.connection_times + 3*f.price;
		return this_value > f_value;
	}
	void print() {
		std::cout << flight_number << " " << duration << " " << connections << " " << connection_times << " " << price << std::endl;
	}
};

inline size_t parse_time(const std::string& time) {
	size_t h_pos = time.find('h');
	size_t hour = std::stoi(time.substr(0, h_pos));
	size_t m_pos = time.find('m');
	size_t minute = (m_pos == std::string::npos) ? 0 : std::stoi(time.substr(h_pos+1, m_pos-h_pos-1));
	return hour*60 + minute;
}


inline std::priority_queue<Flight> gather_flights(const std::string& filename) {
    std::priority_queue<Flight> flights;

	std::ifstream  txt_data(filename, std::ios::in);
	if (!txt_data.is_open()) {
		throw std::runtime_error("read file failed");
	}
	std::string line;
	while(getline(txt_data, line)) {
		std::stringstream sin(line);
		Flight f;
		std::string temp;
		getline(sin, temp, ':');
		getline(sin, f.flight_number, ' ');

		getline(sin, temp, ':');
		getline(sin, temp, ' ');
		f.duration = parse_time(temp);

		getline(sin, temp, ':');
		sin >> f.connections;

		f.connection_times = 0;
		getline(sin, temp, ':');
		while(getline(sin, temp, ',')) {
			// std::cout << temp << std::endl;
			f.connection_times += parse_time(temp);
		}

		std::stringstream sin2(temp);
		getline(sin2, temp, ':');
		// std::cout << temp <<std::endl;
		f.price = 0;
		sin2 >> f.price;
		// f.print();
		flights.push(std::move(f));		
	}
	return flights;
}
}

#endif //Q3_H