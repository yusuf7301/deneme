#ifndef RunAction_h
#define RunAction_h  // Başlık dosyasının birden fazla kez eklenmesini önler

#include "G4UserRunAction.hh"  // Geant4 run düzeyi user action taban sınıfı
#include "globals.hh"          // G4double gibi Geant4 temel türleri için gerekli başlık

class G4Run;  // G4Run sınıfını ileri bildirim ile tanıtıyoruz

class RunAction : public G4UserRunAction  // Kendi run action sınıfımız
{
public:
    RunAction();   // Kurucu fonksiyon bildirimi
    ~RunAction() override;  // Yıkıcı fonksiyon bildirimi

    void BeginOfRunAction(const G4Run* run) override;  // Her run başında çağrılır
    void EndOfRunAction(const G4Run* run) override;    // Her run sonunda çağrılır

    void AddEdep(G4double edep);  // Event sonlarında veya başka yerlerden toplam enerji eklemek için yardımcı fonksiyon
    G4double GetTotalEdep() const;  // Toplam biriken enerjiyi okumak için yardımcı fonksiyon

private:
    G4double fTotalEdep;  // Run boyunca biriktireceğimiz toplam enerji bırakımı
};

#endif  // RunAction_h