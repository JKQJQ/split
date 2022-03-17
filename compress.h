/*
 * Copyright (c) Yann Collet, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under both the BSD-style license (found in the
 * LICENSE file in the root directory of this source tree) and the GPLv2 (found
 * in the COPYING file in the root directory of this source tree).
 * You may select, at your option, one of the above-listed licenses.
 */

#include <stdio.h>     // printf
#include <stdlib.h>    // free
#include <string.h>    // strlen, strcat, memset
#include <zstd.h>      // presumes zstd library is installed
#include "compress_common.h"  // Helper functions, CHECK(), and CHECK_ZSTD()
static void compress_orDie(void* const fBuff, int inputSize, const char* oname)
{
    size_t fSize = inputSize;
    //void* const fBuff = mallocAndLoadFile_orDie(fname, &fSize);
    //size_t const cBuffSize = ZSTD_compressBound(fSize);
    size_t const cBuffSize = inputSize;
    printf("cBuffSize=%d fSize=%d\n", cBuffSize, fSize);
    void* const cBuff = malloc_orDie(cBuffSize);


    /* Compress.
     * If you are doing many compressions, you may want to reuse the context.
     * See the multiple_simple_compression.c example.
     */
    size_t const cSize = ZSTD_compress(cBuff, cBuffSize, fBuff, fSize, 3);
    CHECK_ZSTD(cSize);

    saveFile_orDie(oname, cBuff, cSize);

    /* success */
    printf("%6u -> %7u - %s \n", (unsigned)fSize, (unsigned)cSize, oname);
    assert(fSize = inputSize);
    //free(fBuff);
    free(cBuff);
}

static char* createOutFilename_orDie(const char* filename)
{
    size_t const inL = strlen(filename);
    size_t const outL = inL + 5;
    void* const outSpace = malloc_orDie(outL);
    memset(outSpace, 0, outL);
    strcat((char *)outSpace, filename);
    strcat((char *)outSpace, ".zst");
    return (char*)outSpace;
}

void start_compress(void* const fBuff, int inputSize, string filename)
{

    // if (argc!=2) {
    //     printf("wrong arguments\n");
    //     printf("usage:\n");
    //     printf("%s FILE\n", exeName);
    //     return 1;
    // }

    const char* const inFilename = filename.c_str();

    char* const outFilename = createOutFilename_orDie(inFilename);
    compress_orDie(fBuff, inputSize, outFilename);
    free(outFilename);
}