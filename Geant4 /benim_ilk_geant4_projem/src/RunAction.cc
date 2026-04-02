#include "RunAction.hh"      // Kendi RunAction başlık dosyamız

#include "G4Run.hh"          // G4Run sınıfı
#include "G4UnitsTable.hh"   // Fiziksel büyüklükleri uygun birimle yazdırmak için gerekli başlık
#include "G4ios.hh"          // G4cout ve G4endl için gerekli başlık

RunAction::RunAction()       // Kurucu fonksiyon
    : G4UserRunAction(),     // Taban sınıf kurucusunu çağırır
      fTotalEdep(0.)         // Toplam enerji bırakımını başlangıçta sıfırlar
{
    // Şimdilik ek işlem yapmıyoruz
}

RunAction::~RunAction()      // Yıkıcı fonksiyon
{
    // Şimdilik ek işlem yapmıyoruz
}

void RunAction::BeginOfRunAction(const G4Run* run)   // Her run başında çağrılır
{
    fTotalEdep = 0.;                                 // Yeni run başladığında toplam enerji sayacını sıfırlar

    G4cout << G4endl;                                // Ekrana boş satır basar
    G4cout << "========================================" << G4endl;   // Başlık çizgisi basar
    G4cout << "=== Run basladi : Run ID = "                         // Run başlangıç bilgisini basar
           << run->GetRunID()
           << G4endl;
    G4cout << "========================================" << G4endl;   // Başlık çizgisi basar
}

void RunAction::EndOfRunAction(const G4Run* run)     // Her run sonunda çağrılır
{
    G4int numberOfEvents = run->GetNumberOfEvent();  // Bu run içinde işlenen toplam event sayısını alır

    G4double averageEdep = 0.;                       // Event başına ortalama enerji için değişken tanımlar

    if (numberOfEvents > 0)                          // Sıfıra bölme hatasını önlemek için kontrol yapar
    {
        averageEdep = fTotalEdep / numberOfEvents;   // Ortalama enerjiyi hesaplar
    }

    G4cout << G4endl;                                // Ekrana boş satır basar
    G4cout << "========================================" << G4endl;   // Özet başlık çizgisi basar
    G4cout << "=== Run bitti : Run ID = "                           // Run bitiş bilgisini basar
           << run->GetRunID()
           << G4endl;

    G4cout << "Islenen event sayisi = "                              // İşlenen event sayısını basar
           << numberOfEvents
           << G4endl;

    G4cout << "Toplam biriken enerji = "                             // Toplam enerjiyi uygun birimle basar
           << G4BestUnit(fTotalEdep, "Energy")
           << G4endl;

    G4cout << "Event basina ortalama enerji = "                      // Event başına ortalama enerjiyi basar
           << G4BestUnit(averageEdep, "Energy")
           << G4endl;

    G4cout << "========================================" << G4endl;   // Özet alt çizgisi basar
    G4cout << G4endl;                                                // Ekrana boş satır basar
}

void RunAction::AddEdep(G4double edep)               // Dışarıdan gelen enerji katkısını toplama ekler
{
    fTotalEdep += edep;                              // Gelen enerjiyi run toplamına ekler
}

G4double RunAction::GetTotalEdep() const             // Toplam biriken enerjiyi döndürür
{
    return fTotalEdep;                               // Saklanan toplam enerji değerini geri verir
}