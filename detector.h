#ifndef DETECTOR_H
#define DETECTOR_H

#include <string>
#include "lepton.h"

class detector {
private:
    std::string detector_type;
    bool status;
    int detector_particles_number;

public:
    detector();
    detector(const std::string& type);
    ~detector();
    void set_detector_type(const std::string& type);
    void set_status(bool on);
    std::string get_detector_type() const;
    bool get_status() const;
    void turn_on();
    void turn_off();
    int detect(const lepton& particle);
    void print_status() const;
};

#endif // DETECTOR_H
