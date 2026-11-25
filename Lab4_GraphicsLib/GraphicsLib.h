#pragma once

#include <winsock2.h>
#include <cstdint>
#include <string>
#include <vector>

class GraphicsLib
{
public:
    GraphicsLib();
    ~GraphicsLib();

    bool Connect(const std::string& ip, uint16_t port);
    void Disconnect();

    void ClearDisplay(uint16_t color);

    void DrawPixel(int16_t x, int16_t y, uint16_t color);
    void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

    void DrawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void FillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

    void DrawEllipse(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void FillEllipse(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

    void DrawCircle(int16_t x, int16_t y, int16_t radius, uint16_t color);
    void FillCircle(int16_t x, int16_t y, int16_t radius, uint16_t color);

    void DrawRoundedRectangle(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color);
    void FillRoundedRectangle(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color);

    void DrawText(int16_t x, int16_t y, uint16_t color, uint8_t font, const std::string& text);

    void DrawImage(int16_t x, int16_t y, int16_t w, int16_t h, const std::vector<uint8_t>& imageData);

    void SetOrientation(uint8_t orientation);

private:
    SOCKET socketHandle;
    sockaddr_in serverAddress;
    bool connected;

    void sendPacket(const std::vector<uint8_t>& packet);
    void addInt16(std::vector<uint8_t>& packet, int16_t value);
    void addColor(std::vector<uint8_t>& packet, uint16_t color);
};