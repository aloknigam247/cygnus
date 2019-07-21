# Common procs used accross the project

# returns the filename in the path given
define filename
	$(lastword $(subst /, ,$1))
endef
