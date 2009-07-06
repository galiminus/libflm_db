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

#include "flm/alloc.h"
#include "flm/sqlite_base.h"
#include "flm/sqlite_result.h"

flm_sqlite *
flm_sqlite_new (const char * path)
{
	flm_sqlite * sqlite;

	sqlite = flm_malloc (sizeof (flm_sqlite));
	if (sqlite == NULL) {
		return (NULL);
	}
	if (flm_sqlite__init (sqlite, path) == -1) {
		flm_free (sqlite);
		return (NULL);
	}
	return (sqlite);
}

int
flm_sqlite__init (flm_sqlite * sqlite,
		 const char * path)
{
	if (sqlite3_open (path, &sqlite->file) == -1) {
		goto error;
	}
	if (flm_db__init (&sqlite->db, -1) == -1) {
		goto pqfinish;
	}
	sqlite->super.sqlite = sqlite;

	FLM_OBJECT (sqlite)->destruct =				\
		(flm_object_destruct_f) flm_sqlite__destruct;

	FLM_IO (sqlite)->read =				\
		(flm_io__event_f) flm_sqlite__read;

	FLM_IO (sqlite)->write =				\
		(flm_io__event_f) flm_sqlite__write;

	return (0);

pqfinish:
	sqlite3_close (sqlite->file);
error:
	return (-1);
}

void
flm_sqlite__destruct (flm_sqlite * sqlite)
{
	if (sqlite->file) {
		sqlite3_close (sqlite->file);
	}
	flm_db__destruct (FLM_DB (sqlite));
	return ;
}

void
flm_sqlite__read (flm_sqlite * sqlite)
{
	(void) sqlite;

	return ;
}

void
flm_sqlite__write (flm_sqlite * sqlite)
{
	(void) sqlite;
}
