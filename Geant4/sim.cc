#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh" // YENİ: Görselleştirme kütüphanesi

// Kendi yazdığımız sınıfları çağırıyoruz
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv) {
    // 1. Kullanıcı Arayüzünü Başlat
    G4UIExecutive* ui = 0;
    if (argc == 1) { ui = new G4UIExecutive(argc, argv); }

    // 2. Geant4 Ana Motorunu (RunManager) Oluştur
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // 3. Yazdığımız Sınıfları Motora Yükle
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());

    // 4. Motoru Hazırla
    runManager->Initialize();

    // ----------------------------------------------------
    // YENİ: Görselleştirme (Visualization) Yöneticisini Başlat
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    // ----------------------------------------------------

    // 5. Simülasyonu Ekranda Çalıştır
    if (ui) {
        ui->SessionStart();
        delete ui;
    }

    // Temizlik
    delete visManager; // Bellekten sil
    delete runManager;
    return 0;
}