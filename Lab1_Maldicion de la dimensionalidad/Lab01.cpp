#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <cstdlib> 

using namespace std;

double distanciaEuclidiana(const vector<double>& punto1, const vector<double>& punto2) {
	if (punto1.size() != punto2.size()) {
		cerr << "Los puntos tienen dimensiones diferentes." << endl;
		return -1.0;  // Valor de error
	}
	
	double distancia = 0.0;
	for (size_t i = 0; i < punto1.size(); ++i) {
		distancia += pow(punto1[i] - punto2[i], 2);
	}
	
	return sqrt(distancia);
}
vector<vector<double>> Puntos(int columnas){
	int x=100;
	//cin>>x;
	int filas = x;
	//int d;
	//cin>>d;
	//int columnas = d;
	vector<vector<double>> vec(filas, std::vector<double>(columnas));
	
	//cin>>d;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<> dis(0.0, 1.0);
	for (int n = 0; n < x; ++n){
		for(int i=0;i<columnas;i++){
			vec[n][i] =dis(gen);
		}
		
	}
	return vec;

}
void Run_Python(){
	int result = std::system("python3 Graficos.py"); 
	if (result == 0) {
        std::cout << "El script de Python se ejecutó exitosamente." << std::endl;
    } else {
        std::cerr << "Error al ejecutar el script de Python." << std::endl;
    }
}
int main(){
	ofstream archivo("distancias.txt");	int d;
	if (!archivo.is_open()) {
		cerr << "No se pudo abrir el archivo de salida." << endl;
		return 1;
	}
	cin>>d;
	//int columnas = d;
	int k=1;
	vector<vector<double>> vec =Puntos(d);
	archivo <<d<<endl;
	for (int i = 0; i < 100; ++i) {
		for (int j = i + 1; j < 100; ++j) {
			double dist = distanciaEuclidiana(vec[i], vec[j]);
			cout <<k<<") Distancia entre punto " << i << " y punto " << j << ": " << dist << endl;
			archivo <<dist<<endl;
			k++;
		}
	}
	archivo.close();
	/*
	for(int i=0; i<100;i++){
		cout<<i+1<<"_ (";
		for (int j=0; j<d;j++){
			cout<<vec[i][j]<<",";
		}
		cout<<")"<<endl;
	}*/
	Run_Python();
	return 0;
}

