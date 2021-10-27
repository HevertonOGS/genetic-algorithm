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

typedef struct {
  vector<int> itens;
  int sobras;
} Padrao;

int tamBarra, qtdeItens;
vector<Demanda> demandas;
vector<vector<int>> populacao;
vector<vector<Padrao>> populacaoPadroes;

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

void imprimirPopuplacao(int individuoId){
  cout << "Indivíduo " << individuoId << ":" << endl; 
  for(int j= 0; j < populacao[individuoId].size(); j++){
    cout << populacao[individuoId][j] << " ";
  }
  cout << endl << endl;
}

void gerarPopulacao(){
  for(int i= 0; i < TAM_POPULACAO; i++){
    populacao.push_back(gerarIndividuos());

    imprimirPopuplacao(i);
  }
}

void imprimirPopuplacaoDecodificada(){
  for(int i = 0; i < populacaoPadroes.size(); i++){
    cout << "----------------------------------- " << endl;
    cout << "Indivíduo " << i << ":" << endl; 
    for(int j = 0; j < populacaoPadroes[i].size(); j++){
      cout << "Padrão " << j << ":" << endl; 
      cout << "Sobras: " << populacaoPadroes[i][j].sobras << endl; 
      cout << "itens: "; 
      for(int k = 0; k < populacaoPadroes[i][j].itens.size(); k++){
        cout << populacaoPadroes[i][j].itens[k] << " ";
      }
      cout << endl << endl;
    }
  }
}

void decodificar(){
  vector<vector<int>> populacaoInterna = populacao;

  for(int i = 0; i < populacaoInterna.size(); i++){
    vector<int> individuo = populacaoInterna[i];
    vector<Padrao> individuosPadroes;

    while(!individuo.empty()){
      individuosPadroes.push_back({sobras: tamBarra});
      int j = 0;

      while(j < individuo.size()){
        int item = individuo[j];

        if(demandas[item].tamanho <= individuosPadroes[individuosPadroes.size()-1].sobras){
          individuosPadroes[individuosPadroes.size()-1].itens.push_back(item);
          individuosPadroes[individuosPadroes.size()-1].sobras -= demandas[item].tamanho;
          individuo.erase(individuo.begin());
          j--;
        }

        j++;
      }
    }

    populacaoPadroes.push_back(individuosPadroes);
  }

  imprimirPopuplacaoDecodificada();
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
  decodificar();

  return 0;
}