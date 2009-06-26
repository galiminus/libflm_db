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
#include "flm_db_request.h"

flm_db_request *
flm_db_request_new (int id,
		    flm_object * data,
		    const char * format,
		    ...)
{
	va_list ap;
	flm_db_request * db_request;

	va_start (ap, format);
	db_request = flm_db_request_vnew (id, data, format, ap);
	va_end (ap);
	return (db_request);
}

flm_db_request *
flm_db_request_vnew (int id,
		     flm_object * data,
		     const char * format,
		     va_list ap)
{
	flm_db_request * db_request;

	db_request = flm_malloc (sizeof (flm_db_request));
	if (db_request == NULL) {
		return (NULL);
	}
	if (flm_db_request__init (db_request, id, data, format, ap) == -1) {
		flm_free (db_request);
		return (NULL);
	}
	return (db_request);
}

int
flm_db_request__init (flm_db_request * db_request,
		      int id,
		      flm_object * data,
		      const char * format,
		      va_list ap)
{
	if (flm_object__init (&db_request->object) == -1) {		goto error;
	}
	db_request->super.db_request = db_request;

	FLM_OBJECT (db_request)->destruct =	\
		(flm_object_destruct_f) flm_db_request__destruct;

	db_request->data = flm_retain (data);

	if ((db_request->content = flm_buffer_new ()) == NULL) {
		goto object_destruct;
	}

	if (flm_buffer_vprintf (db_request->content, format, ap) == -1) {
		goto release_content;
	}

	db_request->id = id;

	return (0);

release_content:
	flm_release (db_request->content);
object_destruct:
	flm_object__destruct (FLM_OBJECT (db_request));
error:
	return (-1);
}

void
flm_db_request__destruct (flm_db_request * db_request)
{
	if (db_request->content) {
		flm_release (db_request->content);
	}
	if (db_request->data) {
		flm_release (db_request->data);
	}
	flm_object__destruct (FLM_OBJECT (db_request));
	return ;
}

/* public */
flm_buffer *
flm_db_request_content (flm_db_request * db_request)
{
	return (db_request->content);
}

int
flm_db_request_id (flm_db_request * db_request)
{
	return (db_request->id);
}
