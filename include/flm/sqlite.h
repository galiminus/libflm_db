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

#ifndef _FLM_SQLITE_H_
# define _FLM_SQLITE_H_

#include "sqlite3.h"

#include "flm/db_base.h"

typedef struct flm_sqlite
{
	/* inheritance */
	flm_db db;
	union {
		struct flm_object *	object;
		struct flm_io *		io;
		struct flm_db *		db;
		struct flm_sqlite *	sqlite;
	} super;

	sqlite3 *	file;
} flm_sqlite;

#define FLM_SQLITE(_object) FLM_CAST(_object,list)

flm_sqlite *
flm_sqlite_new (const char *);

/* protected */
int
flm_sqlite__init (flm_sqlite *, const char *);

void
flm_sqlite__destruct (flm_sqlite *);

void
flm_sqlite__read (flm_sqlite *);

void
flm_sqlite__write (flm_sqlite *);

#endif /* !_FLM_SQLITE_H_ */
