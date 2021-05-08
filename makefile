#####################################################################
# 本文件包括对子目录和当前目录有多个目标的编译
# 若需要编译多个子目录，设置 SUBDIRS 变量为子目录的名称
# 若需要编译当前目录下的多个目标，设置 SUBMAKES 变量为 Makefile 的文件名
# 修订历史：
#      lixp      2008-09-15 创建文件
#      weict     2015-08-21 增加no-keep-going控制
#####################################################################
ifeq "$(UNITTEST_EXEC_TIME)" ""
  export UNITTEST_EXEC_TIME := $(shell date +%Y%m%d_%H%M%S)
endif

ifeq "$(UNITTEST_REPORT_SUM_NAME)" ""
  export UNITTEST_REPORT_SUM_NAME := $(subst $(OB_SRC)/,,$(shell pwd))
  UNITTEST_REPORT_SUM_NAME := $(subst /,\#,$(UNITTEST_REPORT_SUM_NAME))\#
endif
TEMP_CMD_GOALS=$(findstring $(MAKECMDGOALS), all rebuild depend install install_all make_install_all)
.PHONY: all checkenv clean clean_all rebuild depend install install_headers install_idl install_all make_install_all unittest cppcheck
all checkenv clean clean_all rebuild depend install install_headers install_idl install_all make_install_all unittest cppcheck: $(SUBDIRS)
ifneq "$(SUBDIRS)" ""
ifneq "$(MAKE_NO_KEEP_GOING)" "0"
	(for i in ${SUBDIRS}; do (cd $$i; pwd; ${MAKE} $@)|| exit "$$?"; done)
else
	(for i in ${SUBDIRS}; do (cd $$i; pwd; ${MAKE} $@); done)
endif
endif
ifneq "$(SUBMAKES)" ""
  ifdef NEED_CLEAN_OBJS
    ifneq "$(TEMP_CMD_GOALS)" ""
		for i in ${SUBMAKES};\
			do (${MAKE} -f $$i $@;${MAKE} -f $$i clean_all);\
		done
    else
		for i in ${SUBMAKES};\
			do (${MAKE} -f $$i $@;);\
		done
    endif
  else
ifeq "$(MAKE_NO_KEEP_GOING)" "1"
	for i in ${SUBMAKES};\
        do (${MAKE} -f $$i $@;) || exit "$$?"; \
	done
else
	for i in ${SUBMAKES};\
        do (${MAKE} -f $$i $@;); \
	done
endif
  endif
endif
