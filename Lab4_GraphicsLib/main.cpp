#include <iostream>
#include "GraphicsLib.h"

int main()
{
    GraphicsLib display;

    if (!display.Connect("127.0.0.1", 12345))
    {
        std::cout << "Не удалось подключиться к серверу!" << std::endl;
        return 1;
    }

    std::cout << "Клиент подключен к серверу." << std::endl;

    display.ClearDisplay(0x0000);

    display.DrawPixel(50, 50, 0xF800);
    display.DrawLine(20, 20, 200, 100, 0x07E0);

    display.DrawRectangle(30, 120, 150, 80, 0x001F);
    display.FillRectangle(200, 120, 100, 80, 0xF800);

    display.DrawCircle(100, 300, 40, 0xFFFF);
    display.FillCircle(250, 300, 40, 0x07E0);

    display.DrawText(50, 400, 0xFFFF, 1, "Hello Display!");

    display.SetOrientation(0);

    std::cout << "Команды отправлены." << std::endl;

    display.Disconnect();

    return 0;
}