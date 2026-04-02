# bilgisyara karşı kullanıcının taş kağıt makas oyunu yapacağız. ancak yapacağım veride bilgisayar hızlı seçim yapsın ve oranlı olsun 

import random  # Rastgele seçimler yapabilmek için gerekli kütüphaneyi içeri aktarıyoruz.
import time    # Kodun akışını kısa süreliğine durdurup (bekleme efekti) hız kazandırmak için kullanıyoruz.

def uclu_oyun():
    # Seçeneklerimizi bir liste (list) içerisinde tanımlıyoruz.
    secenekler = ["taş", "kağıt", "makas"]
    
    # Bilgisayarın hangi seçeneği ne kadar ihtimalle seçeceğini belirliyoruz (Ağırlıklı Oran).
    # Bu örnekte: Tas %40, Kagit %30, Makas %30 ihtimalle gelir.
    oranlar = [0.33, 0.33, 0.33]
    
    # Skorları takip etmek için değişkenlerimizi (integer) 0 olarak başlatıyoruz.
    kullanici_skor = 0
    bilgisayar_skor = 0
    toplam_tur = 3  # Oyunun kaç tur süreceğini burada belirliyoruz.

    print("--- 3 Tur Üzerinden Taş-Kağıt-Makas Başlıyor! akıllıca oyna ---")

    # range(1, 4) fonksiyonu 1, 2 ve 3 değerlerini döndürerek döngüyü 3 kez çalıştırır.
    for tur in range(1, toplam_tur + 1):
        
        # --- KRİTİK NOKTA: Bilgisayar, kullanıcı hamlesini girmeden seçimini yapar. ---
        # random.choices: Belirlediğimiz 'oranlar' (weights) doğrultusunda rastgele seçim yapar.
        # k=1 tek bir seçim yapmasını sağlar, [0] ise sonucu liste dışına çıkarır.
        bilgisayar_secimi = random.choices(secenekler, weights=oranlar, k=1)[0]

        print(f"\n--- {tur}. TUR ---")
        
        # Kullanıcıdan girdi alıyoruz. .lower() ile tüm harfleri küçültüp hata payını azaltıyoruz.
        kullanici = input("Hamleni yap (taş, kağıt, makas): ").lower()

        # Doğrulama Döngüsü: Kullanıcı yanlış kelime girerse doğru girene kadar sormaya devam eder.
        while kullanici not in secenekler:
            kullanici = input("Hatalı giriş! Lütfen sadece 'taş', 'kağıt' veya 'makas' yazın: ").lower()

        # Sonuçların açıklanma aşamasına bir bekleme efekti ekleyerek "hız ve heyecan" katıyoruz.
        print("Bilgisayarın seçimi açıklanıyor...")
        time.sleep(0.1) # 0.4 saniye bekleme (hızlı ama fark edilebilir).
        
        print(f"Senin seçimin: {kullanici.upper()}")
        print(f"Bilgisayarın seçimi: {bilgisayar_secimi.upper()}")

        # KAZANMA/KAYBETME MANTIĞI:
        if kullanici == bilgisayar_secimi:
            print(">> Sonuç: Berabere!")
        elif (kullanici == "taş" and bilgisayar_secimi == "makas") or \
             (kullanici == "kağıt" and bilgisayar_secimi == "taş") or \
             (kullanici == "makas" and bilgisayar_secimi == "kağıt"):
            # Kullanıcı kazandığında kendi skoruna 1 puan ekler.
            print(">> Sonuç: Aferin lan kazandın!")
            kullanici_skor += 1
        else:
            # Bilgisayar kazandığında onun skoruna 1 puan ekler.
            print(">> Sonuç: Büyüde gel!")
            bilgisayar_skor += 1
            
        # Her tur sonu güncel skoru f-string kullanarak ekrana yazdırıyoruz.
        print(f"Skor Durumu -> Sen: {kullanici_skor} | Bilgisayar: {bilgisayar_skor}")

    # --- OYUN SONU: 3 tur bittiğinde genel kazananı ilan ediyoruz. ---
    print("\n" + "="*40)
    print("OYUN SONA ERDİ")
    if kullanici_skor > bilgisayar_skor:
        print(f"TEBRİKLER! {kullanici_skor}-{bilgisayar_skor} hadi hadi şans eseri kazandın.")
    elif bilgisayar_skor > kullanici_skor:
        print(f"MAALESEF! {bilgisayar_skor}-{kullanici_skor} Git büyüde gel lan")
    else:
        print(f"BERABERE! Skor: {kullanici_skor}-{bilgisayar_skor} İdare edersin.")
    print("="*40)

# Programın doğrudan çalıştırılması durumunda ana fonksiyonu çağırıyoruz.
if __name__ == "__main__":
    uclu_oyun()