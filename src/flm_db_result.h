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

#ifndef _FLM_DB_RESULT_H_
# define _FLM_DB_RESULT_H_

#include <flm_buffer.h>
#include <flm_object.h>

struct flm_db_result;
typedef const char *(*flm_db_result__get_f)	\
	(struct flm_db_result *, size_t, const char *);

typedef size_t (*flm_db_result__nbrow_f) (struct flm_db_result *);

typedef struct flm_db_result
{
	/* inheritance */
	flm_object object;
	union {
		struct flm_object *	object;
		struct flm_db_result *	db_result;
	} super;

	int				id;

	flm_db_result__get_f		get;
	flm_db_result__nbrow_f		nbrow;
} flm_db_result;

#define FLM_DB_RESULT(_object) FLM_CAST(_object,db_result)

#define flm_db_result_foreach(db, row)				\
	for (row = 0; row < flm_db_result_nbrow (db); ++row)

flm_db_result *
flm_db_result_new (int);

/* protected */
int
flm_db_result__init (flm_db_result *, int);

void
flm_db_result__destruct (flm_db_result *);

/* public */
int
flm_db_result_id (flm_db_result *);

const char *
flm_db_result_get (flm_db_result *, size_t, const char *);

size_t
flm_db_result_nbrow (flm_db_result *);

#endif /* !_FLM_DB_RESULT_H_ */
