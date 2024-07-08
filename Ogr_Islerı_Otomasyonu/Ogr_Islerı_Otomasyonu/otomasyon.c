#include <stdio.h>
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

void OgretimGorevlisiIslemleri()
{
    // Öğretim görevlisi işlemleri burada olacak
}

void DersIslemleri()
{
    // Ders işlemleri burada olacak
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
void NotIslemleri()
{
    printf("Hello world");
    // Not işlemleri burada olacak
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
