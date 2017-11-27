#include "graph.h"

int main()
{
    std::cout << "Jared Agle and Brian Clinkenbeard | CS1D | HW10"
              << std::endl << "This program will demonstrate a DFS "
              << "and a BFS on an undirected graph containing "
              << "weighted edges. It will identify all discovery, "
              << "back, and cross edges as well as display the "
              << "total mileage for all discovery edges traversed."
              << std::endl << std::endl;

    Graph my_graph;

    // vertices
    my_graph.add_vertex("San Francisco");
    my_graph.add_vertex("Seattle");
    my_graph.add_vertex("Los Angeles");
    my_graph.add_vertex("Denver");
    my_graph.add_vertex("Kansas City");
    my_graph.add_vertex("Dallas");
    my_graph.add_vertex("Chicago");
    my_graph.add_vertex("Houston");
    my_graph.add_vertex("Atlanta");
    my_graph.add_vertex("New York");
    my_graph.add_vertex("Miami");
    my_graph.add_vertex("Boston");

    // from San Francisco
    my_graph.add_edge("San Francisco", "Los Angeles", 381);
    my_graph.add_edge("San Francisco", "Seattle", 807);
    my_graph.add_edge("San Francisco", "Denver", 1267);

    // from Seattle
    my_graph.add_edge("Seattle", "Denver", 1267);
    my_graph.add_edge("Seattle", "Chicago", 2097);

    // from Los Angeles
    my_graph.add_edge("Los Angeles", "Denver", 1015);
    my_graph.add_edge("Los Angeles", "Dallas", 1435);
    my_graph.add_edge("Los Angeles", "Kansas City", 1663);

    // from Denver
    my_graph.add_edge("Denver", "Kansas City", 599);
    my_graph.add_edge("Denver", "Chicago", 1003);

    // from Kansas City
    my_graph.add_edge("Kansas City", "Chicago", 533);
    my_graph.add_edge("Kansas City", "New York", 1260);
    my_graph.add_edge("Kansas City", "Atlanta", 864);
    my_graph.add_edge("Kansas City", "Dallas", 496);

    // from Dallas
    my_graph.add_edge("Dallas", "Atlanta", 781);
    my_graph.add_edge("Dallas", "Houston", 239);

    // from Chicago
    my_graph.add_edge("Chicago", "Boston", 983);
    my_graph.add_edge("Chicago", "New York", 787);

    // from Houston
    my_graph.add_edge("Houston", "Atlanta", 810);
    my_graph.add_edge("Houston", "Miami", 1187);

    // from Atlanta
    my_graph.add_edge("Atlanta", "Miami", 661);
    my_graph.add_edge("Atlanta", "New York", 888);

    // from New York
    my_graph.add_edge("New York", "Boston", 214);

    // from Miami
    // none

    std::cout << "Djikstra starting at Atlanta: " << std::endl;
    my_graph.DF
    std::cout << std::endl << "Edge statuses for DFS: " << std::endl;
    my_graph.print_edge_statuses();
    std::cout << std::endl << "Total distance traveled on discovery edges: "
              << my_graph.get_total_distance() << std::endl;

    my_graph.refresh_graph();
    std::cout << std::endl << "BFS starting at Dallas: " << std::endl;
    my_graph.BFS(start);
    std::cout << std::endl << "Edge statuses for BFS: " << std::endl;
    my_graph.print_edge_statuses();
    std::cout << std::endl << "Total distance traveled on discovery edges: "
              << my_graph.get_total_distance() << std::endl;

    return 0;
}

