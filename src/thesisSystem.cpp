#include <Controler.h>
#include <CommonMessages.h>

int main()
{
    Controler controler;
    while (1)
        controler.receiveMessages();
}
