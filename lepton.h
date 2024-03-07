#ifndef LEPTON_H
#define LEPTON_H
#include <string>

class lepton {
private:
    std::string particle_type;
    double rest_mass;
    bool check_particle;
    double velocity;
    double beta;
    static constexpr double light_speed = 2.99792458e8;

public:
    lepton();
    lepton(const std::string& type, double mass, bool particle, double v);
    ~lepton();
    void set_particle_type(const std::string& type);
    void set_rest_mass(double mass);
    void set_check_particle(bool particle);
    void set_Velocity(double v);
    std::string get_particle_type() const;
    double get_rest_mass() const;
    bool get_check_particle() const;
    int get_charge() const;
    double get_velocity() const;
    double get_beta() const;
    void print_particle_data() const;
};

#endif // LEPTON_H
