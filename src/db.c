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
#include "flm/db.h"

flm_db *
flm_db_new (int fd)
{
	flm_db * db;

	db = flm_malloc (sizeof (db));
	if (db == NULL) {
		return (NULL);
	}
	if (flm_db__init (db, fd) == -1) {
		flm_free (db);
		return (NULL);
	}
	return (db);
}

int
flm_db__init (flm_db * db,
	      int fd)
{
	if (flm_io__init (&db->io, fd) == -1) {
		goto error;
	}
	db->super.db = db;

	FLM_OBJECT (db)->destruct = \
		(flm_object_destruct_f) flm_db__destruct;

	if ((db->requests = flm_list_new ()) == NULL) {
		goto io_destruct;
	}

	if ((db->sent = flm_list_new ()) == NULL) {
		goto release_requests;
	}

	db->result = NULL;

	return (0);

release_requests:
	flm_release (db->requests);
io_destruct:
	flm_io__destruct (FLM_IO (db));
error:
	return (-1);
}

void
flm_db__destruct (flm_db * db)
{
	if (db->requests) {
		flm_release (db->requests);
	}
	if (db->sent) {
		flm_release (db->sent);
	}
	if (db->result) {
		flm_release (db->result);
	}
	flm_io__destruct (FLM_IO (db));
	return ;
}

/* public */
int
flm_db_query (flm_db * db,
	      int id,
	      flm_object * data,
	      const char * format,
	      ...)
{
	va_list ap;
	int ret;

	va_start (ap, format);
	ret = flm_db_vquery (db, id, data, format, ap);
	va_end (ap);

	if (ret == -1) {
		return (-1);
	}
	return (0);
}

int
flm_db_vquery (flm_db * db,
	       int id,
	       flm_object * data,
	       const char * format,
	       va_list ap)
{
	flm_db_request * request;

	if ((request = flm_db_request_vnew (id, data, format, ap)) == NULL) {
		goto error;
	}
	if (flm_io__want_write (FLM_IO (db)) == -1) {
		goto release_request;
	}
	if (flm_list_add (db->requests, FLM_OBJECT (request)) == -1) {
		goto release_request;
	}
	flm_release (request);
	return (0);

release_request:
	flm_release (request);
error:
	return (-1);
}

int
flm_db_send (flm_db * db)
{
	return (0);
}

flm_db_result *
flm_db_retrieve_result (flm_db * db)
{
	flm_db_result * result;

	if (db->result == NULL) {
		return (NULL);
	}
	result = db->result;
	db->result = NULL;
	return (result);
}
