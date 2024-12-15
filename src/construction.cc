#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    return DefineVolumes();
}

G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes()
{
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *C = nist->FindOrBuildMaterial("G4_C");
    G4Material *H = nist->FindOrBuildMaterial("G4_H");
    G4Material *N = nist->FindOrBuildMaterial("G4_N");
    G4Material *O = nist->FindOrBuildMaterial("G4_O");
    
    G4Material *UGLLT = new G4Material("UltimaGold LLT", 0.983*g/cm3, 4);  //de verificat compozitiile masice procentuale
    UGLLT->AddMaterial(C, 76.4*perCent);
    UGLLT->AddMaterial(H, 9.6*perCent);
    UGLLT->AddMaterial(N, 0.1*perCent);
    UGLLT->AddMaterial(O, 13.9*perCent);

    G4Material *glass = nist->FindOrBuildMaterial("G4_Pyrex_Glass");  //de verificat daca este bun materialul sticlei

    
    //00000000000000000000000000000000000000000000000000000000000000000000000000000
    
    diametru_sticla = 2.72*cm;  //masurata cu subler, in care este inclusa si grosimea peretelui sticlutei
    grosime_sticla = 0.18*cm;
    inaltime_LS = 2.2*cm - grosime_sticla;  //inaltimea lichidului scintilator
    inaltime_sticla = 4.7*cm;  //masurata cu subler, in care este inclusa grosimea fundului sticlutei


    G4Box *solidWorld = new G4Box("solidWorld", 15*cm, 15*cm, 15*cm);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0);

    G4Tubs *solidPerete = new G4Tubs("solidPerete", diametru_sticla/2-grosime_sticla, diametru_sticla/2, inaltime_sticla/2-grosime_sticla/2, 0*deg, 360*deg);
    G4LogicalVolume *logicPerete = new G4LogicalVolume(solidPerete, glass, "logicPerete");
    G4VPhysicalVolume *physPerete = new G4PVPlacement(0, G4ThreeVector(0, 0, inaltime_sticla/2-grosime_sticla/2-inaltime_LS/2), logicPerete, "physPerete", logicWorld, false, 0);

    G4Tubs *solidFund = new G4Tubs("solidFund", 0*cm, diametru_sticla/2, grosime_sticla/2, 0*deg, 360*deg);
    G4LogicalVolume *logicFund = new G4LogicalVolume(solidFund, glass, "logicFund");
    G4VPhysicalVolume *physFund = new G4PVPlacement(0, G4ThreeVector(0, 0, -inaltime_LS/2-grosime_sticla/2), logicFund, "physFund", logicWorld, false, 0);

    G4Tubs *solidLS = new G4Tubs("solidLS", 0*cm, diametru_sticla/2-grosime_sticla, inaltime_LS/2, 0*deg, 360*deg);
    G4LogicalVolume *logicLS = new G4LogicalVolume(solidLS, UGLLT, "logicLS");
    G4VPhysicalVolume *physLS = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicLS, "physLS", logicWorld, false, 0);

    //00000000000000000000000000000000000000000000000000000000000000000000000000000


    G4VisAttributes *yellow = new G4VisAttributes(G4Colour::Yellow());
    yellow->SetVisibility(true);
    yellow->SetForceSolid(true);

    logicPerete->SetVisAttributes(G4Colour::Blue());
    logicFund->SetVisAttributes(G4Colour::Blue());
    logicLS->SetVisAttributes(yellow);


    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
    G4MultiFunctionalDetector *LSdetector;
    G4VPrimitiveScorer *primitive;

    LSdetector = new G4MultiFunctionalDetector("LSdetector");

    primitive = new G4PSEnergyDeposit("Edep");
    LSdetector->RegisterPrimitive(primitive);

    SetSensitiveDetector("logicLS", LSdetector);
    G4SDManager::GetSDMpointer()->AddNewDetector(LSdetector);
}
