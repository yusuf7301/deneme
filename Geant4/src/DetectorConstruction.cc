#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // 1. Materyal Tanımlama: NIST veri tabanından "Vakum" (Galaktik ortam) çağırıyoruz.
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

    // 2. Geometri Tanımlama: 1 metrelik bir küp tasarlıyoruz.
    // Geant4'te G4Box yarı uzunluk (half-length) alır, bu yüzden boyutu 2'ye bölüyoruz.
    G4double worldSize = 1.0 * m;
    G4Box* solidWorld = new G4Box("World", worldSize/2, worldSize/2, worldSize/2);

    // 3. Mantıksal Hacim: Geometri ile materyali (Vakum) birleştiriyoruz.
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World");

    // 4. Fiziksel Hacim: Mantıksal hacmi uzayda (0,0,0) noktasına yerleştiriyoruz.
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        0,                  // Rotasyon yok
        G4ThreeVector(),    // Merkez koordinatı (0,0,0)
        logicWorld,         // Mantıksal hacim
        "World",            // İsim
        0,                  // Anne hacim (Bu en dış hacim olduğu için anne hacmi yok)
        false,              // Boolean operasyonu yok
        0,                  // Kopya numarası
        true                // Çakışma (overlap) kontrolü açık
    );

    return physWorld;
}