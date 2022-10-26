#include "cube_r.h"
#include "corner_edge.h"
#include <vector>



class solver {
public:
    std::string scramble[1000];
    int position = 0;

    corner getCorner(cube_r& cubeR);

    edge getEdge(cube_r& cubeR);

    centre getCentre(cube_r& cubeR);

    bool check_invariant(cube_r& cubeR);





    bool contains_corner(const std::string& str, const char corner[3]);

    bool contains_edge(const std::string& str, const char edge[2]);


    bool evaluateCube(cube_r& cubeR);

    void move(int number, cube_r& cubeR);

    void random_moves(cube_r& cubeR);

    void print_scramble();

    solver(cube_r& cubeR);

    solver() = default;

    void step0(cube_r& cubeR);
    void step1(cube_r& cubeR);
    void step2(cube_r& cubeR);
    void step3(cube_r& cubeR);
    void step4(cube_r& cubeR);
    void step5(cube_r& cubeR);
    void step6(cube_r& cubeR);
    void step7(cube_r& cubeR);


};