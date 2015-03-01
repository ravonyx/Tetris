#include <stack>
#include "Defines.h"   
#include "States.h"
#include "Render.h"
#include "Input.h"
#include "Global.h"

int main(int argc, char **argv)
{
    Init();
    while (!g_StateStack.empty())
    {
        g_StateStack.top().StatePointer(); 
    }
    ShutDown();

    return 0;
}

