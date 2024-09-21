#ifndef Q2_H
#define Q2_H

#include <fstream>
#include <algorithm>

namespace q2 {

struct Patient {
	std::string name;
	size_t age;
	size_t smokes;
	size_t area_q;
	size_t alkhol;
    size_t possibility;    
    bool operator<(const Patient& p) const {
        return possibility > p.possibility;
    }
};

inline std::vector<Patient> read_file(std::string filename) {
    std::vector<Patient> patient;

    std::ifstream csv_data(filename, std::ios::in);
    if (!csv_data.is_open()) {
        throw std::runtime_error("read file failed");
    }
    std::string line;
    getline(csv_data, line);
    getline(csv_data, line);
    std::vector<std::string> words;
    std::string word;
    while (getline(csv_data, line)) {
        std::istringstream sin(line);
        while (getline(sin, word, ',')) {
            words.push_back(word);
        }
        std::string name;
        if (words[0][words[0].length()-1] == ' ') {
            name = words[0] + words[1];
        } else {
            name = words[0] + " " + words[1];
        }
        Patient p{
            name,
            static_cast<size_t>(std::stoi(words[2])),
            static_cast<size_t>(std::stoi(words[3])),
            static_cast<size_t>(std::stoi(words[4])),
            static_cast<size_t>(std::stoi(words[5])),
            3*p.age + 5*p.smokes + 2*p.area_q + 4*p.alkhol
            };
        words.clear();
        patient.push_back(std::move(p));
    }
    return patient;
}

inline void sort(std::vector<Patient>& patient) {
    std::sort(patient.begin(), patient.end());
}


}


#endif //Q2_H