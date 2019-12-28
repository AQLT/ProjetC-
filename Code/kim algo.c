#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
//#include <cstdlib>
#include <sstream>
#include <algorithm> //??

#define INT_MAX 10000000
#define nb_noeuds 4

using namespace std;

void DijkstrasTest();
class Node;
class Edge;
void Dijkstras();
vector<Node*>* AdjacentRemainingNodes(Node* node);
Node* ExtractSmallest(vector<Node*>& nodes);
int Distance(Node* node1, Node* node2);
bool Contains(vector<Node*>& nodes, Node* node);
void PrintShortestRouteTo(Node* destination);
vector<Node*> nodes;
vector<Edge*> edges;

class Node
{
public:
    Node(std::string id)
        : id(id), previous(NULL), distanceFromStart(INT_MAX)
    {
        nodes.push_back(this);
    }

        Node() //NEW CONSTRUCTEUR KIM
        : id("abc"), previous(NULL), distanceFromStart(INT_MAX)
    {
        nodes.push_back(this);
    }

public:
    std::string id; //char
    Node* previous;
    int distanceFromStart;
   // std::string getid(){return id;} //KIM


};
class Edge
{
public:
    Edge(Node* node1, Node* node2, int distance)
        : node1(node1), node2(node2), distance(distance)
    {
        edges.push_back(this);
    }
    Edge()//NEW CONSTRUCTEUR KIM
        : distance(0)
    {
        Node* n1;
        node1 = n1;
        Node* n2;
        node2 = n2;
        edges.push_back(this);
    }

    bool Connects(Node* node1, Node* node2)
    {
        return (
                   (node1 == this->node1 &&
                    node2 == this->node2)
                    //|| //dans le mauvais sens ?
                   //(node1 == this->node2 &&
                    //node2 == this->node1)
                )
                    ;
    }
public:
    Node* node1;
    Node* node2;
    int distance;
};

void Dijkstras()
{
    while (nodes.size() > 0)
    {
        Node* smallest = ExtractSmallest(nodes);
        vector<Node*>* adjacentNodes =
            AdjacentRemainingNodes(smallest);
        const int size = adjacentNodes->size();
        for (int i=0; i<size; ++i)
        {
            Node* adjacent = adjacentNodes->at(i);
            int distance = Distance(smallest, adjacent) +
                           smallest->distanceFromStart;

            if (distance < adjacent->distanceFromStart)
            {
                adjacent->distanceFromStart = distance;
                adjacent->previous = smallest;
            }
        }
        delete adjacentNodes;
    }
}


// Find the node with the smallest distance,
// remove it, and return it.
Node* ExtractSmallest(vector<Node*>& nodes)
{
    int size = nodes.size();
    if (size == 0)
        return NULL;
    int smallestPosition = 0;
    Node* smallest = nodes.at(0);
    for (int i=1; i<size; ++i)
    {
        Node* current = nodes.at(i);
        if (current->distanceFromStart <
                smallest->distanceFromStart)
        {
            smallest = current;
            smallestPosition = i;
        }
    }
    nodes.erase(nodes.begin() + smallestPosition);
    return smallest;
}
// Return all nodes adjacent to 'node' which are still
// in the 'nodes' collection.
vector<Node*>* AdjacentRemainingNodes(Node* node)
{
    vector<Node*>* adjacentNodes = new vector<Node*>();
    const int size = edges.size();
    for(int i=0; i<size; ++i)
    {
        Edge* edge = edges.at(i);
        Node* adjacent = NULL;
        if (edge->node1 == node)
        {
            adjacent = edge->node2;
        }
        //else if (edge->node2 == node) //pas dans les deux sens
        //{
         //   adjacent = edge->node1;
        //}
        if (adjacent && Contains(nodes, adjacent))
        {
            adjacentNodes->push_back(adjacent);
        }
    }
    return adjacentNodes;
}
// Return distance between two connected nodes
int Distance(Node* node1, Node* node2)
{
    const int size = edges.size();
    for(int i=0; i<size; ++i)
    {
        Edge* edge = edges.at(i);
        if (edge->Connects(node1, node2))
        {
            return edge->distance;
        }
    }
    return -1; // should never happen
}
// Does the 'nodes' vector contain 'node'
bool Contains(vector<Node*>& nodes, Node* node)
{
    const int size = nodes.size();
    for(int i=0; i<size; ++i)
    {
        if (node == nodes.at(i))
        {
            return true;
        }
    }
    return false;
}
///////////////////
void PrintShortestRouteTo(Node* destination)
{
    Node* previous = destination;
    cout << "Temps de trajet : "
         << destination->distanceFromStart << endl;
    while (previous)
    {
        cout << previous->id << " ";
        previous = previous->previous;
    }
    cout << endl;
}



// these two not needed
vector<Edge*>* AdjacentEdges(vector<Edge*>& Edges, Node* node);
void RemoveEdge(vector<Edge*>& Edges, Edge* edge);
vector<Edge*>* AdjacentEdges(vector<Edge*>& edges, Node* node)
{
    vector<Edge*>* adjacentEdges = new vector<Edge*>();
    const int size = edges.size();
    for(int i=0; i<size; ++i)
    {
        Edge* edge = edges.at(i);
        if (edge->node1 == node)
        {
            cout << "adjacent: " << edge->node2->id << endl;
            adjacentEdges->push_back(edge);
        }
        else if (edge->node2 == node)
        {
            cout << "adjacent: " << edge->node1->id << endl;
            adjacentEdges->push_back(edge);
        }
    }
    return adjacentEdges;
}
void RemoveEdge(vector<Edge*>& edges, Edge* edge)
{
    vector<Edge*>::iterator it;
    for (it=edges.begin(); it<edges.end(); ++it)
    {
        if (*it == edge)
        {
            edges.erase(it);
            return;
        }
    }
}

int getIndiceFromNode(std::string identifiant ,vector<Node*> les_noeuds)
{

 int indice_sortie;
 const int size = les_noeuds.size();
 for(int i=0; i<size; ++i){
 //       cout << "identifiant noeud : " << les_noeuds[i]->id << endl;
 //       cout << "identifiant : " << identifiant << endl;
        if(les_noeuds[i]->id== identifiant){
            indice_sortie = i;

        }

 }


 return(indice_sortie);

}

std::vector<std::string> split(std::string str,std::string sep)
{
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL)
    {
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

vector<Node*> charger_nodes(char* chemin){
    std::string chaine;
    std::ifstream fichier(chemin); // acquisition
    int nligne = 0;
    vector<Node*> noeuds;
    string ligne;
    getline(fichier,ligne);
    std::vector<std::string> identifiants_ligne;

    //ligne.erase(remove(ligne.begin(), ligne.end(), '\"' ),ligne.end()); //enlever les ""
    //const char* ligne_char = ligne.c_str();
    //identifiants_ligne=split(ligne_char,"\t");

   string lignemetro;
    stringstream ligne_fichier(ligne);
   while(getline(ligne_fichier, lignemetro,'\t') ){
        lignemetro.erase(remove(lignemetro.begin(), lignemetro.end(), '\"' ),lignemetro.end());
        identifiants_ligne.push_back(lignemetro);
   }

        for (int i=0; i<identifiants_ligne.size(); i++)
            {
                Node* noeud = new Node(identifiants_ligne[i]);
                noeuds.push_back(noeud);
            }
    fichier.close();
    return(noeuds);
}

Edge** charger_edges(char* chemin, vector<Node*> noeuds){
    std::string chaine;
    std::ifstream fichier(chemin); // acquisition
    int nligne = 0;
     Edge** edges = 0;
     edges = new Edge*[noeuds.size()]; //test const

    do
    {

        string ligne;
        getline(fichier,ligne);


       if (nligne==0)  // Si c'est la premi�re ligne je r�cup�re les identifiants d'arret
       {
        }
        else   // Je recupere les coordonn�es
        {
            edges[nligne-1] = new Edge[noeuds.size()]; //test const

            std::vector<string> distances;
            distances=split(ligne,"\t");




            for (int i=1; i<noeuds.size()+1; i++) //test const
            {
             stringstream geek(distances[i]);
             int num = 0;
             geek >> num;
             if (num!=(-1))
             {
                Edge edge(noeuds[nligne-1],noeuds[i-1],num) ;
                edges[nligne-1][i-1] = edge;
             }
            }
        }

        if (fichier.eof())
            break;
        nligne++;
    }
    //while ( !fichier.eof() );
    while ( nligne< 759 ); //BUG

    fichier.close(); // rel�chement
            return(edges);
}

DijkstrasFinal(vector<Node*> nodes, Edge** edges, std::string entree,std::string sortie){ //vector<Node*> nodes, Edge** edges,

int entree_int = getIndiceFromNode(entree,nodes);
int sortie_int = getIndiceFromNode(sortie,nodes);

nodes[entree_int]->distanceFromStart = 0; // set start node
Dijkstras();
PrintShortestRouteTo(nodes[sortie_int]);

}

int main()
{

vector<Node*> nodes_loaded = charger_nodes("W:/Bureau/voisins.txt");
Edge** edges_loaded = charger_edges("W:/Bureau/voisins.txt",nodes_loaded);
vector<Node*> nodes;
Edge** edges;

// Faire les trois �tapes sinon on �crase mal ce qui est fait avant...
nodes = nodes_loaded;
edges = edges_loaded;
DijkstrasFinal(nodes, edges, "1804","1948");

nodes = nodes_loaded;
edges = edges_loaded;
DijkstrasFinal(nodes, edges, "1804","1948");


}