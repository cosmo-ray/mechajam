function generic_handlerRefresh(npc)
   if yeGetString(npc.char.type) == "sprite" then
      sprite_man.handlerRefresh(npc)
   else
      lpcs.handlerRefresh(npc)
   end
end

function generic_handlerNullify(npc)
   if yeGetString(npc.char.type) == "sprite" then
      sprite_man.handlerNullify(npc)
   else
      lpcs.handlerNullify(npc)
   end
end

function generic_handlerPos(npc)
   if yIsNil(npc) or npc.char == nil then
      return
   end
   if yeGetString(npc.char.type) == "sprite" then
      return sprite_man.handlerPos(npc)
   else
      return ylpcsHandlerPos(npc)
   end
end

function generic_handlerSize(npc)
   if yIsNil(npc) or npc.char == nil then
      return
   end
   if yeGetString(npc.char.type) == "sprite" then
      return sprite_man.handlerSize(npc)
   else
      return ylpcsHandlerSize(npc)
   end
end

function generic_setDir(npc, dir)
   if yeGetString(npc.char.type) == "sprite" then
      dir = yeGetInt(dir)
      if yeGetString(npc.sp.disposition) == "uldr" then
	 if dir == LPCS_LEFT then
	    yeSetAt(npc, "y_offset", 32)
	 elseif dir == LPCS_RIGHT then
	    yeSetAt(npc, "y_offset", 96)
	 elseif dir == LPCS_DOWN then
	    yeSetAt(npc, "y_offset", 64)
	 else
	    yeSetAt(npc, "y_offset", 0)
	 end
      elseif yeGetString(npc.sp.disposition) == "urdl" then
	 if dir == LPCS_LEFT then
	    yeSetAt(npc, "y_offset", 96)
	 elseif dir == LPCS_RIGHT then
	    yeSetAt(npc, "y_offset", 32)
	 elseif dir == LPCS_DOWN then
	    yeSetAt(npc, "y_offset", 64)
	 else
	    yeSetAt(npc, "y_offset", 0)
	 end
      else
	 if dir == LPCS_LEFT then
	    yeSetAt(npc, "y_offset", 32)
	 elseif dir == LPCS_RIGHT then
	    yeSetAt(npc, "y_offset", 64)
	 elseif dir == LPCS_UP then
	    yeSetAt(npc, "y_offset", 96)
	 else
	    yeSetAt(npc, "y_offset", 0)
	 end
      end
   else
      lpcs.handlerSetOrigXY(npc, 0, dir)
      generic_handlerRefresh(npc)
   end
end

function generic_setPos(npc, pos)
   if yeGetString(npc.char.type) == "sprite" then
      sprite_man.handlerSetPos(npc, pos)
   else
      ylpcsHandlerSetPos(npc, pos)
   end
end

function generic_handlerMove(npc, add)
   ywPosAdd(generic_handlerPos(npc), add)
end

function generic_handlerMoveXY(npc, x, y)
   ywPosAddXY(generic_handlerPos(npc), x, y)
end

function mod_init(mod)
   mod = Entity.wrapp(mod)

   mod.name = "generic_sprite"
   mod["pre-load"] = {}
   mod["pre-load"][0] = {};
   mod["pre-load"][0].type = "module";
   mod["pre-load"][0].path = "YIRL_MODULES_PATH/Universal-LPC-spritesheet";
   mod["pre-load"][1] = {};
   mod["pre-load"][1].type = "module";
   mod["pre-load"][1].path = "YIRL_MODULES_PATH/sprite-manager/";

   ygRegistreFunc(1, "generic_handlerRefresh", "generic_handlerRefresh")
   ygRegistreFunc(1, "generic_handlerNullify", "generic_handlerNullify")
   ygRegistreFunc(1, "generic_handlerPos", "generic_handlerPos")
   ygRegistreFunc(1, "generic_handlerSize", "generic_handlerSize")

   ygRegistreFunc(2, "generic_setDir", "generic_setDir")
   ygRegistreFunc(2, "generic_setPos", "generic_setPos")
   ygRegistreFunc(2, "generic_handlerMove", "generic_handlerMove")

   ygRegistreFunc(2, "generic_handlerMoveXY", "generic_handlerMoveXY")
   return mod
end
