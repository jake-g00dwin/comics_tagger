/**
 * @brief Module description
 * @details This file is an <Purpose here>
 * @author Jake G
 * @date 2026
 * @copyright (c) 2026 Jake Goodwin
 * @file cbz.h
 */

// #pragma once
#ifndef cbz_H
#define cbz_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <locale.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#include <zip.h>

#define CBZ_MAX_TITLE_LEN 255 //
#define CBZ_MAX_AUTHOR_LEN 255
#define CBZ_MAX_LANG_LEN 32
#define CBZ_MAX_DESC_LEN 512
#define CBZ_DEFAULT_FIELD_LEN 255

#define CBZ_DEFAULT_YEAR 1971
#define CBZ_DEFAULT_MONTH 1
#define CBZ_DEFAULT_DAY 1
#define CBZ_DEFAULT_ISSUE 1

#define CBZ_DEFAULT_TAGVEC_CAP 16

    enum status_codes
    {
        STATUS_OK  = 0,
        STATUS_ERR = 1,
    };

    typedef struct
    {
        char        *name;
        zip_uint64_t index;
    } cbz_page_t;

    typedef struct
    {
        int year;
        int month;
        int day;
    } pub_date_t;

    typedef struct
    {
        char *name;
        char *value;
    } metadata_field_t;

    typedef struct
    {
        metadata_field_t *fields;
        size_t            length;
        size_t            vec_capacity;
    } metadata_field_vec_t;

    typedef struct
    {
        char *tag_type;
        char *tag_value;
    } metadata_tag_t;

    typedef struct
    {
        metadata_tag_t *tags;
        size_t          length;
        size_t          capacity;
    } metadata_tag_vec_t;

    typedef struct
    {
        char              *title;
        char              *series;
        char              *author;
        char              *publisher;
        uint16_t           year;
        uint8_t            month;
        uint8_t            day;
        uint16_t           issue;
        char              *language;
        char              *description;
        metadata_tag_vec_t tag_vector;
        bool               is_initialized;
    } cbz_metadata_t;

    typedef struct
    {
        zip_t         *archive;
        cbz_page_t    *pages;
        size_t         page_count;
        size_t         capacity;
        cbz_metadata_t meta_data;
        char          *filename;
        char          *file_path;
        bool           has_metadata;
    } cbz_t;

    // cbz_metadata_t cbz_init_metadata(void);
    int cbz_init_metadata(cbz_metadata_t *md);
    int cbz_free_metadata(cbz_metadata_t *md);

    int cbz_tag_vec_init(metadata_tag_vec_t *tag_vec);
    int cbz_tag_vec_set_capacity(metadata_tag_vec_t *tag_vec, size_t capacity);

    // Externally defined function pointer.
    extern void *(*malloc_fn)(size_t size);
    extern void *(*calloc_fn)(size_t number, size_t size);
    extern void (*free_fn)(void *ptr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // cbz_H
