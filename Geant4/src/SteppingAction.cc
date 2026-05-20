#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Electron.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction() : G4UserSteppingAction() {}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    // Mevcut adımı atan parçacığın (Track) bilgilerini alıyoruz
    G4Track* track = step->GetTrack();

    // 1. Filtre: Parçacık bir elektron mu? (Beta eksi bozunumu)
    if (track->GetDefinition() == G4Electron::Electron()) {
        
        // 2. Filtre: Sadece parçacığın fırladığı ilk anı yakala.
        // Bunu yapmazsak, elektron vakumda ilerlerken her adımda aynı enerjiyi yazdırır.
        if (track->GetCurrentStepNumber() == 1) {
            
            // Kinetik enerjisini al
            G4double kineticEnergy = track->GetKineticEnergy();
            
            // Enerjiyi keV cinsinden terminale yazdır
            G4cout << ">>> Firlayan Beta Parcacigi (Elektron) Enerjisi: " 
                   << kineticEnergy / keV << " keV" << G4endl;
        }
    }
}