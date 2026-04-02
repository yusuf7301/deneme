#ifndef ActionInitialization_h
#define ActionInitialization_h  // Başlık dosyasının birden fazla kez eklenmesini önler

#include "G4VUserActionInitialization.hh"  // Geant4 user action initialization taban sınıfı

class ActionInitialization : public G4VUserActionInitialization  // Kendi aksiyon bağlama sınıfımız
{
public:
    ActionInitialization();   // Kurucu fonksiyon bildirimi
    ~ActionInitialization() override;  // Yıkıcı fonksiyon bildirimi

    void Build() const override;           // Sıralı mod ve worker thread için aksiyonları kurar
    void BuildForMaster() const override;  // Sadece master thread için gerekli aksiyonu kurar
};

#endif  // ActionInitialization_h