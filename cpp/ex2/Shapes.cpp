#include <iostream>
#define EXPECTED_NUM_ARGS 3
#define MSG_INCORRECT_ARGC "Incorrect amount of arguments"



int main(int argc, char** arv)
{
    /**
     * Might be relevant:
     * det...
     *
     *
     */
    std::cout << "Shapes" << std::endl;
    if (argc != EXPECTED_NUM_ARGS)
    {

        std::cerr << MSG_INCORRECT_ARGC << std::endl;
        return -1;
    }
    /*
     * TODO: Read file, could not read file, write to file.
     */
    return 0;
}