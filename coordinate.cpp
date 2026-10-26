#include <iostream>
#include <iomanip>
#include <cmath>
#include "coordinate.h"

// prints one node as: id 4: (12.34, 56.78)
static void print_coordinate(Coordinate *c)
{
    std::cout << "  id " << std::setw(3) << c->coord_id << ": ("
              << std::fixed << std::setprecision(2)
              << c->x << ", " << c->y << ")" << std::endl;
}

void add_coordinate(Coordinate *list_end, float x, float y)
{
    if (list_end == nullptr)
    {
        std::cout << "add_coordinate: no list to add to" << std::endl;
        return;
    }

    // walk forward to the true end, in case the pointer we were handed
    // isn't actually the last node anymore.
    while (list_end->next != nullptr)
        list_end = list_end->next;

    // walk back to the beginning so list_length() can count the list.
    Coordinate *list_beginning = list_end;
    while (list_beginning->previous != nullptr)
        list_beginning = list_beginning->previous;

    Coordinate *new_coord = new Coordinate;
    new_coord->x = x;
    new_coord->y = y;
    new_coord->coord_id = list_length(list_beginning) + 1; // ids start at 1
    new_coord->next = nullptr;
    new_coord->previous = list_end;

    list_end->next = new_coord;
}

void forward_display(Coordinate *list_beginning)
{
    std::cout << "forward (beginning -> end)" << std::endl;
    for (Coordinate *c = list_beginning; c != nullptr; c = c->next)
        print_coordinate(c);
}

void backward_display(Coordinate *list_end)
{
    std::cout << "backward (end -> beginning)" << std::endl;
    for (Coordinate *c = list_end; c != nullptr; c = c->previous)
        print_coordinate(c);
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
    // find the node with the matching id
    Coordinate *target = list_beginning;
    while (target != nullptr && target->coord_id != coord_id_to_delete)
        target = target->next;

    if (target == nullptr)
    {
        std::cout << "delete_coordinate: id " << coord_id_to_delete
                  << " not found" << std::endl;
        return;
    }

    if (target == list_beginning)
    {
        // The head is passed by value, so we can't change main's pointer to
        // it. SO we copy the second node into the head, then delete the
        // second node. The head's address stays the same and its data moves up.
        Coordinate *second = list_beginning->next;
        if (second == nullptr)
        {
            std::cout << "delete_coordinate: can't delete the only node"
                      << std::endl;
            return;
        }

        list_beginning->x = second->x;
        list_beginning->y = second->y;
        list_beginning->coord_id = second->coord_id;
        list_beginning->next = second->next;
        if (second->next != nullptr)
            second->next->previous = list_beginning;

        delete second;
        return;
    }

    // middle or end node: link its neighbors to each other, then free it
    target->previous->next = target->next;
    if (target->next != nullptr)
        target->next->previous = target->previous;

    delete target;
}

int list_length(Coordinate *list_beginning)
{
    int length = 0;
    for (Coordinate *c = list_beginning; c != nullptr; c = c->next)
        length++;
    return length;
}

void closest_to(Coordinate *list_beginning, float x, float y)
{
    if (list_beginning == nullptr)
    {
        std::cout << "closest_to: list is empty" << std::endl;
        return;
    }

    Coordinate *closest = nullptr;
    float closest_distance = 0.0f;

    for (Coordinate *c = list_beginning; c != nullptr; c = c->next)
    {
        float dx = c->x - x;
        float dy = c->y - y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (closest == nullptr || distance < closest_distance)
        {
            closest = c;
            closest_distance = distance;
        }
    }

    std::cout << std::fixed << std::setprecision(2)
              << "closest point to (" << x << ", " << y << ") is id "
              << closest->coord_id << ": (" << closest->x << ", "
              << closest->y << ")" << std::endl
              << "distance = " << closest_distance << std::endl;
}
