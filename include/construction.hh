#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4VPrimitiveScorer.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"

#include <memory>

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction() override;

public:
    G4VPhysicalVolume* Construct() override;
    virtual void ConstructSDandField() override;

private:
    G4VPhysicalVolume* DefineVolumes();
    
    G4double inaltime_LS, grosime_sticla, diametru_sticla, inaltime_sticla;  //dimensiuni fiola cu LS
};

#endif