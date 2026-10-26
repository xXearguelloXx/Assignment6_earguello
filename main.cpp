#include <iostream>
#include <cstdlib>
#include <ctime>
#include "coordinate.h"

// random float in [min, max]
static float random_float(float min, float max)
{
    return min + (max - min) * (std::rand() / (float) RAND_MAX);
}

// walk forward from the beginning to find the current last node
static Coordinate *find_end(Coordinate *list_beginning)
{
    Coordinate *c = list_beginning;
    while (c != nullptr && c->next != nullptr)
        c = c->next;
    return c;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage: " << argv[0] << " <number of coordinates>"
                  << std::endl;
        return 1;
    }

    int num_coords = std::atoi(argv[1]);
    if (num_coords < 1)
    {
        std::cerr << "number of coordinates must be at least 1" << std::endl;
        return 1;
    }

    std::srand(std::time(nullptr));

    // The first node is built by hand, since add_coordinate needs an
    // existing node to attach to.
    Coordinate *list_beginning = new Coordinate;
    list_beginning->x = random_float(0.0f, 100.0f);
    list_beginning->y = random_float(0.0f, 100.0f);
    list_beginning->coord_id = 1;
    list_beginning->next = nullptr;
    list_beginning->previous = nullptr;

    Coordinate *list_end = list_beginning;

    // add the rest, moving list_end along as the list grows
    for (int i = 1; i < num_coords; i++)
    {
        add_coordinate(list_end, random_float(0.0f, 100.0f),
                       random_float(0.0f, 100.0f));
        list_end = list_end->next;
    }

    std::cout << "list length: " << list_length(list_beginning) << std::endl;
    forward_display(list_beginning);
    backward_display(list_end);

    // delete a coordinate
    int id_to_delete = 3;
    std::cout << std::endl << "deleting id " << id_to_delete << std::endl;
    delete_coordinate(list_beginning, id_to_delete);

    // the deleted node might have been the end, so find the end again
    list_end = find_end(list_beginning);

    std::cout << "list length: " << list_length(list_beginning) << std::endl;
    forward_display(list_beginning);
    backward_display(list_end);

    // find the closest point to the middle of the 0-100 grid
    std::cout << std::endl;
    closest_to(list_beginning, 50.0f, 50.0f);

    // free every node that's left
    Coordinate *current = list_beginning;
    while (current != nullptr)
    {
        Coordinate *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}


