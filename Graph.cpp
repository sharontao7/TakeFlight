#include "Graph.h"

const Airport Graph::InvalidAirport = Airport(0.0, 0.0, "_INVALIDAIRPORT");
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidAirport, Graph::InvalidAirport, Graph::InvalidWeight, Graph::InvalidLabel);

Graph::Graph(bool weighted) : weighted(weighted), directed(false), random(Random(0)) { }


Graph::Graph(bool weighted, bool directed) : weighted(weighted), directed(directed), random(Random(0)) { }


Graph::Graph(bool weighted, std::vector<Airport> airports, unsigned long seed)
    :weighted(weighted),
      directed(false),
     random(Random(seed)) 
{
    if (airports.size() < 2) {
        error("numAirports too low");
        exit(1);
    }

    vector<Airport> airports_;
    for (int i = 0; i < airports.size(); i++) {
        insertAirport(airports[i]);
        airports_.push_back(airports[i]);
    }

    // make sure all Airports are connected
    random.shuffle(airports_);
    Airport cur = airports_[0];
    for (size_t i = 0; i < airports.size() - 1; ++i) {
        Airport next = airports_[i + 1];
        insertEdge(cur, next);

        if (weighted) {
            int weight = random.nextInt();
            setEdgeWeight(cur, next, weight);
        }
        cur = next;
    }

    // keep the graph from being overpopulated with edges,
    //  while still maintaining a little randomness
    int numFailures = 0;
    int idx = 0;
    random.shuffle(airports_);
    while (numFailures < 2) {

        if (!insertEdge(airports_[idx], airports_[idx + 1])) {
            ++numFailures;

        } else {
            // if insertEdge() succeeded...
            if (weighted)
                setEdgeWeight(airports_[idx], airports_[idx + 1],
                              random.nextInt());
            ++idx;
            if (idx >= airports_.size() - 2) {
                idx = 0;
                random.shuffle(airports_);
            }
        }
    }
}

vector<Airport> Graph::getAdjacent(Airport source) const {
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Airport>();

    else {
        vector<Airport> airport_list;
        unordered_map <Airport, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++) {
            airport_list.push_back(it->first);
        }
        return airport_list;
    }
}

Airport Graph::getStartingAirport() const {
    return adjacency_list.begin()->first;
}

vector<Airport> Graph::getAirports() const {
    vector<Airport> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++) {
        ret.push_back(it->first);
    }
    return ret;
}

Edge Graph::getEdge(Airport source , Airport destination) const {
    if (assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const {
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Airport, Airport>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++) {
        Airport source = it->first;

        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++) {
            Airport destination = its->first;

            if (seen.find(make_pair(source, destination)) == seen.end()) {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source, destination));

                if (!directed) {
                    seen.insert(make_pair(destination, source));
                }
            }
        }
    }
    return ret;
}

bool Graph::AirportExists(Airport v) const { return assertAirportExists(v, ""); }

bool Graph::edgeExists(Airport source, Airport destination) const {
    return assertEdgeExists(source, destination, "");
}

Edge Graph::setEdgeLabel(Airport source, Airport destination, string label) {
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    if(!directed) {
        Edge new_edge_reverse(destination,source, e.getWeight(), label);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}


string Graph::getEdgeLabel(Airport source, Airport destination) const {
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
}

int Graph::getEdgeWeight(Airport source, Airport destination) const {
    if (!weighted)
        error("can't get edge weights on non-weighted graphs!");

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

void Graph::insertAirport(Airport v) {
    // will overwrite if old stuff was there
    removeAirport(v);
    
    // make it empty again
    adjacency_list[v] = unordered_map<Airport, Edge>();
}

Airport Graph::removeAirport(Airport v) {
    if (adjacency_list.find(v) != adjacency_list.end()) {
        if(!directed) {
            for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++) {
                Airport u = it->first;
                adjacency_list[u].erase(v); 
            }
            adjacency_list.erase(v);
            return v;
        }
        
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++) {
            Airport u = it2->first;
            if (it2->second.find(v)!=it2->second.end()) {
                it2->second.erase(v);
            }
        }
        return v;
    }
    return InvalidAirport;
}

bool Graph::insertEdge(Airport source, Airport destination) {
    if (adjacency_list.find(source) != adjacency_list.end() 
        && adjacency_list[source].find(destination) != adjacency_list[source].end()) {
        //edge already exists
        return false; 
    }

    if (adjacency_list.find(source) == adjacency_list.end()) {
        adjacency_list[source] = unordered_map<Airport, Edge>();
    }

    //source Airport exists
    adjacency_list[source][destination] = Edge(source, destination);
    if (!directed) {
        if (adjacency_list.find(destination) == adjacency_list.end()) {
            adjacency_list[destination] = unordered_map<Airport, Edge>();
        }
        adjacency_list[destination][source] = Edge(source, destination);
    }
    return true;
}

Edge Graph::removeEdge(Airport source, Airport destination) {
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    
    // if undirected, remove the corresponding edge
    if(!directed) {
        adjacency_list[destination].erase(source);
    }
    return e;
}


Edge Graph::setEdgeWeight(Airport source, Airport destination, int weight) {
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    //std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;

    if(!directed) {
        Edge new_edge_reverse(destination,source, weight, e.getLabel());
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}

bool Graph::assertAirportExists(Airport v, string functionName) const {
    if (adjacency_list.find(v) == adjacency_list.end()) {
        if (functionName != "")
            error(functionName + " called on nonexistent Airports");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Airport source, Airport destination, string functionName) const {
    if (assertAirportExists(source,functionName) == false)
        return false;

    if (adjacency_list[source].find(destination)== adjacency_list[source].end()) {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source.name_ + " -> " + destination.name_);
        return false;
    }

    if(!directed) {
        if (assertAirportExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end()) {
            if (functionName != "")
                error(functionName + " called on nonexistent edge " + destination.name_ + " -> " + source.name_);
            return false;
        }
    }
    return true;
}

bool Graph::isDirected() const { return directed; }

void Graph::clear() {
    adjacency_list.clear();
}


/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const {
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}

/**
 * Creates a name for snapshots of the graph.
 * @param title - the name to save the snapshots as
 */
void Graph::initSnapshot(string title) {
    picNum = 0;
    picName = title;
}

/**
 * Saves a snapshot of the graph to file.
 * initSnapshot() must be run first.
 */
void Graph::snapshot() {
    std::stringstream ss;
    ss << picNum;
    string newName = picName + ss.str();
    savePNG(newName);
    ++picNum;
}

/**
 * Prints the graph to stdout.
 */
void Graph::print() const {
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) {
        cout << it->first << endl;

        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            std::stringstream ss;
            ss << it2->first; 
            string AirportColumn = "    => " + ss.str();
            AirportColumn += " " ;
            cout << std::left << std::setw(26) << AirportColumn;
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(26) << edgeColumn;
            if (weighted)
                cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

/**
 * Saves the graph as a PNG image.
 * @param title - the filename of the PNG image
 */
void Graph::savePNG(string title) const {
    std::ofstream neatoFile;
    string filename = "images/" + title + ".dot";
    neatoFile.open(filename.c_str());

    if (!neatoFile.good())
        error("couldn't create " + filename + ".dot");

    neatoFile
        << "strict graph G {\n"
        << "\toverlap=\"false\";\n"
        << "\tdpi=\"1300\";\n"
        << "\tsep=\"1.5\";\n"
        << "\tnode [fixedsize=\"true\", shape=\"circle\", fontsize=\"7.0\"];\n"
        << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    vector<Airport> allv = getAirports();
    //lambda expression
    sort(allv.begin(), allv.end(), [](const Airport& lhs, const Airport& rhs) {
        return stoi(lhs.name_.substr(3)) > stoi(rhs.name_.substr(3));
    });

    int xpos1 = 100;
    int xpos2 = 100;
    int xpos, ypos;
    for (auto it : allv) {
        string current = it.name_;
        neatoFile 
            << "\t\"" 
            << current
            << "\"";
        if (current[1] == '1') {
            ypos = 100;
            xpos = xpos1;
            xpos1 += 100;
        }
        else {
            ypos = 200;
            xpos = xpos2;
            xpos2 += 100;
        }
        neatoFile << "[pos=\""<< xpos << "," << ypos <<"\"]";
        neatoFile << ";\n";
    }

    neatoFile << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            string Airport1Text = it->first.name_;
            string Airport2Text = it2->first.name_;

            neatoFile << "\t\"" ;
            neatoFile << Airport1Text;
            neatoFile << "\" -- \"" ;
            neatoFile << Airport2Text;
            neatoFile << "\"";

            string edgeLabel = it2->second.getLabel();
            if (edgeLabel == "WIN") {
                neatoFile << "[color=\"blue\"]";
            } else if (edgeLabel == "LOSE") {
                neatoFile << "[color=\"red\"]";                
            } else {
                neatoFile << "[color=\"grey\"]";
            }
            if (weighted && it2->second.getWeight() != -1)
                neatoFile << "[label=\"" << it2->second.getWeight() << "\"]";
            
            neatoFile<< "[constraint = \"false\"]" << ";\n";
        }
    }

    neatoFile << "}";
    neatoFile.close();
    string command = "neato -n -Tpng " + filename + " -o " + "images/" + title
                     + ".png 2> /dev/null";
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Output graph saved as images/" << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
    }

    string rmCommand = "rm -f " + filename + " 2> /dev/null";
    system(rmCommand.c_str());
}
