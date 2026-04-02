#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"

void geant_analiz() {
    // 1. Geant4'ten çıkan dosyayı aç
    // Not: Şu an dosyan olmadığı için hata alabilirsin, mantığı anlamak önemli.
    TFile *dosya = new TFile("simulasyon_verisi.root", "READ");

    // 2. Dosyanın içindeki "Tree"yi (Ağacı) bul
    // Geant4 projelerinde genelde adı "Ntuple" veya "Hits" olur.
    TTree *tree = (TTree*)dosya->Get("Hits");

    // 3. Veriyi içine çekeceğimiz bir değişken tanımla
    double enerji;
    tree->SetBranchAddress("Energy", &enerji);

    // 4. Analiz için bir histogram oluştur
    TH1F *h_enerji = new TH1F("h_enerji", "Asteroid Yuzey Enerji Spektrumu;MeV;Sayi", 100, 0, 10);

    // 5. Tree içindeki tüm olayları (parçacık çarpmalarını) oku
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i); // i. olayı oku
        h_enerji->Fill(enerji); // Okunan enerjiyi histograma at
    }

    // 6. Çizdir
    TCanvas *c1 = new TCanvas("c1", "Geant4 Analizi", 800, 600);
    h_enerji->Draw();
}