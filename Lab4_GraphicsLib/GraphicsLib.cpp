#include "GraphicsLib.h"
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

GraphicsLib::GraphicsLib()
{
    socketHandle = INVALID_SOCKET;
    connected = false;
}

GraphicsLib::~GraphicsLib()
{
    Disconnect();
}

bool GraphicsLib::Connect(const std::string& ip, uint16_t port)
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return false;

    socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socketHandle == INVALID_SOCKET)
    {
        WSACleanup();
        return false;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    InetPtonA(AF_INET, ip.c_str(), &serverAddress.sin_addr);

    connected = true;
    return true;
}

void GraphicsLib::Disconnect()
{
    if (connected)
    {
        closesocket(socketHandle);
        socketHandle = INVALID_SOCKET;
        connected = false;
        WSACleanup();
    }
}

void GraphicsLib::addInt16(std::vector<uint8_t>& packet, int16_t value)
{
    packet.push_back(value & 0xFF);
    packet.push_back((value >> 8) & 0xFF);
}

void GraphicsLib::addColor(std::vector<uint8_t>& packet, uint16_t color)
{
    packet.push_back(color & 0xFF);
    packet.push_back((color >> 8) & 0xFF);
}

void GraphicsLib::sendPacket(const std::vector<uint8_t>& packet)
{
    if (!connected)
        return;

    int result = sendto(
        socketHandle,
        reinterpret_cast<const char*>(packet.data()),
        static_cast<int>(packet.size()),
        0,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    );

    if (result == SOCKET_ERROR)
        std::cout << "Помилка використання команди: " << WSAGetLastError() << std::endl;
}

void GraphicsLib::ClearDisplay(uint16_t color)
{
    std::vector<uint8_t> packet = { 0x01 };
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::DrawPixel(int16_t x, int16_t y, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x02 };
    addInt16(packet, x);
    addInt16(packet, y);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x03 };
    addInt16(packet, x0);
    addInt16(packet, y0);
    addInt16(packet, x1);
    addInt16(packet, y1);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::DrawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x04 };
    addInt16(packet, x);
    addInt16(packet, y);
    addInt16(packet, w);
    addInt16(packet, h);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::FillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x05 };
    addInt16(packet, x);
    addInt16(packet, y);
    addInt16(packet, w);
    addInt16(packet, h);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::DrawEllipse(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x06 };
    addInt16(packet, x);
    addInt16(packet, y);
    addInt16(packet, w);
    addInt16(packet, h);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::FillEllipse(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x07 };
    addInt16(packet, x);
    addInt16(packet, y);
    addInt16(packet, w);
    addInt16(packet, h);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::DrawCircle(int16_t x, int16_t y, int16_t radius, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x08 };
    addInt16(packet, x);
    addInt16(packet, y);
    addInt16(packet, radius);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::FillCircle(int16_t x, int16_t y, int16_t radius, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x09 };
    addInt16(packet, x);
    addInt16(packet, y);
    addInt16(packet, radius);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::DrawRoundedRectangle(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x0A };
    addInt16(packet, x);
    addInt16(packet, y);
    addInt16(packet, w);
    addInt16(packet, h);
    addInt16(packet, radius);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::FillRoundedRectangle(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color)
{
    std::vector<uint8_t> packet = { 0x0B };
    addInt16(packet, x);
    addInt16(packet, y);
    addInt16(packet, w);
    addInt16(packet, h);
    addInt16(packet, radius);
    addColor(packet, color);
    sendPacket(packet);
}

void GraphicsLib::DrawText(int16_t x, int16_t y, uint16_t color, uint8_t font, const std::string& text)
{
    std::vector<uint8_t> packet = { 0x0C };
    addInt16(packet, x);
    addInt16(packet, y);
    addColor(packet, color);
    packet.push_back(font);

    uint16_t length = static_cast<uint16_t>(text.size());
    addInt16(packet, length);

    packet.insert(packet.end(), text.begin(), text.end());
    sendPacket(packet);
}

void GraphicsLib::DrawImage(int16_t x, int16_t y, int16_t w, int16_t h, const std::vector<uint8_t>& imageData)
{
    std::vector<uint8_t> packet = { 0x0D };
    addInt16(packet, x);
    addInt16(packet, y);
    addInt16(packet, w);
    addInt16(packet, h);

    packet.insert(packet.end(), imageData.begin(), imageData.end());
    sendPacket(packet);
}

void GraphicsLib::SetOrientation(uint8_t orientation)
{
    std::vector<uint8_t> packet = { 0x0E, orientation };
    sendPacket(packet);
}