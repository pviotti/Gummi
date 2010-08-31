/**
 * @file   environment.c
 * @brief  
 * @author Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 *
 * Copyright (C) 2010 -  Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "environment.h"
#include "utils.h"

/* reference to global environment instance */
extern gummi_t* gummi;
int workfd = -1;


gummi_t* gummi_init(editor_t* ed, iofunctions_t* iof, motion_t* mo,
        preview_t* prev) {
    gummi_t* g = (gummi_t*)malloc(sizeof(gummi_t));
    
    tmpdir = g_get_tmp_dir();
    g->editor = ed;
    g->iofunc = iof;
    g->motion = mo;
    g->preview = prev;
    g->filename = NULL;
    g->pdffile = NULL;
    g->workfile = NULL;
    return g;
}


void gummi_create_environment() {
    if (workfd != -1) {
        close(workfd);
    } // close previous work file using its file descriptor
    
    // TODO: use const char TMPDIR (see environment.h)
    char tname[] = "/tmp/gummi_XXXXXXX"; 
    workfd = mkstemp(tname); 
    if (gummi->workfile) free(gummi->workfile);
    gummi->workfile = (gchar*)malloc(strlen(tname) + 1);
    strcpy(gummi->workfile, tname);

    char *tmp = (gchar*)malloc(strlen(tname) + 5);    
    strcpy(tmp, tname);
    strncat(tmp, ".pdf", sizeof (tmp + 4));
    gummi->pdffile = tmp;
    
    slog(L_INFO, "Environment created for:\n");
    slog(L_INFO, "TEX: %s\n", gummi->filename);
    slog(L_INFO, "TMP: %s\n", gummi->workfile);
    slog(L_INFO, "PDF: %s\n", gummi->pdffile); 
}


