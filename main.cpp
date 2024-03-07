#include <iostream>
#include <vector>
#include "lepton.h"
#include "detector.h"

int main()
{
  
  // Vector containing the specified particles
  // std::vector<lepton> particles =
  // {
  //   // 2 electrons, 4 muons, 1 anti-electron and 1 anti-muon
  //   lepton("electron", 0.511, true, 1e7), lepton("electron", 0.511, true, 1e7), lepton("muon", 105.7, true, 1.5e8), lepton("muon", 105.7, true, 1.5e8), lepton("muon", 105.7, true, 1.5e8), lepton("muon", 105.7, true, 1.5e8), lepton("electron", 0.511, false, 1e7), lepton("muon", 105.7, false, 1.5e8)
  // };
  
  std::vector<lepton> particles;
  particles.reserve(8); // Reserve space for efficiency

  // Emplace back objects directly into the vector
  particles.emplace_back("electron", 0.511, true, 1e7);
  particles.emplace_back("electron", 0.511, true, 1e7);
  particles.emplace_back("muon", 105.7, true, 1.5e8);
  particles.emplace_back("muon", 105.7, true, 1.5e8);
  particles.emplace_back("muon", 105.7, true, 1.5e8);
  particles.emplace_back("muon", 105.7, true, 1.5e8);
  particles.emplace_back("electron", 0.511, false, 1e7);
  particles.emplace_back("muon", 105.7, false, 1.5e8);

  // Print information about all particles in the vector
  for (const auto& particle : particles)
  {
    particle.print_particle_data();
  }

  // Instantiate the three types of detectors
  detector tracker("tracker"), calorimeter("calorimeter"), muonChamber("muon chamber");

  // Array of pointers to detectors for easier iteration
  std::vector<detector*> detectors = {&tracker, &calorimeter, &muonChamber};

  // Operate the detectors using iterators
  for (auto detector_iterator = detectors.begin(); detector_iterator != detectors.end(); ++detector_iterator)
  {
    detector* detector_using = *detector_iterator;
    detector_using->turn_on();

    for (auto particle_iterator = particles.begin(); particle_iterator != particles.end(); ++particle_iterator)
    {
      const lepton& particle = *particle_iterator;
      detector_using->detect(particle);
    }

    detector_using->turn_off();
    // Attempt to detect the first particle with the detector off
    detector_using->detect(particles.front());
  }
  return 0;
}

// g== -std=c++17 -o testing main.cpp lepton.cpp detector.cpp
// .\testing