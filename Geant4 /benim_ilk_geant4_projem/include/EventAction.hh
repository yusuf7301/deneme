#ifndef EventAction_h
#define EventAction_h  // Başlık dosyasının birden fazla kez eklenmesini önler

#include "G4UserEventAction.hh"  // Geant4 event düzeyi user action taban sınıfı
#include "globals.hh"            // G4double gibi temel Geant4 türleri için gerekli başlık

class G4Event;    // G4Event sınıfını ileri bildirim ile tanıtıyoruz
class RunAction;  // RunAction sınıfını ileri bildirim ile tanıtıyoruz

class EventAction : public G4UserEventAction  // Kendi event action sınıfımız
{
public:
    EventAction(RunAction* runAction);  // RunAction işaretçisini alacak kurucu fonksiyon bildirimi
    ~EventAction() override;            // Yıkıcı fonksiyon bildirimi

    void BeginOfEventAction(const G4Event* event) override;  // Her event başında çağrılır
    void EndOfEventAction(const G4Event* event) override;    // Her event sonunda çağrılır

    void AddEdep(G4double edep);  // Step düzeyinden gelen enerji katkılarını event toplamına ekler
    G4double GetEdep() const;     // Event boyunca biriken toplam enerjiyi geri verir

private:
    RunAction* fRunAction;  // Event sonunda toplam enerjiyi aktaracağımız RunAction işaretçisi
    G4double fEdep;         // Tek bir event boyunca biriken toplam enerji bırakımı
};

#endif  // EventAction_h