/*
 * Copyright (c) 2008-2009, Victor Goya <phorque@phorque.net>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _FLM_DB_BASE_H_
# define _FLM_DB_BASE_H_

#include <flm/list.h>
#include <flm/io.h>

#include "flm/db_request.h"
#include "flm/db_result.h"

typedef struct flm_db
{
	/* inheritance */
	flm_io io;
	union {
		struct flm_object *	object;
		struct flm_io *		io;
		struct flm_db *		db;
	} super;

	flm_list *		requests;
	flm_list *		sent;

	flm_db_result *		result;
} flm_db;

#define FLM_DB(_object) FLM_CAST(_object,db)

flm_db *
flm_db_new (int);

/* protected */
int
flm_db__init (flm_db *, int);

void
flm_db__destruct (flm_db *);

/* public */
int
flm_db_query (flm_db *, int, flm_object *, const char *, ...);

int
flm_db_vquery (flm_db *, int, flm_object *, const char *, va_list);

int
flm_db_send (flm_db *);

flm_db_result *
flm_db_retrieve_result (flm_db *);

#endif /* !_FLM_DB_BASE_H_ */
