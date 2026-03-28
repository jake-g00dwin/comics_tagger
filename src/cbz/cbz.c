/*
 * Author: username
 * Date: 2026
 * filename: cbz.c
 * description: module_purpose
 */

#include "cbz.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
// #include <uchar.h>
#include <zip.h>

// Constants

// Globals and Function Pointer assignments.

// Default implimentation assignments.
void *(*calloc_fn)(size_t number, size_t size) = calloc;
void *(*malloc_fn)(size_t size)                = malloc;
void (*free_fn)(void *ptr)                     = free;

// Helper(Private) Functions

int init_metadata_title(cbz_metadata_t *md)
{
    md->title = calloc_fn(CBZ_MAX_TITLE_LEN, sizeof(char));
    if (!md->title)
    {
        fprintf(stderr, "Failed to allocate memory for: title\n");
        return STATUS_ERR;
    }
    strcpy(md->title, "default_title");
    return STATUS_OK;
}

int init_metadata_series(cbz_metadata_t *md)
{
    md->series = calloc_fn(CBZ_DEFAULT_FIELD_LEN, sizeof(char));
    if (!md->series)
    {
        fprintf(stderr, "Failed to allocate memory for: series\n");
        return STATUS_ERR;
    }
    return STATUS_OK;
}

int init_metadata_author(cbz_metadata_t *md)
{
    md->author = calloc_fn(CBZ_MAX_AUTHOR_LEN, sizeof(char));
    if (!md->author)
    {
        fprintf(stderr, "Failed to allocate memory for: author\n");
        return STATUS_ERR;
    }
    return STATUS_OK;
}

int init_metadata_publisher(cbz_metadata_t *md)
{
    md->publisher = calloc_fn(CBZ_DEFAULT_FIELD_LEN, sizeof(char));
    if (!md->publisher)
    {
        fprintf(stderr, "Failed to allocate memory for: publisher\n");
        return STATUS_ERR;
    }
    return STATUS_OK;
}

void init_metadata_date(cbz_metadata_t *md)
{
    md->year  = (uint16_t)CBZ_DEFAULT_YEAR;
    md->month = (uint8_t)CBZ_DEFAULT_MONTH;
    md->day   = (uint8_t)CBZ_DEFAULT_DAY;
}

int init_metadata_language(cbz_metadata_t *md)
{
    md->language = calloc_fn(CBZ_MAX_LANG_LEN, sizeof(char));
    if (!md->language)
    {
        fprintf(stderr, "Failed to allocate memory for: language\n");
        return STATUS_ERR;
    }
    strcpy(md->language, "english");
    return STATUS_OK;
}

int init_metadata_description(cbz_metadata_t *md)
{
    md->description = calloc_fn(CBZ_MAX_DESC_LEN, sizeof(char));
    if (!md->description)
    {
        fprintf(stderr, "Failed to allocate memory for: description\n");
        return STATUS_ERR;
    }
    return STATUS_OK;
}

int init_metadata_tags(cbz_metadata_t *md)
{
    md->tag_vector.length   = 0;
    md->tag_vector.capacity = CBZ_DEFAULT_TAGVEC_CAP;
    md->tag_vector.tags     = calloc_fn(md->tag_vector.capacity, sizeof(metadata_tag_t));
    if (!md->tag_vector.tags)
    {
        fprintf(stderr, "Failed to allocate memory for: tags\n");
        return STATUS_ERR;
    }
    return STATUS_OK;
}

// Public facing functions.

int cbz_init_metadata(cbz_metadata_t *md)
{
    if (md->is_initialized)
    {
        fprintf(stderr, "Passed metadata already initialized.\n");
        return STATUS_ERR;
    }

    if (init_metadata_title(md) != STATUS_OK) { return STATUS_ERR; }
    if (init_metadata_series(md) != STATUS_OK) { return STATUS_ERR; }
    if (init_metadata_author(md) != STATUS_OK) { return STATUS_ERR; }
    if (init_metadata_publisher(md) != STATUS_OK) { return STATUS_ERR; }

    init_metadata_date(md);

    if (init_metadata_language(md) != STATUS_OK) { return STATUS_ERR; }
    if (init_metadata_description(md) != STATUS_OK) { return STATUS_ERR; }

    md->issue = (uint16_t)CBZ_DEFAULT_ISSUE;

    if (init_metadata_tags(md) != STATUS_OK) { return STATUS_ERR; }

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

    free_fn(md->title);
    md->title = NULL;

    free_fn(md->series);
    md->series = NULL;

    free_fn(md->author);
    md->author = NULL;

    free_fn(md->publisher);
    md->publisher = NULL;

    md->year      = (uint16_t)CBZ_DEFAULT_YEAR;
    md->month     = (uint8_t)CBZ_DEFAULT_MONTH;
    md->day       = (uint8_t)CBZ_DEFAULT_DAY;

    free_fn(md->language);
    md->language = NULL;

    free_fn(md->description);
    md->description = NULL;

    // Probably need to free each individual tag as well.
    free_fn(md->tag_vector.tags);
    md->tag_vector.tags     = NULL;
    md->tag_vector.capacity = 0;
    md->tag_vector.length   = 0;

    return STATUS_OK;
}

int cbz_create(cbz_t *cbz, const char *path)
{
    // zip_t        *archive;
    // zip_error_t  *zip_err;
    // zip_source_t *zip_src;

    // int           error;

    // Create the archive if it doesn't exist, throw error if it does.
    // archive = zip_open(path, ZIP_CREATE | ZIP_EXCL, &error);
    // archive = zip_open_from_source(zip_src,ZIP_CREATE|ZIP_EXCL , zip_err);

    return 0;
}

int cbz_tag_vec_init(metadata_tag_vec_t *tag_vec)
{
    if (!tag_vec)
    {
        return STATUS_ERR;
    }

    tag_vec->tags     = NULL;
    tag_vec->length   = 0;
    tag_vec->capacity = 0;

    return STATUS_OK;
}

int cbz_tag_vec_set_capacity(metadata_tag_vec_t *tag_vec, size_t capacity)
{
    tag_vec->capacity = capacity;
    tag_vec->tags     = calloc_fn(capacity, sizeof(metadata_tag_t));
    return STATUS_OK;
}
