#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h  // Başlık dosyasının birden fazla kez eklenmesini önler

#include "G4VUserPrimaryGeneratorAction.hh"  // Birincil parçacık üretim taban sınıfı

class G4ParticleGun;  // G4ParticleGun sınıfını ileri bildirim ile tanıtıyoruz
class G4Event;        // G4Event sınıfını ileri bildirim ile tanıtıyoruz

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction  // Kendi primary generator sınıfımız
{
public:
    PrimaryGeneratorAction();   // Kurucu fonksiyon bildirimi
    ~PrimaryGeneratorAction() override;  // Yıkıcı fonksiyon bildirimi

    void GeneratePrimaries(G4Event* anEvent) override;  // Her event başında çağrılan ana üretim fonksiyonu

private:
    G4ParticleGun* fParticleGun;  // Birincil parçacığı üretmek için kullanacağımız particle gun işaretçisi
};

#endif  // PrimaryGeneratorAction_h