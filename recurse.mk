subs?=$(patsubst %/Makefile,%,$(wildcard */Makefile))
targets?=all clean

define recurse_template
.PHONY: $(1)
$(1):: $$(subs:%=%-$(1))
%-$(1):
	$$(MAKE) -C $$* $(1)
endef

$(foreach target,$(targets),$(eval $(call recurse_template,$(target))))
