#include "SteppingAction.hh"        // Kendi SteppingAction başlık dosyamız
#include "EventAction.hh"           // Enerji katkısını aktaracağımız EventAction sınıfı
#include "DetectorConstruction.hh"  // Scoring volume bilgisini alacağımız geometri sınıfı

#include "G4Step.hh"                // G4Step sınıfı
#include "G4LogicalVolume.hh"       // G4LogicalVolume sınıfı
#include "G4VPhysicalVolume.hh"     // G4VPhysicalVolume sınıfı
#include "G4RunManager.hh"          // Run manager üzerinden detector construction'a erişmek için gerekli başlık

SteppingAction::SteppingAction(EventAction* eventAction)  // Kurucu fonksiyon
    : G4UserSteppingAction(),                             // Taban sınıf kurucusunu çağırır
      fEventAction(eventAction),                          // Dışarıdan gelen EventAction işaretçisini saklar
      fScoringVolume(nullptr)                             // Başlangıçta scoring volume işaretçisini boş yapar
{
    // Şimdilik ek işlem yapmıyoruz
}

SteppingAction::~SteppingAction()  // Yıkıcı fonksiyon
{
    // Şimdilik ek işlem yapmıyoruz
}

void SteppingAction::UserSteppingAction(const G4Step* step)  // Her step sonunda çağrılır
{
    if (!fScoringVolume)  // Eğer scoring volume henüz alınmadıysa
    {
        const DetectorConstruction* detectorConstruction =
            static_cast<const DetectorConstruction*>(
                G4RunManager::GetRunManager()->GetUserDetectorConstruction()
            );  // Run manager içinden kendi detector construction sınıfımıza erişir

        fScoringVolume = detectorConstruction->GetScoringVolume();  // Seçili scoring volume'ü bir kez alıp saklar
    }

    G4LogicalVolume* volume =
        step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();  // Step'in başladığı logical volume'ü alır

    if (volume != fScoringVolume)  // Eğer step bizim seçtiğimiz hacimde değilse
    {
        return;                    // Bu step için hiçbir şey yapmadan fonksiyondan çıkar
    }

    G4double edepStep = step->GetTotalEnergyDeposit();  // Bu step boyunca bırakılan toplam enerjiyi alır

    if (edepStep <= 0.)  // Eğer bırakılan enerji yoksa veya sıfırsa
    {
        return;          // Gereksiz işlem yapmadan çıkar
    }

    fEventAction->AddEdep(edepStep);  // Bu step'teki enerji katkısını event toplamına ekler
}