/*
 * Copyright (C) 2007, libturglem development team.
 *
 * This file is released under the LGPL.
 */

#include <stdio.h>
#include <string.h>
#include <turglem/lemmatizer.h>
#include <turglem/russian/charset_adapters.h>

turglem lem;

void lemmatize_and_print(const char *s)
{
	/* for chsr* to letters */
	MAFSA_letter in_buf[1024];
	ssize_t in_sz;
	/* for lemmatization */
	int forms[1024*2];
	size_t form_cnt;
	size_t i;
	MAFSA_letter out_buf[1024];
	size_t out_sz;
	/* for letters to char* */
	char out_ch[1024];

	in_sz = LEM_RUSSIAN_conv_string_to_letters_utf8(s, in_buf, 1024);
	if (in_sz > 0)
	{
		printf("entered russian word (%d letters)\n", in_sz);

		form_cnt = turglem_lemmatize(lem, in_buf, in_sz, forms, 1024, RUSSIAN_LETTER_DELIM, 1);
		printf("total lemmatization forms: %d\n", form_cnt);

		for (i = 0; i < form_cnt; i++)
		{
			out_sz = turglem_build_form(lem, in_buf, in_sz, out_buf, 1024, forms[2*i+0], forms[2*i+1], 0);
			LEM_RUSSIAN_conv_letters_to_string_utf8(out_buf, out_sz, out_ch, 1024);
			printf("Form-0 is '%s'\n", out_ch);
		}
	}
	else
	{
		printf("error: should be russian word in UTF-8.\n");
	}
}

int main(int argc, char **argv)
{
	char in_s_buf[1024];
	char *nl_ptr;

	if(argc != 4)
	{
		printf("Usage: %s words.dic predict.dic paradigms.bin\n", argv[0]);
		return -1;
	}

	lem = turglem_load(argv[1], argv[2], argv[3]);

	while (!feof(stdin))
	{
		fgets(in_s_buf, 1024, stdin);
		nl_ptr = strchr(in_s_buf, '\n');
		if (nl_ptr) *nl_ptr = 0;
		nl_ptr = strchr(in_s_buf, '\r');
		if (nl_ptr) *nl_ptr = 0;

		lemmatize_and_print(in_s_buf);
	}

	turglem_close(lem);

	return 0;
}

