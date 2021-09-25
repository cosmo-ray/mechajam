/**        DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2020 Matthias Gatto <uso.cosmo.ray@gmail.com>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include <yirl/all.h>

void *action(int nbArgs, void **args)
{
	printf("action\n");
	return NULL;
}

void *game_init(int nbArgs, void **args)
{
	Entity *g = args[0];

	YEntityBlock {
		g.action = action;
	}

	void *ret = ywidNewWidget(g, "canvas");
	return ret;
}

void *mod_init(int nbArg, void **args)
{
	Entity *mod = args[0];
	Entity *init = yeCreateArray(NULL, NULL);

	YEntityBlock {
		init.name = "MSCB";
		init.callback = game_init;
		mod.name = "MSCB";
		mod.starting_widget = "test_mscb";
		mod.test_mscb = [];
		mod["window size"] = [800, 600];
		mod.test_mscb["<type>"] = "MSCB";
		mod.test_rc.background = "rgba: 10 150 255 255";
		mod["window name"] = "Mecha-Super-Cook-Battle";
	}

	ywidAddSubType(init);
	printf("Gretting and Salutation !\n");
	return mod;
}
