/*
 * Author: username
 * Date: 2026
 * filename: cbz.c
 * description: module_purpose
 */

#include "cbz.h"

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/stat.h>
#include <sys/syscall.h>

// #include <uchar.h>

#include <zip.h>

int cbz_init_metadata(cbz_metadata_t *md)
{
    if (md->is_initialized)
    {
        fprintf(stderr, "Passed metadata already initialized.\n");
        return STATUS_ERR;
    }

    md->title = calloc(CBZ_MAX_TITLE_LEN, sizeof(char));
    if (!md->title)
    {
        fprintf(stderr, "Failed to allocate memory for: title\n");
        return STATUS_ERR;
    }
    strcpy(md->title, "default_title");

    md->series = calloc(CBZ_DEFAULT_FIELD_LEN, sizeof(char));
    if (!md->series)
    {
        fprintf(stderr, "Failed to allocate memory for: series\n");
        return STATUS_ERR;
    }

    md->author = calloc(CBZ_MAX_AUTHOR_LEN, sizeof(char));
    if (!md->author)
    {
        fprintf(stderr, "Failed to allocate memory for: author\n");
        return STATUS_ERR;
    }

    md->publisher = calloc(CBZ_DEFAULT_FIELD_LEN, sizeof(char));
    if (!md->publisher)
    {
        fprintf(stderr, "Failed to allocate memory for: publisher\n");
        return STATUS_ERR;
    }

    md->year           = (uint16_t)CBZ_DEFAULT_YEAR;
    md->month          = (uint8_t)CBZ_DEFAULT_MONTH;
    md->day            = (uint8_t)CBZ_DEFAULT_DAY;

    md->is_initialized = true;
    return STATUS_OK;
}

int cbz_free_metadata(cbz_metadata_t *md)
{
    if (!md->is_initialized)
    {
        fprintf(stderr, "Error: passed uninitialized struct.\n");
        return STATUS_ERR;
    }

    free(md->title);
    md->title = NULL;

    free(md->series);
    md->series = NULL;

    free(md->author);
    md->author = NULL;

    free(md->publisher);
    md->publisher = NULL;

    md->year      = (uint16_t)CBZ_DEFAULT_YEAR;
    md->month     = (uint8_t)CBZ_DEFAULT_MONTH;
    md->day       = (uint8_t)CBZ_DEFAULT_DAY;

    return STATUS_OK;
}

int cbz_create(cbz_t *cbz, const char *path)
{
    zip_t        *archive;
    zip_error_t  *zip_err;
    zip_source_t *zip_src;

    int           error;

    // Create the archive if it doesn't exist, throw error if it does.
    archive = zip_open(path, ZIP_CREATE | ZIP_EXCL, &error);
    // archive = zip_open_from_source(zip_src,ZIP_CREATE|ZIP_EXCL , zip_err);

    return 0;
}

// dumb test function
int add_two(int a)
{
    int b = a;
    b += 2;
    return b;
}
