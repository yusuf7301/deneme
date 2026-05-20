#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList() {
    // 1. Standart Elektromanyetik Fizik
    // Çıkan beta parçacıklarının (elektronların) hareketini ve özelliklerini tanımlar.
    RegisterPhysics(new G4EmStandardPhysics());

    // 2. Standart Bozunum Fiziği
    // Geant4'ün temel bozunum kinematiklerini yükler.
    RegisterPhysics(new G4DecayPhysics());

    // 3. Radyoaktif Bozunum Fiziği (En Önemlisi!)
    // Veri tabanlarına (ENSDF) bağlanarak Karbon-14 gibi izotopların
    // yarı ömürlerini ve beta enerji spektrumlarını doğru bir şekilde simüle eder.
    RegisterPhysics(new G4RadioactiveDecayPhysics());
}

PhysicsList::~PhysicsList() {}