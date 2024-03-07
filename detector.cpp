#include <iostream>
#include "detector.h"

detector::detector():
  detector_type("tracker"), status(false), detector_particles_number(0)
{}

detector::detector(const std::string& type):
  detector_type(type), status(false), detector_particles_number(0)
{}

detector::~detector()
{
  std::cout<<"Destroying "<<detector_type<<std::endl;
}

void detector::set_detector_type(const std::string& type)
{
  detector_type = type;
}
void detector::set_status(bool on) { status = on; }
std::string detector::get_detector_type() const { return detector_type; }
bool detector::get_status() const { return status; }
void detector::turn_on() {
    status = true;
    std::cout<<"Turning on "<<detector_type<<std::endl;
}

void detector::turn_off()
{
  status = false;
  std::cout<<"Shutting down "<<detector_type<<std::endl;
}

int detector::detect(const lepton& particle)
{
  if (!status)
  {
    std::cout<<"Trying to detect with "<<detector_type<<" turned off.\n";
    return 0;
  }
  else
  {
    bool detected = false;
    if (detector_type == "tracker")
    {
    detected = true; // Tracker detects all types
    }
    else if (detector_type == "calorimeter" && particle.get_particle_type() == "electron")
    {
    detected = true; // Calorimeter detects only electrons
    }
    else if (detector_type == "muon chamber" && particle.get_particle_type() == "muon")
    {
    detected = true; // Muon chamber detects only muons
    }
    if (detected)
    {
    std::cout << particle.get_particle_type() << (particle.get_check_particle() ? "" : " antiparticle") << " was detected." << std::endl;
    detector_particles_number++;
    return 1;
    }
    return 0; // Particle type not detected by this detector
  }
}

void detector::print_status() const
{
  std::cout << "Detector Type: " << detector_type << " - Status: " << (status ? "On" : "Off") << std::endl;
}
