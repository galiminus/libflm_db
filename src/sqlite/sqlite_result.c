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
#include "flm/sqlite_result.h"

flm_sqlite_result *
flm_sqlite_result_new (int id,
		      flm_sqlite * sqlite)
{
	flm_sqlite_result * sqlite_result;

	sqlite_result = flm_malloc (sizeof (flm_sqlite_result));
	if (sqlite_result == NULL) {
		return (NULL);
	}
	if (flm_sqlite_result__init (sqlite_result, id, sqlite) == -1) {
		flm_free (sqlite_result);
		return (NULL);
	}
	return (sqlite_result);
}

int
flm_sqlite_result__init (flm_sqlite_result * sqlite_result,
			int id,
			flm_sqlite * sqlite)
{
	if (flm_db_result__init (&sqlite_result->db_result, id) == -1) {
		goto error;
	}
	sqlite_result->super.sqlite_result = sqlite_result;

	FLM_OBJECT (sqlite_result)->destruct =				\
		(flm_object_destruct_f) flm_sqlite_result__destruct;

	FLM_DB_RESULT (sqlite_result)->nbrow =				\
		(flm_db_result__nbrow_f) flm_sqlite_result__nbrow;
	FLM_DB_RESULT (sqlite_result)->get =				\
		(flm_db_result__get_f) flm_sqlite_result__get;
	return (0);

error:
	return (-1);
}

void
flm_sqlite_result__destruct (flm_sqlite_result * sqlite_result)
{
	flm_object__destruct (FLM_OBJECT (sqlite_result));
	return ;
}


const char *
flm_sqlite_result__get (flm_sqlite_result * sqlite_result,
		       size_t row,
		       const char * col)
{
	return ("");

}

size_t
flm_sqlite_result__nbrow (flm_sqlite_result * sqlite_result)
{
	return (0);
}
