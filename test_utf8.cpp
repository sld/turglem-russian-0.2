/*
 * Copyright (C) 2007, libturglem development team.
 *
 * This file is released under the LGPL.
 */

#include <turglem/lemmatizer.hpp>
#include <turglem/russian/charset_adapters.hpp>

int main(int argc, char **argv)
{
	char in_s_buf[1024];
	char *nl_ptr;

	tl::lemmatizer lem;

	if(argc != 4)
	{
		printf("Usage: %s words.dic predict.dic paradigms.bin\n", argv[0]);
		return -1;
	}

	lem.load_lemmatizer(argv[1], argv[3], argv[2]);

	while (!feof(stdin))
	{
		fgets(in_s_buf, 1024, stdin);
		nl_ptr = strchr(in_s_buf, '\n');
		if (nl_ptr) *nl_ptr = 0;
		nl_ptr = strchr(in_s_buf, '\r');
		if (nl_ptr) *nl_ptr = 0;

		if (in_s_buf[0])
		{
			tl::paradigms pars;
			size_t pcnt = lem.lemmatize<russian_utf8_adapter>(in_s_buf, pars);

			for (size_t i = 0; i < pcnt; i++)
			{
				std::string s;
				u_int32_t src_form = lem.get_src_form(pars, i);
				s = lem.get_text<russian_utf8_adapter>(pars, i, 0);
				printf("PARADIGM %d: normal form '%s'\n", i, s.c_str());
				printf("\tpart of speech:%d\n", lem.get_part_of_speech(pars, i, src_form));
			}
		}
	}

	return 0;
}

