/**
 * @file save.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Save file handling for the engine
 * @version 1.0
 * @date 2021-12-13
 */

#pragma once

#include "../../calc.hpp"
#include "../../draw_functions.hpp"

#include <sdk/os/file.hpp>
#include <sdk/os/mem.hpp>
#include <sdk/os/string.hpp>

// change this to change the save file path
// #define SAVE_PATH "\\fls0\\dev\\"

void getPath(char* path, const char* fileName) {
    #ifdef SAVE_PATH
		strcpy(path, SAVE_PATH);
	#else
		strcpy(path, "\\fls0\\saves\\");
	#endif
    strcat(path, fileName);
}

void loadSave(const char* filename) {	

    char path[128];
	getPath(path, filename);

    int fd = open(path, OPEN_READ);
    if (fd < 0) {
        Debug_Printf(4,42,true,0,"[ERROR::File:Open] [%i]", fd);
        return;
    }

    uint16_t buf[6];
    int ret = read(fd, buf, sizeof(buf));
    if (ret < 0) {
        Debug_Printf(4,42,true,0,"[ERROR::File:Read] [%i]", ret);
        close(fd);
        return;
    }

    // read the header for the len bytes
    uint16_t len = 0;
    if (buf[3] == 2) {
        len = uint8to16(buf[4], buf[5]);
    } else {
        len = uint8to16(0, buf[4]);
    }

    // Print the length of the save file
    Debug_Printf(4,42,true,0,"Ver: %i.%i.%i BL: %i Len: %i", buf[0], buf[1], buf[2], buf[3], len);

    // Close the file as we don't need it anymore
    ret = close(fd);
    if (ret < 0) {
        Debug_Printf(4,42,true,0,"[ERROR::File:Close] [%i]", ret);
        return;
    }

    return;
}

void writeSave(const char* filename) {

    char path[128];
	getPath(path, filename);

    int fd = open(path, OPEN_WRITE | OPEN_CREATE);
    if (fd < 0) {
        Debug_Printf(4,42,true,0,"[ERROR::File:Open] [%i]", fd);
        return;
    }

    // Save file format
    // [0] = 0x00 Major of engine
    // [1] = 0x00 Minor of engine
    // [2] = 0x01 Patch of engine
    // [3] = 0x01 Length bytes of save file - 1 - 2
    // [4-5] = 0x03 Data length byte/s - 1/2 bytes
    // [5] = 0x48 "H" - hex data byte
    // [6] = 0x69 "i" - hex data byte
    // [7] = 0x21 "!" - hex data byte

    uint8_t buf[] = {0, 0, 1, 1, 3, 72, 105, 33};
    int ret = write(fd, buf, sizeof(buf));
    if (ret < 0) {
        Debug_Printf(4,42,true,0,"[ERROR::File:Write] [%i]", ret);
        close(fd);
        return;
    }
    ret = close(fd);
    if (ret < 0) {
        Debug_Printf(4,42,true,0,"[ERROR::File:Close] [%i]", ret);
        return;
    }

    Debug_Printf(4,42,true,0,"Successful write");
    return;
}