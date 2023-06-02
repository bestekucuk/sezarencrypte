#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ogrenci {
    char ad[50];
    char soyad[50];
    char numara[50];
    char parola[50];
    int shift;
};

void shiftRight(char *str, int shift) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = 'A' + (str[i] - 'A' + shift) % 26;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = 'a' + (str[i] - 'a' + shift) % 26;
        }
    }
}

void shiftLeft(char *str, int shift) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = 'A' + (str[i] - 'A' - shift + 26) % 26;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = 'a' + (str[i] - 'a' - shift + 26) % 26;
        }
    }
}

void writeToFile(const char *filename, const char *text) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Dosya oluşturulamadı.");
        return;
    }

    fprintf(file, "%s", text);
    fclose(file);
}

void readFromFile(const char *filename, char *text, int max_length) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı.");
        return;
    }

    fgets(text, max_length, file);
    fclose(file);
}

int findLargestPrimeFactor(int number) {
    int largestPrimeFactor = 0;

    while (number % 2 == 0) {
        largestPrimeFactor = 2;
        number /= 2;
    }

    for (int i = 3; i * i <= number; i += 2) {
        while (number % i == 0) {
            largestPrimeFactor = i;
            number /= i;
        }
    }

    if (number > 2) {
        largestPrimeFactor = number;
    }

    return largestPrimeFactor;
}

int main() {
    struct Ogrenci ogrenci;

    printf("Ad: ");
    scanf("%s", ogrenci.ad);

    printf("Soyad: ");
    scanf("%s", ogrenci.soyad);

    printf("Öğrenci numaranız nedir?  ");
    scanf("%s", ogrenci.numara);

    printf("Öğrenci numaranızın en büyük asal çarpanı nedir? ");
    scanf("%s", ogrenci.parola);

    ogrenci.shift = (ogrenci.numara[strlen(ogrenci.numara) - 1] - '0');
    if (ogrenci.numara[strlen(ogrenci.numara) - 1] == '0') {
        ogrenci.shift = ogrenci.numara[strlen(ogrenci.numara) - 2] - '0';
    }

    int sayi = atoi(ogrenci.numara);
    int a = findLargestPrimeFactor(sayi);

    if (atoi(ogrenci.parola) != a) {
        printf("Hatalı bir parola girdiniz. Lütfen tekrar deneyin.\n");
        return 0;
    }

    char sifrelenen_metin[150];
    strcpy(sifrelenen_metin, ogrenci.ad);
    strcat(sifrelenen_metin, ogrenci.soyad);
    shiftRight(sifrelenen_metin, ogrenci.shift);

    writeToFile("sifrelimetin.txt", sifrelenen_metin);

    printf("Metin şifrelendi ve 'sifrelimetin.txt' dosyasına yazıldı.\n");
    printf("Şifreli Metin: %s\n", sifrelenen_metin);

    char okunan_metin[150];
    readFromFile("sifrelimetin.txt", okunan_metin, sizeof(okunan_metin));

    shiftLeft(okunan_metin, ogrenci.shift);
    printf("Çözülen Metin: %s\n", okunan_metin);
    printf("Okul numarası: %s\n", ogrenci.numara);

    return 0;
}
