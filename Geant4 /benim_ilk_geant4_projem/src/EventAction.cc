#include "EventAction.hh"   // Kendi EventAction başlık dosyamız
#include "RunAction.hh"     // Event sonunda sonucu aktaracağımız RunAction sınıfı

#include "G4Event.hh"       // G4Event sınıfı
#include "G4ios.hh"         // G4cout ve G4endl için gerekli başlık

EventAction::EventAction(RunAction* runAction)   // Kurucu fonksiyon
    : G4UserEventAction(),                       // Taban sınıf kurucusunu çağırır
      fRunAction(runAction),                     // Dışarıdan gelen RunAction işaretçisini saklar
      fEdep(0.)                                 // Event enerjisini başlangıçta sıfırlar
{
    // Şimdilik ek işlem yapmıyoruz
}

EventAction::~EventAction()   // Yıkıcı fonksiyon
{
    // Şimdilik ek işlem yapmıyoruz
}

void EventAction::BeginOfEventAction(const G4Event* event)   // Her event başında çağrılır
{
    fEdep = 0.;                                               // Yeni event başladığında enerji sayacını sıfırlar

    // İstersen aşağıdaki satırı açıp event başlangıçlarını ekranda görebilirsin
    // G4cout << "Event basladi : Event ID = " << event->GetEventID() << G4endl;
}

void EventAction::EndOfEventAction(const G4Event* event)     // Her event sonunda çağrılır
{
    if (fRunAction)                                           // Eğer RunAction işaretçisi geçerliyse
    {
        fRunAction->AddEdep(fEdep);                           // Event boyunca biriken enerjiyi run toplamına ekler
    }

    // İstersen aşağıdaki satırı açıp event sonu toplam enerjisini ekranda görebilirsin
    // G4cout << "Event bitti : Event ID = " << event->GetEventID()
    //        << "  Event enerjisi = " << fEdep << G4endl;
}

void EventAction::AddEdep(G4double edep)   // Step düzeyinden gelen enerji katkısını event toplamına ekler
{
    fEdep += edep;                          // Gelen enerjiyi event boyunca biriken toplam enerjiye ekler
}

G4double EventAction::GetEdep() const      // Event boyunca biriken toplam enerjiyi geri döndürür
{
    return fEdep;                          // Saklanan toplam event enerjisini döndürür
}