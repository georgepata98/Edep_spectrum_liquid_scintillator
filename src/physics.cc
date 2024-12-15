#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    SetVerboseLevel(0);
    G4EmParameters::Instance();

    RegisterPhysics(new G4EmPenelopePhysics(0));
    //RegisterPhysics(new G4EmExtraPhysics(0));
}

MyPhysicsList::~MyPhysicsList()
{}

void MyPhysicsList::SetCuts()
{
    G4VUserPhysicsList::SetCuts();
    defaultCutValue = 0.1*mm;  //valoarea default in Geant4 este 1 mm
    SetCutsWithDefault();

    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100*eV, 100*GeV);
}