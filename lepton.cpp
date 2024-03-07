#include <iostream>
#include "lepton.h"


lepton::lepton(): particle_type("Cat"), rest_mass(0), check_particle(true), velocity(0), beta(0)
{}

lepton::lepton(const std::string& type, double mass, bool particle, double v):
  particle_type(type), rest_mass(mass), check_particle(particle), velocity(v), beta(v / light_speed)
  {
    if (beta > 1) {
      velocity = light_speed;
      beta = 1;
    }
  }

lepton::~lepton()
{
  std::cout<<"Destroying lepton: "<<particle_type<<std::endl;
}

void lepton::set_particle_type(const std::string& type) { particle_type = type; }
void lepton::set_rest_mass(double mass) { rest_mass = mass; }
void lepton::set_check_particle(bool particle) { check_particle = particle; }
void lepton::set_Velocity(double v) {
    velocity = (v <= light_speed) ? v : light_speed;
    beta = velocity / light_speed;
}

std::string lepton::get_particle_type() const { return particle_type; }
double lepton::get_rest_mass() const { return rest_mass; }
bool lepton::get_check_particle() const { return check_particle; }
int lepton::get_charge() const { return check_particle ? 1 : -1; }
double lepton::get_velocity() const { return velocity; }
double lepton::get_beta() const { return beta; }

void lepton::print_particle_data() const
{
  std::cout<<"-------------"<<std::endl;
  std::cout<<"Particle type: "<<particle_type<<" | "<<"Rest mass (MeV): "<<rest_mass<<" | "<<"Charge: "<<(check_particle ? "Particle" : "Antiparticle")<<" | "<<"Velocity (m/s): "<<velocity<<" | "<<"Beta (v/c): "<<beta<<std::endl;
  std::cout<<"-------------"<<std::endl;
}
