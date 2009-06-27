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

#ifndef _FLM_DB_REQUEST_H_
# define _FLM_DB_REQUEST_H_

#include <stdarg.h>

#include <flm/buffer.h>
#include <flm/object.h>

typedef struct flm_db_request
{
	/* inheritance */
	flm_object object;
	union {
		struct flm_object *	object;
		struct flm_db_request *	db_request;
	} super;

	flm_buffer *			content;
	flm_object *			data;
	int				id;
} flm_db_request;

#define FLM_DB_REQUEST(_object) FLM_CAST(_object,db_request)

flm_db_request *
flm_db_request_new (int, flm_object *, const char *, ...);

flm_db_request *
flm_db_request_vnew (int, flm_object *, const char *, va_list);

/* protected */
int
flm_db_request__init (flm_db_request *, int, flm_object *,	\
		      const char *, va_list);

void
flm_db_request__destruct (flm_db_request *);

/* public */
flm_buffer *
flm_db_request_content (flm_db_request *);

int
flm_db_request_id (flm_db_request *);

#endif /* !_FLM_DB_REQUEST_H_ */
