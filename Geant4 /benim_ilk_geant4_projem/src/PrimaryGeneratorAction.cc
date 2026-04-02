#include "PrimaryGeneratorAction.hh"   // Kendi primary generator başlık dosyamız

#include "G4ParticleGun.hh"            // G4ParticleGun sınıfı
#include "G4Event.hh"                  // G4Event sınıfı
#include "G4ParticleTable.hh"          // Parçacık tablosuna erişmek için gerekli sınıf
#include "G4ParticleDefinition.hh"     // Parçacık tanımı sınıfı
#include "G4SystemOfUnits.hh"          // MeV, cm gibi birimleri kullanmak için gerekli başlık
#include "G4ThreeVector.hh"            // Konum ve yön vektörleri için gerekli sınıf

PrimaryGeneratorAction::PrimaryGeneratorAction()   // Kurucu fonksiyon
    : G4VUserPrimaryGeneratorAction(),             // Taban sınıf kurucusunu çağırır
      fParticleGun(nullptr)                        // Başlangıçta particle gun işaretçisini boş yapar
{
    G4int numberOfParticles = 1;                  // Her event için üretilecek primary parçacık sayısı
    fParticleGun = new G4ParticleGun(numberOfParticles);  // Particle gun nesnesini oluşturur

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();  // Geant4 parçacık tablosunu alır
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma"); // Gamma parçacığını tablodan bulur

    fParticleGun->SetParticleDefinition(particle);                  // Üretilecek parçacığı gamma olarak ayarlar
    fParticleGun->SetParticleEnergy(1.0 * MeV);                     // Parçacık enerjisini 1 MeV yapar
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -20. * cm)); // Başlangıç konumunu z ekseninde geriye koyar
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.)); // Parçacığı +z yönüne gönderir
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()   // Yıkıcı fonksiyon
{
    delete fParticleGun;                            // Particle gun nesnesini bellekten temizler
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)   // Her event başında çağrılan üretim fonksiyonu
{
    fParticleGun->GeneratePrimaryVertex(anEvent);   // Event içine primary vertex ve parçacığı yerleştirir
}