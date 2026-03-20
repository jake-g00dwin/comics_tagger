/*
 * Author: username
 * Date: 2026
 * filename: cbz.c
 * description: module_purpose
 */

#include "cbz.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/syscall.h>
#include <errno.h>

//#include <sys/stat.h>

//#include <locale.h>
//#include <uchar.h>
//#include <wchar.h>

#include <zip.h>


int cbz_init_metadata(cbz_metadata_t *md)
{
    md = (cbz_metadata_t *)malloc(sizeof(cbz_metadata_t));
    if(!md){
        fprintf(stderr, "Failed to allocate memory: cbz_init_metadata()\n");
        return STATUS_ERR;
    }

    return STATUS_OK;
}

int  cbz_create(cbz_t *cbz, const char *path)
{
    zip_t *archive;
    zip_error_t *zip_err;
    zip_source_t *zip_src;

    int error;

    //Create the archive if it doesn't exist, throw error if it does.
    archive = zip_open(path, ZIP_CREATE|ZIP_EXCL, &error);
    //archive = zip_open_from_source(zip_src,ZIP_CREATE|ZIP_EXCL , zip_err);

    return 0;
}

// dumb test function
int add_two(int a)
{
    int b = a;
    b += 2;
    return b;
}
