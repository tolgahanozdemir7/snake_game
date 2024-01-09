
#include <iostream>
#include <Windows.h>

using namespace std;

enum RENK{
    RENK_SIYAH      = 0,
    RENK_KOYUMAVI   = 1,
    RENK_KOYUYESIL  = 2,
    RENK_AQUA       = 3,
    RENK_KAHVERENGI = 4,
    RENK_KOYUMOR    = 5,
    RENK_ACIKKAHVE  = 6,
    RENK_GRI        = 7,
    RENK_KOYUGRI    = 8,
    RENK_MAVI       = 9,
    RENK_YESIL      = 10,
    RENK_ACIKMAVI   = 11,
    RENK_KIRMIZI    = 12,
    RENK_MOR        = 13,
    RENK_SARI       = 14,
    RENK_BEYAZ      = 15,
};

enum YON{
    YON_SOL    = 1,
    YON_SAG    = 2,
    YON_YUKARI = 3,
    YON_ASAGI  = 4
};
struct YilanHucre{
    int x;
    int y;
    YON yon;
    char karakter;
};

const int genislik = 80;
const int yukseklik = 20;
const int maxYilanUzunlugu = 500;
const char yilanKarakteri = 219;
int kuyrukUzunlugu = 0;
const int bs = 10; // bekleme süresi. miliSaniye

char sahne[genislik][yukseklik];
char tuslar[256];
YilanHucre yilanKuyrugu[maxYilanUzunlugu];

void klavyeOku(char tuslar[])
{
    for (int x=0; x < 256; x++)
    {
        tuslar[x] = (char)(GetAsyncKeyState(x)>>8);
    }
}
void gotoxy (int x,int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void kursoruGizle()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible=false;
    SetConsoleCursorInfo(out,&cursorInfo);
}
void sahneyiCiz()
{
    for (int y=0; y<yukseklik ; y++)
    {
        for (int x=0; x<genislik ; x++)
        {
            cout << sahne[x][y];
        }
        cout << endl;
    }
}
void sahneyiTemizle()
{
    for (int y=0; y<yukseklik ; y++)
    {
        for (int x=0; x<genislik ; x++)
        {
            sahne[x][y]=' ';
        }
    }
}
void sinirlariOlustur()
{
    for (int x=0; x<genislik ; x++)
    {
        sahne[x][0]=219;
        sahne[x][yukseklik-1]=219;
    }
    for (int y=0; y<yukseklik ; y++)
    {
        sahne[0][y]=219;
        sahne[genislik-1][y]=219;
    }
}
void yilanKuyrugunaEkle()
{
    if (kuyrukUzunlugu==maxYilanUzunlugu)
        return;
    int    x = yilanKuyrugu[kuyrukUzunlugu-1].x;
    int    y = yilanKuyrugu[kuyrukUzunlugu-1].y;
    YON  yon = yilanKuyrugu[kuyrukUzunlugu-1].yon;
    char kar = yilanKuyrugu[kuyrukUzunlugu-1].karakter;

    switch(yilanKuyrugu[kuyrukUzunlugu-1].yon)
    {
    case YON_SAG:
        x--;
        break;
    case YON_SOL:
        x++;
        break;
    case YON_ASAGI:
        y--;
        break;
    case YON_YUKARI:
        y++;
        break;
    }
    yilanKuyrugu[kuyrukUzunlugu].x=x;
    yilanKuyrugu[kuyrukUzunlugu].y=y;
    yilanKuyrugu[kuyrukUzunlugu].yon=yon;
    yilanKuyrugu[kuyrukUzunlugu].karakter=kar;
    kuyrukUzunlugu++;
}
void klavyeKontrol()
{
    klavyeOku(tuslar);

    if (tuslar[VK_LEFT] != 0)
    {
        yilanKuyrugu[0].yon=YON_SOL;
    }
    if (tuslar[VK_RIGHT] != 0)
    {
        yilanKuyrugu[0].yon=YON_SAG;
    }
    if (tuslar[VK_UP] != 0)
    {
        yilanKuyrugu[0].yon=YON_YUKARI;
    }
    if (tuslar[VK_DOWN] != 0)
    {
        yilanKuyrugu[0].yon=YON_ASAGI;
    }
    if (tuslar['A'] != 0)
    {
        yilanKuyrugunaEkle();
    }
}

void yilanOlustur()
{
    kuyrukUzunlugu=1;

    yilanKuyrugu[0].x = 20;
    yilanKuyrugu[0].y = 10;
    yilanKuyrugu[0].yon = YON_SAG;
    yilanKuyrugu[0].karakter = yilanKarakteri;

    yilanKuyrugunaEkle();
    yilanKuyrugunaEkle();
}
void yilaniSahneyeYerlestir()
{
    for (int i=0; i< kuyrukUzunlugu; i++)
    {
        int x = yilanKuyrugu[i].x;
        int y = yilanKuyrugu[i].y;
        sahne[x][y] = yilanKuyrugu[i].karakter;
    }
}
void renkAta(RENK arkaplan, RENK yazirengi){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arkaplan * 16 + yazirengi);

}
void yilaniHareketEttir()
{
    for (int i=0; i< kuyrukUzunlugu; i++)
    {
        switch(yilanKuyrugu[i].yon)
        {
        case YON_SAG:
            yilanKuyrugu[i].x++;
            break;
        case YON_SOL:
            yilanKuyrugu[i].x--;
            break;
        case YON_ASAGI:
            yilanKuyrugu[i].y++;
            break;
        case YON_YUKARI:
            yilanKuyrugu[i].y--;
            break;
        }
    }
    for (int i = kuyrukUzunlugu -1; i>0 ; i--)
    {
        yilanKuyrugu[i].yon = yilanKuyrugu[i-1].yon;
    }
}

int main()
{
    kursoruGizle();

    yilanOlustur();

    while (true)
    {
        renkAta(RENK_KAHVERENGI, RENK_SARI);
        sahneyiTemizle();
        sinirlariOlustur();
        klavyeKontrol();

        yilaniHareketEttir();
        yilaniSahneyeYerlestir();

        gotoxy(0,0);
        sahneyiCiz();
        Sleep(bs);
    }
}


