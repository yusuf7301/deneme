#include "G4RunManagerFactory.hh"   // Geant4 run manager'ı üretmek için gerekli başlık
#include "G4UImanager.hh"           // Komutları Geant4'e gönderen UI manager başlığı
#include "G4UIExecutive.hh"         // Interactive oturum açmak için UI başlığı
#include "G4VisExecutive.hh"        // Hazır görselleştirme yöneticisi başlığı
#include "QBBC.hh"                  // Hazır reference physics list başlığı

#include "DetectorConstruction.hh"  // Birazdan yazacağımız geometri sınıfı başlığı
#include "ActionInitialization.hh"  // Birazdan yazacağımız aksiyon bağlama sınıfı başlığı

int main(int argc, char** argv)     // Programın başlangıç noktası; argc/argv ile batch mi interactive mi anlayacağız
{
    G4UIExecutive* ui = nullptr;    // Başta UI oturumu yok kabul ediyoruz

    if (argc == 1)                  // Komut satırında ek argüman yoksa interactive modda çalışacağız
    {
        ui = new G4UIExecutive(argc, argv, "tcsh");  // Qt komut kutusu yerine terminal tabanlı oturum açar
    }

    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::SerialOnly);  // MT yerine sıralı modda run manager oluşturur
    runManager->SetUserInitialization(new DetectorConstruction());  // Geometri ve malzeme sınıfını sisteme bağlar

    auto* physicsList = new QBBC;   // Hazır QBBC physics list nesnesini oluşturur
    physicsList->SetVerboseLevel(1);  // Physics list için temel bilgi düzeyini ayarlar
    runManager->SetUserInitialization(physicsList);  // Physics list'i run manager'a bağlar

    runManager->SetUserInitialization(new ActionInitialization());  // Primary generator ve diğer aksiyonları bağlayan sınıfı ekler
    runManager->Initialize();  // Geant4 çekirdeğini başlatır
    auto* visManager = new G4VisExecutive;  // Görselleştirme yöneticisini oluşturur
    visManager->Initialize();               // Görselleştirme sistemini başlatır

    auto* uiManager = G4UImanager::GetUIpointer();  // Geant4 UI manager işaretçisini alır

    if (!ui)                                // Eğer ui yoksa batch moddayız demektir
    {
        G4String command = "/control/execute ";  // Macro çalıştırma komutunun ilk kısmı
        G4String fileName = argv[1];             // Kullanıcının verdiği macro dosyası adını alır
        uiManager->ApplyCommand(command + fileName);  // Verilen macro dosyasını çalıştırır
    }
    else                                    // Eğer ui varsa interactive moddayız demektir
    {
        uiManager->ApplyCommand("/control/execute vis.mac");  // Başlangıç görselleştirme ayarlarını vis.mac içinden yükler
        ui->SessionStart();                                   // Interactive oturumu başlatır
        delete ui;                                            // UI oturumu bitince belleği temizler
    }

    delete visManager;                    // Görselleştirme yöneticisini siler
    delete runManager;                    // Run manager'ı siler
    return 0;                             // Programı sorunsuz şekilde bitirir
}