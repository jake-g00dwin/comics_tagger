/**
 * @brief Module description
 * @details This file is an <Purpose here>
 * @author Jake G
 * @date 2026
 * @copyright None
 * @file cbz.h
 */

// #pragma once
#ifndef cbz_H
#define cbz_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

enum status_codes{
    STATUS_OK = 0,
    STATUS_ERR = 1,
};

    typedef struct{
        int year;
        int month;
        int day;
    }pub_date_t;

    typedef struct{
        char *name;
        char *value;
    }metadata_field_t;

    typedef struct{
        char *tag_type;
        char *tag_value;
    }metadata_tag_t;

    typedef struct
    {
        char *title;
        char *language;
        char *description;
/*
        char *source_url;
        bool is_multi_work;
        bool is_manga;
        bool is_colored;
        int version;
        uint16_t view_count;
        uint8_t stars;
        pub_date_t published_date;
        size_t bookmarked_page_index;
        size_t num_pages;
*/
    }cbz_metadata_t;



    typedef struct 
    {
        cbz_metadata_t meta_data;
        char  *filename;
        char *file_path;
    }cbz_t;

    //cbz_metadata_t cbz_init_metadata(void);
    int cbz_init_metadata(cbz_metadata_t *md);

    cbz_t cbz_new(void);
    int    cbz_create(cbz_t *cbz);
    int    cbz_write(void);
    int    cbz_open(void);
    int    cbz_get_metadata(void);
    int    cbz_set_metadata(void);
    int    cbz_get_image(size_t page_index);
    size_t cbz_get_size(void);
    int get_cbz_data(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // cbz_H
