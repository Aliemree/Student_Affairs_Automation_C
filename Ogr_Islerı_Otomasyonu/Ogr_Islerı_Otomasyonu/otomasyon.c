#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void BolumIslemleri()
{
    // Bölüm işlemleri burada olacak
}
void NotIslemleri()
{
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
