#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4EmParameters.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProductionCutsTable.hh"

//#include "G4EmStandardPhysics_option4.hh"
#include "G4EmPenelopePhysics.hh"
//#include "G4EmLivermorePhysics.hh"
//#include "G4EmExtraPhysics.hh"  //de folosit cu G4DecayPhysics altfel da segmentation fault

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList();
    ~MyPhysicsList() override;

    void SetCuts();
};

#endif