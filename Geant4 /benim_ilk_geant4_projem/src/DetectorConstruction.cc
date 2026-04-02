#include "DetectorConstruction.hh"   // Kendi geometri sınıfımızın başlık dosyası

#include "G4Box.hh"                  // Kutu geometrisi oluşturmak için gerekli sınıf
#include "G4LogicalVolume.hh"        // Logical volume tanımı için gerekli sınıf
#include "G4PVPlacement.hh"          // Physical volume yerleştirmek için gerekli sınıf
#include "G4SystemOfUnits.hh"        // cm, m gibi birim sabitlerini kullanmak için gerekli başlık
#include "G4NistManager.hh"          // NIST malzeme veritabanına erişmek için gerekli sınıf
#include "G4Material.hh"             // Malzeme sınıfı tanımı
#include "G4VPhysicalVolume.hh"      // Physical volume dönüş tipi için gerekli başlık
#include "G4ThreeVector.hh"          // Konum vektörleri için gerekli başlık
#include "G4VisAttributes.hh"        // Hacimlerin görsel özelliklerini ayarlamak için gerekli başlık
#include "G4Colour.hh"               // Renk tanımlamak için gerekli başlık

DetectorConstruction::DetectorConstruction()   // Sınıfın kurucu fonksiyonu
    : G4VUserDetectorConstruction(),           // Taban sınıfın kurucusunu çağırır
      fScoringVolume(nullptr)                  // Başlangıçta scoring volume işaretçisini boş yapar
{
    // Şimdilik kurucu içinde ek işlem yapmıyoruz
}

DetectorConstruction::~DetectorConstruction()  // Sınıfın yıkıcı fonksiyonu
{
    // Şimdilik elle silmemiz gereken özel bir nesne yok
}

G4VPhysicalVolume* DetectorConstruction::Construct()  // Geometrinin gerçekten kurulduğu ana fonksiyon
{
    // Geant4'in dahili malzeme yöneticisini alır
    G4NistManager* nist = G4NistManager::Instance();

    // Dünya hacmi için hava malzemesini veritabanından alır
    G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_AIR");

    // Hedef hacim için su malzemesini veritabanından alır
    G4Material* targetMaterial = nist->FindOrBuildMaterial("G4_WATER");

    // Dünya hacminin x yönündeki yarı uzunluğunu tanımlar
    G4double worldHalfX = 0.5 * m;

    // Dünya hacminin y yönündeki yarı uzunluğunu tanımlar
    G4double worldHalfY = 0.5 * m;

    // Dünya hacminin z yönündeki yarı uzunluğunu tanımlar
    G4double worldHalfZ = 0.5 * m;

    // Hedef kutunun x yönündeki yarı uzunluğunu tanımlar
    G4double targetHalfX = 5.0 * cm;

    // Hedef kutunun y yönündeki yarı uzunluğunu tanımlar
    G4double targetHalfY = 5.0 * cm;

    // Hedef kutunun z yönündeki yarı uzunluğunu tanımlar
    G4double targetHalfZ = 5.0 * cm;

    // Dünya hacmi için geometrik kutu şekli oluşturur
    G4Box* solidWorld = new G4Box(
        "World",         // Geometrik cismin adı
        worldHalfX,      // x yarı uzunluğu
        worldHalfY,      // y yarı uzunluğu
        worldHalfZ       // z yarı uzunluğu
    );

    // Dünya hacminin logical volume'ünü oluşturur
    G4LogicalVolume* logicWorld = new G4LogicalVolume(
        solidWorld,      // Kullanılacak geometrik şekil
        worldMaterial,   // Dünya hacminin malzemesi
        "World"          // Logical volume adı
    );

    // Dünya hacmini görünmez yapar
    G4VisAttributes* worldVisAtt = new G4VisAttributes();
    worldVisAtt->SetVisibility(false);
    logicWorld->SetVisAttributes(worldVisAtt);

    // Dünya hacmini fiziksel olarak yerleştirir
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        nullptr,         // Dönme matrisi yok
        G4ThreeVector(), // Konum vektörü; (0,0,0) yani orijin
        logicWorld,      // Yerleştirilecek logical volume
        "World",         // Physical volume adı
        nullptr,         // Dünya hacminin mother volume'ü yok
        false,           // Boole işlemi kullanılmıyor
        0,               // Kopya numarası
        true             // Overlap kontrolü yap
    );

    // Hedef hacim için geometrik kutu şekli oluşturur
    G4Box* solidTarget = new G4Box(
        "Target",        // Hedef geometrisinin adı
        targetHalfX,     // x yarı uzunluğu
        targetHalfY,     // y yarı uzunluğu
        targetHalfZ      // z yarı uzunluğu
    );

    // Hedef hacmin logical volume'ünü oluşturur
    G4LogicalVolume* logicTarget = new G4LogicalVolume(
        solidTarget,     // Hedefin geometrik şekli
        targetMaterial,  // Hedef malzemesi
        "Target"         // Logical volume adı
    );

    // Hedef hacmi kırmızı ve dolu görünür yapar
    G4VisAttributes* targetVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    targetVisAtt->SetVisibility(true);
    targetVisAtt->SetForceSolid(true);
    logicTarget->SetVisAttributes(targetVisAtt);

    // Hedef hacmi dünya hacminin merkezine yerleştirir
    new G4PVPlacement(
        nullptr,               // Dönme matrisi yok
        G4ThreeVector(),       // Dünya merkezine yerleştir
        logicTarget,           // Yerleştirilecek logical volume
        "Target",              // Physical volume adı
        logicWorld,            // Mother volume dünya hacmi
        false,                 // Boole işlemi kullanılmıyor
        0,                     // Kopya numarası
        true                   // Overlap kontrolü yap
    );

    // İleride enerji bırakımını bu hacimde toplayabilmek için hedefi scoring volume olarak saklar
    fScoringVolume = logicTarget;

    // Geant4'e en dış fiziksel hacmi yani dünya hacmini geri döndürür
    return physWorld;
}

G4LogicalVolume* DetectorConstruction::GetScoringVolume() const  // Seçili scoring volume'ü dışarı verir
{
    // Saklanan scoring volume işaretçisini geri döndürür
    return fScoringVolume;
}