#include <time.h>
#include <iostream>
#include <vector>
#define _null NULL

using namespace std;

int Roleta(vector<float> fitnes);

vector<float> somaCumulativa(vector<float> v);


int main(){
	int n=10, popSize=5;
    vector<vector<int>> populacao;
    vector<vector<int>> novaGeracao;
    vector<int> sort;
    vector<float> fitness;
    fitness.push_back(0.12);
    fitness.push_back(0.534);
    fitness.push_back(0.348);
    fitness.push_back(0.15);
    fitness.push_back(0.851);
    fitness.push_back(0.1523);
    vector<vector<int>> indCruza;
    int sorteado;
    int b = 20;
    vector<int> p, a;

    for(int i=0;i<n;i++){
        p.push_back(i+1);
        a.push_back(n-i);
    }

    vector<float> copfitness;
    for(int i=0;i<fitness.size();i++){
        copfitness.push_back(fitness[i]);
    }

    for(int i=0;i<copfitness.size()/2;i++){

    		sorteado = Roleta(copfitness);
            sort.push_back(sorteado);
            copfitness.insert(copfitness.begin()+ sorteado,0);
    		
    		sorteado = Roleta(copfitness);
            
            sort.push_back(sorteado);
            copfitness.insert(copfitness.begin() + sorteado,0);
    		indCruza.push_back(sort);
            sort.clear(); 
    }

    for(int i=0;i<popSize;i++){    
    	cout << "Pai: " <<indCruza[i][0] << " Mãe: "<<indCruza[i][1]<< endl;

    }

}

/// realiza o sorteio dos valores passados
int Roleta(vector<float> fitnes){
    
    int sorteado;
    int p;
    vector<float> numerosDaSorte = somaCumulativa(fitnes);
    
	srand(time(NULL));
    vector<int> numInt;
    cout << "aqui 1" << endl;
    for(int i = 0;i<numerosDaSorte.size();i++){
        numInt.push_back(100*numerosDaSorte[i]);
        //cout << 100*numerosDaSorte[i] << " ";
        //cout << numInt[i]<< " ";
    }
	int random;
    random = numInt.back();
    p = (rand() % random)+1;
    cout << "randomico "<< p <<endl;
	sorteado = -1;
    
	for(int i=0;i<numerosDaSorte.size();i++){
		if(numInt[i] > p){
			sorteado = i;
			break;
		}
	}
    numerosDaSorte.clear();
    numInt.clear();
    cout << "sort "<< sorteado <<endl;
    return sorteado;

}

// constroi o range da roleta
vector<float> somaCumulativa(vector<float> v){
    
    std::vector<float> acumulacao;
    acumulacao.push_back(v[0]);
    for(int i=0; i<v.size()-1;i++){
        acumulacao.push_back(acumulacao[0+i]+v[1+i]);
    }
    return acumulacao;

}