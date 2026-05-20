#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() 
: G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
    // Her "Event" (olay) için 1 adet parçacık üreteceğiz
    fParticleGun = new G4ParticleGun(1);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // 1. İzotopu Tanımlama (Karbon-14)
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4IonTable* ionTable = particleTable->GetIonTable();
    
    G4int Z = 6;      // Karbonun atom numarası
    G4int A = 14;     // Kütle numarası
    G4double excitationEnergy = 0.0 * keV; // Temel hal (uyarılmamış)
    
    // İyonu veri tabanından çekip tabancamıza yüklüyoruz
    G4ParticleDefinition* ion = ionTable->GetIon(Z, A, excitationEnergy);
    fParticleGun->SetParticleDefinition(ion);

    // 2. Başlangıç Koşulları (En kritik kısım)
    // Parçacığı 0 eV enerjiyle (tamamen durur halde) bırakıyoruz.
    fParticleGun->SetParticleEnergy(0.0 * eV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0.*cm, 0.*cm, 0.*cm)); // Uzayın tam merkezi
    
    // Enerji sıfır olduğu için momentum yönünün pratikte bir önemi yok, 
    // ancak Geant4 hata vermesin diye rastgele bir yön tanımlıyoruz.
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));

    // 3. Olayı Başlat
    fParticleGun->GeneratePrimaryVertex(anEvent);
}