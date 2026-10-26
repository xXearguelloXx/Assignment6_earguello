#ifndef COORDINATE_H
#define COORDINATE_H

struct _coordinate
{
  float x;
  float y;
  int coord_id;
  struct _coordinate *next;
  struct _coordinate *previous;
};
typedef struct _coordinate Coordinate;

// adds a coordinate to the end of the linked list
void add_coordinate(Coordinate *list_end, float x, float y);

// displays all coordinates from beginning to end
void forward_display(Coordinate *list_beginning);

// displays all coordinates from end to beginning
void backward_display(Coordinate *list_end);

// removes a coordinate from the linked list and frees its memory
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete);

// returns the number of coordinates in the list
int list_length(Coordinate *list_beginning);

// finds the coordinate closest to (x,y) and prints it with the distance
void closest_to(Coordinate *list_beginning, float x, float y);

#endif
