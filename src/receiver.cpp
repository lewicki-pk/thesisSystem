//#include <spi.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <Controler.h>
#include <CommonMessages.h>

int i = 0;

void loop(void)
{
}

int main()
{
    Controler controler;
    while (1)
        controler.receiveMessages();
}
