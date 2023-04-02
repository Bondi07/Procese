#include <iostream>
#include<time.h>
#include<queue>
#include<vector>


#define Imin 100 //TIMPU INTRE PROCESSE
#define Imax 500

#define DelMin 10   //VIATA UNUI PROCESS
#define DelMax 2500


using namespace std;

int TS = 100000; //TIMPUL SIMULARII
int q = 60; //DURATA CUANTEI
int n = 0; //NUMARUL DE PROCESE
int p = 0; //NUMAR DE PROCESE READY
float mediaProcese = 0;//MEDIA PROCESULUI

vector<int> t;//CAND E INCARCAT PROCESUL
vector<int> r;//DISTANTA DINTRE PROCESE
vector<int> Procese;//ARE FIECARE PROCES IN EL
vector<int> viataProcese;//DURATA FIECARUIA PROCES
queue<int> proceseReady;//TOTAE PROCESE IN COADA PE CARE LE SCOATE SI LE ADAUGA LA SFRSIT




//FUNCTIA CARE SCADE VIATA PROCESULUI IN CUANTA PRIMITA CA PARAMETRU
void noua_viata_proces(int NrProces, int NrCuanta)
{
    viataProcese[NrProces] -= q;//SCADEM VIATA
    if(viataProcese[NrProces] <= 0)//DACA E 0 ATUNCA S-A TERMINAT PROCESUL
    {
        cout<<endl<<"Procesul numarul "<<NrProces+1<<" s-a terminat la cuanta: "<<NrCuanta;
        p--;// SCADEM NR DE PROCESE READY
        proceseReady.pop();//SCOATEM PROCESU DIN COADA
        cout<<endl;
        cout<<"Procese Ready ramase: "<<p<<": ";//AFISAZA CATE PROCESE READY SUNT
        int mCoada = proceseReady.size(); //MCOADA = MARIMEA COZII
        int i = 1, p;
        //AFISEAZA ELEMENTE DIN COADA
        while(i <= mCoada)
        {
            p = proceseReady.front();//LUAM PRIMUL ELEMENT DIN COADA
            cout<<p+1<< " ";//AFISAM ACEL PROCES
            proceseReady.pop();//SCOATEM PRIM ELEM
            proceseReady.push(p);//IL BAGAM IN SPATE COZII
            i++;//CRESTE NR.CATE PROCESE AM SCOS DIN COADA SI AM BAGAT INAPOI

        }
        cout<<endl;

    }
    //DACA NU SA TERMINAT PROCESUL
    else
    {
        proceseReady.push(NrProces);//BAGAM ELEMENTUL IN SPATELE COZII
        proceseReady.pop();//SCOATEM ELEM DIN COADA

    }

}


int main()
{

    int i;
    cout<<"Durata simulari: "<<TS<<endl;
    cout<<"Durata cuantei: "<<q<<endl;
    cout <<"Introduce numaru de procese : ";
    cin>>n;
    cout<<endl;

    //
    srand (time(NULL));
    for( i=0;i<n;i++)
    {
        r.push_back(rand() %Imax + Imin); //DISTANTA PANA LA PROCESUL VIITOR
        // IN IF => DACA PROCESE NU SUNT CREATE PANA ACUM PROCESUL ESTE 0 + R
        if(i==0)
            t.push_back(0 + r.back());//ADAUGA MOMENTUL  CAND A FOST CREAT PRIMU PROCES

        //DACA EXISTA PROCESUL FACUT MOMENTUL IN CARE E CREAT PROCESUL
        //T => POZITIA UNDE E CREAT PROCES
        //R => DINSTANTA DINTRE PROCESUL TRECUT SI PROCESUL DE ACUM
        else
            t.push_back(t.back() + r.back());//

        viataProcese.push_back(rand() % DelMax + DelMin);//CREAZA VIATA PROCESULUI
        mediaProcese += viataProcese[i];
    }




    int NrCuanta = 0;
    int NrProces = 0;
    for(i=0;i<TS;i++)
    {

        //DACA INCEPE CUANTA
        if(i % q == 0)
        {
            //VERIFICA SA NU FIE COADA GOALA
            if(!proceseReady.empty())
            {
                int procesRunning = proceseReady.front();//PRIMU PROCES DIN CUANTA
                noua_viata_proces(procesRunning, NrCuanta);//

            }
            NrCuanta++;//CRESTE CUANTA
        }

        if(i == t[NrProces])// DACA I = POZITIA UNDE SA CREAT PROCESUL
        {
            Procese.push_back(NrProces);// ADOUGAM PROCES
            cout<<endl<<"Procesul numarul "<<NrProces+1<<" a fost creat la cuanta "<<NrCuanta<<", la momentul: "<<t[NrProces];
            cout<<endl<<"Viata procesului: "<<viataProcese[NrProces]<<endl;
            cout<<"Distanta dintre procesul actual si trecut: "<<r[NrProces]<<endl;
            cout<<endl;
            proceseReady.push(NrProces);//ADAUGAM IN COADAS
            NrProces++;// CRESTE NR PROCESULUI
            p++;// NUMARU DE PROCESE READY CRESTE

        }
    }

    cout<<endl<<"Numar total de cuante: "<<NrCuanta<<endl;


    mediaProcese = mediaProcese / Procese.size();
    cout<<"Durata medie a unui proces: "<<mediaProcese<<endl;

    return 0;

}
