#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

void main()
{
    string sFileName;
    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFOHEADER bmpInfoHeader;
    int Width, Height;
    RGBQUAD Palette[16];
    BYTE* inBuf;
    WORD* outBuf;
    HANDLE hInputFile, hOutFile;
    DWORD RW;

    cout << "Enter the full name, please: ";
    cin >> sFileName;

    hInputFile = CreateFile(sFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    if (hInputFile == INVALID_HANDLE_VALUE)
        return;

    hOutFile = CreateFile("Result.bmp", GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);

    if (hOutFile == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hInputFile);
        return;
    }

    // Read the BMP file header and info header
    ReadFile(hInputFile, &bmpFileHeader, sizeof(bmpFileHeader), &RW, NULL);
    ReadFile(hInputFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &RW, NULL);

    // Set the file pointer to the start of the bitmap data
    SetFilePointer(hInputFile, bmpFileHeader.bfOffBits, NULL, FILE_BEGIN);

    Width = bmpInfoHeader.biWidth;
    Height = bmpInfoHeader.biHeight;

    // Allocate memory for the input and output buffers
    int inBufSize = Width / 2 * Height;
    int outBufSize = Width * Height;
    inBuf = new BYTE[inBufSize];
    outBuf = new WORD[outBufSize];

    // Set the output bitmap headers
    bmpFileHeader.bfOffBits = sizeof(bmpFileHeader) + sizeof(bmpInfoHeader) + 64;
    bmpInfoHeader.biBitCount = 16;
    bmpInfoHeader.biClrUsed = 16;
    bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + outBufSize * sizeof(WORD) + Height * (Width % 4);

    // Write the output bitmap headers
    WriteFile(hOutFile, &bmpFileHeader, sizeof(bmpFileHeader), &RW, NULL);
    WriteFile(hOutFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &RW, NULL);

    // Set the color palette
    for (int i = 0; i < 16; i++)
    {
        Palette[i].rgbBlue = i * 16;
        Palette[i].rgbGreen = i * 16;
        Palette[i].rgbRed = i * 16;
        Palette[i].rgbReserved = 0;
    }

    WriteFile(hOutFile, Palette, 16 * sizeof(RGBQUAD), &RW, NULL);

    // Read the input bitmap data
    for (int i = 0; i < Height; i++)
    {
        ReadFile(hInputFile, inBuf, inBufSize, &RW, NULL);
        for (int j = 0; j < Width / 2; j++)
        {
            BYTE b = inBuf[j];
            outBuf[i * Width + j * 2] = b >> 4; // upper nibble
            outBuf[i * Width + j * 2 + 1] = b & 0x0F; // lower nibble
        }
        // Write the padding bytes
        WriteFile(hOutFile, Palette, (Width % 4), &RW, NULL);
    }

    // Write the output bitmap data
    WriteFile(hOutFile, outBuf, outBufSize * sizeof(WORD), &RW, NULL);

    // Clean up
    delete[] inBuf;
    delete[] outBuf;
    CloseHandle(hInputFile);
    CloseHandle(hOutFile);
    cout << "Conversion complete." << endl;
    system("pause");
}