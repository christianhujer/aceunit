subs:=\
	leapyear \
	hello_world_mocked_macro \
	hello_world_mocked_obj \

ifeq "$(shell uname -s)" "Darwin"
subs+=\
	hello_world_mocked_interpose \

else
subs+=\
	hello_world_mocked_link \

endif

include ../../../../recurse.mk
