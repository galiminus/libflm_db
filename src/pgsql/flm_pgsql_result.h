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

#ifndef _FLM_PGSQL_RESULT_H_
# define _FLM_PGSQL_RESULT_H_

#include <libpq-fe.h>

#include "flm_pgsql.h"
#include "flm_db_result.h"

typedef struct flm_pgsql_result
{
	/* inheritance */
	flm_db_result db_result;
	union {
		struct flm_object *		object;
		struct flm_db_result *		db_result;
		struct flm_pgsql_result *	pgsql_result;
	} super;

	PGresult *	pg_result;

} flm_pgsql_result;

#define FLM_PGSQL_RESULT(_object) FLM_CAST(_object,pgsql_result)

flm_pgsql_result *
flm_pgsql_result_new (int, flm_pgsql *);

/* protected */
int
flm_pgsql_result__init (flm_pgsql_result *, int, flm_pgsql *);

void
flm_pgsql_result__destruct (flm_pgsql_result *);

const char *
flm_pgsql_result__get (flm_pgsql_result *, size_t, const char *);

size_t
flm_pgsql_result__nbrow (flm_pgsql_result *);

#endif /* !_FLM_PGSQL_RESULT_H_ */
