#include <iostream>
#include <map>
#include <deque>
#include <algorithm>
#include <fstream>

void InitFile();
void EndFile();
void WriteDotLanguage(std::string v0, std::string v1);
bool HavelHakimiAlgorithm(std::deque<std::pair<std::string, int>>& nodes);

void SortData(std::deque<std::pair<std::string, int>>& nodes, bool display = false);
bool OrdernarPorValor(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
    return (a.second > b.second);
}

int main(){
    int numElementos;
    std::deque<std::pair<std::string, int>> nodes;

    std::cout << "Algoritmo de Havel Hakimi" << std::endl;
    InitFile();

    std::cout<<"Ingresa el numero de elementos:";
    std::cin>>numElementos;

    // filling the deque with data
    for(int i=0; i<numElementos; ++i){
        std::string node = "v" + std::to_string(i+1);
        int value;
        std::cout<<"ingresa el valor del nodo "<<node<<": ";
        std::cin>>value;
        nodes.push_back(make_pair(node, value));
    }
    
    SortData(nodes, true);
    std::cout<<(HavelHakimiAlgorithm(nodes) ? "Graphviz file created" : "Unable to create a graph with the data provided")<<std::endl;

}

void SortData(std::deque<std::pair<std::string, int>> &nodes, bool display){
    // Sorting deque by value
    sort(nodes.begin(), nodes.end(), OrdernarPorValor);

    if (display){
        std::cout << std::endl;
        std::cout << "sorted by value is : " << std::endl;
        for (int i = 0; i < nodes.size(); i++)
            std::cout << nodes[i].first << ": " << nodes[i].second << std::endl;
        
    }
}

void InitFile(){
    std::ofstream file;
    file.open("graph.gv");
    
    if(file.fail())
        exit(1);

    file<<"graph G {\n";
    file.close();
}

void EndFile(){
    std::ofstream file;
    file.open("graph.gv", std::ios::out | std::ios::app);
    
    if(file.fail())
        exit(1);

    file<<"}";
    file.close();
}

void WriteDotLanguage(std::string v0, std::string v1){
    std::ofstream file;
    file.open("graph.gv", std::ios::out | std::ios::app);

    if(file.fail())
        exit(1);
        
    file<<v0<<"--"<<v1<<"\n";
    file.close();
}

bool HavelHakimiAlgorithm(std::deque<std::pair<std::string, int>>& nodes){
    int sum =0;
    SortData(nodes);

    // the first element must be less than the number of elements
    if(nodes.front().second > nodes.size()){
        remove("graph.gv");
        return false;
    }

    // negative are not allowed
    if(nodes.back().second < 0){
        remove("graph.gv");
        return false;
    }

    for(int i=0; i<nodes.size(); ++i)
        sum += nodes[i].second;

    if(sum % 2 != 0){
        remove("graph.gv");
        return false;
    }

    if(nodes.front().second == 0){
        EndFile();
        return true;
    }

    auto front = nodes.front();

    for(int i=1; i<=front.second; ++i){
        --nodes[i].second;
        WriteDotLanguage(front.first, nodes[i].first);
    }

    nodes.pop_front();

    HavelHakimiAlgorithm(nodes);
}
