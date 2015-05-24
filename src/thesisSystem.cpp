#include <Controler.hpp>
#include <CommonMessages.hpp>

int main()
{
    Controler controler;
    while (1)
    {
        controler.receiveMessages();
        controler.handleInitializations();
        controler.handleMessages();
        controler.sendResponses();
    }
}
