#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bolum
{
    int BolumID;
    char bolumAd[30];
} bolum;

void OgrenciIslemleri()
{
    // Öğrenci işlemleri burada olacak
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
    printf("\n\t1-Bolum Ekle\n");
    printf("\n\t2-Bolum Listele\n");
    printf("\n\t0-PROGRAMI KAPAT \n");
    printf("\n\t Seciminiz : ");
    scanf_s("%d", &secim);
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
