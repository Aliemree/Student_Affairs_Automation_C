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
    // Öğrenci silme işlemleri burada olacak
}

void ogrenciara()
{
    // Öğrenci arama işlemleri burada olacak
}

void ogrencilistele()
{
    // Öğrenci listeleme işlemleri burada olacak
}

void ogrencibelgesi()
{
    // Öğrenci belgesi işlemleri burada olacak
}

void Transkript()
{
    // Transkript işlemleri burada olacak
}

void ogrencimezuniyeti()
{
    // Öğrenci mezuniyet işlemleri burada olacak
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
