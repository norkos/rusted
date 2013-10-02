TARGET:=ctags
TYPE:=custom

ctags:
	@/bin/echo -e '$(FONT_BOLD)ctags$(FONT_RESET)'
	@ctags -R --c++-kinds=+p --fields=+miaS --extra=+q --exclude=".svn" --exclude="boost*" -f tags $(TARGET_BASE) /usr/include/c++ /usr/include/OGRE/ $(BUILD)
