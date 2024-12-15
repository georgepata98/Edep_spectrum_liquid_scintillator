#include "run.hh"

MyRunAction::MyRunAction()
{
    G4RunManager::GetRunManager()->SetPrintProgress(0);

    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(totalEdep);

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->CreateH1("Edep", "Edep in LS", 1000, 0, 1350);
}

MyRunAction::~MyRunAction()
{
    if(fOutputFile.is_open()) fOutputFile.close();
}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4int runID = run->GetRunID();

    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();

    G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    fOutputFile.open(("histo_data_Run" + std::to_string(runID) + ".txt").c_str());


    auto analysisManager = G4AnalysisManager::Instance();

    G4String fileName = ("spectra_Run" + std::to_string(runID) + ".root").c_str();
    analysisManager->OpenFile(fileName);
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4int runID = run->GetRunID();
    if(run->GetNumberOfEvent() == 0) return;

    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    if(fOutputFile.is_open()) fOutputFile.close();

    G4cout << G4endl << "*************** End of Run " << runID << " ***************" << G4endl << "Number of events: " << run->GetNumberOfEvent() << G4endl << "********************************************" << G4endl << G4endl;


    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}

std::ofstream* MyRunAction::GetOutputFile()
{
    return &fOutputFile;
}