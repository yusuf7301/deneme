#ifndef SteppingAction_h
#define SteppingAction_h  // Başlık dosyasının birden fazla kez eklenmesini önler

#include "G4UserSteppingAction.hh"  // Geant4 step düzeyi user action taban sınıfı

class G4Step;              // G4Step sınıfını ileri bildirim ile tanıtıyoruz
class G4LogicalVolume;     // G4LogicalVolume sınıfını ileri bildirim ile tanıtıyoruz
class DetectorConstruction; // DetectorConstruction sınıfını ileri bildirim ile tanıtıyoruz
class EventAction;         // EventAction sınıfını ileri bildirim ile tanıtıyoruz

class SteppingAction : public G4UserSteppingAction  // Kendi stepping action sınıfımız
{
public:
    SteppingAction(EventAction* eventAction);  // EventAction işaretçisini alacak kurucu fonksiyon bildirimi
    ~SteppingAction() override;                // Yıkıcı fonksiyon bildirimi

    void UserSteppingAction(const G4Step* step) override;  // Her step sonunda çağrılan ana metod

private:
    EventAction* fEventAction;             // Enerji katkısını aktaracağımız EventAction işaretçisi
    G4LogicalVolume* fScoringVolume;       // Enerji toplamak için izleyeceğimiz logical volume işaretçisi
};

#endif  // SteppingAction_h