#include <iostream>
#include <string>
#include <queue>
#include <climits>
#include <vector>
#include <string.h>
#define DEBUG if(1)


void Dijkstra(std::vector<std::vector<int>> graph, int s, int dist[], int pre[]){
    int len = graph.size();
    for (int u=0; u<len; ++u){
        dist[u] = INT_MAX;
        pre[u] = -1;
    }
    dist[s] = 0;
    std::priority_queue<std::pair<int, int>> h;
    h.push({dist[0], s});
    while(!h.empty()){
        int i = h.top().second;
        // int j = h.top().first;
        h.pop();
        for (int v=0; v<len; ++v){
            if (graph[i][v]!=0){
                // if (pre[v]==-1){
                    if (dist[v]>dist[i]+graph[i][v]){
                        dist[v]=dist[i]+graph[i][v];
                        pre[v] = i;
                        h.push({dist[v], v});
                        // std::cout<<"UMA VEZ, pre="<<pre[v]<<",v="<<v<<"\n";
                    }
                // }
            }
        }
    }
}


int main(int argv, char** argc){
    for (int index_arg=0; index_arg<argv; ++index_arg){
        if (argc[index_arg][0]=='-' && argc[index_arg][1]=='f'){
            FILE* file = fopen(argc[index_arg+1], "r");
            if (file==NULL){
                std::cout << "File not found.\n";
                return 0;
            }
            int lenx, leny;
            fscanf(file, "%d %d", &lenx, &leny);
            // std::cin >> lenx >> leny;
            std::vector<std::vector<int>> graph(lenx, std::vector<int>(lenx, 0));
            
            for (int i=0; i<leny; i++){
                int vertex_init, vertex_end, weight;
                // std::cin >> vertex_init >> vertex_end >> weight;
                fscanf(file, "%d %d %d", &vertex_init, &vertex_end, &weight);
                graph[vertex_init-1][vertex_end-1] = weight;
                graph[vertex_end-1][vertex_init-1] = weight;
            }

            int dist[lenx];
            int pre[lenx];
            int s = 0;
            for (int index_arg1=0; index_arg1<argv; index_arg1++){
                if (argc[index_arg1][0]=='-' && argc[index_arg1][1]=='i'){
                    s = std::stoi(argc[index_arg1+1])-1;
                }
            }

            Dijkstra(graph, s, dist, pre);

            FILE* savefile;
            int save=0;
            for (int index_arg2=0; index_arg2<argv; ++index_arg2){
                if (argc[index_arg2][0]=='-' && argc[index_arg2][1]=='o'){
                    save=1;
                    savefile = fopen(argc[index_arg2+1], "w");
                    break;
                }
            }

            // if (save==1){fprintf(savefile, "Dist e pre:\n");}
            // std::cout << "Dist e pre:\n";
            for (int j=0; j<lenx; ++j){
                std::cout<<dist[j]<<":"<<pre[j]<<" ";
                if (save==1){fprintf(savefile, "%d:%d ", dist[j], pre[j]);}
            }
            std::cout<<"\n";

            if (save==1){fclose(savefile);}
            fclose(file);
        }
        if (argc[index_arg][0]=='-' && argc[index_arg][1]=='h'){
            std::cout<<"Para executar um algoritmo esteja branch \"main\", tenha o g++ e execute os seguintes passos:\n\n";
            std::cout<<"1º: Acesse a pasta do algoritmo;\n\n";
            std::cout<<"2º: Digite sem as aspas a palavra \"make\" para compilar.\n\n";
            std::cout<<"3º: Digite sem as aspas a palavra \"./<nome_do_algoritmo> <parametros>\" para executar.\n\n";
            std::cout<<"Em caso de dúvida digite -h como parâmetro.\n\n";
            std::cout<<"Direcione a saída para um arquivo com o parâmetro -o e nome_do_arquivo.dat\n";
            std::cout<<"Indique um arquivo que contém o grafo com o parâmetro -f e nome_do_arquivo.dat\n";
            // std::cout<<"Mostre a solução em ordem crescente com o parâmetro -s\n";
            std::cout<<"Defina o vértice inicial com o parâmetro -i.\n\n";
        }
    }

}