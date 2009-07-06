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
#include "flm/pgsql_base.h"
#include "flm/pgsql_result.h"

flm_pgsql *
flm_pgsql_new (const char * host,
	       const char * port,
	       const char * database,
	       const char * username,
	       const char * password)
{
	flm_pgsql * pgsql;

	pgsql = flm_malloc (sizeof (flm_pgsql));
	if (pgsql == NULL) {
		return (NULL);
	}
	if (flm_pgsql__init (pgsql, host, port, database, username, password) == -1) {
		flm_free (pgsql);
		return (NULL);
	}
	return (pgsql);
}

int
flm_pgsql__init (flm_pgsql * pgsql,
		 const char * host,
		 const char * port,
		 const char * database,
		 const char * username,
		 const char * password)
{
	pgsql->pgconn = PQsetdbLogin (host, port,			\
				      NULL, NULL,			\
				      database, username, password);
	if (pgsql->pgconn == NULL) {
		goto error;
	}
	if (PQstatus (pgsql->pgconn) == CONNECTION_BAD) {
		goto pqfinish;
	}
	if (flm_db__init (&pgsql->db, PQsocket (pgsql->pgconn)) == -1) {
		goto pqfinish;
	}
	pgsql->super.pgsql = pgsql;

	FLM_OBJECT (pgsql)->destruct =				\
		(flm_object_destruct_f) flm_pgsql__destruct;

	FLM_IO (pgsql)->read =				\
		(flm_io__event_f) flm_pgsql__read;

	FLM_IO (pgsql)->write =				\
		(flm_io__event_f) flm_pgsql__write;

	return (0);

pqfinish:
	PQfinish (pgsql->pgconn);
error:
	return (-1);
}

void
flm_pgsql__destruct (flm_pgsql * pgsql)
{
	if (pgsql->pgconn) {
		PQfinish (pgsql->pgconn);
	}
	flm_db__destruct (FLM_DB (pgsql));
	return ;
}

void
flm_pgsql__read (flm_pgsql * pgsql)
{
	flm_pgsql_result *	pgsql_result;
	ConnStatusType		status;
	flm_db_request *	db_request;
	int			id;

	if ((status = PQstatus (pgsql->pgconn)) == CONNECTION_BAD) {
		FLM_IO (pgsql)->revent.can = 0;
		return ;
	}

	if (PQconsumeInput (pgsql->pgconn) == 0) {
		FLM_IO (pgsql)->revent.can = 0;
		return ;
	}

	if (PQisBusy (pgsql->pgconn) == 1) {
		FLM_IO (pgsql)->revent.can = 1;
		return ;
	}

	flm_list_retrieve_each (FLM_DB (pgsql)->sent, db_request) {
		id = flm_db_request_id (db_request);

		if ((pgsql_result = flm_pgsql_result_new (id, pgsql)) == NULL) {
			break ;
		}

		FLM_DB (pgsql)->result = FLM_DB_RESULT (pgsql_result);
		flm_io_event (FLM_IO (pgsql), id);

		if (FLM_DB (pgsql)->result) {
			flm_release (FLM_DB (pgsql)->result);
			FLM_DB (pgsql)->result = NULL;
		}
	}
	return ;
}

void
flm_pgsql__write (flm_pgsql * pgsql)
{
	flm_db_request * db_request;
	flm_buffer * query_buf;

	flm_list_retrieve_each (FLM_DB (pgsql)->requests, db_request) {
		query_buf = flm_db_request_content (db_request);
		if (query_buf == NULL) {
			continue ;
		}

		if (PQsendQuery (pgsql->pgconn, flm_buffer_str (query_buf)) !=
		    PGRES_COMMAND_OK) {
			continue ;
		}
	}
	return ;
}

PGconn *
flm_pgsql__conn (flm_pgsql * pgsql)
{
	return (pgsql->pgconn);
}
