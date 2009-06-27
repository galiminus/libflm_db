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
#include "flm/db_result.h"

flm_db_result *
flm_db_result_new (int id)
{
	flm_db_result * db_result;

	db_result = flm_malloc (sizeof (flm_db_result));
	if (db_result == NULL) {
		return (NULL);
	}
	if (flm_db_result__init (db_result, id) == -1) {
		flm_free (db_result);
		return (NULL);
	}
	return (db_result);
}

int
flm_db_result__init (flm_db_result * db_result,
		     int id)
{
	if (flm_object__init (&db_result->object) == -1) {
		return (-1);
	}
	db_result->super.db_result = db_result;

	FLM_OBJECT (db_result)->destruct =	\
		(flm_object_destruct_f) flm_db_result__destruct;

	db_result->id = id;
	db_result->nbrow = NULL;
	db_result->get = NULL;
	return (0);
}

void
flm_db_result__destruct (flm_db_result * db_result)
{
	flm_object__destruct (FLM_OBJECT (db_result));
	return ;
}

/* public */
int
flm_db_result_id (flm_db_result * db_result)
{
	return (db_result->id);
}

const char *
flm_db_result_get (flm_db_result * db_result,
		   size_t row,
		   const char * col)
{
	if (db_result->get == NULL) {
		return (NULL);
	}
	return (db_result->get (db_result, row, col));
}

size_t
flm_db_result_nbrow (flm_db_result * db_result)
{
	if (db_result->nbrow == NULL) {
		return (0);
	}
	return (db_result->nbrow (db_result));
}
