#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a link between nodes
struct Link {
    int source;     // Source node of the link
    int destination; // Destination node of the link
    int weight;     // Weight (cost) of the link
};

// Structure to represent the network
struct Network {
    int num_nodes;   // Number of nodes in the network
    int num_links;   // Number of links in the network
    struct Link* links; // Array of links in the network
};

// Main function
void main() {
    int num_nodes, num_links, source_node;

    printf("Distance Vector Routing using Bellman-Ford Algorithm\n");

    // Input number of nodes and links
    printf("Enter number of nodes: ");
    scanf("%d", &num_nodes);
    printf("Enter number of links: ");
    scanf("%d", &num_links);

    // Allocate memory for the network structure and links array
    struct Network* network = (struct Network*)malloc(sizeof(struct Network));
    if (network == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    network->num_nodes = num_nodes;
    network->num_links = num_links;
    network->links = (struct Link*)malloc(num_links * sizeof(struct Link));
    if (network->links == NULL) {
        printf("Memory allocation failed\n");
        free(network);
        return;
    }

    // Input details for each link
    for (int i = 0; i < num_links; i++) {
        printf("Link %d: enter source, destination, and weight: ", i + 1);
        scanf("%d %d %d", &network->links[i].source, &network->links[i].destination, &network->links[i].weight);
    }

    // Input source node
    printf("Enter source node: ");
    scanf("%d", &source_node);

    // Initialize distance array
    int distances[num_nodes];
    for (int i = 0; i < num_nodes; i++)
        distances[i] = INT_MAX;
    distances[source_node] = 0;

    // Bellman-Ford algorithm
    for (int i = 1; i < num_nodes; i++) {
        for (int j = 0; j < num_links; j++) {
            int u = network->links[j].source;
            int v = network->links[j].destination;
            int wt = network->links[j].weight;
            if (distances[u] != INT_MAX && distances[u] + wt < distances[v])
                distances[v] = distances[u] + wt;
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < num_links; i++) {
        int u = network->links[i].source;
        int v = network->links[i].destination;
        int wt = network->links[i].weight;
        if (distances[u] != INT_MAX && distances[u] + wt < distances[v]) {
            printf("Network contains negative weight cycle\n");
            free(network->links);
            free(network);
            return;
        }
    }

    // Print distances from the source node to all other nodes
    printf("Node\tDistance from Source\n");
    for (int i = 0; i < num_nodes; i++) {
        printf("%d\t%d\n", i, distances[i]);
    }

    // Free allocated memory
    free(network->links);
    free(network);
}

