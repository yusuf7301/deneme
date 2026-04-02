#include "ActionInitialization.hh"   // Kendi action initialization başlık dosyamız

#include "PrimaryGeneratorAction.hh" // Birincil parçacık üretim sınıfı
#include "RunAction.hh"              // Run düzeyindeki işlemleri yöneten sınıf
#include "EventAction.hh"            // Event düzeyindeki işlemleri yöneten sınıf
#include "SteppingAction.hh"         // Step düzeyindeki işlemleri yöneten sınıf

ActionInitialization::ActionInitialization()   // Kurucu fonksiyon
    : G4VUserActionInitialization()            // Taban sınıf kurucusunu çağırır
{
    // Şimdilik ek işlem yok
}

ActionInitialization::~ActionInitialization()  // Yıkıcı fonksiyon
{
    // Şimdilik ek işlem yok
}

void ActionInitialization::BuildForMaster() const  // Sadece master thread için çalışır
{
    SetUserAction(new RunAction());  // Master tarafında yalnızca RunAction kuruyoruz
}

void ActionInitialization::Build() const  // Sıralı modda veya worker thread tarafında çalışır
{
    SetUserAction(new PrimaryGeneratorAction());  // Başlangıç parçacığını üreten sınıfı bağlar

    RunAction* runAction = new RunAction();       // RunAction nesnesini oluşturur
    SetUserAction(runAction);                     // RunAction'ı Geant4'e kaydeder

    EventAction* eventAction = new EventAction(runAction);  // EventAction'a RunAction işaretçisini verir
    SetUserAction(eventAction);                               // EventAction'ı kaydeder

    SetUserAction(new SteppingAction(eventAction));  // SteppingAction'a EventAction işaretçisini vererek kaydeder
}