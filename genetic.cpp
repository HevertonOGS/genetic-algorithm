#include <iostream>
#include <random>
#include <vector>

#define TAM_POPULACAO 3

using namespace std;

typedef struct {
  int id;
  int tamanho;
  int quantidade;
} Demanda;

int tamBarra, qtdeItens;
vector<Demanda> demandas;
vector<vector<int>> populacao;

// Referência https://www.cplusplus.com/reference/random/
int gerarAleatorio(int valorInicial, int valorFinal){
  random_device semente;
  default_random_engine gerador(semente());
  uniform_int_distribution<default_random_engine::result_type> intervalo(valorInicial, valorFinal); 

  return intervalo(gerador);
}

vector<int> gerarIndividuos(){
  vector<int> individuos;
  vector<Demanda> demandaInterna = demandas;

  while(!demandaInterna.empty()){
    int i = gerarAleatorio(0, demandaInterna.size()-1);

    int itemId = demandaInterna[i].id;
    individuos.push_back(itemId);
    demandaInterna[i].quantidade--;
    if(demandaInterna[i].quantidade == 0){
      demandaInterna.erase(demandaInterna.begin()+i);
    }
  }

  return individuos;
}

void imprimirPopuplacao(int populacaoId){
  cout << "População " << populacaoId << ":" << endl; 
  for(int j= 0; j < populacao[populacaoId].size(); j++){
    cout << populacao[populacaoId][j] << " ";
  }
  cout << endl << endl;
}

void gerarPopulacao(){
  for(int i= 0; i < TAM_POPULACAO; i++){
    populacao.push_back(gerarIndividuos());

    imprimirPopuplacao(i);
  }
}

int main(){
  cin >> tamBarra >> qtdeItens;

  for(int i = 0; i < qtdeItens; i++){
    Demanda aux;
    aux.id = i;
    cin >> aux.quantidade >> aux.tamanho;

    demandas.push_back(aux);
  }

  gerarPopulacao();
  return 0;
}