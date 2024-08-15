// ~seligman/root-class/ExampleEvent.cxx
// 21-May-2009 <seligman@nevis.columbia.edu>

// This class was created as part of Bill Seligman's two-day ROOT
// tutorial in 2009.  It mimics the kind of information that one might
// find in a typical physics-event class.  In a real experiment, the
// data structures would be much more complex.

#include "ExampleEvent.h"

#include <TF1.h>
#include <TRandom3.h>
#include <TObject.h>
#include <Rtypes.h>

#include <cmath>

// Required for ROOT I/O; the complement of ClassDef in the header
// file.
ClassImp(ExampleParticle)
ClassImp(ExampleEvent)


// Class constructor
ExampleEvent::ExampleEvent( Int_t run, Int_t event )
  : m_run(run)
  , m_event(event)
{}

// Class destructor
ExampleEvent::~ExampleEvent()
{}


// The Build method erases any existing content of this class and
// creates "dummy" data for the purpose of the tutorial.  In a real
// experiment, such a method would not exist.

// By the way, this is a darned poor particle simulation.  Don't use
// this for physics, please!

void ExampleEvent::Build()
{
  // Clear out any old particle information.
  m_leptons.clear();
  m_photons.clear();
  m_hadrons.clear();

  // Increment the event number (for a hypothetical "new event."
  ++m_event;

  // How many leptons, photons, and hadrons are there?
  static TRandom3 random;
  Int_t numberLeptons = random.Poisson(1);
  Int_t numberPhotons = random.Poisson(1);
  Int_t numberHadrons = random.Poisson(5);
  // Makes sure there's at least one particle in the event.
  if ( (numberLeptons + numberPhotons + numberHadrons) == 1 )
    numberLeptons = 1;

  // Pick some overall dummy energy for this event.
  static TF1 energyDistribution("energyDistribution","gaus(0)+gaus(3)",0.,500.);
  energyDistribution.SetParameters(200.0, 75.0, 50, 100.0, 225.0, 100.0 );
  Double_t energy = energyDistribution.GetRandom();
  if ( energy <= 0. ) energy = 0.1;

  Double_t leptonic = 0.;
  if ( numberLeptons > 0 )
    {
      // Some fraction of this energy is leptonic.
      leptonic = energy * random.Rndm();

      // Distribute the energy/momentum among all the particles.
      Double_t remaining = leptonic;
      for ( Int_t i = 0; i != numberLeptons; ++i )
	{
	  Double_t particleEnergy;
	  if ( (i+1) == numberLeptons )
	    particleEnergy = remaining;
	  else
	    {
	      particleEnergy = remaining * random.Rndm();
	      remaining -= particleEnergy;
	    }

	  // Come up with a momentum direction.
	  Double_t phi = 2.*M_PI*random.Rndm();
	  Double_t theta = random.Gaus(0.,.004);

	  // Build the particle definition.
	  ExampleParticle particle;
	  particle.px = particleEnergy * cos(phi) * sin(theta);
	  particle.py = particleEnergy * sin(phi) * sin(theta);
	  particle.pz = particleEnergy * cos(theta);

	  // Randomly select the PDG type from a list.
	  static const Int_t pdgList[] = {
	    11,  // e-
	    -11, // e+
	    13,  // mu-
	    -13, // mu+
	  };
	  static const UInt_t listSize = sizeof(pdgList) / sizeof (Int_t);
	  UInt_t listIndex = random.Integer( listSize );
	  particle.pdg = pdgList[ listIndex ];

	  // Save the particle in the particle list.
	  m_leptons.push_back( particle );
	}
    }

  Double_t photonic = 0.;
  if ( numberPhotons > 0 ) 
    {
      // Another fraction is photonic.
      photonic = ( energy - leptonic ) * random.Rndm();

      // Distribute the energy/momentum among all the particles.
      Double_t remaining = photonic;
      for ( Int_t i = 0; i != numberPhotons; ++i )
	{
	  Double_t particleEnergy;
	  if ( (i+1) == numberPhotons )
	    particleEnergy = remaining;
	  else
	    {
	      particleEnergy = remaining * random.Rndm();
	      remaining -= particleEnergy;
	    }

	  // Come up with a momentum direction.
	  Double_t phi = 2.*M_PI*random.Rndm();
	  Double_t theta = random.Gaus(0.,.004);

	  // Build the particle definition.
	  ExampleParticle particle;
	  particle.px = particleEnergy * cos(theta) * sin(phi);
	  particle.py = particleEnergy * sin(theta) * sin(phi);
	  particle.pz = particleEnergy * cos(phi);

	  particle.pdg = 22; // photon

	  // Save the particle in the particle list.
	  m_photons.push_back( particle );
	}
    }

  Double_t hadronic = 0.;
  if ( numberHadrons > 0. ) 
    {
      // The rest is hadronic.
      hadronic = energy - leptonic - photonic;

      // Distribute the energy/momentum among all the particles.
      Double_t remaining = hadronic;
      for ( Int_t i = 0; i != numberHadrons; ++i )
	{
	  Double_t particleEnergy;
	  if ( (i+1) == numberHadrons )
	    particleEnergy = remaining;
	  else
	    {
	      particleEnergy = remaining * random.Rndm();
	      remaining -= particleEnergy;
	    }

	  // Come up with a momentum direction.
	  Double_t phi = 2.*M_PI*random.Rndm();
	  Double_t theta = random.Gaus(0.,.004);

	  // Build the particle definition.
	  ExampleParticle particle;
	  particle.px = particleEnergy * cos(phi) * sin(theta);
	  particle.py = particleEnergy * sin(phi) * sin(theta);
	  particle.pz = particleEnergy * cos(theta);

	  // Randomly select the PDG type from a list.
	  static const Int_t pdgList[] = {
	    111,   // pi0
	    211,   // pi+
	    -211,  // pi-
	    2212,  // proton
	    -2212, // antiproton
	    2112,  // neutron
	    -2112, // antineutron
	    130,   // K0_L
	    310,   // K0_S
	    311,   // K0
	    321,   // K+
	    -321,  // K-
	  };
	  static const UInt_t listSize = sizeof(pdgList) / sizeof (Int_t);
	  UInt_t listIndex = random.Integer( listSize );
	  particle.pdg = pdgList[ listIndex ];

	  // Save the particle in the particle list.
	  m_hadrons.push_back( particle );
	}
    }
}
