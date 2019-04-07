#include <iostream>
#include "polinom.h"
// C:\cygwin\bin\c++.exe

//constructori
//1. constructor fara parametri
polinom :: polinom ()
{
    nrCoeficienti=1;
    coeficienti= new float [1];
    coeficienti[0]=0;
}
//2. constructor cu parametru- parametrul este numarul de elemente al vectorului coeficienti si nr-1 reprezinta gradul polinomului pe care il creez
polinom :: polinom( int nr){
    nrCoeficienti=nr;
    coeficienti= new float [nrCoeficienti];
}

//destructor
polinom ::~polinom() {
    delete [] coeficienti;
}

//copy constructor
polinom :: polinom (const polinom& poli) {
    //copiez in polinomul curent datele din polinomul poli
    nrCoeficienti= poli.nrCoeficienti;
    //aloc memorie pentru vectorul de coeficienti al polinomului curent
    coeficienti= new float [nrCoeficienti];
    for( int i=0; i< nrCoeficienti; i++)
        coeficienti[i]=poli.coeficienti[i];
}

//adaugarea unui termen de grad i
void polinom ::adaugareTermen( int i , float coef) {
    //verific daca termenul pe care vreau sa-l adaug are gradul mai mare sau mai mic decat gradul polinomului curent
    if ( i < nrCoeficienti )
        coeficienti[i]+=coef;// in acest caz, adun la  valoarea coeficienului de pe pozitia i coef
    else{
        float *array;
        //creez un vector ce contine elementele polinomului curent, zero- uri incepand de la pozitia nrCoeficienti, pana la i-1 si pe pozitia i, adaug coef
        array=new float [i+1];
        for(int j=0; j<=i; j++)
            array[j]=0;
        for(int j=0; j<nrCoeficienti;j++)
            array[j]=coeficienti[j];
        array[i]=coef;
        delete[]coeficienti;// dezaloc memoria ocupata initial de polinomul curent
        nrCoeficienti=i+1;// actualizez numarul de coeficienti
        coeficienti=array;// acum coeficienti pointeaza spre noul vector de coeficienti

    }
}

//eliminarea unui termen de grad i
void polinom ::eliminareTermen(int i) {
    if( i >= nrCoeficienti ) return;
    else {
        coeficienti[i]=0;
        // verific daca s-a modificat gradul polinomului si daca da, il realoc doar pentru dimensiunea pe care o necesita
        int j= nrCoeficienti-1;
        while ((j >=0)&&(coeficienti[j]==0)) j--;
        if (j==nrCoeficienti-1) return  ;//nu s-a modificat gradul polinomului
        else {
            float *array;
            array= new float [j+1];
            for(int k=0;k<=j;k++)
                array[k]=coeficienti[k];
            delete [] coeficienti;
            nrCoeficienti=j+1;
            coeficienti=array;
            // acum (nrCoeficient-1) reprezinta gradul polinomului
        }

    }
}

//valoarea polinomului intr-un punct x
float polinom ::valoarePolinom(float x) {
    int i=0;
    float P=coeficienti[i];// primul element din suma polinomului
    while( i < nrCoeficienti ) {
        P += coeficienti[i] * pow(x, i);
        i++;
    }
    return P;
}

// supraincarcarea operatorului +
polinom polinom :: operator+ (polinom poli ) {
    polinom temp;
    int nr,i;
    nr=nrCoeficienti>poli.nrCoeficienti? nrCoeficienti: poli.nrCoeficienti;//nr va lua valoarea cea mai mare dintre cele 2
    temp.nrCoeficienti=nr;
    temp.coeficienti=new float [nr];// aloc memorie pentru noul polinom
    for( i=0; i< nr-abs(nrCoeficienti-poli.nrCoeficienti); i++)
        temp.coeficienti[i]=coeficienti[i]+poli.coeficienti[i];//coeficientii termenilor cu acelasi grad se vor aduna
    //pentru termenii cu grade ce apartin doar unui polinom (le agaugam pe pozitiile corespunzatoare)
    if(nrCoeficienti>poli.nrCoeficienti)
        for(i=poli.nrCoeficienti;i<nr;i++)
            temp.coeficienti[i]=coeficienti[i];
    else
        for ( i=nrCoeficienti; i<nr; i++)
            temp.coeficienti[i]=poli.coeficienti[i];
    return temp;
}

//supraincarcarea operatorului =
polinom polinom ::operator= (polinom poli) {
    delete [] coeficienti;
    nrCoeficienti= poli.nrCoeficienti;
    coeficienti= new float [nrCoeficienti];
    for( int i=0; i< nrCoeficienti; i++)
        coeficienti[i]=poli.coeficienti[i];
    return *this; //polinomul curent in care s-a actualizat informatia cu date din polinomul o
}

//returnarea gradului polinomului
int polinom ::gradPolinom(polinom poli) {
    return poli.nrCoeficienti-1; // gradul polinomului va fi cu 1 mai mic decat numarul de coeficienti pentru ca incepe de la gradul 0
}

// supraincarcarea operatorului [] pt a obtine termenul de pe pozitia i
float polinom :: operator[] (int i){
    if((i<0)||(i>=nrCoeficienti)) return 0; //i nu este grad al polinomului, deci nu are coeficienti
    else return coeficienti[i]; //returneaza coeficientul termenului de grad i
}

//suprincarcareaa operatorului *
// 1. inmultirea polinomului cu un numar intreg
polinom operator*(int a, polinom poli) {
    polinom temp;
    //aloc memorie pentru polinmul in care se va face imultirea
    temp.nrCoeficienti = poli.nrCoeficienti;
    temp.coeficienti = new float [temp.nrCoeficienti];
    for (int i=0; i< poli.nrCoeficienti; i++ )
        temp.coeficienti[i]= a * poli.coeficienti[i];
    return temp; //returnez polinomul obtinut
}
// 2. inmultirea a doua polinoame
polinom operator* (polinom poli1, polinom poli2){
    polinom temp;
    int i, j;
    temp.nrCoeficienti = poli1.nrCoeficienti+ poli2.nrCoeficienti-1; // deoarece prin inmultirea polinoamelor se va obtine un polinomde grad egal cu suma gradelor lor, si cum indexarea se face de la 0, trebuie sa adaugam 1
    temp.coeficienti = new float [temp.nrCoeficienti];
    for(i=0; i< temp.nrCoeficienti; i++)
        temp.coeficienti[i]=0;//este posibil ca nu toate elementele sa se actualizeze asa ca, pe acele pozitii, se vor gasi valori reziduale, motiv pentru care trebuie sa le actualizam cu valoarea 0
    i= 0;
    while(i<poli1.nrCoeficienti){
        // inmultim, actualizand fiecare coeficient, de fiecare data cand valoarea coeficientului de pe pozitia i este diferita de 0
        if(poli1.coeficienti[i]==0) i++;
        else
        { j=0;
            while( j< poli2.nrCoeficienti){
                if(poli2.coeficienti[j]==0) j++; //adunarea cu 0 nu schimba coeficientii asa ca trecem mai departe
                else{
                    temp.coeficienti [i+j] += poli1.coeficienti[i]*poli2.coeficienti[j];
                    j++;}
            }
            i++;}
    }
    return temp;
}
//supraincarcarea operatorului / pentru impartirea a 2 polinoame

polinom operator/ ( polinom poli1, polinom poli2 ){ // in acest caz, deimpartitul este poli1 si impartitorul este poli2
    polinom cat;
    //verificam daca polinomul poli1 poate fi impartit la poli2
    if( poli1.nrCoeficienti < poli2.nrCoeficienti ) return cat;//daca impartirea nu este posibila
    else {//daca impartirea este posibila
        cat.nrCoeficienti=poli1.nrCoeficienti-poli2.nrCoeficienti+1;//gradul polinomului cat va fi diferenta gradelor polinoamelor impartite, dar va avea un element in plus deoarece pleaca de la gradul 0
        cat.coeficienti=new float [cat.nrCoeficienti];
        for(int k=0; k<cat.nrCoeficienti; k++)
            cat.coeficienti[k]=0;//zona de memorie ocupata trebuie intitializata cu 0 deoarece, nu toti termenii se vor actualiza si vor ramane valori reziduale
        int i, j;
        // parcurgem fiecare termenii deimpartitului si impartitorului de la termenul cu gradul cel mai mare
        i = poli1.nrCoeficienti - 1;
        j = poli2.nrCoeficienti - 1;
        while (j <= i) {
            if ( poli1.coeficienti[i] == 0 ) i--; // inseamna ca termenul de grad i este 0 si nu avem de facut aceasta impartire
            if(poli2.coeficienti[j]== 0) j--;
            else {
                cat.coeficienti[i-j]=poli1.coeficienti[i]/poli2.coeficienti[j];// obtin astfel coeficientul termenului degrad i-j al cat-ului
                //actualizez polinomul pe care il impart
                for(int k=0; k<=j; k++)
                    poli1.coeficienti[k+i-j] -= poli2.coeficienti[k]*cat.coeficienti[i-j];//se actualizeaza coeficientii
                //dupa efectuarea acestor pasi, coeficientul termenului de grad i va fi 0 asa ca putem trece la impartirea termenului de grad i-1
            }
            i--;
        }
    }
    return cat;
}

//supraincarcarea operatorului de iesire <<
ostream &operator<< (ostream & out, const polinom& poli){
    int i=0, ok=0;
    if(poli.coeficienti[i]!=0)
    {out<<poli.coeficienti[i]<<"*X^0 ";
        ok=1;}
    i++;
    while(i< poli.nrCoeficienti){
        if((poli.coeficienti[i]>0)&&(ok==0))
            out<<poli.coeficienti[i]<<"*X^"<<i<<" ";
        if((poli.coeficienti[i]>0)&&(ok==1))
            out<<"+"<<poli.coeficienti[i]<<"*X^"<<i<<" ";
        if(poli.coeficienti[i]<0)
            out<<poli.coeficienti[i]<<"*X^"<<i<<" ";
        i++;
    }
    return out;
}

//supraincarcarea operatorului de intrarea >>
istream &operator>> (istream & in, polinom &poli){
    int i;
    delete [] poli.coeficienti;
    in>>poli.nrCoeficienti;
    poli.coeficienti=new float [poli.nrCoeficienti];//aloc memorie pentru polinomul poli
    //poli(poli.nrCoeficienti);
    for(i=0; i<poli.nrCoeficienti; i++)
        in>>poli.coeficienti[i];
    // poli=temp;
    return in;
}
int main() {
polinom a(6), b, c,d,e;
    a.adaugareTermen(0,-6);
    a.adaugareTermen(1,6);
    a.adaugareTermen(2,-3);
    a.adaugareTermen(3,9);
    a.adaugareTermen(5,3);
    a.adaugareTermen(6,1);
    //cout<<a[3];
   a.eliminareTermen(6);
    cout<<a;
    cout<<endl<<a.gradPolinom(a)<<endl;
    b.adaugareTermen(0,-1);
    b.adaugareTermen(1,1);
    b.adaugareTermen(3,1);
    cout<<b;
    c=b;
    cout<<endl;
    cout<<c;
    cout<<endl;
    c=a/b;
    cout<<c;
    cout<<endl;
    c=c+b;
    cout<<c;
    c=2*c;
    cout<<endl;
    cout<<c;
    cout<<endl;
    d.adaugareTermen(0,1);
    d.adaugareTermen(1,4);
    e.adaugareTermen(2,1);
    e.adaugareTermen(0,3);
    e=d*e;
    cout<<e;
    polinom f;
    cout<<endl<<"Dati numarul de coeficienti si coeficientii polinomului: ";
    cin>>f;
    cout<<f;
    return 0;
}