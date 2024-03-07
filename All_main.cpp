#include <iostream>
#include <string>
#include <vector>

class lepton
{
  private:
    // "electron" or "muon"
    std::string particle_type;
    // in MeV
    double rest_mass;
    // true for particle, false for antiparticle
    bool check_particle;
    // in m/s, between 0 and the speed of light
    double velocity;
    // velocity / speed of light
    double beta;
    // speed of light
    static constexpr double light_speed = 2.99792458e8;

  public:
    // Default constructor
    lepton():
      particle_type("Cat"), rest_mass(0), check_particle(true), velocity(0), beta(0)
    {}

    // Parameterized constructor
    lepton(const std::string& type, double mass, bool particle, double v):
      particle_type(type), rest_mass(mass), check_particle(particle), velocity(v), beta(v / light_speed)
      {
        if (beta > 1)
        {
          velocity = light_speed;
          beta = 1;
        }
      }

    // Destructor
    ~lepton()
    {
      std::cout<<"Destroying lepton: "<<particle_type<<std::endl;
    }

    // Setters
    void set_particle_type(const std::string& type)
    {
      particle_type = type;
    }
    void set_rest_mass(double mass)
    {
      rest_mass = mass;
    }
    void set_check_particle(bool particle)
    {
      check_particle = particle;
    }
    void set_Velocity(double v)
    {
      velocity = (v <= light_speed) ? v : light_speed;
      beta = velocity / light_speed;
    }

    // Getters
    std::string get_particle_type() const
    {
      return particle_type;
    }
    double get_rest_mass() const
    {
      return rest_mass;
    }
    bool get_check_particle() const
    {
      return check_particle;
    }
    int get_charge() const 
    {
      return check_particle ? 1 : -1;
    }
    double get_velocity() const 
    {
      return velocity;
    }
    double get_beta() const
    {
      return beta;
    }

    void print_particle_data()
      const;
};

// print_particle_data outside the class
void lepton::print_particle_data() const
{
  std::cout<<"-------------"<<std::endl;
  std::cout<<"Particle type: "<<particle_type<<" | "<<"Rest mass (MeV): "<<rest_mass<<" | "<<"Charge: "<<(check_particle ? "Particle" : "Antiparticle")<<" | "<<"Velocity (m/s): "<<velocity<<" | "<<"Beta (v/c): "<<beta<<std::endl;
  std::cout<<"-------------"<<std::endl;
}

class detector
{
  private:
    // "tracker", "calorimeter", or "muon chamber"
    std::string detector_type;
    // true for on, false for off
    bool status;
    // Number of particles detected
    int detector_particles_number;

  public:
    // Default constructor
    detector():
      detector_type("tracker"), status(false), detector_particles_number(0)
    {}

    // Parameterized constructor
    detector(const std::string& type):
      detector_type(type), status(false), detector_particles_number(0)
    {}

    // Destructor
    ~detector()
    {
      std::cout<<"Destroying "<<detector_type<<std::endl;
    }

    // Setters
    void set_detector_type(const std::string& type)
    {
      detector_type = type;
    }
    void set_status(bool on)
    {
      status = on;
    }

    // Getters
    std::string get_detector_type() const
    {
      return detector_type;
    }

    bool get_status() const
    {
      return status;
    }

    // Turn the detector on
    void turn_on()
    {
      status = true;
      std::cout<<"Turning on "<<detector_type<<std::endl;
    }

    // Turn the detector off
    void turn_off() 
    {
      status = false;
      std::cout<<"Shutting down "<<detector_type<<std::endl;
    }

    // Detect function
    int detect(const lepton& particle)
    {
      if (!status)
      {
        std::cout<<"Trying to detect with "<<detector_type<<" turned off.\n"<<std::endl;
        return 0;
      }
      else
      {
      bool detected = false;
      if (detector_type == "tracker")
      {
        // Tracker detects all types
        detected = true;
      }
      else if (detector_type == "calorimeter" && particle.get_particle_type() == "electron")
      {
        // Calorimeter detects only electrons
        detected = true;
      }
      else if (detector_type == "muon chamber" && particle.get_particle_type() == "muon")
      {
        // Muon chamber detects only muons
        detected = true;
      }
      if (detected)
      {
        std::cout<<particle.get_particle_type()<<(particle.get_check_particle() ? "" : " antiparticle")<<" was detected."<<std::endl;
        detector_particles_number++;
        return 1;
      }
      // Particle type not detected by this detector
      return 0;
      }
    }

    void print_status()
      const;
};

// Print function outside the class
void detector::print_status() const
  {
    std::cout<<"Detector Type: "<<detector_type<<" - Status: "<<(status ? "On" : "Off")<<std::endl;
  }

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
