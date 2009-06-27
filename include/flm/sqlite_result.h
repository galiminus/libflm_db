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

#ifndef _FLM_SQLITE_RESULT_H_
# define _FLM_SQLITE_RESULT_H_

#include "sqlite3.h"

#include "flm/sqlite.h"
#include "flm/db_result.h"

typedef struct flm_sqlite_result
{
	/* inheritance */
	flm_db_result db_result;
	union {
		struct flm_object *		object;
		struct flm_db_result *		db_result;
		struct flm_sqlite_result *	sqlite_result;
	} super;
} flm_sqlite_result;

#define FLM_SQLITE_RESULT(_object) FLM_CAST(_object,sqlite_result)

flm_sqlite_result *
flm_sqlite_result_new (int, flm_sqlite *);

/* protected */
int
flm_sqlite_result__init (flm_sqlite_result *, int, flm_sqlite *);

void
flm_sqlite_result__destruct (flm_sqlite_result *);

const char *
flm_sqlite_result__get (flm_sqlite_result *, size_t, const char *);

size_t
flm_sqlite_result__nbrow (flm_sqlite_result *);

#endif /* !_FLM_SQLITE_RESULT_H_ */
