﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bolum
{
    int BolumID;
    char bolumAd[30];
} bolum;
typedef struct kisi
{
    int numara;
    char tc[12], adsoyad[30], dTarih[30], dYeri[30];
    char cinsiyet;
    char adres[30], tel[30], ePosta[30];
    int askerlikDurumu, bolumID, durum; //durum=1 ise aktif ogrenci, silinmiş=0,mezun=2
} ogr;
typedef struct ogretimGorevlisi
{
    int numara;
    char tc[12], adsoyad[30], dTarih[30], dYeri[30];
    char cinsiyet;
    char adres[30], tel[30], ePosta[30];
    int bolumID, durum; //durum=1 ise aktif, silinmiş=0
} ogretimGorevlisi;
typedef struct ders
{
    int dersID;
    char dersAd[30];
    int kredi;
} ders;
typedef struct not {
    int ogrenciID;
    int dersID;
    int notDegeri;
} notKaydi;

void notEkle();
void notSil();
void notAra();
void notListele();

void BolumListele();
void Transkript();
void ogrencimezuniyeti();
void ogrenciekle();
void ogrenciekle()
{
    system("cls");
    printf("Ogrenci Ekleme Islemi..\n");
    ogr o1;

    FILE* numptr;
    if (fopen_s(&numptr, "ogrenciNumaralari.dat", "a+b") != 0) {
        perror("File opening failed");
        return;
    }
    int numara = 0;
    while (fread(&numara, sizeof(int), 1, numptr)) {
        // Dosyadan son numarayı okuyun
    }
    numara += 1;
    o1.numara = numara;
    fwrite(&numara, sizeof(int), 1, numptr);
    fclose(numptr);

    printf("TC: ");
    getchar(); // Önceki girişten kalan newline karakterini tüketir
    fgets(o1.tc, sizeof(o1.tc), stdin);
    o1.tc[strcspn(o1.tc, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("AD SOYAD: ");
    fgets(o1.adsoyad, sizeof(o1.adsoyad), stdin);
    o1.adsoyad[strcspn(o1.adsoyad, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("DOGUM TARIHI: ");
    fgets(o1.dTarih, sizeof(o1.dTarih), stdin);
    o1.dTarih[strcspn(o1.dTarih, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("DOGUM YERI: ");
    fgets(o1.dYeri, sizeof(o1.dYeri), stdin);
    o1.dYeri[strcspn(o1.dYeri, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("CINSIYET (E/K): ");
    o1.cinsiyet = getchar();
    getchar(); // Newline karakterini kaldırır

    printf("ADRES: ");
    fgets(o1.adres, sizeof(o1.adres), stdin);
    o1.adres[strcspn(o1.adres, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("TELEFON NO: ");
    fgets(o1.tel, sizeof(o1.tel), stdin);
    o1.tel[strcspn(o1.tel, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("E-POSTA: ");
    fgets(o1.ePosta, sizeof(o1.ePosta), stdin);
    o1.ePosta[strcspn(o1.ePosta, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("ASKERLIK DURUMU (1: Tamam, 0: Tamam Degil): ");
    scanf_s("%d", &o1.askerlikDurumu);

    BolumListele();

    printf("BOLUM NUMARASI: ");
    scanf_s("%d", &o1.bolumID);

    FILE* ptr;
    if (fopen_s(&ptr, "ogrenciler.dat", "a+b") != 0) {
        perror("File opening failed");
        return;
    }
    fwrite(&o1, sizeof(ogr), 1, ptr);
    fclose(ptr);

    printf("%d Numarali Ogrenci Kaydi Tamam...\n", numara);
}
void ogrencisil()
{
    system("cls");
    printf("Ogrenci Silme Islemi..\n");
    int numara;
    printf("Silinecek Ogrenci Numarasi: ");
    scanf_s("%d", &numara);

    FILE* ptr;
    FILE* temp;
    if (fopen_s(&ptr, "ogrenciler.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }
    if (fopen_s(&temp, "temp.dat", "wb") != 0) {
        perror("File opening failed");
        return;
    }

    ogr o1;
    int found = 0;
    while (fread(&o1, sizeof(ogr), 1, ptr)) {
        if (o1.numara == numara) {
            found = 1;
            o1.durum = 0; // Durumu silinmiş olarak güncelle
        }
        fwrite(&o1, sizeof(ogr), 1, temp);
    }

    fclose(ptr);
    fclose(temp);

    remove("ogrenciler.dat");
    rename("temp.dat", "ogrenciler.dat");

    if (found) {
        printf("%d Numarali Ogrenci Basariyla Silindi.\n", numara);
    }
    else {
        printf("Ogrenci bulunamadi.\n");
    }
}
void ogrenciara()
{
    system("cls");
    printf("Ogrenci Arama Islemi..\n");
    int numara;
    printf("Aranacak Ogrenci Numarasi: ");
    scanf_s("%d", &numara);

    FILE* ptr;
    if (fopen_s(&ptr, "ogrenciler.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    ogr o1;
    int found = 0;
    while (fread(&o1, sizeof(ogr), 1, ptr)) {
        if (o1.numara == numara) {
            found = 1;
            printf("Numara: %d\n", o1.numara);
            printf("TC: %s\n", o1.tc);
            printf("Ad Soyad: %s\n", o1.adsoyad);
            printf("Dogum Tarihi: %s\n", o1.dTarih);
            printf("Dogum Yeri: %s\n", o1.dYeri);
            printf("Cinsiyet: %c\n", o1.cinsiyet);
            printf("Adres: %s\n", o1.adres);
            printf("Telefon No: %s\n", o1.tel);
            printf("E-Posta: %s\n", o1.ePosta);
            printf("Askerlik Durumu: %d\n", o1.askerlikDurumu);
            printf("Bolum ID: %d\n", o1.bolumID);
            printf("Durum: %d\n", o1.durum);
            break;
        }
    }

    if (!found) {
        printf("Ogrenci bulunamadi.\n");
    }

    fclose(ptr);
}
void ogrencilistele()
{
    system("cls");
    printf("Ogrenci Listeleme Islemi..\n");

    FILE* ptr;
    if (fopen_s(&ptr, "ogrenciler.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    ogr o1;
    printf("Numara         | TC            | Ad Soyad         | Dogum Tarihi | Dogum Yeri | Cinsiyet | Adres    | Telefon No | E-Posta   | Askerlik Durumu | Bolum ID | Durum\n");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    while (fread(&o1, sizeof(ogr), 1, ptr)) {
        printf("%6d | %-9s | %-10s | %-12s | %-10s | %-8c | %-13s | %-8s | %-15s | %-10d | %-8d | %-5d\n",
            o1.numara, o1.tc, o1.adsoyad, o1.dTarih, o1.dYeri, o1.cinsiyet, o1.adres, o1.tel, o1.ePosta, o1.askerlikDurumu, o1.bolumID, o1.durum);
    }

    fclose(ptr);
}
void ogrencibelgesi()
{
    system("cls");
    printf("Ogrenci Belgesi Islemi..\n");
    int numara;
    printf("Belgesi Alinacak Ogrenci Numarasi: ");
    scanf_s("%d", &numara);

    FILE* ptr;
    if (fopen_s(&ptr, "ogrenciler.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    ogr o1;
    int found = 0;
    while (fread(&o1, sizeof(ogr), 1, ptr)) {
        if (o1.numara == numara) {
            found = 1;
            printf("\nOGRENCI BELGESI\n");
            printf("Numara: %d\n", o1.numara);
            printf("TC: %s\n", o1.tc);
            printf("Ad Soyad: %s\n", o1.adsoyad);
            printf("Dogum Tarihi: %s\n", o1.dTarih);
            printf("Dogum Yeri: %s\n", o1.dYeri);
            printf("Cinsiyet: %c\n", o1.cinsiyet);
            printf("Adres: %s\n", o1.adres);
            printf("Telefon No: %s\n", o1.tel);
            printf("E-Posta: %s\n", o1.ePosta);
            printf("Askerlik Durumu: %d\n", o1.askerlikDurumu);
            printf("Bolum ID: %d\n", o1.bolumID);
            printf("Durum: %d\n", o1.durum);
            break;
        }
    }

    if (!found) {
        printf("Ogrenci bulunamadi.\n");
    }

    fclose(ptr);
}
void Transkript()
{
    system("cls");
    printf("Transkript Islemi..\n");
    int numara;
    printf("Transkripti Alinacak Ogrenci Numarasi: ");
    scanf_s("%d", &numara);

    // Transkript bilgileri burada olacak
    // Örnek olarak, sadece temel bilgileri gösteriyoruz
    FILE* ptr;
    if (fopen_s(&ptr, "ogrenciler.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    ogr o1;
    int found = 0;
    while (fread(&o1, sizeof(ogr), 1, ptr)) {
        if (o1.numara == numara) {
            found = 1;
            printf("\nTRANSKRIPT\n");
            printf("Numara: %d\n", o1.numara);
            printf("TC: %s\n", o1.tc);
            printf("Ad Soyad: %s\n", o1.adsoyad);
            printf("Dogum Tarihi: %s\n", o1.dTarih);
            printf("Dogum Yeri: %s\n", o1.dYeri);
            printf("Cinsiyet: %c\n", o1.cinsiyet);
            printf("Adres: %s\n", o1.adres);
            printf("Telefon No: %s\n", o1.tel);
            printf("E-Posta: %s\n", o1.ePosta);
            printf("Askerlik Durumu: %d\n", o1.askerlikDurumu);
            printf("Bolum ID: %d\n", o1.bolumID);
            printf("Durum: %d\n", o1.durum);
            // Daha fazla bilgi ekleyebilirsiniz
            break;
        }
    }

    if (!found) {
        printf("Ogrenci bulunamadi.\n");
    }

    fclose(ptr);
}
void ogrencimezuniyeti()
{
    system("cls");
    printf("Ogrenci Mezuniyet Islemi..\n");
    int numara;
    printf("Mezuniyet Islemi Yapilacak Ogrenci Numarasi: ");
    scanf_s("%d", &numara);

    FILE* ptr;
    FILE* temp;
    if (fopen_s(&ptr, "ogrenciler.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }
    if (fopen_s(&temp, "temp.dat", "wb") != 0) {
        perror("File opening failed");
        return;
    }

    ogr o1;
    int found = 0;
    while (fread(&o1, sizeof(ogr), 1, ptr)) {
        if (o1.numara == numara) {
            found = 1;
            o1.durum = 2; // Durumu mezun olarak güncelle
        }
        fwrite(&o1, sizeof(ogr), 1, temp);
    }

    fclose(ptr);
    fclose(temp);

    remove("ogrenciler.dat");
    rename("temp.dat", "ogrenciler.dat");

    if (found) {
        printf("%d Numarali Ogrenci Basariyla Mezun Edildi.\n", numara);
    }
    else {
        printf("Ogrenci bulunamadi.\n");
    }
}
int Ogrencimenu()
{
    int secim;
    printf("\n\tOGRENCI ISLERI ...\n\n");
    printf("--------------------------------------------------\n");
    printf("\n\t1-OGRENCI EKLE\n");
    printf("\n\t2-OGRENCI SIL\n");
    printf("\n\t3-OGRENCI ARA\n");
    printf("\n\t4-OGRENCI LISTELE\n");
    printf("\n\t5-OGRENCI BELGESI\n");
    printf("\n\t6-TRANSKRIPT\n");
    printf("\n\t7-OGRENCI MEZUNIYETI\n");
    printf("\n\t0-PROGRAMI KAPAT \n");
    printf("\n\t Seciminiz : ");
    scanf_s("%d", &secim);
    system("cls");
    return secim;
}
void OgrenciIslemleri()
{
    int secim = Ogrencimenu();
    while (secim != 0)
    {
        switch (secim)
        {
        case 1: ogrenciekle();
            break;
        case 2: ogrencisil();
            break;
        case 3: ogrenciara();
            break;
        case 4: ogrencilistele();
            break;
        case 5: ogrencibelgesi();
            break;
        case 6: Transkript();
            break;
        case 7: ogrencimezuniyeti();
            break;
        case 0:
            break;
        default: printf("Hatali Seçim Yaptiniz !\n");
        }
        secim = Ogrencimenu();
    }
    printf("Bolum Islemlerinden Cikis Yapiliyor !!");
}
void ogretimGorevlisiEkle()
{
    system("cls");
    printf("Ogretim Gorevlisi Ekleme Islemi..\n");
    ogretimGorevlisi o1;

    FILE* numptr;
    if (fopen_s(&numptr, "ogretimGorevlisiNumaralari.dat", "a+b") != 0) {
        perror("File opening failed");
        return;
    }
    int numara = 0;
    while (fread(&numara, sizeof(int), 1, numptr)) {
        // Dosyadan son numarayı okuyun
    }
    numara += 1;
    o1.numara = numara;
    fwrite(&numara, sizeof(int), 1, numptr);
    fclose(numptr);

    printf("TC: ");
    getchar(); // Önceki girişten kalan newline karakterini tüketir
    fgets(o1.tc, sizeof(o1.tc), stdin);
    o1.tc[strcspn(o1.tc, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("AD SOYAD: ");
    fgets(o1.adsoyad, sizeof(o1.adsoyad), stdin);
    o1.adsoyad[strcspn(o1.adsoyad, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("DOGUM TARIHI: ");
    fgets(o1.dTarih, sizeof(o1.dTarih), stdin);
    o1.dTarih[strcspn(o1.dTarih, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("DOGUM YERI: ");
    fgets(o1.dYeri, sizeof(o1.dYeri), stdin);
    o1.dYeri[strcspn(o1.dYeri, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("CINSIYET (E/K): ");
    o1.cinsiyet = getchar();
    getchar(); // Newline karakterini kaldırır

    printf("ADRES: ");
    fgets(o1.adres, sizeof(o1.adres), stdin);
    o1.adres[strcspn(o1.adres, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("TELEFON NO: ");
    fgets(o1.tel, sizeof(o1.tel), stdin);
    o1.tel[strcspn(o1.tel, "\n")] = '\0'; // Newline karakterini kaldırır

    printf("E-POSTA: ");
    fgets(o1.ePosta, sizeof(o1.ePosta), stdin);
    o1.ePosta[strcspn(o1.ePosta, "\n")] = '\0'; // Newline karakterini kaldırır

    BolumListele();

    printf("BOLUM NUMARASI: ");
    scanf_s("%d", &o1.bolumID);

    FILE* ptr;
    if (fopen_s(&ptr, "ogretimGorevlileri.dat", "a+b") != 0) {
        perror("File opening failed");
        return;
    }
    fwrite(&o1, sizeof(ogretimGorevlisi), 1, ptr);
    fclose(ptr);

    printf("%d Numarali Ogretim Gorevlisi Kaydi Tamam...\n", numara);
}
void ogretimGorevlisiSil()
{
    system("cls");
    printf("Ogretim Gorevlisi Silme Islemi..\n");
    int numara;
    printf("Silinecek Ogretim Gorevlisi Numarasi: ");
    scanf_s("%d", &numara);

    FILE* ptr;
    FILE* temp;
    if (fopen_s(&ptr, "ogretimGorevlileri.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }
    if (fopen_s(&temp, "temp.dat", "wb") != 0) {
        perror("File opening failed");
        return;
    }

    ogretimGorevlisi o1;
    int found = 0;
    while (fread(&o1, sizeof(ogretimGorevlisi), 1, ptr)) {
        if (o1.numara == numara) {
            found = 1;
            o1.durum = 0; // Durumu silinmiş olarak güncelle
        }
        fwrite(&o1, sizeof(ogretimGorevlisi), 1, temp);
    }

    fclose(ptr);
    fclose(temp);

    remove("ogretimGorevlileri.dat");
    rename("temp.dat", "ogretimGorevlileri.dat");

    if (found) {
        printf("%d Numarali Ogretim Gorevlisi Basariyla Silindi.\n", numara);
    }
    else {
        printf("Ogretim Gorevlisi bulunamadi.\n");
    }
}
void ogretimGorevlisiAra()
{
    system("cls");
    printf("Ogretim Gorevlisi Arama Islemi..\n");
    int numara;
    printf("Aranacak Ogretim Gorevlisi Numarasi: ");
    scanf_s("%d", &numara);

    FILE* ptr;
    if (fopen_s(&ptr, "ogretimGorevlileri.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    ogretimGorevlisi o1;
    int found = 0;
    while (fread(&o1, sizeof(ogretimGorevlisi), 1, ptr)) {
        if (o1.numara == numara) {
            found = 1;
            printf("Numara: %d\n", o1.numara);
            printf("TC: %s\n", o1.tc);
            printf("Ad Soyad: %s\n", o1.adsoyad);
            printf("Dogum Tarihi: %s\n", o1.dTarih);
            printf("Dogum Yeri: %s\n", o1.dYeri);
            printf("Cinsiyet: %c\n", o1.cinsiyet);
            printf("Adres: %s\n", o1.adres);
            printf("Telefon No: %s\n", o1.tel);
            printf("E-Posta: %s\n", o1.ePosta);
            printf("Bolum ID: %d\n", o1.bolumID);
            printf("Durum: %d\n", o1.durum);
            break;
        }
    }

    if (!found) {
        printf("Ogretim Gorevlisi bulunamadi.\n");
    }

    fclose(ptr);
}
void ogretimGorevlisiListele()
{
    system("cls");
    printf("Ogretim Gorevlisi Listeleme Islemi..\n");

    FILE* ptr;
    if (fopen_s(&ptr, "ogretimGorevlileri.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    ogretimGorevlisi o1;
    while (fread(&o1, sizeof(ogretimGorevlisi), 1, ptr)) {
        printf("Numara: %d\n", o1.numara);
        printf("TC: %s\n", o1.tc);
        printf("Ad Soyad: %s\n", o1.adsoyad);
        printf("Dogum Tarihi: %s\n", o1.dTarih);
        printf("Dogum Yeri: %s\n", o1.dYeri);
        printf("Cinsiyet: %c\n", o1.cinsiyet);
        printf("Adres: %s\n", o1.adres);
        printf("Telefon No: %s\n", o1.tel);
        printf("E-Posta: %s\n", o1.ePosta);
        printf("Bolum ID: %d\n", o1.bolumID);
        printf("Durum: %d\n\n", o1.durum);
    }

    fclose(ptr);
}
void OgretimGorevlisiIslemleri()
{
    while (1)
    {
        int secim = OgretimGorevlisiMenu();
        switch (secim)
        {
        case 1:
            ogretimGorevlisiEkle();
            break;
        case 2:
            ogretimGorevlisiSil();
            break;
        case 3:
            ogretimGorevlisiAra();
            break;
        case 4:
            ogretimGorevlisiListele();
            break;
        case 5:
            return;
        default:
            printf("Hatali Secim. Tekrar deneyin.\n");
            break;
        }
    }
}
int OgretimGorevlisiMenu()
{
    printf("OGRETIM GOREVLISI ISLEMLERI\n");
    printf("1. Ogretim Gorevlisi Ekle\n");
    printf("2. Ogretim Gorevlisi Sil\n");
    printf("3. Ogretim Gorevlisi Ara\n");
    printf("4. Ogretim Gorevlisi Listele\n");
    printf("5. Ana Menuye Don\n");
    printf("Seciminiz: ");
    int secim;
    scanf_s("%d", &secim);
    return secim;
}
void dersEkle();
void dersSil();
void dersAra();
void dersListele();
void DersIslemleri()
{
    int secim;

    do
    {
        printf("\n Ders Islemleri\n");
        printf("1. Ders Ekle\n");
        printf("2. Ders Sil\n");
        printf("3. Ders Ara\n");
        printf("4. Ders Listele\n");
        printf("0. Ana Menuye Don\n");
        printf("Seçiminiz: ");
        scanf_s("%d", &secim);

        switch (secim)
        {
        case 1:
            dersEkle();
            break;
        case 2:
            dersSil();
            break;
        case 3:
            dersAra();
            break;
        case 4:
            dersListele();
            break;
        case 0:
            printf("Ana menüye dönülüyor...\n");
            break;
        default:
            printf("Gecersiz secim! Tekrar deneyin.\n");
            break;
        }
    } while (secim != 0);
}
void dersEkle()
{
    system("cls");
    printf("Ders Ekleme Islemi..\n");

    // Ders yapısını tanımlayın
    typedef struct ders
    {
        int dersID;
        char dersAd[30];
        int kredi;
    } ders;

    ders d1;

    // Ders adı
    printf("Ders Adi: ");
    getchar(); // Önceki girişten kalan newline karakterini tüketir
    fgets(d1.dersAd, sizeof(d1.dersAd), stdin);
    d1.dersAd[strcspn(d1.dersAd, "\n")] = '\0'; // Newline karakterini kaldırır

    // Ders kredisi
    printf("Kredi: ");
    scanf_s("%d", &d1.kredi);

    // Dosyadan son ders numarasını okuyun ve yeni ders numarasını ayarlayın
    FILE* numptr;
    if (fopen_s(&numptr, "dersNumaralari.dat", "a+b") != 0) {
        perror("File opening failed");
        return;
    }
    int numara = 0;
    while (fread(&numara, sizeof(int), 1, numptr)) {
        // Dosyadan son numarayı okuyun
    }
    numara += 1;
    fwrite(&numara, sizeof(int), 1, numptr);
    fclose(numptr);
    d1.dersID = numara;

    // Yeni dersi dosyaya yazın
    FILE* ptr;
    if (fopen_s(&ptr, "dersler.dat", "a+b") != 0) {
        perror("File opening failed");
        return;
    }
    fwrite(&d1, sizeof(ders), 1, ptr);
    fclose(ptr);

    printf("%d Numarali Ders Kaydi Tamam...\n", numara);
}
void dersSil()
{
    system("cls");
    printf("Ders Silme Islemi..\n");
    int dersID;
    printf("Silinecek Ders Numarasi: ");
    scanf_s("%d", &dersID);

    FILE* ptr;
    FILE* temp;
    if (fopen_s(&ptr, "dersler.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }
    if (fopen_s(&temp, "temp.dat", "wb") != 0) {
        perror("File opening failed");
        return;
    }

    typedef struct ders
    {
        int dersID;
        char dersAd[30];
        int kredi;
    } ders;

    ders d1;
    int found = 0;
    while (fread(&d1, sizeof(ders), 1, ptr)) {
        if (d1.dersID == dersID) {
            found = 1;
        }
        else {
            fwrite(&d1, sizeof(ders), 1, temp);
        }
    }

    fclose(ptr);
    fclose(temp);

    remove("dersler.dat");
    rename("temp.dat", "dersler.dat");

    if (found) {
        printf("%d Numarali Ders Basariyla Silindi.\n", dersID);
    }
    else {
        printf("Ders bulunamadi.\n");
    }
}
void dersAra()
{
    system("cls");
    printf("Ders Arama Islemi..\n");
    int dersID;
    printf("Aranacak Ders Numarasi: ");
    scanf_s("%d", &dersID);

    FILE* ptr;
    if (fopen_s(&ptr, "dersler.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    typedef struct ders
    {
        int dersID;
        char dersAd[30];
        int kredi;
    } ders;

    ders d1;
    int found = 0;
    while (fread(&d1, sizeof(ders), 1, ptr)) {
        if (d1.dersID == dersID) {
            found = 1;
            printf("Ders ID: %d\n", d1.dersID);
            printf("Ders Adi: %s\n", d1.dersAd);
            printf("Kredi: %d\n", d1.kredi);
            break;
        }
    }

    if (!found) {
        printf("Ders bulunamadi.\n");
    }

    fclose(ptr);
}
void dersListele()
{
    system("cls");
    printf("Ders Listeleme Islemi..\n");

    FILE* ptr;
    if (fopen_s(&ptr, "dersler.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    ders d1;
    printf("Ders ID   | Ders Adi                     | Kredi\n");
    printf("-------------------------------------------------\n");
    while (fread(&d1, sizeof(ders), 1, ptr)) {
        printf("%-10d | %-30s | %d\n", d1.dersID, d1.dersAd, d1.kredi);
    }

    fclose(ptr);
}


void NotIslemleri()
{
    // Not işlemleri burada olacak
    int secim;

    do {
        system("cls");
        printf("1. Not Ekle\n");
        printf("2. Not Sil\n");
        printf("3. Not Ara\n");
        printf("4. Not Listele\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf_s("%d", &secim);

        switch (secim) {
        case 1:
            notEkle();
            break;
        case 2:
            notSil();
            break;
        case 3:
            notAra();
            break;
        case 4:
            notListele();
            break;
        }
    } while (secim != 0);
}

void notEkle()
{
    system("cls");
    printf("Not Ekleme Islemi..\n");

    notKaydi yeniNot;

    // Öğrenci ID
    printf("Ogrenci ID: ");
    scanf_s("%d", &yeniNot.ogrenciID);

    // Ders ID
    printf("Ders ID: ");
    scanf_s("%d", &yeniNot.dersID);

    // Not değeri
    printf("Not Degeri: ");
    scanf_s("%d", &yeniNot.notDegeri);

    // Yeni notu dosyaya yazın
    FILE* ptr;
    if (fopen_s(&ptr, "notlar.dat", "a+b") != 0) {
        perror("File opening failed");
        return;
    }
    fwrite(&yeniNot, sizeof(notKaydi), 1, ptr);
    fclose(ptr);

    printf("Not Kaydi Tamam...\n");
}

void notSil()
{
    system("cls");
    printf("Not Silme Islemi..\n");
    int ogrenciID, dersID;
    printf("Silinecek Notun Ogrenci ID'si: ");
    scanf_s("%d", &ogrenciID);
    printf("Silinecek Notun Ders ID'si: ");
    scanf_s("%d", &dersID);

    FILE* ptr;
    FILE* temp;
    if (fopen_s(&ptr, "notlar.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }
    if (fopen_s(&temp, "temp.dat", "wb") != 0) {
        perror("File opening failed");
        return;
    }

    notKaydi n;
    int found = 0;
    while (fread(&n, sizeof(notKaydi), 1, ptr)) {
        if (n.ogrenciID == ogrenciID && n.dersID == dersID) {
            found = 1;
        }
        else {
            fwrite(&n, sizeof(notKaydi), 1, temp);
        }
    }

    fclose(ptr);
    fclose(temp);

    remove("notlar.dat");
    rename("temp.dat", "notlar.dat");

    if (found) {
        printf("Not Basariyla Silindi.\n");
    }
    else {
        printf("Not bulunamadi.\n");
    }
}

void notAra()
{
    system("cls");
    printf("Not Arama Islemi..\n");
    int ogrenciID, dersID;
    printf("Aranacak Notun Ogrenci ID'si: ");
    scanf_s("%d", &ogrenciID);
    printf("Aranacak Notun Ders ID'si: ");
    scanf_s("%d", &dersID);

    FILE* ptr;
    if (fopen_s(&ptr, "notlar.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    notKaydi n;
    int found = 0;
    while (fread(&n, sizeof(notKaydi), 1, ptr)) {
        if (n.ogrenciID == ogrenciID && n.dersID == dersID) {
            found = 1;
            printf("Ogrenci ID: %d\n", n.ogrenciID);
            printf("Ders ID: %d\n", n.dersID);
            printf("Not Degeri: %d\n", n.notDegeri);
            break;
        }
    }

    if (!found) {
        printf("Not bulunamadi.\n");
    }

    fclose(ptr);
}

void notListele()
{
    system("cls");
    printf("Not Listeleme Islemi..\n");

    FILE* ptr;
    if (fopen_s(&ptr, "notlar.dat", "rb") != 0) {
        perror("File opening failed");
        return;
    }

    notKaydi n;
    printf("Ogrenci ID | Ders ID   | Not Degeri\n");
    printf("----------------------------------\n");
    while (fread(&n, sizeof(notKaydi), 1, ptr)) {
        printf("%-10d | %-8d | %d\n", n.ogrenciID, n.dersID, n.notDegeri);
    }

    fclose(ptr);
}

void BolumEkle()
{
    system("cls");
    printf("Bolum Ekleme Islemi..\n");
    bolum b1;
    printf("Bolum Adi : ");
    getchar(); // Önceki girişten kalan newline karakterini tüketir
    fgets(b1.bolumAd, sizeof(b1.bolumAd), stdin);
    b1.bolumAd[strcspn(b1.bolumAd, "\n")] = '\0'; // Newline karakterini kaldırır

    FILE* numptr;
    if (fopen_s(&numptr, "bolumNumaralari.dat", "a+b") != 0) {
        perror("File opening failed");
        return;
    }
    int numara = 0;
    while (fread(&numara, sizeof(int), 1, numptr)) {
        // Dosyadan son numarayı okuyun
    }
    numara += 1;
    fwrite(&numara, sizeof(int), 1, numptr);
    fclose(numptr);
    b1.BolumID = numara;

    FILE* ptr;
    if (fopen_s(&ptr, "bolumler.dat", "a+b") != 0) {
        perror("File opening failed");
        return;
    }
    fwrite(&b1, sizeof(bolum), 1, ptr);
    fclose(ptr);

    printf("%d Numarali Bolum Kaydi Tamam...\n", numara);
}

void BolumListele()
{
    system("cls");
    printf("Bolum Listeleme Islemi..\n");
    bolum b1;

    FILE* ptr;
    if (fopen_s(&ptr, "bolumler.dat", "r+b") != 0) {
        perror("File opening failed");
        return;
    }

    printf("%-20s%-30s\n", "BOLUM_ID", "BOLUM_ADI");
    printf("--------------------------------------------------\n");

    while (fread(&b1, sizeof(bolum), 1, ptr)) {
        printf("%-20d%-30s\n", b1.BolumID, b1.bolumAd);
    }

    fclose(ptr);
}


int BolumMenu()
{
    int secim;

    printf("\n\t BOLUM ISLEMLERI...\n\n");
    printf("--------------------------------------------------\n");
    printf("\n\t1-Bolum Ekle\n");
    printf("\n\t2-Bolum Listele\n");
    printf("\n\t0-PROGRAMI KAPAT \n");
    printf("\n\t Seciminiz : ");
    scanf_s("%d", &secim);
    system("cls");
    return secim;
}
void BolumIslemleri()
{
    int secim = BolumMenu();
    while (secim != 0)
    {
        switch (secim)
        {
        case 1: BolumEkle();
            break;
        case 2: BolumListele();
         
            break;
        case 0:
            break;
        default: printf("Hatali Seçim Yaptiniz !\n");
        }
        secim = BolumMenu();
        
    }
    printf("Bolum Islemlerinden Cikis Yapiliyor !!");
    return 0;
}

int menu()
{
    int secim;
    printf("\n\tOGRENCI ISLERI OTOMASYONU\n\n");
    printf("--------------------------------------------------\n");
    printf("\n\t1-OGRENCI ISLEMLERI\n");
    printf("\n\t2-OGRETIM GOREVLISI ISLEMLERI\n");
    printf("\n\t3-DERS ISLEMLERI\n");
    printf("\n\t4-BOLUM ISLEMLERI\n");
    printf("\n\t5-NOT ISLEMLERI\n");
    printf("\n\t0-PROGRAMI KAPAT \n");
    printf("\n\t Seciminiz : ");
    scanf_s("%d", &secim);  
    return secim; 
}
int main()
{
    int secim = menu();
    while (secim != 0)
    {
        switch (secim)
        {
        case 1: OgrenciIslemleri();
            break;
        case 2: OgretimGorevlisiIslemleri();
            break;
        case 3: DersIslemleri();
            break;
        case 4: BolumIslemleri();
            break;
        case 5: NotIslemleri();
            break;
        case 0:
            break;

        default: printf("Hatali Seçim Yaptiniz !\n");
        }
        secim = menu();
    }
    printf("Programiniz Kapatiliyor!!");
    return 0;
}
