/*
 * Copyright (C) 2007, libturglem development team.
 *
 * This file is released under the LGPL.
*/

#include <turglem/morph_compiler.hpp>
#include <turglem/russian/charset_adapters.hpp>

int main(int argc, char ** argv)
{
	if (argc != 6)
	{
		printf("%s paradigms.xml lemmas.xml dict.dic flexias.bin prediction.dic\n", argv[0]);
		return -1;
	}

	morph_compiler<russian_utf8_adapter> rmc;

	rmc.load_and_convert_paradigms(argv[1], argv[4]);
	printf("Flexias loaded and saved in binary mode\n");

	rmc.load_lemmas(argv[2]);
	printf("Lemmas loaded\n");

	rmc.process_and_save_dicts(argv[3], argv[5]);

	printf("Dictionary and prediction saved!\n");

	return 0;
}

