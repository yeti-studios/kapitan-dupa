#include <axxegro/axxegro.hpp>

int main(int, char**) 
{
    al::FullInit();
    std::set_terminate(al::Terminate);

    al::Display disp(800, 600);
    al::Sleep(0.4);


}
