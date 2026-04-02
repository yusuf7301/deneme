#include "TCanvas.h"    //çizim penceresi(root)
#include "TH1F.h"       // 1D histogram
#include "TRandom3.h"   // rastgele sayı üretici
#include "TLegend.h"   // açıklama kutusu (legend)
#include "TStyle.h"   // global stil ayarları

void ders2(){

    gStyle->SetOptStat(1110);  //stil: istatistik kutusunda Enteries/Mean/RMS gibi bilgileri göster
    TCanvas* c1 = new TCanvas("c1","İKİ HİSTOGRAM",1000,500); //canvas oluştur
    
    