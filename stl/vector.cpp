/*unsigned int size();            Returns the number of elements in a vector
push_back(type element);        Adds an element to the end of a vector
bool empty();                   Returns true if the vector is empty
void clear();                   Erases all elements of the vector
type at(int n);                 Returns the element at index n, with bounds checking*/
/*=           Assignment replaces a vector's contents with the contents of another
==          An element by element comparison of two vectors
[]          Random access to an element of a vector (usage is similar to that
            of the operator with arrays.) Keep in mind that it does not provide
            bounds checking.*/
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    vector <int> example;         //Vector to store integers
    example.push_back(3);         //Add 3 onto the vector
    example.push_back(10);        //Add 10 to the end
    example.push_back(33);        //Add 33 to the end
    for(int x=0; x<example.size(); x++) 
    {
        cout<<example[x]<<" ";    //Should output: 3 10 33
    }
    if(!example.empty())          //Checks if empty
        example.clear();          //Clears vector
    vector <int> another_vector;  //Creates another vector to store integers
    another_vector.push_back(10); //Adds to end of vector
    example.push_back(10);        //Same
    if(example==another_vector)   //To show testing equality
    {
        example.push_back(20); 
    }
    for(int y=0; y<example.size(); y++)
    {
        cout<<example[y]<<" ";    //Should output 10 20
    }
    return 0;
}
/*Summary of Vector Benefits

Vectors are somewhat easier to use than regular arrays. At the very least, they get around having to be resized constantly using new and delete. Furthermore, their immense flexibility - support for any datatype and support for automatic resizing when adding elements - and the other helpful included functions give them clear advantages to arrays.

Another argument for using vectors are that they help avoid memory leaks--you don't have to remember to free vectors, or worry about how to handle freeing a vector in the case of an exception. This simplifies program flow and helps you write tighter code. Finally, if you use the at() function to access the vector, you get bounds checking at the cost of a slight performance penalty.*/
