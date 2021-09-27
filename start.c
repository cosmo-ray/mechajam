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

static Entity *tf;
static Entity *tf_do_action;
static Entity *tf_set_globals;

void *action(int nbArgs, void **args)
{
	printf("action\n");
	return yesCall(tf_do_action, args[1]);
}

void *game_init(int nbArgs, void **args)
{
	Entity *g = args[0];

	tf = ygGet("tactical-fight");
	tf_do_action = yeGet(tf, "do_action");
	tf_set_globals = yeGet(tf, "set_globals");
	YEntityBlock {
		g.action = action;
		g.entries = {};
		g.pj = {};
	};

	Entity *pj = yeGet(g, "pj");
	Entity *pj_sp = yeCreateArray(pj, "sprite");
	YEntityBlock {
		pj.name = "Eon";
		pj_sp.path = "Sprites/guardBlue64.png";
		pj_sp.disposition = "lrdu";
		pj_sp.size = 32;
		pj_sp.length = 3;
	}

	Entity *mainScreen = ywCreateCanvasEnt(g, "mainScreen");
	void *ret = ywidNewWidget(g, "container");
	ywPushNewWidget(g, mainScreen, 0);
	yesCall(tf_set_globals, g, NULL, yeGet(g, "pj"));
	yesCall(yeGet(tf, "init_mode"), NULL);
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
		mod["pre-load"] = {};
		mod["pre-load"][0] = {};
		mod["pre-load"][0].type = "module";
		mod["pre-load"][0].file = "./tactical-fight";
		mod["pre-load"][1] = {};
		mod["pre-load"][1].type = "module";
		mod["pre-load"][1].file = "./generic_handler";
	}

	ywidAddSubType(init);
	return mod;
}
