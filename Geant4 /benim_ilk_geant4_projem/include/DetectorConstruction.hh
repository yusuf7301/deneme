#ifndef DetectorConstruction_h
#define DetectorConstruction_h  // Bu satır başlık dosyasının birden fazla kez eklenmesini önler

#include "G4VUserDetectorConstruction.hh"  // Geant4'te geometri sınıfı yazmak için gereken taban sınıf

class G4VPhysicalVolume;  // Fiziksel hacim sınıfını ileri bildirim ile tanıtıyoruz
class G4LogicalVolume;    // Mantıksal hacim sınıfını ileri bildirim ile tanıtıyoruz

class DetectorConstruction : public G4VUserDetectorConstruction  // Kendi geometri sınıfımızı Geant4 taban sınıfından türetiyoruz
{
public:
    DetectorConstruction();   // Kurucu fonksiyon bildirimi
    ~DetectorConstruction() override;  // Yıkıcı fonksiyon bildirimi

    G4VPhysicalVolume* Construct() override;  // Geometrinin gerçekten kurulacağı temel fonksiyon

    G4LogicalVolume* GetScoringVolume() const;  // İleride enerji bırakımını izleyeceğimiz hacmi dışarı vermek için yardımcı fonksiyon

private:
    G4LogicalVolume* fScoringVolume;  // Ölçüm veya enerji biriktirme için seçeceğimiz mantıksal hacim işaretçisi
};

#endif  // DetectorConstruction_h