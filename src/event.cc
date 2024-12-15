#include "event.hh"

MyEventAction::MyEventAction(MyRunAction* runAction)
:fRunAction(runAction)
{
    G4RunManager::GetRunManager()->SetPrintProgress(0);

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(0);

    fOutputFile = runAction->GetOutputFile();
}

MyEventAction::~MyEventAction()
{}

G4THitsMap<G4double>* MyEventAction::GetHitsCollection(G4int hcID, const G4Event *event) const
{
    auto hitsCollection = static_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(hcID));

    if(!hitsCollection)
    {
        G4ExceptionDescription msg;
        msg << "Cannot access hitsCollection ID " << hcID;
        G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
    }

    return hitsCollection;
}

G4double MyEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
    G4double sumValue = 0;

    for(auto it:*hitsMap->GetMap())
    {
        sumValue += *(it.second);
    }

    return sumValue;
}

void MyEventAction::BeginOfEventAction(const G4Event *event)
{}

void MyEventAction::EndOfEventAction(const G4Event *event)
{
    if(fLSHCID == -1) 
    {
        fLSHCID = G4SDManager::GetSDMpointer()->GetCollectionID("LSdetector/Edep");  //numele la MultiFunctionalDetector si PrimitiveScorer 
    }

    G4double edep = GetSum(GetHitsCollection(fLSHCID, event));

    auto analysisManager = G4AnalysisManager::Instance();

    if(edep > 0.)
    {
        fRunAction->AddEdep(edep);
        //*fOutputFile << edep / keV << "  keV" << G4endl;  //energia depozitata, in keV, dupa fiecare event
        analysisManager->FillH1(0, edep / keV);
    }
}