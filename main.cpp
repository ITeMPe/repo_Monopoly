///                     R E G U L A M I N                                       ///
/// Kolejnosc graczy jest nastepujaca: Gracz_1, Gracz_2, Gracz_3, Gracz4        ///
/// Gracz przesuwa sie o tyle miejsc po planszy ile zostanie wylosoway          ///
/// jego ruch.                                                                  ///
/// POLE MIASTO --->>>Jesli zatrzyma sie na polu, ktore jest miastem to moze    ///
/// je kupic pod warunkiem, ze ma wystarczajaco duzo pieniedzy oraz nie jest    ///
/// ono juz kupione przez innego gracza. Jesli Gracz stanie na polu, ktore      ///
/// nalezy do innego gracza to Gracz musi zaplacic czynsz wlascicielowi pola    ///
///                                                                             ///
/// POLE KARTA -->> Jesli Gracz znajdzie sie na tym polu, losowana jest karta   ///
/// albo bedize to bonus lub kara pieniezna.                                    ///
///                                                                             ///
/// POLE HOTEL -->>Jesli Gracz znajdzie sie na tym polu, to sytuacja wyglada    ///
/// tak jak w przypadku pola MIASTO, z tym ze pole HOTEL moze byc rozbudowywane ///
///                                                                             ///
/// POLE SKOK -->> Pole to umozliwia skok o tyle pol ile Gracz chce skoczyc     ///
///                                                                             ///
/// POLE BEZPLANY_POSTOJ -->> Nie do kupienia, nie placi sie za pobyt.          ///
///                                                                             ///
/// POLE WIEZIENIE -->> Trafiajac do wiezienia mozna tylko po przez normalny    ///
/// ruch. Wyjsc z niego mozna po wplaceniu kaucji lub odczekaniu 2 tur          ///
///                                                                             ///
/// POLE KASYNO -->> Jesli wyladujemy w Kasynie to zaplacimy czynsz jesli nie   ///
/// jest to nasze kasyno. W Gramy w nim, jesli uda nam sie wygrac to zarobimy   ///
/// pieniadze. Posiadanie Kasyna pomaga bankrutowac innych graczy.              ///
/// Wlasciciel kasyna nie moze w niim grac (zeby nie przegrac pieniedzy)        ///
///                                                                             ///
/// POLE START -->> Gracz za kazdy razem gdy na nim wyladuje dostaje bonus 100  ///
/// za przejscie calej planszy (nie liczy sie to na poczatku gry)               ///
///                                                                             ///
/// POLE PODATEK -->> Gracz musi zaplacic podatek dochodowy, ma dw wyjscia albo ///
/// 1) stala kwota = 200                                                        ///
/// 2) 10% od posiadanego majatku                                               ///
///                                                                             ///
/// GRE WYGRYWA GRACZ KTORY DOPROWADZI DO BANKRUTWA INNYCH GRACZY               ///
/// WLASNOSCI KTORE NALEZALY DO GRACZA KTORY ZBANKRUTOWAL PRZEJMUJE BANK I INNI ///
/// GRACZE MOGA KUPIC TE POLA. (przedostatniemu graczowi bank nic nie zabiera,  ///
/// poniewaz i tak konczy sie wtedy juz gra, bo zostaje jedyny gracz ktory nie  ///
/// zbankrutowal)                                                               ///
///                                                                             ///






#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;


string tab1[40]={"START","Bielsko_Biala","KARTA","Olsztyn","SKOK","HOTEL","Zabrze","SKOK","Gliwice","Rzeszow","Kielce","KARTA","Torun","Sosnowiec","HOTEL","Radom","KARTA","Czestochowa","Gdynia","Kasyno","WIEZIENIE","Bialystok","_PODATEK_","Katowice","Lublin","HOTEL","Bydgoszcz","Szczecin","KARTA","Gdansk","BEZPLATNY_POSTOJ","Poznan","Wroclaw","KARTA","Lodz","HOTEL","Krakow","KARTA","Warszawa","Kasyno"};
    string wlas="Brak_wlasciciela";
    /// tablica danych cen kazdego z pol
    int tab2[40]={0,60,0,60,0,100,100,0,100,120,140,0,140,160,160,180,0,180,200,400,50,220,0,220,240,240,260,260,0,280,0,300,300,0,320,320,350,0,400,200};
    /// tablica cen czynszu kazdego z pol
    int tab3[40]={0,2,0,4,0,6,6,0,6,8,10,0,10,12,12,14,0,14,16,32,0,18,0,18,20,20,22,22,0,24,0,26,26,0,28,24,35,0,50,75};



class Pole
{public:
    string nazwa;
    string wlasnosc;
    int wartosc;
    int czynsz;
    int poziom;  ///*

    Pole *next;  /// wskaznik na nastepne pole
    Pole *pop;   /// wskaznik na poprzednie pole

    Pole *gracz;     ///wskaznik na gracza
    string nazwa_gracza;
    int majatek;

    Pole(string _nazwa, string _wlasnosc,int _wartosc,int _czynsz,Pole *_pop,Pole *_next)       /// KONSTRUKTOR POLA
    {
        nazwa=_nazwa;
        wlasnosc=_wlasnosc;
        wartosc=_wartosc;
        czynsz=_czynsz;
        pop=_pop;
        next=_next;
        poziom=1; ///**
    }
    ~Pole()
    {
       /// cout<<"DESTRUKTOR POLA -->>"<<nazwa<<endl;
    }
friend class Plansza;
};










class Gracz
{public:
    string nazwa_gracza;
    int majatek;
    Pole *wsk;
    int wiezien; ///*
    Gracz(string _nazwa_gracza,int _majatek, Pole *_wsk)
    {
        nazwa_gracza=_nazwa_gracza;
        majatek=_majatek;
        wsk=_wsk;
        wiezien=0; ///**
    }
    ~Gracz()
    {
        ///cout<<"DESTRUKTOR GRACZA"<<endl;
    }

Pole *ruch_wp(Pole *p, int ile)
{
    cout<<"ruch z:"<<p->nazwa<<" o "<<ile<<" pol  do -->";
    Pole *ptr=p;
    int k=ile;

    for(int i=0;i<k;i++)
    {
        ptr=ptr->next;
    }
    return ptr;
}

Pole *ruch_wt(Pole *p, int ile)
{
   cout<<"ruch z:"<<p->nazwa<<" o "<<ile<<" pol  do -->";
    Pole *ptr=p;
    int k=ile;

    for(int i=0;i<k;i++)
    {
        ptr=ptr->pop;
    }
    return ptr;
}

void *del_majatek(string naz_gr,Pole *p)
{
    cout<<endl<<"Bank zajmuje caly majatek graca ktory zbankrutowal"<<endl;
    string gracz=naz_gr;
    Pole *ptr=p;
    int ile=40;
    while(ile--)
    {
        if(gracz==ptr->wlasnosc)
        {
            ptr->wlasnosc="Brak_wlasciciela";
        }
        ptr=ptr->next;
    }
}

friend class Plansza;
};


class Plansza
{
  Pole *first;  /// wskaznik na pierwsze pole

public:
      Plansza()
      {
          first=NULL;   /// pusta plansza
      }
      ~Plansza()
      {
        int x=40;
        Pole *pom=first;
        Pole *pom_next=pom->next;
        while(x--)
        {
            delete pom;
            pom=pom_next;
            pom_next=pom_next->next;
        }
      }
///------------------***
/// M E T O D Y

void init()         /// tworze plansze do gry
{
        if(first==NULL)
        {
            first =new Pole(tab1[0],wlas,tab2[0],tab3[0],NULL,NULL);
            first->pop=first;
            first->next=first;
        }
        Pole *wsk=first;
    int x=39;
    int i=1;
    while(x--)
    {
       wsk->next=new Pole(tab1[i],wlas,tab2[i],tab3[i],wsk,first);
       first->pop=wsk->next;
       wsk=wsk->next;
       i++;
    }
}


Pole *wskaznik()
{
    return first;
}

void show()     /// funkcja wyswietlajaca plansze do gry
{
    Pole *ptr=first;
    int x=40;
    while(x)
    {
        x--;
        cout<<"Nazwa-->> "<<ptr->nazwa<<endl<<"Wlasciciel-->> "<<ptr->wlasnosc<<endl<<"Wartosc Pola-->> "<<ptr->wartosc<<endl<<"Wartosc czynszu-->> "<<ptr->czynsz<<endl<<"Poziom-->> "<<ptr->poziom<<endl<<endl;
        ptr=ptr->next;
    }
}

void show_rev()     /// funkcja wyswietlajaca plansze do gry
{
    Pole *ptr=first;
    int x=40;
    while(x)
    {
        x--;
        cout<<"Nazwa-->> "<<ptr->nazwa<<endl<<"Wlasciciel-->> "<<ptr->wlasnosc<<endl<<"Wartosc Pola-->> "<<ptr->wartosc<<endl<<"Wartosc czynszu-->> "<<ptr->czynsz<<endl<<"Poziom-->> "<<ptr->poziom<<endl<<endl;
        ptr=ptr->pop;
    }
}


};











int rzut()
{
return rand()%12 +1;
}












int main()
{
srand(time(NULL));
    cout <<endl<< "             WITAJ W GRZE MONOPOLY       " <<endl<<endl;


Plansza P;
P.init();
string dalej;
Pole *wsk1;
Pole *wsk2;
Pole *wsk3;
Pole *wsk4;
Gracz g1("Gracz_1",1500,wsk1=P.wskaznik());
Gracz g2("Gracz_2",1500,wsk2=P.wskaznik());
Gracz g3("Gracz_3",1500,wsk3=P.wskaznik());
Gracz g4("Gracz_4",1500,wsk4=P.wskaznik());
int liczba_oczek;

while(true)
{

    cout<<endl<<endl<<endl<<"           Tura  dla: Gracz_1"<<endl;
    if(g1.majatek>0 and g1.wiezien==0)
    {
        liczba_oczek=rzut();
        cout<<endl<<"Wylosowano --> "<<liczba_oczek<<endl;
        g1.wsk=g1.ruch_wp(g1.wsk,liczba_oczek);cout<<" "<<g1.wsk->nazwa<<endl;

        if(g1.wsk->nazwa=="SKOK")
        {
            cout<<"Trafiles na pole: "<<g1.wsk->nazwa<<". Mozesz zdecydowac o ile miejsc chcesz przejsc dalej."<<endl
            <<"Wpisz liczbe o ile chcesz przeskoczyc "<<endl;
            int skok=0;
            cin>>skok;
            ///
            cout<<"Wartosc skoku: "<<skok<< " "<<endl;
            int xxx;
            cin>>xxx;
            ///
            cout<<endl<<"Wbrales skok o --> "<<skok<<" pol "<<endl;
            g1.wsk=g1.ruch_wp(g1.wsk,skok);cout<<" "<<g1.wsk->nazwa<<endl;
            cout<<"Wyladowales w: "<<g1.wsk->nazwa<<endl<<endl;
        }
        if(g1.wsk->nazwa!="KARTA" and g1.wsk->nazwa!="HOTEL" and g1.wsk->nazwa!="START" and g1.wsk->nazwa!="SKOK" and g1.wsk->nazwa!="_PODATEK_" and g1.wsk->nazwa!="WIEZIENIE" and g1.wsk->nazwa!="BEZPLATNY_POSTOJ" )  /// jest to jakies miasto
        {
            cout<<"Wyladowales w: "<<g1.wsk->nazwa<<endl<<endl;
            if(g1.wsk->wlasnosc=="Gracz_1")
            {
                cout<<"To pole nalezy do Ciebie!! Czuj sie jak u siebie w domu. :) "<<endl;
            }
           if(g1.wsk->wlasnosc=="Brak_wlasciciela") /// mozna kupowac
           {    cout<<"Majatek "<<g1.nazwa_gracza<<" wynosi: "<<g1.majatek<<endl;
               if(g1.majatek>g1.wsk->wartosc)
               {
                    cout<<"Stac Cie kupic to pole, do nikogo nie nalezy "<<g1.wsk->nazwa<<endl<<"Koszt zakupu wynosi: "<<g1.wsk->wartosc<<endl<<endl;
                    cout<<"Jesli chcesz kupic to pole wcisnij 1. "<<endl;
                    int wybor1;
                    cin>>wybor1;
                    if(wybor1==1)
                    {
                        g1.majatek=g1.majatek - g1.wsk->wartosc;
                        g1.wsk->wlasnosc="Gracz_1";
                        cout<<"Udalo sie, "<<g1.nazwa_gracza<<" stales sie wlascicielem: "<<g1.wsk->nazwa<<endl;
                    }
                    else
                    {
                        cout<<"Gracz "<<g1.nazwa_gracza<<" nie zdecydowal sie na zakup. Kolej na gracza "<<g2.nazwa_gracza<<endl;
                        if(g2.majatek>g1.wsk->wartosc)
                        {
                            cout<<"Majatek wynosi: "<<g2.majatek<<endl;
                            cout<<"Jesli chcesz kupic miasto wcisnij 1. "<<endl;
                            int wybor2;
                            cin>>wybor2;
                            if(wybor2==1)
                            {
                                g2.majatek=g2.majatek - g1.wsk->wartosc;
                                g1.wsk->wlasnosc="Gracz_2";
                                cout<<"Udalo sie, "<<g2.nazwa_gracza<<" stales sie wlascicielem: "<<g1.wsk->nazwa<<endl;
                            }
                            else
                            {
                               cout<<"Kolejny gracz tez sie nie zdecydowal"<<endl;
                            }
                        }
                        else
                        {
                            cout<<g2.nazwa_gracza<<" niestety nie stac na zakup pola"<<endl;
                        }
                    }
               }
               else
               {
                   cout<<"Niestety nie stac Cie na kupno tego miasta "<<endl;
               }
            }
           else if(g1.wsk->wlasnosc!="Gracz_1")  /// trzeba placic czynsz
           {
               cout<<"Niestety nie mozesz kupic pola. "<<g1.wsk->nazwa<<" Nalezy do innego gracza."<<endl
               <<" Musisz zaplacic czynsz o wartosci:"<<g1.wsk->czynsz<<endl;
               g1.majatek=g1.majatek-g1.wsk->czynsz;
                if(g1.wsk->wlasnosc=="Gracz_2")
                {
                    g2.majatek=g2.majatek+g1.wsk->czynsz;cout<<"majatek Gracza_2: "<<g2.majatek<<endl;
                }
                   if(g1.wsk->wlasnosc=="Gracz_3")
                {
                    g3.majatek=g3.majatek+g1.wsk->czynsz;cout<<"majatek Gracza_3: "<<g3.majatek<<endl;
                }
                   if(g1.wsk->wlasnosc=="Gracz_4")
                {
                    g4.majatek=g4.majatek+g1.wsk->czynsz;cout<<"majatek Gracza_4: "<<g4.majatek<<endl;
                }
            }
        }
        if(g1.wsk->nazwa=="Kasyno" and g1.wsk->wlasnosc!="Gracz_1" and g1.wsk->wlasnosc!="Brak_wlasciciela")
                {
                    cout<<"Trafiles do  kasyna !!. Jesli bedzIesz miec szczescie, to wygrasz pieniadze, jesli nie to przegrasz 100!! "<<endl
                    <<"Wybierz jedna z cyfr od 0 do 9 !"<<endl;
                    int cyfra =rand()%10;
                    int podana_cyfra;
                    cin>>podana_cyfra;
                    if(podana_cyfra==cyfra)
                    {
                        cout<<"Udalo Ci sie!! Masz szczescie, wygrywasz 300 !!"<<endl;
                        g1.majatek=g1.majatek+300;
                    }
                    else
                    {
                        cout<<"Niestety, ale przegrales 100"<<endl;
                        g1.majatek=g1.majatek-100;
                    }
                }



        if(g1.wsk->nazwa=="START")
        {
            cout<<"Udalo Ci sie przejsc cala plansze, dostajesz bonus o wartosci: 100 "<<endl;
            g1.majatek=g1.majatek+100;
        }
        if(g1.wsk->nazwa=="HOTEL")
        {
            cout<<"Wyladowales w: "<<g1.wsk->nazwa<<endl<<endl;
            if(g1.wsk->wlasnosc=="Gracz_1")    ///-->jestes w swoim hotelu
            {
                cout<<"To Twoj hotel. Jesli chcesz mozesz go rozbudowac wybierajac 1. Rozbudowa kosztuje polowe aktualnej wartosci Hotelu "<<endl;
                int rozbudowa=0;
                cout<<"Aktualna wartosc hotelu: "<<g1.wsk->wartosc<<endl;
                cin>>rozbudowa;
                if(rozbudowa==1)
                {
                    cout<<"poziom-->>"<<g1.wsk->poziom<<" czynsz-->>"<<g1.wsk->czynsz<<"wartosc-->>"<<g1.wsk->wartosc<<endl;
                    g1.wsk->poziom=g1.wsk->poziom+1;
                    g1.wsk->czynsz=g1.wsk->czynsz+g1.wsk->czynsz;
                    g1.wsk->wartosc=g1.wsk->wartosc+0.5*g1.wsk->wartosc;
                    g1.majatek=g1.majatek-0.5*g1.wsk->wartosc;
                    cout<<"poziom-->>"<<g1.wsk->poziom<<" czynsz-->>"<<g1.wsk->czynsz<<"wartosc-->>"<<g1.wsk->wartosc<<endl;
                }
                else
                {
                    cout<<"Zdecydowales nie rozbudowywac narazie Hotelu. "<<endl;
                }
            }
            if(g1.wsk->wlasnosc=="Brak_wlasciciela")
            {
                if(g1.majatek>g1.wsk->wartosc)
                {
                    cout<<"Mozesz kupic hotel !!."<<endl<<" Bedziesz mogl go rozbudowywac i pobierac wieksze czynsze od innych graczy."<<endl
                    <<"Jesli chcesz kupic hotel wybierz 1."<<endl;
                    int kupuje=0;
                    cin>>kupuje;
                    if(kupuje==1)
                    {
                        g1.wsk->wlasnosc="Gracz_1";
                        g1.majatek=g1.majatek-g1.wsk->wartosc;
                    }
                    else
                    {
                        cout<<"Gracz "<<g1.nazwa_gracza<<" nie zdecydowal sie na zakup. Kolej na gracza "<<g2.nazwa_gracza<<endl;
                        if(g2.majatek>g1.wsk->wartosc)
                        {
                            cout<<"Majatek wynosi: "<<g2.majatek<<endl;
                            cout<<"Jesli chcesz kupic miasto wcisnij 1. "<<endl;
                            int wybor2;
                            cin>>wybor2;
                            if(wybor2==1)
                            {
                                g2.majatek=g2.majatek - g1.wsk->wartosc;
                                g1.wsk->wlasnosc="Gracz_2";
                                cout<<"Udalo sie, "<<g2.nazwa_gracza<<" stales sie wlascicielem: "<<g1.wsk->nazwa<<endl;
                            }
                            else
                            {
                               cout<<"Kolejny gracz tez sie nie zdecydowal"<<endl;
                            }
                        }
                        else
                        {
                            cout<<g2.nazwa_gracza<<" niestety nie stac na zakup pola"<<endl;
                        }

                    }
                }
                else
                {
                    cout<<"Nie masz wystarczajaco duzo pieniedzy aby kupic hotel."<<endl;
                }
            }
            else if(g1.wsk->wlasnosc!="Gracz_1" and g1.wsk->wlasnosc!="Brak_wlasciciela")
            {
                cout<<"Nie jestes w swoim hotelu. Musisz zaplacic za nocleg!!"<<endl
                <<"Czynsz wynosi: "<<g1.wsk->czynsz<<endl;
                g1.majatek=g1.majatek-g1.wsk->czynsz;
                if(g1.wsk->wlasnosc=="Gracz_2")
                {
                    g2.majatek=g2.majatek+g1.wsk->czynsz;
                }
                if(g1.wsk->wlasnosc=="Gracz_3")
                {
                    g3.majatek=g3.majatek+g1.wsk->czynsz;
                }
                if(g1.wsk->wlasnosc=="Gracz_4")
                {
                    g4.majatek=g4.majatek+g1.wsk->czynsz;
                }
            }
        }
        if(g1.wsk->nazwa=="_PODATEK_")
        {
            int wybor=1;
            cout<<"Niestety musisz zaplacic PODATEK. Masz 2 opcje: 1.Placisz 200  2.Placisz 10% swojego majatku. "<<endl
            <<"Jesli chcesz zaplacic staly podatek o wartosci 200 wybierz 1."<<endl<<" W przeciwnym wypadku zaplacisz podatek o wartosci10% swojego majatku. "<<endl;
            cout<<endl<<" Twoj majatek: "<<g1.majatek<<endl;
            cin>>wybor;
            if(wybor==1)
            {
                g1.majatek=g1.majatek-200;
            }
            else
            {
                cout<<endl<<"majatek: "<<g1.majatek<<"    podatek: "<<g1.majatek*0.1<<endl;
                g1.majatek=g1.majatek- g1.majatek*0.1; /// majatek ma wartosci calkowite, podatek jest wiec zaokraglany do wart calkowitej
            }
        }

        if(g1.wsk->nazwa=="WIEZIENIE")
        {
            if(g1.wiezien==0) ///-->> trafilem do wiezienia 1 raz
            {
                cout<<"Ty BANDYTO, PRZESTEPCO !!! Zlapalismy Cie wreszcie!! "<<endl<<" Trafisz do wiezienia, chyba ze wplacisz kaucje w wysokosci: 150 "<<endl
                <<"W przeciwnym wypadku bedziesz musial odsiedziec kare ->> 2 tury !! "<<endl<<"Jesli chcesz wplacic kaucje wybierz 1. "<<endl
                <<"W przeciwnym wypadku bedziesz czekac 2 tury "<<endl;
                int wybor=1;
                cin>>wybor;
                if(wybor==1)
                {
                    cout<<"Zdecydowales sie wplacic kaucie. "<<endl;
                    g1.majatek=g1.majatek-150;
                }
                else
                {
                    cout<<"Wybrales wiezienie. Rozgosc sie w swojej celi ! :) "<<endl;
                    g1.wiezien=2;

                }
            }
            else
            {
                g1.wiezien=g1.wiezien-1;
                g1.wsk=g1.ruch_wp(g1.wsk,40);cout<<" "<<g1.wsk->nazwa<<endl;
            }

        }
        if(g1.wsk->nazwa=="KARTA")
        {
            cout<<"Jestes na polu w ktorym wylosujesz karte. Moze Ci przyniesc szczescie lub pecha "<<endl
            <<"zaraz sie przekonasz. "<<endl;
            int karta=0;
            karta=rand()%4+1;
            switch(karta)
            {
            case 1:
                cout<<"Dostales BONUS w wysokosci 200: "<<endl;
                g1.majatek=g1.majatek+200;
                break;
            case 2:
                cout<<"Dostales KARE w wysokosci 200: "<<endl;
                g1.majatek=g1.majatek-200;
                break;
            case 3:
                cout<<"Dostales BONUS w wysokosci 50: "<<endl;
                g1.majatek=g1.majatek+50;
                break;
            case 4:
                cout<<"Dostales KARE w wysokosci 50: "<<endl;
                g1.majatek=g1.majatek-50;
                break;
            }
        }
    }
    else if(g1.wiezien!=0)
    {
        cout<<endl<<"          "<<g1.wsk->nazwa<<endl<<"Jestes w wiezieniu, odsiadujesz swoj wyrok"<<endl;
        g1.wiezien=g1.wiezien-1;
        g1.wsk=g1.ruch_wp(g1.wsk,40);cout<<" "<<g1.wsk->nazwa<<endl;
    }
    else
    {
        cout<<" Z B A N K R U T O W A L E S  !!!"<<endl<<"Przegrales..."<<endl<<endl;
        g1.del_majatek("Gracz_1",g1.wsk);


    }

cout<<endl<<endl<<"         WCISNIJ DOWOLNY KLAWISZ ABY KONTYNUOWAC GRE !!      "<<endl<<endl;
cin>>dalej;

///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------
///------------------------------------- G R A C Z _ 2 -----------------------------------------------
///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------

cout<<endl<<endl<<endl<<"           Tura  dla: Gracz_2"<<endl;
    if(g2.majatek>0 and g2.wiezien==0)
    {
        liczba_oczek=rzut();
        cout<<endl<<"Wylosowano --> "<<liczba_oczek<<endl;
        g2.wsk=g2.ruch_wp(g2.wsk,liczba_oczek);cout<<" "<<g2.wsk->nazwa<<endl;
        if(g2.wsk->nazwa=="SKOK")
        {
            cout<<"Trafiles na pole: "<<g2.wsk->nazwa<<". Mozesz zdecydowac o ile miejsc chcesz przejsc dalej."<<endl
            <<"Wpisz liczbe o ile chcesz przeskoczyc "<<endl;
            int skok=0;
            cin>>skok;
                 ///
            cout<<"Wartosc skoku: "<<skok<< " "<<endl;
            int xxx;
            cin>>xxx;
            ///
            cout<<endl<<"Wbrales skok o --> "<<skok<<" pol "<<endl;
            g2.wsk=g2.ruch_wp(g2.wsk,skok);cout<<" "<<g2.wsk->nazwa<<endl;
            cout<<"Wyladowales w: "<<g2.wsk->nazwa<<endl<<endl;
        }
        if(g2.wsk->nazwa!="KARTA" and g2.wsk->nazwa!="HOTEL" and g2.wsk->nazwa!="START" and g2.wsk->nazwa!="kolko" and g2.wsk->nazwa!="SKOK" and g2.wsk->nazwa!="_PODATEK_" and g2.wsk->nazwa!="WIEZIENIE" and g2.wsk->nazwa!="BEZPLATNY_POSTOJ" )  /// jest to jakies miasto
        {
            cout<<"Wyladowales w: "<<g2.wsk->nazwa<<endl<<endl;
            if(g2.wsk->wlasnosc=="Gracz_2")
            {
                cout<<"To pole nalezy do Ciebie!! Czuj sie jak u siebie w domu. :) "<<endl;
            }
           if(g2.wsk->wlasnosc=="Brak_wlasciciela") /// mozna kupowac
           {    cout<<"Majatek "<<g2.nazwa_gracza<<" wynosi: "<<g2.majatek<<endl;
               if(g2.majatek>g2.wsk->wartosc)
               {
                    cout<<"Stac Cie kupic to pole, do nikogo nie nalezy. "<<g2.wsk->nazwa<<endl<<"Koszt zakupu wynosi: "<<g2.wsk->wartosc<<endl<<endl;
                    cout<<"Jesli chcesz kupic to pole wcisnij 1. "<<endl;
                    int wybor1;
                    cin>>wybor1;
                    if(wybor1==1)
                    {
                        g2.majatek=g2.majatek - g2.wsk->wartosc;
                        g2.wsk->wlasnosc="Gracz_2";
                        cout<<"Udalo sie, "<<g2.nazwa_gracza<<" stales sie wlascicielem: "<<g2.wsk->nazwa<<endl;
                    }
                    else
                    {
                        cout<<"Gracz "<<g2.nazwa_gracza<<" nie zdecydowal sie na zakup. Kolej na gracza "<<g3.nazwa_gracza<<endl;
                        if(g3.majatek>g2.wsk->wartosc)
                        {
                            cout<<"Majatek wynosi:"<<g3.majatek<<endl;
                            cout<<"Jesli chcesz kupic pole wcisnij 1. "<<endl;
                            int wybor2;
                            cin>>wybor2;
                            if(wybor2==1)
                            {
                                g3.majatek=g3.majatek - g2.wsk->wartosc;
                                g3.wsk->wlasnosc="Gracz_3";
                                cout<<"Udalo sie, "<<g3.nazwa_gracza<<" stales sie wlascicielem: "<<g2.wsk->nazwa<<endl;
                            }
                            else
                            {
                               cout<<"Kolejny gracz tez sie nie zdecydowal"<<endl;
                            }
                        }
                        else
                        {
                            cout<<g3.nazwa_gracza<<" niestety nie stac na zakup pola"<<endl;
                        }

                    }
               }
               else
               {
                  cout<<g2.nazwa_gracza<<" niestety nie stac na zakup pola"<<g2.wsk->nazwa<<endl;
               }
            }
           else if(g2.wsk->wlasnosc!="Gracz_2")  /// trzeba placic czynsz
           {
               cout<<"Niestety nie mozesz kupic pola. "<<g2.wsk->nazwa<<" Nalezy do innego gracza."<<endl
               <<" Musisz zaplacic czynsz o wartosci:"<<g2.wsk->czynsz<<endl;
               g2.majatek=g2.majatek-g2.wsk->czynsz;
                if(g2.wsk->wlasnosc=="Gracz_1")
                {
                    g1.majatek=g1.majatek+g2.wsk->czynsz;cout<<"majatek Gracza_1: "<<g1.majatek<<endl;
                }
                   if(g2.wsk->wlasnosc=="Gracz_3")
                {
                    g3.majatek=g3.majatek+g2.wsk->czynsz;cout<<"majatek Gracza_3: "<<g3.majatek<<endl;
                }
                   if(g2.wsk->wlasnosc=="Gracz_4")
                {
                    g4.majatek=g4.majatek+g2.wsk->czynsz;cout<<"majatek Gracza_4: "<<g4.majatek<<endl;
                }

            }
        }
         if(g2.wsk->nazwa=="Kasyno" and g2.wsk->wlasnosc!="Gracz_2" and g2.wsk->wlasnosc!="Brak_wlasciciela")
                {
                    cout<<"Trafiles do kasyna !!. Jesli bedizesz miec szczescie, to wygrasz pieniadze, jesli nie to przegrasz 100!! "<<endl
                    <<"Wybierz jedna z cyfr od 0 do 9 !"<<endl;
                    int cyfra =rand()%10;
                    int podana_cyfra;
                    cin>>podana_cyfra;
                    if(podana_cyfra==cyfra)
                    {
                        cout<<"Udalo Ci sie!! Masz szczescie, wygrywasz 300 !!"<<endl;
                        g2.majatek=g1.majatek+300;
                    }
                    else
                    {
                        cout<<"Niestety, ale przegrales 100"<<endl;
                        g2.majatek=g1.majatek-100;
                    }
                }

        if(g2.wsk->nazwa=="START")
        {
            cout<<"Udalo Ci sie przejsc cala plansze, dostajesz bonus o wartosci: 100 "<<endl;
            g2.majatek=g2.majatek+100;
        }
        if(g2.wsk->nazwa=="HOTEL")
        {
            cout<<"Wyladowales w: "<<g2.wsk->nazwa<<endl<<endl;
            if(g2.wsk->wlasnosc=="Gracz_2")    ///-->jestes w swoim hotelu
            {
                cout<<"To Twoj hotel. Jesli chcesz mozesz go rozbudowac wybierajac 1. Rozbudowa kosztuje polowe aktualnej wartosci Hotelu "<<endl;
                int rozbudowa=0;
                cout<<"Aktualna wartosc hotelu: "<<g2.wsk->wartosc<<endl;
                cin>>rozbudowa;
                if(rozbudowa==1)
                {
                    cout<<"poziom-->>"<<g2.wsk->poziom<<" czynsz-->>"<<g2.wsk->czynsz<<"wartosc-->>"<<g2.wsk->wartosc<<endl;
                    g2.wsk->poziom=g2.wsk->poziom+1;
                    g2.wsk->czynsz=g2.wsk->czynsz+g2.wsk->czynsz;
                    g2.wsk->wartosc=g2.wsk->wartosc+0.5*g2.wsk->wartosc;
                    g2.majatek=g2.majatek-0.5*g2.wsk->wartosc;
                    cout<<"poziom-->>"<<g2.wsk->poziom<<" czynsz-->>"<<g2.wsk->czynsz<<"wartosc-->>"<<g2.wsk->wartosc<<endl;
                }
                else
                {
                    cout<<"Zdecydowales nie rozbudowywac narazie Hotelu. "<<endl;
                }
            }
            if(g2.wsk->wlasnosc=="Brak_wlasciciela")
            {
                if(g2.majatek>g2.wsk->wartosc)
                {
                    cout<<"Mozesz kupic hotel !!."<<endl<<" Bedziesz mogl go rozbudowywac i pobierac wieksze czynsze od innych graczy."<<endl
                    <<"Jesli chcesz kupic hotel wybierz 1."<<endl;
                    int kupuje=0;
                    cin>>kupuje;
                    if(kupuje==1)
                    {
                        g2.wsk->wlasnosc="Gracz_2";
                        g2.majatek=g2.majatek-g2.wsk->wartosc;
                    }
                    else
                    {
                        cout<<"Gracz "<<g2.nazwa_gracza<<" nie zdecydowal sie na zakup. Kolej na gracza "<<g1.nazwa_gracza<<endl;
                        if(g1.majatek>g2.wsk->wartosc)
                        {
                            cout<<"Majatek wynosi:"<<g1.majatek<<endl;
                            cout<<"Jesli chcesz kupic pole wcisnij 1. "<<endl;
                            int wybor2;
                            cin>>wybor2;
                            if(wybor2==1)
                            {
                                g1.majatek=g1.majatek - g2.wsk->wartosc;
                                g2.wsk->wlasnosc="Gracz_1";
                                cout<<"Udalo sie, "<<g1.nazwa_gracza<<" stales sie wlascicielem: "<<g2.wsk->nazwa<<endl;
                            }
                            else
                            {
                               cout<<"Kolejny gracz tez sie nie zdecydowal"<<endl;
                            }
                        }
                        else
                        {
                            cout<<g1.nazwa_gracza<<" niestety nie stac na zakup pola"<<endl;
                        }
                    }
                }
                else
                {
                    cout<<"Nie masz wystarczajaco duzo pieniedzy aby kupic hotel."<<endl;
                }
            }
            else if(g2.wsk->wlasnosc!="Gracz_2" and g2.wsk->wlasnosc!="Brak_wlasciciela")
            {
                cout<<"Nie jestes w swoim hotelu. Musisz zaplacic za nocleg!!"<<endl
                <<"Czynsz wynosi: "<<g2.wsk->czynsz<<endl;
                g2.majatek=g2.majatek-g2.wsk->czynsz;
                if(g2.wsk->wlasnosc=="Gracz_1")
                {
                    g1.majatek=g1.majatek+g2.wsk->czynsz;
                }
                if(g2.wsk->wlasnosc=="Gracz_3")
                {
                    g3.majatek=g3.majatek+g2.wsk->czynsz;
                }
                if(g2.wsk->wlasnosc=="Gracz_4")
                {
                    g4.majatek=g4.majatek+g2.wsk->czynsz;
                }
            }
        }
        if(g2.wsk->nazwa=="_PODATEK_")
        {int wybor=1;
            cout<<"Niestety musisz zaplacic PODATEK. Masz 2 opcje: 1.Placisz 200  2.Placisz 10% swojego majatku. "<<endl
            <<"Jesli chcesz zaplacic staly podatek o wartosci 200 wybierz 1."<<endl<<" W przeciwnym wypadku zaplacisz podatek o wartosci10% swojego majatku. "<<endl;
            cout<<endl<<" Twoj majatek: "<<g2.majatek<<endl;
            cin>>wybor;
            if(wybor==1)
            {
                g2.majatek=g2.majatek-200;
            }
            else
            {
                cout<<endl<<"majatek: "<<g2.majatek<<"    podatek: "<<g2.majatek*0.1<<endl;
                g2.majatek=g2.majatek- g2.majatek*0.1; /// majatek ma wartosci calkowite, podatek jest wiec zaokraglany do wart calkowitej
            }
        }

        if(g2.wsk->nazwa=="WIEZIENIE")
        {
            if(g2.wiezien==0) ///-->> trafilem do wiezienia 1 raz
            {
                cout<<"Ty BANDYTO, PRZESTEPCO !!! Zlapalismy Cie wreszcie!! "<<endl<<" Trafisz do wiezienia, chyba ze wplacisz kaucje w wysokosci: 150 "<<endl
                <<"W przeciwnym wypadku bedziesz musial odsiedziec kare ->> 2 tury !! "<<endl<<"Jesli chcesz wplacic kaucje wybierz 1. "<<endl
                <<"W przeciwnym wypadku bedziesz czekac 2 tury "<<endl;

                int wybor=1;
                cin>>wybor;
                if(wybor==1)
                {
                    cout<<"Zdecydowales sie wplacic kaucie. "<<endl;
                    g2.majatek=g2.majatek-150;
                }
                else
                {
                    cout<<"Wybrales wiezienie. Rozgosc sie w swojej celi ! :) "<<endl;
                     g2.wiezien=2;
                }
            }
            else
            {
                g2.wiezien=g2.wiezien-1;
                g2.wsk=g2.ruch_wp(g2.wsk,40);cout<<" "<<g2.wsk->nazwa<<endl;
            }

        }

        if(g2.wsk->nazwa=="KARTA")
        {
            cout<<"Jestes na polu w ktorym wylosujesz karte. Moze Ci przyniesc szczescie lub pecha "<<endl
            <<"zaraz sie przekonasz. "<<endl;
            int karta=0;
            karta=rand()%4+1;
            switch(karta)
            {
            case 1:
                cout<<"Dostales BONUS w wysokosci 200: "<<endl;
                g2.majatek=g2.majatek+200;
                break;
            case 2:
                cout<<"Dostales KARE w wysokosci 200: "<<endl;
                g2.majatek=g2.majatek-200;
                break;
            case 3:
                cout<<"Dostales BONUS w wysokosci 50: "<<endl;
                g2.majatek=g2.majatek+50;
                break;
            case 4:
                cout<<"Dostales KARE w wysokosci 50: "<<endl;
                g2.majatek=g2.majatek-50;
                break;

            }
        }

    }
    else if(g2.wiezien!=0)
    {
        cout<<endl<<"           "<<g2.wsk->nazwa<<endl<<"Jestes w wiezieniu, odsiadujesz swoj wyrok"<<endl;
        g2.wiezien=g2.wiezien-1;
        g2.wsk=g2.ruch_wp(g2.wsk,40);cout<<" "<<g2.wsk->nazwa<<endl;
    }
    else
    {
        cout<<" Z B A N K R U T O W A L E S  !!!"<<endl<<"Przegrales..."<<endl<<endl;
         g2.del_majatek("Gracz_2",g2.wsk);

    }

cout<<endl<<endl<<"         WCISNIJ DOWOLNY KLAWISZ ABY KONTYNUOWAC GRE !!      "<<endl<<endl;
cin>>dalej;


///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------
///------------------------------------- G R A C Z _ 3 -----------------------------------------------
///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------

cout<<endl<<endl<<endl<<"           Tura  dla: Gracz_3"<<endl;
    if(g3.majatek>0 and g3.wiezien==0)
    {
        liczba_oczek=rzut();
        cout<<endl<<"Wylosowano --> "<<liczba_oczek<<endl;
        g3.wsk=g3.ruch_wp(g3.wsk,liczba_oczek);cout<<" "<<g3.wsk->nazwa<<endl;
        if(g3.wsk->nazwa=="SKOK")
        {
            cout<<"Trafiles na pole: "<<g3.wsk->nazwa<<". Mozesz zdecydowac o ile miejsc chcesz przejsc dalej."<<endl
            <<"Wpisz liczbe o ile chcesz przeskoczyc "<<endl;
            int skok=0;
            cin>>skok;
                 ///
            cout<<"Wartosc skoku: "<<skok<< " "<<endl;
            int xxx;
            cin>>xxx;
            ///
            cout<<endl<<"Wbrales skok o --> "<<skok<<" pol "<<endl;
            g3.wsk=g3.ruch_wp(g3.wsk,skok);cout<<" "<<g3.wsk->nazwa<<endl;
            cout<<"Wyladowales w: "<<g3.wsk->nazwa<<endl<<endl;
        }
        if(g3.wsk->nazwa!="KARTA" and g3.wsk->nazwa!="HOTEL" and g3.wsk->nazwa!="START" and g3.wsk->nazwa!="kolko" and g3.wsk->nazwa!="SKOK" and g3.wsk->nazwa!="_PODATEK_" and g3.wsk->nazwa!="WIEZIENIE" and g3.wsk->nazwa!="BEZPLATNY_POSTOJ" )  /// jest to jakies miasto
        {
            cout<<"Wyladowales w: "<<g3.wsk->nazwa<<endl<<endl;
            if(g3.wsk->wlasnosc=="Gracz_3")
            {
                cout<<"To pole nalezy do Ciebie!! Czuj sie jak u siebie w domu. :) "<<endl;
            }
           if(g3.wsk->wlasnosc=="Brak_wlasciciela") /// mozna kupowac
           {    cout<<"Majatek "<<g3.nazwa_gracza<<" wynosi: "<<g3.majatek<<endl;
               if(g3.majatek>g3.wsk->wartosc)
               {
                    cout<<"Stac Cie kupic to pole, do nikogo nie nalezy. "<<g3.wsk->nazwa<<endl<<"Koszt zakupu wynosi: "<<g3.wsk->wartosc<<endl<<endl;
                    cout<<"Jesli chcesz kupic to pole wcisnij 1. "<<endl;
                    int wybor1;
                    cin>>wybor1;
                    if(wybor1==1)
                    {
                        g3.majatek=g3.majatek - g3.wsk->wartosc;
                        g3.wsk->wlasnosc="Gracz_3";
                        cout<<"Udalo sie, "<<g3.nazwa_gracza<<" stales sie wlascicielem: "<<g3.wsk->nazwa<<endl;
                    }
                    else
                    {
                        cout<<"Gracz "<<g3.nazwa_gracza<<" nie zdecydowal sie na zakup. Kolej na gracza "<<g4.nazwa_gracza<<endl;
                        if(g4.majatek>g3.wsk->wartosc)
                        {
                            cout<<"Majatek wynosi:"<<g4.majatek<<endl;
                            cout<<"Jesli chcesz kupic pole wcisnij 1. "<<endl;
                            int wybor2;
                            cin>>wybor2;
                            if(wybor2==1)
                            {
                                g4.majatek=g4.majatek - g3.wsk->wartosc;
                                g4.wsk->wlasnosc="Gracz_4";
                                cout<<"Udalo sie, "<<g4.nazwa_gracza<<" stales sie wlascicielem: "<<g3.wsk->nazwa<<endl;
                            }
                            else
                            {
                               cout<<"Kolejny gracz tez sie nie zdecydowal"<<endl;
                            }
                        }
                        else
                        {
                            cout<<g4.nazwa_gracza<<" niestety nie stac na zakup pola"<<endl;
                        }

                    }
               }
               else
               {
                  cout<<g3.nazwa_gracza<<" niestety nie stac na zakup pola"<<g3.wsk->nazwa<<endl;
               }
            }
           else if(g3.wsk->wlasnosc!="Gracz_3")  /// trzeba placic czynsz
           {
               cout<<"Niestety nie mozesz kupic pola. "<<g3.wsk->nazwa<<" Nalezy do innego gracza."<<endl
               <<" Musisz zaplacic czynsz o wartosci:"<<g3.wsk->czynsz<<endl;
               g3.majatek=g3.majatek-g3.wsk->czynsz;
                if(g3.wsk->wlasnosc=="Gracz_1")
                {
                    g1.majatek=g1.majatek+g3.wsk->czynsz;cout<<"majatek Gracza_1: "<<g1.majatek<<endl;
                }
                   if(g3.wsk->wlasnosc=="Gracz_2")
                {
                    g2.majatek=g2.majatek+g3.wsk->czynsz;cout<<"majatek Gracza_2: "<<g2.majatek<<endl;
                }
                   if(g3.wsk->wlasnosc=="Gracz_4")
                {
                    g4.majatek=g4.majatek+g3.wsk->czynsz;cout<<"majatek Gracza_4: "<<g4.majatek<<endl;
                }

            }
        }
         if(g3.wsk->nazwa=="Kasyno" and g3.wsk->wlasnosc!="Gracz_3" and g3.wsk->wlasnosc!="Brak_wlasciciela")
                {
                    cout<<"Trafiles do kasyna !!. Jesli bedizesz miec szczescie, to wygrasz pieniadze, jesli nie to przegrasz 100!! "<<endl
                    <<"Wybierz jedna z cyfr od 0 do 9 !"<<endl;
                    int cyfra =rand()%10;
                    int podana_cyfra;
                    cin>>podana_cyfra;
                    if(podana_cyfra==cyfra)
                    {
                        cout<<"Udalo Ci sie!! Masz szczescie, wygrywasz 300 !!"<<endl;
                        g3.majatek=g3.majatek+300;
                    }
                    else
                    {
                        cout<<"Niestety, ale przegrales 100"<<endl;
                        g3.majatek=g3.majatek-100;
                    }
                }

        if(g3.wsk->nazwa=="START")
        {
            cout<<"Udalo Ci sie przejsc cala plansze, dostajesz bonus o wartosci: 100 "<<endl;
            g3.majatek=g3.majatek+100;
        }
        if(g3.wsk->nazwa=="HOTEL")
        {
            cout<<"Wyladowales w: "<<g3.wsk->nazwa<<endl<<endl;
            if(g3.wsk->wlasnosc=="Gracz_3")    ///-->jestes w swoim hotelu
            {
                cout<<"To Twoj hotel. Jesli chcesz mozesz go rozbudowac wybierajac 1. Rozbudowa kosztuje polowe aktualnej wartosci Hotelu "<<endl;
                int rozbudowa=0;
                cout<<"Aktualna wartosc hotelu: "<<g3.wsk->wartosc<<endl;
                cin>>rozbudowa;
                if(rozbudowa==1)
                {
                    cout<<"poziom-->>"<<g3.wsk->poziom<<" czynsz-->>"<<g3.wsk->czynsz<<"wartosc-->>"<<g3.wsk->wartosc<<endl;
                    g3.wsk->poziom=g3.wsk->poziom+1;
                    g3.wsk->czynsz=g3.wsk->czynsz+g3.wsk->czynsz;
                    g3.wsk->wartosc=g3.wsk->wartosc+0.5*g3.wsk->wartosc;
                    g3.majatek=g3.majatek-0.5*g3.wsk->wartosc;
                    cout<<"poziom-->>"<<g3.wsk->poziom<<" czynsz-->>"<<g3.wsk->czynsz<<"wartosc-->>"<<g3.wsk->wartosc<<endl;
                }
                else
                {
                    cout<<"Zdecydowales nie rozbudowywac narazie Hotelu. "<<endl;
                }
            }
            if(g3.wsk->wlasnosc=="Brak_wlasciciela")
            {
                if(g3.majatek>g3.wsk->wartosc)
                {
                    cout<<"Mozesz kupic hotel !!."<<endl<<" Bedziesz mogl go rozbudowywac i pobierac wieksze czynsze od innych graczy."<<endl
                    <<"Jesli chcesz kupic hotel wybierz 1."<<endl;
                    int kupuje=0;
                    cin>>kupuje;
                    if(kupuje==1)
                    {
                        g3.wsk->wlasnosc="Gracz_3";
                        g3.majatek=g3.majatek-g3.wsk->wartosc;
                    }
                    else
                    {
                        cout<<"Gracz "<<g3.nazwa_gracza<<" nie zdecydowal sie na zakup. Kolej na gracza "<<g4.nazwa_gracza<<endl;
                        if(g4.majatek>g3.wsk->wartosc)
                        {
                            cout<<"Majatek wynosi:"<<g4.majatek<<endl;
                            cout<<"Jesli chcesz kupic pole wcisnij 1. "<<endl;
                            int wybor2;
                            cin>>wybor2;
                            if(wybor2==1)
                            {
                                g4.majatek=g4.majatek - g3.wsk->wartosc;
                                g4.wsk->wlasnosc="Gracz_4";
                                cout<<"Udalo sie, "<<g4.nazwa_gracza<<" stales sie wlascicielem: "<<g3.wsk->nazwa<<endl;
                            }
                            else
                            {
                               cout<<"Kolejny gracz tez sie nie zdecydowal"<<endl;
                            }
                        }
                        else
                        {
                            cout<<g4.nazwa_gracza<<" niestety nie stac na zakup pola"<<endl;
                        }
                    }
                }
                else
                {
                    cout<<"Nie masz wystarczajaco duzo pieniedzy aby kupic hotel."<<endl;
                }
            }
            else if(g3.wsk->wlasnosc!="Gracz_3" and g3.wsk->wlasnosc!="Brak_wlasciciela")
            {
                cout<<"Nie jestes w swoim hotelu. Musisz zaplacic za nocleg!!"<<endl
                <<"Czynsz wynosi: "<<g3.wsk->czynsz<<endl;
                g3.majatek=g3.majatek-g3.wsk->czynsz;
                if(g3.wsk->wlasnosc=="Gracz_1")
                {
                    g1.majatek=g1.majatek+g3.wsk->czynsz;
                }
                if(g3.wsk->wlasnosc=="Gracz_2")
                {
                    g2.majatek=g2.majatek+g3.wsk->czynsz;
                }
                if(g3.wsk->wlasnosc=="Gracz_4")
                {
                    g4.majatek=g4.majatek+g3.wsk->czynsz;
                }
            }
        }
        if(g3.wsk->nazwa=="_PODATEK_")
        {int wybor=1;
            cout<<"Niestety musisz zaplacic PODATEK. Masz 2 opcje: 1.Placisz 200  2.Placisz 10% swojego majatku. "<<endl
            <<"Jesli chcesz zaplacic staly podatek o wartosci 200 wybierz 1."<<endl<<" W przeciwnym wypadku zaplacisz podatek o wartosci10% swojego majatku. "<<endl;
            cout<<endl<<" Twoj majatek: "<<g3.majatek<<endl;
            cin>>wybor;
            if(wybor==1)
            {
                g3.majatek=g3.majatek-200;
            }
            else
            {
                cout<<endl<<"majatek: "<<g3.majatek<<"    podatek: "<<g3.majatek*0.1<<endl;
                g3.majatek=g3.majatek- g3.majatek*0.1; /// majatek ma wartosci calkowite, podatek jest wiec zaokraglany do wart calkowitej
            }
        }

        if(g3.wsk->nazwa=="WIEZIENIE")
        {
            if(g3.wiezien==0) ///-->> trafilem do wiezienia 1 raz
            {
                cout<<"Ty BANDYTO, PRZESTEPCO !!! Zlapalismy Cie wreszcie!! "<<endl<<" Trafisz do wiezienia, chyba ze wplacisz kaucje w wysokosci: 150 "<<endl
                <<"W przeciwnym wypadku bedziesz musial odsiedziec kare ->> 2 tury !! "<<endl<<"Jesli chcesz wplacic kaucje wybierz 1. "<<endl
                <<"W przeciwnym wypadku bedziesz czekac 2 tury "<<endl;

                int wybor=1;
                cin>>wybor;
                if(wybor==1)
                {
                    cout<<"Zdecydowales sie wplacic kaucie. "<<endl;
                    g3.majatek=g3.majatek-150;
                }
                else
                {
                    cout<<"Wybrales wiezienie. Rozgosc sie w swojej celi ! :) "<<endl;
                     g3.wiezien=2;
                }
            }
            else
            {
                g3.wiezien=g3.wiezien-1;
                g3.wsk=g3.ruch_wp(g3.wsk,40);cout<<" "<<g3.wsk->nazwa<<endl;
            }

        }

        if(g3.wsk->nazwa=="KARTA")
        {
            cout<<"Jestes na polu w ktorym wylosujesz karte. Moze Ci przyniesc szczescie lub pecha "<<endl
            <<"zaraz sie przekonasz. "<<endl;
            int karta=0;
            karta=rand()%4+1;
            switch(karta)
            {
            case 1:
                cout<<"Dostales BONUS w wysokosci 200: "<<endl;
                g3.majatek=g3.majatek+200;
                break;
            case 2:
                cout<<"Dostales KARE w wysokosci 200: "<<endl;
                g3.majatek=g3.majatek-200;
                break;
            case 3:
                cout<<"Dostales BONUS w wysokosci 50: "<<endl;
                g3.majatek=g3.majatek+50;
                break;
            case 4:
                cout<<"Dostales KARE w wysokosci 50: "<<endl;
                g3.majatek=g3.majatek-50;
                break;

            }
        }

    }
    else if(g3.wiezien!=0)
    {
        cout<<endl<<"           "<<g3.wsk->nazwa<<endl<<"Jestes w wiezieniu, odsiadujesz swoj wyrok"<<endl;
        g3.wiezien=g3.wiezien-1;
        g3.wsk=g3.ruch_wp(g3.wsk,40);cout<<" "<<g3.wsk->nazwa<<endl;
    }
    else
    {
        cout<<" Z B A N K R U T O W A L E S  !!!"<<endl<<"Przegrales..."<<endl<<endl;
         g3.del_majatek("Gracz_3",g3.wsk);
    }


cout<<endl<<endl<<"         WCISNIJ DOWOLNY KLAWISZ ABY KONTYNUOWAC GRE !!      "<<endl<<endl;
cin>>dalej;


///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------
///------------------------------------- G R A C Z _ 4 -----------------------------------------------
///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------

cout<<endl<<endl<<endl<<"           Tura  dla: Gracz_4"<<endl;
    if(g4.majatek>0 and g4.wiezien==0)
    {
        liczba_oczek=rzut();
        cout<<endl<<"Wylosowano --> "<<liczba_oczek<<endl;
        g4.wsk=g4.ruch_wp(g4.wsk,liczba_oczek);cout<<" "<<g4.wsk->nazwa<<endl;
        if(g4.wsk->nazwa=="SKOK")
        {
            cout<<"Trafiles na pole: "<<g4.wsk->nazwa<<". Mozesz zdecydowac o ile miejsc chcesz przejsc dalej."<<endl
            <<"Wpisz liczbe o ile chcesz przeskoczyc "<<endl;
            int skok=0;
            cin>>skok;
                 ///
            cout<<"Wartosc skoku: "<<skok<< " "<<endl;
            int xxx;
            cin>>xxx;
            ///
            cout<<endl<<"Wbrales skok o --> "<<skok<<" pol "<<endl;
            g4.wsk=g4.ruch_wp(g4.wsk,skok);cout<<" "<<g4.wsk->nazwa<<endl;
            cout<<"Wyladowales w: "<<g4.wsk->nazwa<<endl<<endl;
        }
        if(g4.wsk->nazwa!="KARTA" and g4.wsk->nazwa!="HOTEL" and g4.wsk->nazwa!="START" and g4.wsk->nazwa!="kolko" and g4.wsk->nazwa!="SKOK" and g4.wsk->nazwa!="_PODATEK_" and g4.wsk->nazwa!="WIEZIENIE" and g4.wsk->nazwa!="BEZPLATNY_POSTOJ" )  /// jest to jakies miasto
        {
            cout<<"Wyladowales w: "<<g4.wsk->nazwa<<endl<<endl;
            if(g4.wsk->wlasnosc=="Gracz_4")
            {
                cout<<"To pole nalezy do Ciebie!! Czuj sie jak u siebie w domu. :) "<<endl;
            }
           if(g4.wsk->wlasnosc=="Brak_wlasciciela") /// mozna kupowac
           {    cout<<"Majatek "<<g4.nazwa_gracza<<" wynosi: "<<g4.majatek<<endl;
               if(g4.majatek>g4.wsk->wartosc)
               {
                    cout<<"Stac Cie kupic to pole, do nikogo nie nalezy. "<<g4.wsk->nazwa<<endl<<"Koszt zakupu wynosi: "<<g4.wsk->wartosc<<endl<<endl;
                    cout<<"Jesli chcesz kupic to pole wcisnij 1. "<<endl;
                    int wybor1;
                    cin>>wybor1;
                    if(wybor1==1)
                    {
                        g4.majatek=g4.majatek - g4.wsk->wartosc;
                        g4.wsk->wlasnosc="Gracz_4";
                        cout<<"Udalo sie, "<<g4.nazwa_gracza<<" stales sie wlascicielem: "<<g4.wsk->nazwa<<endl;
                    }
                    else
                    {
                        cout<<"Gracz "<<g4.nazwa_gracza<<" nie zdecydowal sie na zakup. Kolej na gracza "<<g1.nazwa_gracza<<endl;
                        if(g1.majatek>g4.wsk->wartosc)
                        {
                            cout<<"Majatek wynosi:"<<g1.majatek<<endl;
                            cout<<"Jesli chcesz kupic pole wcisnij 1. "<<endl;
                            int wybor2;
                            cin>>wybor2;
                            if(wybor2==1)
                            {
                                g1.majatek=g1.majatek - g4.wsk->wartosc;
                                g1.wsk->wlasnosc="Gracz_1";
                                cout<<"Udalo sie, "<<g1.nazwa_gracza<<" stales sie wlascicielem: "<<g4.wsk->nazwa<<endl;
                            }
                            else
                            {
                               cout<<"Kolejny gracz tez sie nie zdecydowal"<<endl;
                            }
                        }
                        else
                        {
                            cout<<g1.nazwa_gracza<<" niestety nie stac na zakup pola"<<endl;
                        }

                    }
               }
               else
               {
                  cout<<g4.nazwa_gracza<<" niestety nie stac na zakup pola"<<g4.wsk->nazwa<<endl;
               }
            }
           else if(g4.wsk->wlasnosc!="Gracz_4")  /// trzeba placic czynsz
           {
               cout<<"Niestety nie mozesz kupic pola. "<<g4.wsk->nazwa<<" Nalezy do innego gracza."<<endl
               <<" Musisz zaplacic czynsz o wartosci:"<<g4.wsk->czynsz<<endl;
               g4.majatek=g4.majatek-g4.wsk->czynsz;
                if(g4.wsk->wlasnosc=="Gracz_1")
                {
                    g1.majatek=g1.majatek+g4.wsk->czynsz;cout<<"majatek Gracza_1: "<<g1.majatek<<endl;
                }
                   if(g4.wsk->wlasnosc=="Gracz_2")
                {
                    g2.majatek=g2.majatek+g4.wsk->czynsz;cout<<"majatek Gracza_2: "<<g2.majatek<<endl;
                }
                   if(g4.wsk->wlasnosc=="Gracz_3")
                {
                    g3.majatek=g3.majatek+g4.wsk->czynsz;cout<<"majatek Gracza_4: "<<g4.majatek<<endl;
                }

            }
        }
         if(g4.wsk->nazwa=="Kasyno" and g4.wsk->wlasnosc!="Gracz_4" and g4.wsk->wlasnosc!="Brak_wlasciciela")
                {
                    cout<<"Trafiles do kasyna !!. Jesli bedizesz miec szczescie, to wygrasz pieniadze, jesli nie to przegrasz 100!! "<<endl
                    <<"Wybierz jedna z cyfr od 0 do 9 !"<<endl;
                    int cyfra =rand()%10;
                    int podana_cyfra;
                    cin>>podana_cyfra;
                    if(podana_cyfra==cyfra)
                    {
                        cout<<"Udalo Ci sie!! Masz szczescie, wygrywasz 300 !!"<<endl;
                        g4.majatek=g4.majatek+300;
                    }
                    else
                    {
                        cout<<"Niestety, ale przegrales 100"<<endl;
                        g4.majatek=g4.majatek-100;
                    }
                }

        if(g4.wsk->nazwa=="START")
        {
            cout<<"Udalo Ci sie przejsc cala plansze, dostajesz bonus o wartosci: 100 "<<endl;
            g4.majatek=g4.majatek+100;
        }
        if(g4.wsk->nazwa=="HOTEL")
        {
            cout<<"Wyladowales w: "<<g4.wsk->nazwa<<endl<<endl;
            if(g4.wsk->wlasnosc=="Gracz_4")    ///-->jestes w swoim hotelu
            {
                cout<<"To Twoj hotel. Jesli chcesz mozesz go rozbudowac wybierajac 1. Rozbudowa kosztuje polowe aktualnej wartosci Hotelu "<<endl;
                int rozbudowa=0;
                cout<<"Aktualna wartosc hotelu: "<<g4.wsk->wartosc<<endl;
                cin>>rozbudowa;
                if(rozbudowa==1)
                {
                    cout<<"poziom-->>"<<g4.wsk->poziom<<" czynsz-->>"<<g4.wsk->czynsz<<"wartosc-->>"<<g4.wsk->wartosc<<endl;
                    g4.wsk->poziom=g4.wsk->poziom+1;
                    g4.wsk->czynsz=g4.wsk->czynsz+g4.wsk->czynsz;
                    g4.wsk->wartosc=g4.wsk->wartosc+0.5*g4.wsk->wartosc;
                    g4.majatek=g4.majatek-0.5*g4.wsk->wartosc;
                    cout<<"poziom-->>"<<g4.wsk->poziom<<" czynsz-->>"<<g4.wsk->czynsz<<"wartosc-->>"<<g4.wsk->wartosc<<endl;
                }
                else
                {
                    cout<<"Zdecydowales nie rozbudowywac narazie Hotelu. "<<endl;
                }
            }
            if(g4.wsk->wlasnosc=="Brak_wlasciciela")
            {
                if(g4.majatek>g4.wsk->wartosc)
                {
                    cout<<"Mozesz kupic hotel !!."<<endl<<" Bedziesz mogl go rozbudowywac i pobierac wieksze czynsze od innych graczy."<<endl
                    <<"Jesli chcesz kupic hotel wybierz 1."<<endl;
                    int kupuje=0;
                    cin>>kupuje;
                    if(kupuje==1)
                    {
                        g4.wsk->wlasnosc="Gracz_4";
                        g4.majatek=g4.majatek-g4.wsk->wartosc;
                    }
                    else
                    {
                        cout<<"Gracz "<<g4.nazwa_gracza<<" nie zdecydowal sie na zakup. Kolej na gracza "<<g1.nazwa_gracza<<endl;
                        if(g1.majatek>g4.wsk->wartosc)
                        {
                            cout<<"Majatek wynosi:"<<g1.majatek<<endl;
                            cout<<"Jesli chcesz kupic pole wcisnij 1. "<<endl;
                            int wybor2;
                            cin>>wybor2;
                            if(wybor2==1)
                            {
                                g1.majatek=g1.majatek - g4.wsk->wartosc;
                                g1.wsk->wlasnosc="Gracz_1";
                                cout<<"Udalo sie, "<<g1.nazwa_gracza<<" stales sie wlascicielem: "<<g1.wsk->nazwa<<endl;
                            }
                            else
                            {
                               cout<<"Kolejny gracz tez sie nie zdecydowal"<<endl;
                            }
                        }
                        else
                        {
                            cout<<g1.nazwa_gracza<<" niestety nie stac na zakup pola"<<endl;
                        }
                    }
                }
                else
                {
                    cout<<"Nie masz wystarczajaco duzo pieniedzy aby kupic hotel."<<endl;
                }
            }
            else if(g4.wsk->wlasnosc!="Gracz_4" and g4.wsk->wlasnosc!="Brak_wlasciciela")
            {
                cout<<"Nie jestes w swoim hotelu. Musisz zaplacic za nocleg!!"<<endl
                <<"Czynsz wynosi: "<<g4.wsk->czynsz<<endl;
                g4.majatek=g4.majatek-g4.wsk->czynsz;
                if(g4.wsk->wlasnosc=="Gracz_1")
                {
                    g1.majatek=g1.majatek+g4.wsk->czynsz;
                }
                if(g4.wsk->wlasnosc=="Gracz_2")
                {
                    g2.majatek=g2.majatek+g4.wsk->czynsz;
                }
                if(g4.wsk->wlasnosc=="Gracz_3")
                {
                    g3.majatek=g3.majatek+g4.wsk->czynsz;
                }
            }
        }
        if(g4.wsk->nazwa=="_PODATEK_")
        {int wybor=1;
            cout<<"Niestety musisz zaplacic PODATEK. Masz 2 opcje: 1.Placisz 200  2.Placisz 10% swojego majatku. "<<endl
            <<"Jesli chcesz zaplacic staly podatek o wartosci 200 wybierz 1."<<endl<<" W przeciwnym wypadku zaplacisz podatek o wartosci10% swojego majatku. "<<endl;
            cout<<endl<<" Twoj majatek: "<<g4.majatek<<endl;
            cin>>wybor;
            if(wybor==1)
            {
                g4.majatek=g4.majatek-200;
            }
            else
            {
                cout<<endl<<"majatek: "<<g4.majatek<<"    podatek: "<<g4.majatek*0.1<<endl;
                g4.majatek=g4.majatek- g4.majatek*0.1; /// majatek ma wartosci calkowite, podatek jest wiec zaokraglany do wart calkowitej
            }
        }

        if(g4.wsk->nazwa=="WIEZIENIE")
        {
            if(g4.wiezien==0) ///-->> trafilem do wiezienia 1 raz
            {
                cout<<"Ty BANDYTO, PRZESTEPCO !!! Zlapalismy Cie wreszcie!! "<<endl<<" Trafisz do wiezienia, chyba ze wplacisz kaucje w wysokosci: 150 "<<endl
                <<"W przeciwnym wypadku bedziesz musial odsiedziec kare ->> 2 tury !! "<<endl<<"Jesli chcesz wplacic kaucje wybierz 1. "<<endl
                <<"W przeciwnym wypadku bedziesz czekac 2 tury "<<endl;

                int wybor=1;
                cin>>wybor;
                if(wybor==1)
                {
                    cout<<"Zdecydowales sie wplacic kaucie. "<<endl;
                    g4.majatek=g4.majatek-150;
                }
                else
                {
                    cout<<"Wybrales wiezienie. Rozgosc sie w swojej celi ! :) "<<endl;
                     g4.wiezien=2;
                }
            }
            else
            {
                g4.wiezien=g4.wiezien-1;
                g4.wsk=g4.ruch_wp(g4.wsk,40);cout<<" "<<g4.wsk->nazwa<<endl;
            }

        }

        if(g4.wsk->nazwa=="KARTA")
        {
            cout<<"Jestes na polu w ktorym wylosujesz karte. Moze Ci przyniesc szczescie lub pecha "<<endl
            <<"zaraz sie przekonasz. "<<endl;
            int karta=0;
            karta=rand()%4+1;
            switch(karta)
            {
            case 1:
                cout<<"Dostales BONUS w wysokosci 200: "<<endl;
                g4.majatek=g4.majatek+200;
                break;
            case 2:
                cout<<"Dostales KARE w wysokosci 200: "<<endl;
                g4.majatek=g4.majatek-200;
                break;
            case 3:
                cout<<"Dostales BONUS w wysokosci 50: "<<endl;
                g4.majatek=g4.majatek+50;
                break;
            case 4:
                cout<<"Dostales KARE w wysokosci 50: "<<endl;
                g4.majatek=g4.majatek-50;
                break;

            }
        }

    }
    else if(g4.wiezien!=0)
    {
        cout<<endl<<"           "<<g4.wsk->nazwa<<endl<<"Jestes w wiezieniu, odsiadujesz swoj wyrok"<<endl;
        g4.wiezien=g4.wiezien-1;
        g4.wsk=g4.ruch_wp(g4.wsk,40);cout<<" "<<g4.wsk->nazwa<<endl;
    }
    else
    {
        cout<<" Z B A N K R U T O W A L E S  !!!"<<endl<<"Przegrales..."<<endl<<endl;
         g4.del_majatek("Gracz_4",g4.wsk);

    }





cout<<endl<<endl<<"         WCISNIJ DOWOLNY KLAWISZ ABY KONTYNUOWAC GRE !!      "<<endl<<endl;
cin>>dalej;








if(g1.majatek>0 and g2.majatek<=0 and g3.majatek<=0 and g4.majatek<=0 )
{
    cout<<endl<<endl<<"K O N I E C    G R Y !! "<<endl<<"Wygral -->> "<<g1.nazwa_gracza;break;
}
if(g1.majatek<=0 and g2.majatek>0 and g3.majatek<=0 and g4.majatek<=0)
{
    cout<<endl<<endl<<"K O N I E C   G R Y !! "<<endl<<"Wygral -->> "<<g2.nazwa_gracza;break;
}
if(g3.majatek>0 and g1.majatek<=0 and g2.majatek<=0 and g4.majatek<=0 )
{
    cout<<endl<<endl<<"K O N I E C    G R Y !! "<<endl<<"Wygral -->> "<<g3.nazwa_gracza;break;
}
if(g4.majatek>0 and g1.majatek<=0 and g2.majatek<=0 and g2.majatek<=0 )
{
    cout<<endl<<endl<<"K O N I E C    G R Y !! "<<endl<<"Wygral -->> "<<g4.nazwa_gracza;break;
}




}///-------- KONIEC WHILE'a -------------


cout<<endl<<endl;
//P.show();
cout<<endl<<endl;
//P.show_rev();
    return 0;
}


