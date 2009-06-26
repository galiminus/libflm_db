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

#include "flm_alloc.h"
#include "flm_pgsql_result.h"

flm_pgsql_result *
flm_pgsql_result_new (int id,
		      flm_pgsql * pgsql)
{
	flm_pgsql_result * pgsql_result;

	pgsql_result = flm_malloc (sizeof (flm_pgsql_result));
	if (pgsql_result == NULL) {
		return (NULL);
	}
	if (flm_pgsql_result__init (pgsql_result, id, pgsql) == -1) {
		flm_free (pgsql_result);
		return (NULL);
	}
	return (pgsql_result);
}

int
flm_pgsql_result__init (flm_pgsql_result * pgsql_result,
			int id,
			flm_pgsql * pgsql)
{
	PGresult * result;
	PGconn * pgconn;

	if ((pgconn = flm_pgsql__conn (pgsql)) == NULL) {
		goto error;
	}

	if ((result = PQgetResult (pgconn)) == NULL) {
		goto error;
	}

	if (flm_db_result__init (&pgsql_result->db_result, id) == -1) {
		goto pgclear;
	}
	pgsql_result->super.pgsql_result = pgsql_result;

	FLM_OBJECT (pgsql_result)->destruct =				\
		(flm_object_destruct_f) flm_pgsql_result__destruct;

	pgsql_result->pg_result = result;

	FLM_DB_RESULT (pgsql_result)->nbrow =				\
		(flm_db_result__nbrow_f) flm_pgsql_result__nbrow;
	FLM_DB_RESULT (pgsql_result)->get =				\
		(flm_db_result__get_f) flm_pgsql_result__get;
	return (0);

pgclear:
	PQclear (pgsql_result->pg_result);
error:
	return (-1);
}

void
flm_pgsql_result__destruct (flm_pgsql_result * pgsql_result)
{
	if (pgsql_result->pg_result) {
		PQclear (pgsql_result->pg_result);
	}
	flm_object__destruct (FLM_OBJECT (pgsql_result));
	return ;
}


const char *
flm_pgsql_result__get (flm_pgsql_result * pgsql_result,
		       size_t row,
		       const char * col)
{
	int col_nb;
	const char * result;

	if ((col_nb = PQfnumber(pgsql_result->pg_result, col)) < 0) {
		return (NULL);
	}
	if ((result = PQgetvalue(pgsql_result->pg_result, row, col_nb)) == NULL) {
		return (NULL);
	}
	return (result);

}

size_t
flm_pgsql_result__nbrow (flm_pgsql_result * pgsql_result)
{
	int nbrow;

	if ((nbrow = PQntuples (pgsql_result->pg_result)) < 0) {
		return (0);
	}
	return ((size_t)(nbrow));
}
