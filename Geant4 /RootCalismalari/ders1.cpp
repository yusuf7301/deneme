// ders1.cpp  // dosya adı: ders1.cpp (Named Macro olacak)  

#include "TCanvas.h"   // ROOT: çizim penceresi (canvas) sınıfı
#include "TH1F.h"      // ROOT: 1 boyutlu float histogram sınıfı
#include "TRandom3.h"  // ROOT: rastgele sayı üreteci (Mersenne Twister tabanlı)

// ders1  // fonksiyon adı dosya adıyla aynı (ders1.cpp -> ders1)
void ders1() { // ROOT makrosunun giriş noktası (main yerine bu çalışır)
    
    TCanvas* c1 = new TCanvas("c1", "Ders 1 - Histogram", 900, 600); // canvas oluştur: isim, başlık, genişlik, yükseklik
    
    TH1F* h1 = new TH1F("h1", "Gaussian Histogram;X;Counts", 100, -4.0, 4.0); // histogram: isim, başlık+eksenler, bin sayısı, min, max
    
    TRandom3 rng(0); // rastgele üreteç (0: zamana bağlı seed gibi davranır; her çalıştırmada farklı olabilir)
    
    for (int i = 0; i < 10000; i++) { // 10 bin olay üret (simülasyon gibi düşün)
        double x = rng.Gaus(0.0, 1.0); // Gaussian dağılımdan sayı çek: ort=0, sigma=1
        h1->Fill(x); // histogramı bu değerle doldur (Counts artar)
    }
    
    h1->Draw(); // histogramı çiz
    
    c1->Update(); // canvas’ı güncelle (bazı sistemlerde anında görmek için iyi)
}