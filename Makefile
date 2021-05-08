#####################################################################
# 本文件包括对应用的推导，并生成最终的编译结果
#
# 变量说明：
#            Sdl2CppSource   从 sdl 文件 list 产生对应的 *.h 和 *.cpp，其中 * 部分由 $(2) 指定
#         Sdl2CppSourceExt   从 sdl 文件 list 产生对应的 *.h、*.cpp 和 *.inc，其中 * 部分由 $(2) 指定
#            Idl2CppSource   从 idl 文件 list 产生对应的 .hh 和 .cc
#            Msg2CppSource   从 msg 文件 list 产生对应的 _msg.h 和 _msg.cpp
#            Source2Object   从源代码文件名转换为 .o 文件名
#         Source2ObjectExt   从源代码文件名转换为带扩展的 .o 文件名
#              CvtBool2Msg   将 0/1 的 boolean 取值转换为 否/是
#                  DB_DEFS   传递给编译器的数据库宏定义
#              DB_INC_PATH   数据库的 include 路径
#               DB_LD_PATH   数据库的库文件路径
#             DB_LIBRARIES   数据库的库文件
#          MBMW_SHORT_NAME   在 OpenBroker 内部定义的中间件短名称
#                  MW_DEFS   传递给编译器的中间件宏定义
#              MW_INC_PATH   中间件的 include 路径
#               MW_LD_PATH   中间件的库文件路径
#             MW_LIBRARIES   中间件的库文件
#                BUILDTYPE   动态库的编译类型，用 D 表示 debug 版本，没有 D 表示 release 版本
#                  DLLTAIL   动态库后缀
#               DEBUG_DEFS   debug 版本的宏定义
#              DEBUG_FLAGS   debug 版本的编译器选项
#                CXX_FLAGS   C++ 编译器的选项
#                PIC_FLAGS   编译 PIC（位置无关代码）时的选项
#                 LD_FLAGS   静态链接器的选项
#               SHLD_FLAGS   动态链接器的选项
#               SYS_LDPATH   系统库的链接路径
#                 SYS_LIBS   系统库名称
#               HP_DA_FLAG   HP 平台数据体系结构的选项
#         PURE_IMPL_DB_SDL   只包含了 *_db.sdl 的 sdl 文件名称
#        PURE_IMPL_DEF_SDL   只包含了 *_def.sdl 的 sdl 文件名称
#        PURE_IMPL_CVT_SDL   只包含了 *_cvt.sdl 的 sdl 文件名称
#            PURE_IMPL_SDL   只包含了函数实现的 sdl 文件名称（即不包含任何 *_db.sdl、*_def.sdl、×_cvt.sdl 的文件名称）
#      PURE_CALLED_DEF_SDL   在 $(CALLED_SDL) 中只包含了 _def.sdl 的 SDL 文件名称
#      PURE_CALLED_CVT_SDL   在 $(CALLED_SDL) 中只包含了 _cvt.sdl 的 SDL 文件名称
#          PURE_CALLED_SDL   在 $(CALLED_SDL) 中，除开 _def.sdl 和 _cvt.sdl 的 SDL 文件名称
#         PURE_INSTALL_SDL   需要安装的 SDL 文件
#     PURE_INSTALL_SDL_EXT   需要安装的 $(IMPL_SDL_EXT_PATH) 目录下的文件
#        IMPL_SDL_EXT_PATH   扩展 SDL 的路径，默认是 idl_ext
#            DEST_REL_PATH   目标相对于 $(OB_SRC_CYGWIN) 的相对路径
#            SDL_NAMESPACE   为每个 sdl 文件添加的 namespace 名称，目前就是目标相对于 $(OB_SRC_CYGWIN) 的路径名，但用 _ 代替了 /
#           DEST_REL_PATH2   用空格替换了 / 的 $(DEST_REL_PATH)
#                SUBSYSTEM   子系统的名称，就是在 openboss 下的一级目录名称
#              MODULE_NAME   模块的名称，就是在 openboss 下的二级目录名称
#             APP_INC_PATH   应用的 include 路径
#              APP_LD_PATH   应用的链接库路径
#            APP_LIBRARIES   应用的链接库名称
#         APP_DEPENDENCIES   应用的依赖文件名称
#      HEADER_INSTALL_PATH   头文件的安装路径
#         SDL_INSTALL_PATH   SDL 文件的安装路径
#             INSTALL_PATH   目标程序的安装路径
#              TARGET_TYPE   目标的程序类型，取值为 EXE、DLL、LIB
#                   TARGET   目标程序名称
#               TOTAL_DEFS   最终的宏定义
#          TOTAL_CXX_FLAGS   最终的 C++ 编译器选项
#           TOTAL_INC_PATH   最终的 include 路径
#           TOTAL_LD_FLAGS   最终的静态链接选项
#            TOTAL_LD_PATH   最终的静态链接路径
#         TOTAL_SHLD_FLAGS   最终的动态链接选项
#          TOTAL_LIBRARIES   最终的链接库
#       TOTAL_SDL_INC_PATH   最终的 SDL 文件 include 路径
#         APP_MESSAGE_PATH   消息文件的完整路径
#              TARGET_OBJS   目标程序源代码对应的 .o 文件
#   SDL2CPP_GENERATED_OBJS   sdl2cpp 所产生源文件编译出的目标文件
#SDL2CPP_GENERATED_SOURCES   sdl2cpp 产生的源文件
#   EMS2CPP_GENERATED_OBJS   ems2cpp 所产生源文件编译出的目标文件
#EMS2CPP_GENERATED_SOURCES   ems2cpp 产生的源文件
#                 VER_OBJS   版本文件的 .o 名称
#              VER_SOURCES   版本文件的 C++ 代码名称
#            HAS_CORBA_IDL   目标程序使用了 CORBA 的 IDL 文件
#                CORBA_IDL   目标程序所使用的 CORBA IDL 文件名称
#     CORBA_GENERATED_OBJS   CORBA IDL 文件对应的 .o 文件名
#  CORBA_GENERATED_SOURCES   CORBA IDL 文件对应的源文件
#               TOTAL_OBJS   所有目标所需要的所有 .o 文件
#  TOTAL_GENERATED_SOURCES   所有自动产生的源文件名称
#            TOTAL_HEADERS   最终需要安装的所有头文件
#       TOTAL_DEPENDENCIES   目标的所有依赖文件
#             CXX_CMD_ARGS   C++ 编译器的命令行参数
#         SDL_CXX_CMD_ARGS   SDL 编译器的命令行参数
#              LD_CMD_ARGS   静态链接器的命令行参数
#            SHLD_CMD_ARGS   动态链接器的命令行参数
#            DLL_STEM_NAME   如果当前编译类型是 DLL，表示去掉 lib 和后缀的动态库名称
#   VIDL2MW_GENERATED_OBJS   vidl2mw 产生的源代码对应的 .o 文件名
#VIDL2MW_GENERATED_SOURCES   vidl2mw 产生的源代码文件
#  VIDL2MW_GENERATED_FILES   vidl2mw 产生的其它文件
#              SOURCE_PATH   所有 DEST_SOURCES 的源代码路径
#                DO_LD_CMD   连接为执行程序的命令行
#    ADDTIONAL_INSTALL_CMD   用户自定义的 install 的 shell 命令
# ADDTIONAL_INSTALL_HEADER_CMD   用户自定义的 install 头文件的 shell 命令
#ADDTIONAL_INSTALL_IDL_CMD   用户自定义的 install SDL 的 shell 命令
#             SDL_SRC_PATH   所有实现的 SDL 文件在源代码中的路径，默认是 idl
################### lizj modifiled ##################################
#       AUTO_DEPEND_SOURCE   需要单独产生.d依赖文件的文件列表
#       AUTO_DEPENDED_FILE   .c/cpp对应依赖的.d文件	
#             EXCLUDE_PATH   判断文件依赖时,排除对基础代码的依赖
#      NAMESPACE_MAKE_FILE   当生成_sdl_c.cpp时,根据用户选择,使用/不用这个自动生成的Makefile文件替代原有模式规则
################### unittest begin ##################################
#  UNITTEST_REPORT_SUM_DIR   单元测试结果汇总输出路径
#  UNITTEST_REPORT_DTL_DIR   单元测试结果明细输出路径
#          UNITTEST_OPTION   执行UNITTEST测试程序时的传入参数   
#UNITTEST_CREATE_REPORTDIR   执行UNITTEST测试程序时的结果输出路径
#           NEED_COVERTEST   是否启用覆盖测试功能
#       UNITTEST_GCOV_LIBS   gcov覆盖测试时，编译和链接所需的库文件
#      CXX_CMD_ARGS_NOGCOV   不带gcov动态库的编译命令，对于unittest的测试程序，不支持gcov的库
#      ADDTIONAL_TEST_LIBS   用户自定义的测试附加库
#  ADDTIONAL_TEST_LIB_PATH   用户自定义的测试附加库搜索路径
#            MAKEFILE_NAME   当前执行的Makefile文件名
#         UNITTEST_LIB_SET   被测试的动态库路径，对于GCC编译器为-Wl,-rpath,$(OUTPUT_DIR)，其他编译器不需要
#          UNNEED_CPP2UNIT   不需要调用cpp2unit工具自动生成测试代码
#      UNITTEST_ORIGIN_LIB   测试所需的源码动态库，防止第一次开启时未生成
#			   UNITTEST_TOTAL_ON   若本次编译的目标程序不需要单元测试功能，可在编译环境中配置UNITTEST_TOTAL_ON为0，表示关闭所有模块的单元测试功能。对于release版本的编译环境，必须配置该参数为0，以防止覆盖率统计功能影响系统的性能。需注意修改该参数后，需clean后重新编译所有模块。
#				 SDL_DOWNLOAD_PATH	 JAVA模块获取C++的SDL后，本地存放路径
#       USER_UNITTEST_DEFS   支持用户自定义单元测试编译时增加的宏
#      UNITTEST_CALLED_SDL   单元测试所需要的CALLED_SDL
#    UNITTEST_SDL_INC_PATH   单元测试SDL的查找路径
################### unittest end   ##################################
################### add by tangxl2 ############################
#       SDLCHECK_NEED_FLAG   SDL规范检查选项，默认0为不检查，1为检查
#       SDLCHECK_BASE_TYPE   检查的文件方式，SVN-基于SVN的text-base目录，OLD_SUFF由用户指定带.old的方式，BASE_DIR由用户指定文件目录
#        SDL_DISPLAY_VISIT   SDL展开序列化选项，默认0为不展开,1为展开
#          SDL_OBJECT_POOL   SDL采用对象池，默认0为不采用，1为采用
#     SDL_MIF_LENGTH_LIMIT   限制SDL的module_interface_function的最大长度为64
#     				DMODULE_NAME	 去掉$(OB_SRC)/后的模块名
############################################################################
################### RE_GEN_DB_SDL begin   ##################################
#            RE_GEN_DB_SDL   控制是否每次gmake时都删除*_db_sdl.h/cpp，重新根据数据库生成。默认为1，即开启状态。
#             TOTAL_DB_SDL   所有*_db.sdl格式的sdl
# SDL2CPP_GENERATED_DB_SOURCES 所有自动生成的*_db_sdl.h/cpp
################### RE_GEN_DB_SDL end   ##################################
#
# 修订历史：
#      lixp      2008-09-15 创建文件
#      lixp      2010-03-18 增加 OPTIMIZE_LEVEL 的推导
#      lizj      2010-04-19 增加 TOTAL_XBUF_PATH的定义以及 xbuf_c.h对.xbuf文件的编译依赖定义
#      yangny    2011-06-16 增加cppcheck目标，增加CPPCHECK_OPTION和USER_CPPCHECK_OPTION
#      lijie5    2011-07-13 1.增加 UNITTEST_OPTION和UNITTEST_CREATE_REPORTDIR的定义；2.增加gmake test的执行命令;3.修改cpp2unit时的$<为$^
#      lijie5    2011-07-25 将单元测试的UNITTEST_SOURCES变量“=”改为“+=”，即可在makefile文件中自定义增加附加的单元测试源码
#      lijie5    2011-08-01 增加 NEED_COVERTEST、UNITTEST_GCOV_LIBS、CXX_CMD_ARGS_NOGCOV的定义以及gcov覆盖测试的支持
#      lijie5    2011-08-08 增加 UNITTEST_REPORT_SUM_DIR、UNITTEST_REPORT_DTL_DIR、MAKEFILE_NAME的定义以及单元测试结果汇总的功能
#      lijie5    2011-08-11 单元测试功能增加对于BIN和LIB类型的支持
#      lijie5    2011-08-15 1.修复之前单元测试不支持BIN类型的问题;2.对于Makefile中的USER_SDL_INC_PATH设置，增加过滤重复的功能
#      lijie5    2011-08-18 1.自动生成的测试文件，增加uttest_前缀；2.增加UNNEED_CPP2UNIT的定义，表示不需要自动生成测试代码
#      lijie5    2011-08-22 增加单元测试总开关UNITTEST_TOTAL_ON的支持，可在环境变量中通过该参数批量开启或关闭单元测试。
#      lijie5    2011-09-06 1、单元测试支持框架初始化。2、单元测试总开关UNITTEST_TOTAL_ON为1时，改为由Makefile控制开关，非全部开启
#      lijie5    2011-09-08 针对AIX上用GCC编译时的兼容性修改
#      lijie5    2011-09-23 增加JAVA模块SDL同步的功能
#      lijie5    2011-09-30 增加判断DEST_TYPE为空时，不进行编译，只尝试生成sdl文件
#      lijie5    2011-10-10 增加KERNEL目标类型的推导
#			 tangxl2   2011-10-11 增加sdl变更规范检查推导 SDLCHECK_NEED_FLAG
#      tangxl2   2011-11-29 增加sdl展开序列化推导 SDL_DISPLAY_VISIT
#      tangxl2   2011-12-14 增加sdl对象池推导 SDL_OBJECT_POOL
#      dengy3    2011-12-02 集成rdl2cpp
#      tangxl2   2012-02-01 SDL_MIF_LENGTH_LIMIT限制SDL的module_interface_function的最大长度为64
#      dengy3 	 2011-12-02 sdl2cpp生成文件新增*_sdl_init.cpp和*_sdl_init.h文件
#      jiangjz 	 2012-04-24 针对GNU GCC编译器，增加ENABLE_ATTR_INLINE宏，在函数声明加上ATTR_ALWAYS_INLINE可以使gcc在编译时强制inline
#      lijie5    2012-06-04 RE_GEN_DB_SDL开关，控制是否每次gmake时都删除*_db_sdl.h/cpp，重新根据数据库生成。默认为1，即开启状态。
#      jiangjz 	 2012-05-31 增加USE_AISTL定义
#      jiangjz 	 2012-06-18 增加USE_POOLVECTOR定义
#      shiym     2012-10-25 增加变量AUTO_DEPENDED_SDL，表示CALLED_SDL中指定的SDL文件自动生成的make依赖文件
#      weict     2013-11-19 uttest_文件生成路径调整，非本目录下cpp文件对应生成的uttest_文件也生成到test路径下
#      jiangjz   2013-11-21 单元测试编译时，可以通过USER_UNITTEST_DEFS自定义额外的宏，TOTAL_UNITTEST_DEFS默认加上-Dprotected=public -Dprivate=public
#      jiangjz   2013-12-14 单元测试编译时，可以通过UNITTEST_CALLED_SDL自定义要编译的SDL
#      weict     2015-01-01 增加fastdepend编译开关 NEED_FASTDEPEND, 默认开启。3rd编译时，关闭fastdepend检查
#      weict     2015-01-07 整个include目录需要安装时，HEADERS_DIR_NEED_INSTALL：指定需要安装的include目录, HEADERS_DIR_INSTALL_PATH：目录内头文件安装的路径，安装路径默认为$(OB_REL)/include下两层目录
#      weict     2015-07-21 增加USER_XC_INC_PATH，可指定XCD文件搜索路径
#      weict     2016-07-16 gcc5.2下开启-Dprivate=public，sstream包含编译失败，去掉TOTAL_UNITTEST_DEFS默认-Dprivate=public，改为在TestSuiteManager.h中添加private=public
#####################################################################
#####################################################################
# 内部拓展的函数
Sdl2CppSource = $(foreach i,$(patsubst %.sdl,%,$(notdir $(1))),$(i)$(2).h $(i)$(2).cpp)
Sdl2CppSourceExt = $(foreach i,$(patsubst %.sdl,%,$(notdir $(1))),$(i)$(2).h $(i)$(2).cpp)
Xc2CppSource = $(foreach i, $(patsubst %.xcd, %,$(notdir $(1))), $(i).cpp $(i).h)
Idl2CppSource = $(foreach i,$(patsubst %.idl,%,$(1)),$(i)$(2).hh $(i)$(2).cc)
Msg2CppSource = $(foreach i,$(patsubst %.ems,%,$(notdir $(1))),$(i)_msg.h $(i)_msg.cpp)
Rdl2CppSource = $(foreach i,$(patsubst %.rdl,%,$(notdir $(1))),$(i)$(2).h $(i)$(2).cpp)
Source2Object = $(foreach i,$(basename $(notdir $(1))),$(i).o)
Source2ObjectExt = $(foreach i,$(basename $(notdir $(1))),$(i)$(2).o)
CvtBool2Msg = $(if $(filter-out 1,$(1)),否,是)

#####################################################################
# 对产品及其参数的推导
ifeq "$(PRODUCT_NAME)" "OPENBOSS"
	#DEFS += SDL_SELECTED_API
	ifneq "$(USER_PROJECT_NAME)" ""
		SDLCC_FLAGS += -prj:$(USER_PROJECT_NAME)
	endif
endif

ifeq "$(PRODUCT_NAME)" "OPENCHANNEL"
	DEFS += SDL_SELECTED_API
	ifneq "$(USER_PROJECT_NAME)" ""
		SDLCC_FLAGS += -prj:$(USER_PROJECT_NAME)
	endif
endif

ifeq "$(PRODUCT_NAME)" "OPENPRM"
	DEFS += SDL_SELECTED_API
	ifneq "$(USER_PROJECT_NAME)" ""
		SDLCC_FLAGS += -prj:$(USER_PROJECT_NAME)
	endif
endif

ifeq "$(PRODUCT_NAME)" "PAKBOSS"
	DEFS += ENGLISH_UI
endif

ifeq "$(NEED_SVR_TRANSACTION)" "1"
	DEFS += __SVR_COMMIT_TRANSACTION__
endif


#####################################################################
# 对需要在有业务全编的机会启用的功能的推导
DEFS += FRAMEWORK_MAIN_VERSION=$(FRAMEWORK_MAIN_VERSION) FRAMEWORK_MINOR_VERSION=$(FRAMEWORK_MINOR_VERSION) FRAMEWORK_REVISION_VERSION=$(FRAMEWORK_REVISION_VERSION)
ifeq "$(ENABLE_THREAD_COMMUNICATION)" "1"
	DEFS += THREAD_COMMUNICATION
endif
ifeq "$(ENABLE_BATCH_ASYNC)" "1"
	DEFS += BATCH_ASYNC
endif

ifneq "$(USE_POOL_ALLOC)" "0"
	DEFS += __POOL_ALLOC__=$(USE_POOL_ALLOC)
endif

ifeq "$(USE_SELFDEFINE_ALLOC)" "1"
	DEFS += __USE_SELFDEFINE_ALLOC__
endif

ifeq "$(USE_GLOBAL_POOL_ALLOC)" "1"
	DEFS += __USE_GLOBAL_POOL_ALLOC__
endif

ifeq "$(USE_AISTL)" "1"
	DEFS += USE_AISTL
endif

ifeq "$(USE_POOLVECTOR)" "1"
	DEFS += USE_POOLVECTOR
endif

#otl增加number(16)的支持 add by lijie 20130507
ifeq "$(USE_OTL_BIGINT)" "1"
	DEFS += USE_OTL_BIGINT
endif

#####################################################################
# 对数据库及其参数的推导
ifeq "$(DB_TYPE)" "SYBASE"
	DB_DEFS = DB_TYPE_SYB
	DB_INC_PATH = $(SYBASE)/include
	DB_LD_PATH = $(SYBASE)/lib
	DB_LIBRARIES = ct_r cs_r comn_r blk_r tcl_r
endif

ifeq "$(DB_TYPE)" "MYSQL"
	DB_DEFS = DB_TYPE_MYSQL
	DB_LIBRARIES = odbc
endif

ifeq "$(DB_TYPE)" "ORACLE"
	DB_DEFS = DB_TYPE_ORA
	DB_INC_PATH_DEL = \
		$(ORACLE_HOME)/rdbms/demo \
		$(ORACLE_HOME)/rdbms/public \
		$(ORACLE_HOME)/plsql/public \
		$(ORACLE_HOME)/network/public
	DB_INC_PATH = \
		$(ORACLE_HOME)/rdbms/public
	ifeq "$(BIT_TYPE)" "64"
		DB_LD_PATH = $(ORACLE_HOME)/lib
	else
		ifeq "$(OS_TYPE)" "Linux"
			DB_LD_PATH = $(ORACLE_HOME)/lib
		else
			DB_LD_PATH = $(ORACLE_HOME)/lib32
		endif
	endif	
	DB_LIBRARIES = clntsh
	ifeq "$(DB_VER)" "8I"
		DB_DEFS += OTL_ORA8I
	endif
	ifeq "$(DB_VER)" "9I"
		DB_DEFS += OTL_ORA9I
	endif
	ifeq "$(DB_VER)" "10G"
		DB_DEFS += OTL_ORA10G_R2
	endif
	ifeq "$(DB_VER)" "11G"
		DB_DEFS += OTL_ORA11G_R2
	endif
	ifeq "$(DB_VER)" "12C"
		DB_DEFS += OTL_ORA12C
	endif		
	ifeq "$(OS_TYPE)" "CYGWIN"
		DB_LIBRARIES = oci
		DB_LD_PATH = $(ORACLE_HOME)/bin
		DB_INC_PATH = $(ORACLE_HOME)/rdbms/demo $(ORACLE_HOME)/oci/include \
			$(ORACLE_HOME)/plsql/include $(ORACLE_HOME)/network/public
	endif
endif

#####################################################################

ifeq "$(OBMW_TYPE)" "WebService"
	MBMW_SHORT_NAME = webservice
	MW_DEFS = THREAD WebService
	ifeq "$(OS_TYPE)" "AIX"
		MW_DEFS += AIX_BITS64
	endif
	ifeq "$(BIT_TYPE)" "64"
		ifeq "$(OS_TYPE)" "HP-UX"
			MW_DEFS+=BITS64
		endif
	endif
	MW_INC_PATH = $(APACHE2_HOME)/include/axis2-1.6.0 ../app ./src
	MW_LD_PATH = $(APACHE2_HOME)/lib
	MW_LIBRARIES = ObSoaInit$(BUILDTYPE) axutil axis2_axiom axis2_engine axis2_parser pthread axis2_http_sender axis2_http_receiver guththila
	ifeq "$(OS_TYPE)" "HP-UX"
		ifeq "$(STL_TYPE)" "HP_STL_2.0"
			MW_LIBRARIES += std_v2
		else
			MW_LIBRARIES += std
		endif
	endif
	ifeq "$(OS_TYPE)" "SunOS"
		MW_LIBRARIES += Crun
	endif
	VIDL2MW_GENERATED_OBJS = $(basename $(PURE_IMPL_SDL))_axis2c_skel_SVC.o axis2_svc_skel_$(basename $(PURE_IMPL_SDL))Service.o adb_WrappedDatabinder.o
	VIDL2MW_GENERATED_SOURCES = $(basename $(PURE_IMPL_SDL))_axis2c_skel_SVC.cpp axis2_svc_skel_$(basename $(PURE_IMPL_SDL))Service.cpp adb_WrappedDatabinder.cpp
	VIDL2MW_GENERATED_FILES = services.xml $(basename $(PURE_IMPL_SDL)).wsdl webservice_interfaces.h
endif

#####################################################################

#####################################################################
# 编译位数的推导
ifeq "$(BIT_TYPE)" "32"
	DEFS += BIT32
endif
ifeq "$(BIT_TYPE)" "64"
	DEFS += BIT64
endif

#####################################################################
# 对 DEBUG 模式的推导
ifeq "$(DEBUG)" "1"
	BUILDTYPE = D
	DEBUG_DEFS += DEBUG
else
	BUILDTYPE =
endif

#####################################################################
# OTL_STREAM_POOL的推导
ifeq "$(USE_OTL_POOL)" "1"
	DEFS += OTL_STREAM_POOLING_ON
endif
#####################################################################
# 对编译器及其参数的推导
ifeq "$(CXX)" "CC"
	CXX_FLAGS += -mt
	PIC_FLAGS = -PIC
	ifeq "$(DEBUG)" "1"
		DEBUG_FLAGS += -g
	endif
	ifeq "$(OPTIMIZE_LEVEL)" "3"
		CXX_FLAGS += -fast
		LD_FLAGS += -fast
		SHLD_FLAGS += -fast
	endif
	SHLD_FLAGS += -G
	SYS_LIBS += Cstd mtmalloc dl pthread nsl socket rt
	CXXTMPOBJ += ir.out $(OUTPUT_DIR)SunWS_cache
	ifeq "$(BIT_TYPE)" "64"
		PIC_FLAGS = -KPIC
                ifeq "$(CPU_TYPE)" ""
                        CXX_FLAGS += -xtarget=ultra -xarch=v9
                        LD_FLAGS += -xtarget=ultra -xarch=v9
                        SHLD_FLAGS += -xtarget=ultra -xarch=v9
                else
                        ifeq "$(CPU_TYPE)" "x86"
                                CXX_FLAGS += -m64 -DCPU_X86
                                LD_FLAGS += -m64
                                SHLD_FLAGS += -m64
                        endif
                endif
                SYS_LDPATH += /usr/lib/64
	endif
endif

ifeq "$(CXX)" "xlC_r"
        DEFS += _THREAD_SAFE
	CXX_FLAGS = -brtl -bexpall -qtls -qlonglong -qlongdouble -q$(BIT_TYPE) -qalign=full -qkeyword=typename
	ifeq "$(DEBUG)" "1"
		DEBUG_FLAGS = -g -qstaticinline
	endif
	ifeq "$(OPTIMIZE_LEVEL)" "3"
		CXX_FLAGS += -O3
		LD_FLAGS += -O3
		SHLD_FLAGS += -O3
	endif
	LD_FLAGS = -brtl -bexpall -bnoipath -q$(BIT_TYPE) -qstaticinline -bhalt:5
	SHLD_FLAGS = -p0 -brtl -lpthreads -bhalt:5
	ifeq "$(BIT_TYPE)" "64"
		ifneq "$(__AIX_BIG_TOC)" ""
			LD_FLAGS += -bbigtoc
			SHLD_FLAGS += -bbigtoc
		endif
		LD_FLAGS += -b maxdata:0x8000000000
		SHLD_FLAGS += -X64
	else
		LD_FLAGS += -b maxdata:0x80000000
	endif
endif

ifeq "$(CXX)" "aCC"
        DEFS += ORBNEWTHROW= _KERNEL_THREADS _THREAD_SAFE _RWSTD_MULTI_THREAD
	ifeq "$(DEBUG)" "1"
		DEBUG_FLAGS = -g0 +d
	endif
	ifeq "$(OPTIMIZE_LEVEL)" "3"
		CXX_FLAGS += +O3 +Oall
		LD_FLAGS += +O3 +Oall
		SHLD_FLAGS += +O3 +Oall
	endif
	ifeq "$(CPU_TYPE)" "IA64"
		ifeq "$(OBMW_TYPE)" "CICS"
			DEFS += CICS_HPUX CICS_HPIT _HPUX_SOURCE _XOPEN_SOURCE_EXTENDED _POSIX_C_SOURCE=200112L
			CXX_FLAGS = +z -Wl,+s +u1 -ext -mt -Aa
			LD_FLAGS = -Wl,+s -Aa -mt
			SHLD_FLAGS = -b +e -bdynamic -Wl,+s -Aa -mt
		else
			CXX_FLAGS = +Z -Wl,+s +u4 -ext -mt -w -AA
			LD_FLAGS = -Wl,+s -AA -mt
			SHLD_FLAGS = -b -bdynamic -Wl,+s -AA -mt
			ifeq "$(OBMW_TYPE)" "VisiBroker"
				# 对 HP 平台，如果使用了 VisiBroker 中间件，那么所有业务代码都要使用 +DD 的选项
				CXX_FLAGS += +DD$(BIT_TYPE)
				LD_FLAGS += +DD$(BIT_TYPE)
			endif
		endif
	else
		HP_DA_FLAG = +DA1.1
		ifeq "$(OBMW_TYPE)" "VisiBroker"
			ifeq "$(OBMW_VER)" "6.5"
				HP_DA_FLAG = +DAportable +W1039
				DEFS += _VIS_STD HPUX_11 INCLUDE_FSTREAM _VIS_LONG_LONG _VIS_LONG_DOUBLE \
					_VIS_UNICODE _VIS_STREAM_WCHAR _VIS_NO_IOSTREAM_WCHAR _VIS_NO_IOSTREAM_LONGDOUBLE
			endif
		endif
		CXX_FLAGS = +Z -Wl,+s +u1 -ext -mt -w $(HP_DA_FLAG)
		LD_FLAGS = -Wl,+s
		SHLD_FLAGS = -b -bdynamic -Wl,+s
		SYS_LIBS += pthread
		ifeq "$(STL_TYPE)" "HP_STL_1.2.1"
			CXX_FLAGS += -Aa OB_NO_STD
			LD_FLAGS += -Aa
			SHLD_FLAGS += -Aa
			DEFS += OB_NO_STD
		endif
		ifeq "$(STL_TYPE)" "HP_STL_2.0"
			CXX_FLAGS +=-AA
			LD_FLAGS +=-AA
			SHLD_FLAGS +=-AA
		endif
	endif
	ifeq "$(BIT_TYPE)" "64"
		CXX_FLAGS += +DD64
		LD_FLAGS += +DD64
		SHLD_FLAGS += +DD64
	endif
endif

ifeq "$(CXX)" "g++"
    ifeq "$(USE_CXX11)" "1"
        CXX_FLAGS += -std=c++11 -DBOOST_NO_AUTO_PTR
        DEFS += USE_CXX11
    else
        CXX_FLAGS += -Dnullptr=NULL
    endif

    ifeq "$(USE_TIMEREPORT)" "1"
        CXX_FLAGS += -ftime-report
    endif

    ifeq "$(USE_PG)" "1"
        CXX_FLAGS += -pg
        SHLD_FLAGS += -pg
        LD_FLAGS += -pg
    endif

    ifeq "$(ENABLE_ATTR_INLINE)" "1"
        DEFS += ENABLE_ATTR_INLINE
    endif
        
    # add by shiym 2013.03.12
    ifeq "$(OS_TYPE)" "SunOS"
		CXX_FLAGS += -pthreads
    endif
    # end add
	
    # for gcc backtrace() support -- shiym 8/19/2013
    SHLD_FLAGS += -rdynamic
    LD_FLAGS += -rdynamic
    # end
        
    ifeq "$(CPU_TYPE)" "x86"

        DEFS += _THREAD_SAFE _RWSTD_MULTI_THREAD _GNU_SOURCE _POSIX_C_SOURCE=200112L CPU_X86

        #目前只有x86的g++编译器需增加该选项
        ifneq "$(OS_TYPE)" "SunOS"
            UNITTEST_LIB_SET ?= -Wl,-rpath,$(OUTPUT_DIR)
        endif

        ifeq "$(DEBUG)" "1"
            DEBUG_FLAGS = -g
        endif

        ifeq "$(OPTIMIZE_LEVEL)" "2"
            CXX_FLAGS += -O2
            LD_FLAGS += -O2
            SHLD_FLAGS += -O2
        endif

        ifeq "$(OPTIMIZE_LEVEL)" "3"
            CXX_FLAGS += -O3
            LD_FLAGS += -O3
            SHLD_FLAGS += -O3
        endif

        CXX_FLAGS += -fpic -ftemplate-depth-64
        SHLD_FLAGS += -shared
        SYS_LIBS += pthread

        ifeq "$(BIT_TYPE)" "64"
            CXX_FLAGS += -m64
            LD_FLAGS += -m64
            SHLD_FLAGS += -m64
        else
            CXX_FLAGS += -m32
            LD_FLAGS += -m32
            SHLD_FLAGS += -m32
        endif
    endif    # end of CPU_TYPE = X86

    ifeq "$(CPU_TYPE)" ""
		ifeq "$(OS_TYPE)" "SunOS"
                        DEFS += _THREAD_SAFE _RWSTD_MULTI_THREAD _GNU_SOURCE _POSIX_C_SOURCE=200112L
	                ifeq "$(DEBUG)" "1"
	                        DEBUG_FLAGS = -g
	                endif
	                ifeq "$(OPTIMIZE_LEVEL)" "2"
	                        CXX_FLAGS += -O2
	                        LD_FLAGS += -O2
	                        SHLD_FLAGS += -O2
	                endif
	                ifeq "$(OPTIMIZE_LEVEL)" "3"
	                        CXX_FLAGS += -O3
	                        LD_FLAGS += -O3
	                        SHLD_FLAGS += -O3
	                endif
	                CXX_FLAGS += -fPIC -ftemplate-depth-64 -pthreads   # -pthreads is add by shiym in 2012/11/22
	                SHLD_FLAGS += -shared -mt
	                SYS_LIBS += pthread
	                ifeq "$(BIT_TYPE)" "64"
	                        CXX_FLAGS += -m64
	                        LD_FLAGS += -m64
	                        SHLD_FLAGS += -m64
	                endif
	        endif
			ifeq "$(OS_TYPE)" "AIX"
                                DEFS += _THREAD_SAFE
			endif
	endif
	ifeq "$(CPU_TYPE)" "IA64"
                DEFS += _THREAD_SAFE _RWSTD_MULTI_THREAD _GNU_SOURCE _POSIX_C_SOURCE=200112L
		ifeq "$(DEBUG)" "1"
			DEBUG_FLAGS = -g
		endif
		ifeq "$(OPTIMIZE_LEVEL)" "2"
			CXX_FLAGS += -O2
			LD_FLAGS += -O2
			SHLD_FLAGS += -O2
		endif
		ifeq "$(OPTIMIZE_LEVEL)" "3"
			CXX_FLAGS += -O3
			LD_FLAGS += -O3
			SHLD_FLAGS += -O3
		endif
		CXX_FLAGS += -fpic -ftemplate-depth-64 -pthread
		SHLD_FLAGS += -shared -pthread
		SYS_LIBS += pthread
		
		ifeq "$(BIT_TYPE)" "64"
	    ifeq "$(CPU_TYPE)" "IA64"
	      CXX_FLAGS += -mlp64
	      LD_FLAGS += -mlp64
	      SHLD_FLAGS += -mlp64
	    endif
    endif	
  endif
	ifeq "$(OS_TYPE)" "AIX"
		ifeq "$(DEBUG)" "1"
			DEBUG_FLAGS = -g
		endif
		ifeq "$(BIT_TYPE)" "64"
			CXX_FLAGS += -maix64 -fpic -ftemplate-depth-64
			SHLD_FLAGS += -maix64 -Wl,-G,-brtl
			LD_FLAGS += -maix64 -Wl,-G,-brtl
		endif
		SHLD_FLAGS += -shared -Wl,-bbigtoc
		SYS_LIBS += pthread
	endif	
  ifeq "$(_USE_PCH)" "1"
  	DEFS+=__USE_GCH__
		ifeq "$(PCH_FLAG)" "1"
			CXX_FLAGS +=
		else
			CXX_FLAGS += -Winvalid-pch
			#CXX_FLAGS += -Winvalid-pch -Wall -H
		endif
  endif
  
endif
	
#####################################################################
# for special platform (eg. linux) given some special definition
ifeq "$(OS_TYPE)" "Linux"
	DEFS += _LINUX_
	SYS_LIBS += dl
endif

ifeq "$(OS_TYPE)" "CYGWIN"
	DEFS +=  __CYGWIN__
	SYS_LIBS += dl
endif

SYS_LIBS += rt


#####################################################################
# 其它定义的推导
ifeq "$(PURIFY)" "1"
	CXX := purify $(PURIFYOPTS) $(CXX) -g
endif
ifeq "$(QUANTIFY)" "1"
	CXX := quantify $(QUANTIFYOPTS) $(CXX)
endif
CPPCHECK_OPTION += $(USER_CPPCHECK_OPTION)
CPP2UNIT_OPTION += $(USER_CPP2UNIT_OPTION)
ifeq "$(DEST_TYPE)" "JAVA"
	ifneq "$(USER_SDL_INC_PATH)" ""
		PURE_DOWNLOAD_SDL2=$(foreach i,$(USER_SDL_INC_PATH),$(addprefix $(i)/,$(TOTAL_CALLED_SDL)))
	else
		PURE_DOWNLOAD_SDL2=$(addprefix $(USER_SDL_INC_PATH),$(TOTAL_CALLED_SDL))
	endif
	PURE_DOWNLOAD_SDL =$(strip $(foreach i,$(PURE_DOWNLOAD_SDL2), $(wildcard $(i))))
	SDL_DOWNLOAD_PATH ?= .	
else

#UNITTEST_CREATE_CODE = $(sort $(dir ))
TOTAL_DB_SDL = $(sort $(notdir $(filter %_db.sdl,$(IMPL_SDL))) $(notdir $(filter %_db.sdl,$(IMPL_SDL_EXT))) $(notdir $(filter %_db.sdl,$(TOTAL_CALLED_SDL))))

PURE_IMPL_DB_SDL = $(notdir $(filter %_db.sdl,$(IMPL_SDL))) $(notdir $(filter %_db.sdl,$(IMPL_SDL_EXT)))
PURE_IMPL_DEF_SDL = $(notdir $(filter %_def.sdl,$(IMPL_SDL))) $(notdir $(filter %_def.sdl,$(IMPL_SDL_EXT)))
PURE_IMPL_CVT_SDL = $(notdir $(filter %_cvt.sdl,$(IMPL_SDL))) $(notdir $(filter %_cvt.sdl,$(IMPL_SDL_EXT)))
PURE_IMPL_SDL = $(notdir $(filter-out %_db.sdl %_def.sdl %_cvt.sdl,$(IMPL_SDL))) \
	$(notdir $(filter-out %_db.sdl %_def.sdl %_cvt.sdl,$(IMPL_SDL_EXT)))
PURE_CALLED_DEF_SDL = $(notdir $(filter %_def.sdl %_db.sdl,$(TOTAL_CALLED_SDL)))
PURE_CALLED_CVT_SDL = $(notdir $(filter %_cvt.sdl,$(TOTAL_CALLED_SDL)))
PURE_CALLED_SDL = $(notdir $(filter-out %_def.sdl %_db.sdl %_cvt.sdl,$(TOTAL_CALLED_SDL)))
endif

ifeq "$(OS_TYPE)" "CYGWIN"
	DEST_REL_PATH = $(subst $(OB_SRC_CYGWIN)/,,$(shell pwd))
else
	DEST_REL_PATH = $(subst $(OB_SRC)/,,$(shell pwd))
endif
SDL_NAMESPACE = $(subst  /,_, $(DEST_REL_PATH))
DEST_REL_PATH2 = $(subst /, , $(DEST_REL_PATH))
SUBSYSTEM = $(word 1, $(DEST_REL_PATH2))
MODULE_NAME = $(word 2, $(DEST_REL_PATH2))
DOMAIN_NAME = $(word 3, $(DEST_REL_PATH2))


#推导出需要增加名字空间的自动生成的文件

#PURE_INSTALL_SDL = $(strip $(addprefix $(OB_SRC_CYGWIN)/$(SUBSYSTEM)/$(MODULE_NAME)/$(DOMAIN_NAME)/idl/, \
#	$(filter %_def.sdl,$(IMPL_SDL))) \
#	$(addprefix $(OB_SRC_CYGWIN)/$(SUBSYSTEM)/$(MODULE_NAME)/$(DOMAIN_NAME)/idl/, \
#	$(filter-out %_db.sdl %_def.sdl %_cvt.sdl,$(IMPL_SDL))))

PURE_INSTALL_SDL_TMP=$(foreach i,$(USER_SDL_INC_PATH) ../idl ., $(addprefix $(i)/,$(IMPL_SDL)))
PURE_INSTALL_SDL_TMP2=$(patsubst $(OB_REL)/idl%,,$(PURE_INSTALL_SDL_TMP))
PURE_INSTALL_SDL_TEMP3=$(foreach i,$(PURE_INSTALL_SDL_TMP2), $(wildcard $(i)))
PURE_INSTALL_SDL =$(sort $(strip $(PURE_INSTALL_SDL_TEMP3)))


#TBC...
IMPL_SDL_EXT_PATH ?= idl_ext
PURE_INSTALL_SDL_EXT = $(strip $(addprefix $(OB_SRC_CYGWIN)/$(SUBSYSTEM)/$(IMPL_SDL_EXT_PATH)/,$(filter %_def.sdl,$(IMPL_SDL_EXT))) \
	$(addprefix $(OB_SRC_CYGWIN)/$(SUBSYSTEM)/$(IMPL_SDL_EXT_PATH)/,$(filter-out %_db.sdl %_def.sdl %_cvt.sdl,$(IMPL_SDL_EXT))))
ifeq "$(IMPL_SDL_EXT)" ""
	SDL_SRC_PATH = idl
else
	SDL_SRC_PATH = $(IMPL_SDL_EXT_PATH)
endif

DLLTAIL = $(BUILDTYPE).$(DLLEXT)

ifeq "$(IS_SDL2CPP_NO_VERSION_CHECK)" "1"
	SDLCC_FLAGS += -noverchk
endif

ifeq "$(SDL_DISPLAY_VISIT)" "1"
	SDLCC_FLAGS += -disp
endif

SDL_OBJECT_POOL ?= 0
ifeq "$(SDL_OBJECT_POOL)" "1"
	SDLCC_FLAGS += -op
endif

SDL_MIF_LENGTH_LIMIT ?= 1
ifeq "$(SDL_MIF_LENGTH_LIMIT)" "1"
	SDLCC_FLAGS += -nllimit
endif

EXCLUDE_FLAG=$(addprefix -E,$(EXCLUDE_PATH))
#####################################################################
# 对各种编译目标类型的推导

APP_INC_PATH = .
HEADER_INSTALL_PATH ?= $(OB_REL)/include/$(DEST_REL_PATH)/
HEADER_INSTALL_LOCALPATH = $(OB_LOCAL)/include/$(DEST_REL_PATH)/
NEED_MAKE_DEPEND ?= 1
#NEED_FASTDEPEND ?= 1 
NEED_FASTDEPEND = 0

APP_LD_PATH = ./build
APP_LIBRARIES =
APP_DEPENDENCIES =
UNITTEST_DEPENDENCIES =

SDL_INSTALL_PATH = $(OB_REL)/idl/$(SUBSYSTEM)/$(MODULE_NAME)/

#关闭预编译头后，默认所有模块均依赖数据库
	NEED_DATABASE?=1

ifeq "$(DEST_TYPE)" "BIN"
	TARGET_TYPE = EXE
	TARGET = $(addprefix $(OUTPUT_DIR),$(DEST)$(BINEXT))
	DLL_STEM_NAME = $(DEST)$(BUILDTYPE)
	INSTALL_PATH ?= $(OB_REL)/bin/
	INSTALL_LOCALPATH ?= $(OB_LOCAL)/bin/
	NEED_DATABASE ?= 0
	NEED_INSTALL = 1
	NEED_MAKE_DEPEND ?= 1
endif

ifeq "$(DEST_TYPE)" "LIB"
	TARGET_TYPE = LIB
	TARGET = $(addprefix $(OUTPUT_DIR),lib$(DEST).a)
	DLL_STEM_NAME = $(DEST)$(BUILDTYPE)
	INSTALL_PATH ?= $(OB_REL)/lib/
	INSTALL_LOCALPATH ?= $(OB_LOCAL)/lib/
	NEED_DATABASE ?= 0
	NEED_INSTALL = 1
	NEED_MAKE_DEPEND ?= 1
endif

ifeq "$(DEST_TYPE)" "DLL"
	TARGET_TYPE = DLL
	TARGET = $(addprefix $(OUTPUT_DIR),lib$(DEST)$(DLLTAIL))
	DLL_STEM_NAME = $(DEST)$(BUILDTYPE)
	INSTALL_PATH ?= $(OB_REL)/lib/
	INSTALL_LOCALPATH ?= $(OB_LOCAL)/lib/
	NEED_DATABASE ?= 0
	NEED_INSTALL = 1
	NEED_MAKE_DEPEND ?= 1
endif

ifeq "$(DEST_TYPE)" "MGR"
	TARGET_TYPE = DLL
	TARGET = $(addprefix $(OUTPUT_DIR),lib$(DEST)_mgr$(DLLTAIL))
	DLL_STEM_NAME = $(DEST)_mgr$(BUILDTYPE)
	INSTALL_PATH = $(OB_REL)/lib/
	INSTALL_LOCALPATH = $(OB_LOCAL)/lib/
	NEED_DATABASE = 1
	NEED_INSTALL = 1
	NEED_MAKE_DEPEND = 1
	APP_LIBRARIES += SdlBuffer$(BUILDTYPE) ailog_interface$(BUILDTYPE)
endif

ifeq "$(DEST_TYPE)" "APP"
	TARGET_TYPE = DLL
	TARGET = $(addprefix $(OUTPUT_DIR),lib$(DEST)_app$(DLLTAIL))
	DLL_STEM_NAME = $(DEST)_app$(BUILDTYPE)
	INSTALL_PATH = $(OB_REL)/lib/
	INSTALL_LOCALPATH = $(OB_LOCAL)/lib/
	NEED_DATABASE = 1
	NEED_INSTALL = 1
	NEED_MAKE_DEPEND = 1
#	APP_LIBRARIES += SdlBuffer$(BUILDTYPE) ailog_interface$(BUILDTYPE)
endif

ifeq "$(DEST_TYPE)" "KERNEL"
	TARGET_TYPE = DLL
	TARGET = $(addprefix $(OUTPUT_DIR),lib$(DEST)_db$(DLLTAIL))
	DLL_STEM_NAME = $(DEST)_kernel$(BUILDTYPE)
	INSTALL_PATH = $(OB_REL)/lib/
	NEED_DATABASE = 1
	NEED_MIDDLE_WARE = 0
	NEED_INSTALL = 1
	NEED_SVR_CTRL = 0
	NEED_MAKE_DEPEND = 1
endif
#####################################################################
# 对当前工程选项的推导
TOTAL_DEFS = $(DEFS)
TOTAL_DEFS += $(addprefix __SDL_,$(addsuffix _SDL_C_IMPL__,$(basename $(shell echo $(PURE_IMPL_SDL) | tr "[a-z]" "[A-Z]"))))
#TOTAL_UNITTEST_DEFS ?= #protected=public private=public
TOTAL_CXX_FLAGS = $(CXX_FLAGS) $(PIC_FLAGS)
#TOTAL_INC_PATH = $(OB_REL)/include/ #$(OB_REL)/include/3rd $(OB_REL)/include/cdk/foundation $(OB_REL)/include/public
TOTAL_LD_FLAGS = $(LD_FLAGS)
TOTAL_LD_PATH = $(SYS_LDPATH)
TOTAL_SHLD_FLAGS = $(SHLD_FLAGS)
TOTAL_LIBRARIES = $(SYS_LIBS)

TOTAL_SDL_INC_PATH = ../idl ./idl .
TOTAL_RDL_INC_PATH = ../rdl ./rdl .

# SDL规范检查选项，SDLCHECK_NEED_FLAG默认0为关闭，
# SDLCHECK_BASE_TYPE表示检查的文件方式，
#     SVN-基于SVN的text-base目录，
#     OLD_SUFF由用户指定带.old的方式
#     BASE_DIR由用户指定文件目录
SDLCHECK_NEED_FLAG ?= 0
SDLCHECK_BASE_TYPE ?= SVN

#TBC...
ifneq "$(IMPL_SDL_EXT)" ""
	TOTAL_SDL_INC_PATH += $(OB_SRC_CYGWIN)/$(SUBSYSTEM)/$(IMPL_SDL_EXT_PATH)
endif


TOTAL_SDL_INC_PATH += $(OB_REL)/idl $(USER_SDL_INC_PATH) $(SDL_INC_PATH)
TOTAL_RDL_INC_PATH += $(OB_REL)/rdl $(USER_RDL_INC_PATH)

TOTAL_XBUF_PATH += $(USER_XBUF_PATH)

DEST_SOURCES_ORIGIN = $(DEST_SOURCES)
ifneq "$(MAKEFILE_NAME)" ""
MAKEFILE_NAME := $(MAKEFILE_NAME)\#
endif
#若设置了测试报告汇总路径
ifneq "$(UNITTEST_REPORT_SUM_DIR)" ""
	ifneq "$(notdir $(UNITTEST_REPORT_SUM_DIR))" ""
		UNITTEST_REPORT_SUM_DIR := $(UNITTEST_REPORT_SUM_DIR)/
	endif
	UNITTEST_CREATE_REPORTDIR += mkdir -p $(UNITTEST_REPORT_SUM_DIR);
	ifeq "$(UNITTEST_REPORT_SUM_NAME)" ""
    UNITTEST_OPTION += -s $(UNITTEST_REPORT_SUM_DIR)$(subst /,\#,$(DEST_REL_PATH))\#
  else
    UNITTEST_OPTION += -s $(UNITTEST_REPORT_SUM_DIR)$(UNITTEST_REPORT_SUM_NAME)
	endif
endif
#-p的参数不允许#开头，若OB_SRC设置不合理则可能出现这种情况
ifeq "$(DEST_REL_PATH)" "$(shell pwd)"
	UNITTEST_OPTION += -p _$(subst /,\#,$(DEST_REL_PATH))\#$(MAKEFILE_NAME)
else
	UNITTEST_OPTION += -p $(subst /,\#,$(DEST_REL_PATH))\#$(MAKEFILE_NAME)
endif
ifeq "$(UNITTEST_TOTAL_ON)" "0"
	NEED_UNITTEST = 0
	NEED_COVERTEST = 0
endif
ifeq "$(DEST_SOURCES)" ""
        NEED_UNITTEST = -1
endif
ifeq "$(NEED_UNITTEST)" "1"
	UNITTEST_PROGRAM=unittest_$(DEST)_main
	UNCPP2UNIT_SOURCES2 = $(filter-out $(UNCPP2UNIT_SOURCES),$(DEST_SOURCES_ORIGIN))	
	UNITTEST_SOURCES += test/unittest_$(DEST)_main.cpp 
	ifneq "$(NEED_AUTO_UNITTEST_SOURCES)" "0"
		UNITTEST_SOURCES += $(foreach i,$(DEST_SOURCES_ORIGIN), test/uttest_$(notdir $(i)))
		#UNITTEST_SOURCES += $(foreach i,$(DEST_SOURCES_ORIGIN), test/$(dir $(i))uttest_$(notdir $(i)))
	endif
	UNITTEST_SDL2CPP_GENERATED_SOURCES = $(addprefix test/,$(call Sdl2CppSource,$(UNITTEST_CALLED_SDL),_sdl_c))
	UNITTEST_SOURCES += $(filter-out %.h %.inc,$(UNITTEST_SDL2CPP_GENERATED_SOURCES))
	UNITTEST_SOURCES2 = $(subst $(OB_SRC),OB_SRC,$(UNITTEST_SOURCES))
	UNITTEST_SOURCES3 = $(subst /./,/,$(UNITTEST_SOURCES2://=/))
	UNITTEST_OBJS=$(subst /./,/,$(subst //,/, $(addprefix $(OUTPUT_DIR),$(UNITTEST_SOURCES3:.cpp=.o))))
	#UNITTEST_OBJS = $(subst $(OB_SRC),/OB_SRC,$(UNITTEST_OBJS_TMP))
	UNITTEST_CREATE_CODE = $(sort $(dir $(UNITTEST_SOURCES3)))
	ifneq "$(TARGET_TYPE)" "DLL"
		UNITTEST_ORIGIN_LIB = $(OUTPUT_DIR)lib$(DEST)$(DLLTAIL)
	endif
	TOTAL_INC_PATH += ./test
	UNITTEST_TOTAL_SDL_INC_PATH += ./test
	#测试明细默认输出到./test/report目录
	ifeq "$(UNITTEST_REPORT_DTL_DIR)" ""
		UNITTEST_REPORT_DTL_DIR = $(shell pwd)/test/report/
	else
		ifneq "$(notdir $(UNITTEST_REPORT_DTL_DIR))" ""
			#结尾增加/符号
			UNITTEST_REPORT_DTL_DIR := $(UNITTEST_REPORT_DTL_DIR)/
		endif 
	endif
	UNITTEST_OPTION += -r $(UNITTEST_REPORT_DTL_DIR)
	UNITTEST_CREATE_REPORTDIR += mkdir -p $(UNITTEST_REPORT_DTL_DIR);
	ifeq "$(NEED_COVERTEST)" "1"
		UNITTEST_OPTION += -c
		UNITTEST_GCOV_LIBS = -ftest-coverage -fprofile-arcs
		UNITTEST_TMP_SOURCES=$(foreach i,$(DEST_SOURCES), $(OUTPUT_DIR)$(i))
		FILTER_OUT_DIR=$(filter-out ../ ./, $(foreach i,$(DEST_SOURCES), $(dir $(i))))
		UNITTEST_TMP_DIR=$(foreach i,$(FILTER_OUT_DIR), $(OUTPUT_DIR)$(i))
	endif
	ADDTIONAL_TEST_LIBS += UnitTest++ cdk_foundation$(BUILDTYPE)# cdk_datetime$(BUILDTYPE)
	ifneq "$(TOTAL_CALLED_SDL)" ""
		USER_DEFS += UNITTEST_NEED_SDL
		ADDTIONAL_TEST_LIBS += public_sdl_basic$(BUILDTYPE)
	else
		ifneq "$(IMPL_SDL)" ""
			USER_DEFS += UNITTEST_NEED_SDL
			ADDTIONAL_TEST_LIBS += public_sdl_basic$(BUILDTYPE)
		endif
	endif
#	ifneq "$(UNITTEST_SDL_INC_PATH)" ""
#		ADDTIONAL_TEST_LIBS += SdlBuffer$(BUILDTYPE)
#	endif
	UNITTEST_DEPENDENCIES += $(TARGET) $(UNITTEST_SOURCES) $(UNITTEST_OBJS)
	vpath %.sdl $(UNITTEST_SDL_INC_PATH)
else
	#若未设置unitttest，则无法进行gcov
	NEED_COVERTEST = 0
endif

ifeq "$(NEED_ERRCFG)" "1"
	DEST_SOURCES+=$(ERRCFG_DEF).cpp
endif

#####################################################################
# g++ env Pre-Compiled Header file definition (PCH)
PCH_H = $(OB_REL)/include/stdafx.h
PCH = $(OB_REL)/include/stdafx.h.gch
SOURCE_PCH=$(OB_SRC)/global/stdafx.h.gch

TARGET_OBJS = $(call Source2Object,$(DEST_SOURCES))
ifneq "$(DEST_IDLS)" ""
    TARGET_OBJS += $(foreach i,$(patsubst %.idl,%,$(notdir $(DEST_IDLS))),$(i)_c.o $(i)_s.o)
    NEED_MIDDLE_WARE = 1
endif

ifneq "$(USER_INSTALL_PATH)" ""
	INSTALL_PATH = $(USER_INSTALL_PATH)/
	INSTALL_LOCALPATH = $(USER_INSTALL_PATH)/
endif

AUTO_DEPEND_SOURCE = $(filter-out %.cc %.c,$(DEST_SOURCES))
IMP_SOURCE_CPP = $(patsubst %.sdl,%_imp.cpp,$(notdir $(PURE_IMPL_SDL)))
IMP_SOURCE_IN_DEST = $(findstring $(IMP_SOURCE_CPP),$(DEST_SOURCES))
ifeq "$(IMP_SOURCE_IN_DEST)" ""
	AUTO_DEPEND_SOURCE += $(IMP_SOURCE_CPP)
endif 

ifneq "$(NEED_FASTDEPEND)" "0"
	AUTO_DEPENDED_FILE = $(addprefix $(OUTPUT_DIR),$(patsubst %.cpp,%.d, $(notdir $(AUTO_DEPEND_SOURCE))))
endif

# BEGIN SHIYM ADD FOR SDL FASTDEPEND
AUTO_DEPENDED_SDL = $(addprefix $(OUTPUT_DIR), $(patsubst %.sdl, %.s, $(notdir $(CALLED_SDL)))) $(addprefix $(OUTPUT_DIR), $(patsubst %.sdl, %.s, $(notdir $(IMPL_SDL))))
# END SHIYM

ifneq "$(NEED_MAKE_DEPEND)" "0"
#	TOTAL_DEPENDENCIES = $(AUTO_DEPENDED_FILE)
	TOTAL_DEPENDENCIES = $(filter-out %.h %.inc,$(TOTAL_GENERATED_SOURCES)) $(DEST_SOURCES)
endif

ifneq "$(NEED_DATABASE)" "0"
	TOTAL_DEFS += $(DB_DEFS)
	TOTAL_INC_PATH += $(DB_INC_PATH)
	SYS_LDPATH += /usr/lib/64
	SYS_LDPATH += $(DB_LD_PATH)
	TOTAL_LIBRARIES += $(DB_LIBRARIES)
endif

ifeq "$(NEED_VERSION_CTRL)" "1"
	#APP_LIBRARIES += SdlBuffer$(BUILDTYPE)
	APP_DEPENDENCIES += $(addprefix,$(OUTPUT_DIR),$(MAKEVER_FILE))
	NEED_MAKE_DEPEND = 1
endif

USER_DEFS +=  UNNEED_BASE_LIB
TOTAL_DEFS += $(USER_DEFS)
TOTAL_UNITTEST_DEFS += $(USER_UNITTEST_DEFS)
TOTAL_CXX_FLAGS += $(USER_CXXFLAGS)
TOTAL_INC_PATH += $(CYGWIN_GCC_INC) $(APP_INC_PATH) $(USER_INC_PATH) $(OB_REL)/include $(OB_REL)/include/$(SUBSYSTEM) $(OB_REL)/include/3rd/UnitTest
TOTAL_INC_PATH += $(OB_REL)/include/3rd $(OB_REL)/include/cdk/foundation $(OB_REL)/include/cdk/datetime $(OB_REL)/include/public
TOTAL_LD_FLAGS += $(USER_LDFLAGS)
TOTAL_LD_PATH += $(OUTPUT_DIR) $(USER_LD_PATH)
ifneq "$(OB_LOCAL)" ""
	TOTAL_LD_PATH += $(OB_LOCAL)/lib $(OB_REL)/lib
	TOTAL_INC_PATH := $(OB_LOCAL)/include $(TOTAL_INC_PATH)
else
	TOTAL_LD_PATH += $(OB_REL)/lib
endif
TOTAL_SHLD_FLAGS += $(USER_SHLDFLAGS)
ifneq "$(IMPL_SDL)" ""
	USER_LIBRARIES += lua$(BUILDTYPE)
	USER_LIBRARIES += public_sdl_basic$(BUILDTYPE)
endif
ifneq "$(CALLED_SDL)" ""
	USER_LIBRARIES += lua$(BUILDTYPE)
	USER_LIBRARIES += public_sdl_basic$(BUILDTYPE)
endif
#由于public_frame中新链接了public_common_baseplus，为了减少其他模块链带修改，增加如下判断
#ifneq "$(findstring public_frame$(BUILDTYPE), $(USER_LIBRARIES))" ""
	#USER_LIBRARIES += public_common_baseplus$(BUILDTYPE)
#endif
TOTAL_LIBRARIES += $(APP_LIBRARIES) $(USER_LIBRARIES)
ifeq "$(USER_MESSAGE_PATH)" ""
	APP_MESSAGE_PATH = $(OB_SRC_CYGWIN)/message
else
	APP_MESSAGE_PATH = $(USER_MESSAGE_PATH)
endif

SDL2CPP_GENERATED_DB_SOURCES = $(call Sdl2CppSource,$(PURE_IMPL_DB_SDL),_sdl_c)
SDL2CPP_GENERATED_SOURCES = $(call Sdl2CppSource,$(PURE_IMPL_DB_SDL),_sdl_c) \
	$(call Sdl2CppSource,$(PURE_IMPL_CVT_SDL),_sdl_c) \
	$(call Sdl2CppSource,$(PURE_IMPL_DEF_SDL),_sdl_c) \
	$(call Sdl2CppSourceExt,$(PURE_IMPL_SDL),_sdl_c) \
	$(call Sdl2CppSource,$(PURE_IMPL_SDL),_sdl_s) \
	$(call Sdl2CppSource,$(PURE_IMPL_SDL),_imp) \
	$(call Sdl2CppSource,$(PURE_CALLED_DEF_SDL),_sdl_c) \
	$(call Sdl2CppSource,$(PURE_CALLED_CVT_SDL),_sdl_c) \
	$(call Sdl2CppSourceExt,$(PURE_CALLED_SDL),_sdl_c)

DEST_SOURCES +=  $(foreach i,$(patsubst %.sdl,%,$(notdir $(PURE_IMPL_SDL))),$(i)_sdl_init.cpp)

ifneq "$(IMPL_XCD)" ""
ifeq "$(NEED_XC_SPLIT)" "1"
XC2CPP_GENERATED_SOURCES = $(shell xc2code -i $(IMPL_XCD) -C $(XC_CFG_PATH) -D $(XC_DBCONN) -T $(DB_TYPE) -v build/xc_cpp_file.list)
XC2CPP_GENERATED_OBJS = $(patsubst %.cpp, %.o, $(XC2CPP_GENERATED_SOURCES))
else
XC2CPP_GENERATED_SOURCES = $(call Xc2CppSource, $(IMPL_XCD))
XC2CPP_GENERATED_OBJS = $(call Source2Object, $(IMPL_XCD))
endif
endif

SDL2CPP_GENERATED_OBJS = $(call Source2ObjectExt,$(IMPL_SDL),_sdl_c) \
	$(call Source2ObjectExt,$(IMPL_SDL_EXT),_sdl_c) \
	$(call Source2ObjectExt,$(PURE_IMPL_SDL),_sdl_s) \
	$(call Source2ObjectExt,$(PURE_IMPL_SDL),_imp) \
	$(call Source2ObjectExt,$(PURE_CALLED_DEF_SDL),_sdl_c) \
	$(call Source2ObjectExt,$(PURE_CALLED_CVT_SDL),_sdl_c) \
	$(call Source2ObjectExt,$(PURE_CALLED_SDL),_sdl_c)

EMS2CPP_GENERATED_SOURCES = $(call Msg2CppSource,$(MESSAGE_FILE))
EMS2CPP_GENERATED_OBJS = $(call Source2Object,$(MESSAGE_FILE:%.ems=%_msg.o))

RDL2CPP_GENERATED_SOURCES = $(call Rdl2CppSource,$(IMPL_RDL),_rdl)
RDL2CPP_GENERATED_OBJS = $(call Source2ObjectExt,$(IMPL_RDL),_rdl)
ifeq "$(NEED_VERSION_CTRL)" "1"
	ifeq "$(TARGET_TYPE)" "DLL"
		VER_OBJS = $(VER_NAME).o
		VER_SOURCES = $(VER_NAME).cpp
	endif
else
	VER_OBJS =
	VER_SOURCES =
endif

#VER_OBJS =
#VER_SOURCES =

TOTAL_OBJS_TEMP = $(addprefix $(OUTPUT_DIR),$(SDL2CPP_GENERATED_OBJS)) $(addprefix $(OUTPUT_DIR),$(EMS2CPP_GENERATED_OBJS)) \
	$(addprefix $(OUTPUT_DIR),$(CORBA_GENERATED_OBJS)) $(addprefix $(OUTPUT_DIR),$(TARGET_OBJS))  $(addprefix $(OUTPUT_DIR),$(VER_OBJS)) \
	$(addprefix $(OUTPUT_DIR),$(RDL2CPP_GENERATED_OBJS)) $(addprefix $(OUTPUT_DIR),$(XC2CPP_GENERATED_OBJS))
TOTAL_OBJS = $(sort $(TOTAL_OBJS_TEMP))
TOTAL_GENERATED_SOURCES = $(RDL2CPP_GENERATED_SOURCES) $(SDL2CPP_GENERATED_SOURCES) $(EMS2CPP_GENERATED_SOURCES) $(CORBA_GENERATED_SOURCES) \
	$(XC2CPP_GENERATED_SOURCES)\
	$(NAMEDQUERY_GENERATED_SOURCES) 

TOTAL_DEPENDENCIES += $(APP_DEPENDENCIES) $(TOTAL_OBJS)

#add by dengyong for rdl2cpp
IMPL_RDL_PATH_TEMP = $(foreach i,$(TOTAL_RDL_INC_PATH), $(addprefix $(i)/,$(IMPL_RDL)))
IMPL_RDL_PATH = $(foreach i,$(IMPL_RDL_PATH_TEMP), $(wildcard $(i)))

RDL_FILE_NAME = $(foreach i,$(IMPL_RDL_PATH),$(if $(shell grep "resource 'rdbms:" $i),$(notdir $i)))
RDL2SDL_FILE = $(foreach i,$(basename $(RDL_FILE_NAME)),$i_def.sdl)
RDL2SDL = $(foreach i,$(RDL2SDL_FILE),$(if $(findstring $i,$(CALLED_SDL)),,$i))

ifneq "$(IMPL_RDL)" ""
       #使用SAL时需要CALLED route_def.sdl, 依赖其产生的路由信息头文件
       #ifeq "$($(findstring route_def.sdl,$(CALLED_SDL)))"  ""
       #      CALLED_SDL += route_def.sdl
       #      USER_SDL_INC_PATH += $(OB_REL)/idl/public/route
       #endif
       #只有NEED_GEN_MAPREDUCE开启时才将mapreduce cpp文件添加到DEST_SOURCES中
       ifeq "$(NEED_GEN_MAPREDUCE)" "1"
	      DEST_SOURCES += $(foreach i,$(patsubst %.rdl,%,$(notdir $(IMPL_RDL))),$(i)_mapreduce_rdl.cpp)
       endif
endif

TOTAL_CALLED_SDL = $(CALLED_SDL)
TOTAL_CALLED_SDL += $(RDL2SDL)
#add end
TOTAL_XC_INC_PATH += .
TOTAL_XC_INC_PATH += $(USER_XC_INC_PATH)

SOURCE_PATH = . $(dir $(DEST_SOURCES))

vpath %.cpp $(SOURCE_PATH)
vpath %.sdl $(TOTAL_SDL_INC_PATH)
vpath %.idl $(OB_REL)/idl/openbroker
vpath %.xbuf $(TOTAL_XBUF_PATH)
vpath %.rdl $(TOTAL_RDL_INC_PATH)
vpath %.xcd $(TOTAL_XC_INC_PATH)

TOTAL_HEADERS = $(HEADERS)
ifneq "$(HEADER_PATH)" ""
	HEADER_INSTALL_PATH := $(HEADER_INSTALL_PATH)$(HEADER_PATH)/
	HEADER_INSTALL_LOCALPATH := $(HEADER_INSTALL_LOCALPATH)$(HEADER_PATH)/
endif
	
CXX_CMD_ARGS_NOGCOV = \
		$(TOTAL_CXX_FLAGS) \
		$(addprefix -D,$(TOTAL_DEFS)) \
		$(addprefix -D,$(TOTAL_UNITTEST_DEFS)) \
		$(addprefix -I,$(TOTAL_INC_PATH))
SDLCC_CMD_ARGS_UNITTEST = \
		$(SDLCC) \
		$(SDLCC_FLAGS) \
		$(addprefix -I,$(TOTAL_SDL_INC_PATH)) \
		$(addprefix -I,$(UNITTEST_SDL_INC_PATH)) \
		$(UNITTEST_GCOV_LIBS)

CXX_CMD_ARGS = $(TOTAL_CXX_FLAGS) $(addprefix -D,$(TOTAL_DEFS)) $(addprefix -I,$(TOTAL_INC_PATH)) $(UNITTEST_GCOV_LIBS)
SDL_CXX_CMD_ARGS = $(TOTAL_CXX_FLAGS) $(addprefix -D,$(TOTAL_DEFS)) $(addprefix -I,$(TOTAL_INC_PATH)) $(UNITTEST_GCOV_LIBS)
SDLCC_CMD_ARGS = $(SDLCC) $(SDLCC_FLAGS) $(addprefix -I,$(TOTAL_SDL_INC_PATH)) $(UNITTEST_GCOV_LIBS)
SDLCHECK_CMD_ARGS = $(SDLCHECK) $(SDLCC_FLAGS) $(addprefix -I,$(TOTAL_SDL_INC_PATH)) $(addprefix -B,$(BASE_SDL_INC_PATH))

### New MACRO Defined 4 Called Sdl Has Namespace [lizj 2009-0224]
SDL_NAMESPACE_FLAG = -ns:$(strip $(SDL_NAMESPACE))
SDLCC_CMD_ARGS_EXT = $(SDLCC) $(SDLCC_FLAGS) $(SDL_NAMESPACE_FLAG) $(addprefix -I,$(TOTAL_SDL_INC_PATH))
### end of Macro Defined

ifeq "$(DEBUG)" "1"
	CXX_CMD_ARGS += $(addprefix -D,$(DEBUG_DEFS)) $(DEBUG_FLAGS)
	CXX_CMD_ARGS_NOGCOV += $(addprefix -D,$(DEBUG_DEFS)) $(DEBUG_FLAGS)
	SDL_CXX_CMD_ARGS += $(addprefix -D,$(DEBUG_DEFS)) $(DEBUG_FLAGS)
endif

TOTAL_OBJS+=$(USER_DEF_OBJS)

LD_CMD_ARGS = $(TOTAL_LD_FLAGS) $(addprefix -L,$(TOTAL_LD_PATH)) $(addprefix -l,$(sort $(TOTAL_LIBRARIES))) $(UNITTEST_GCOV_LIBS)
SHLD_CMD_ARGS = $(TOTAL_SHLD_FLAGS) $(addprefix -L,$(TOTAL_LD_PATH)) $(addprefix -l,$(sort $(TOTAL_LIBRARIES))) $(UNITTEST_GCOV_LIBS)
DO_LD_CMD = $(LD) $(TOTAL_OBJS) $(LD_CMD_ARGS) -o $@
ifeq "$(OBMW_TYPE)" "TUXEDO_ATMI"
	ifeq "$(DEST_TYPE)" "SVR"
		ifeq "$(OS_TYPE)" "SunOS"
			ifneq "$(INST_DEST)" ""
				DO_LD_CMD = CC=$(CXX); DEST=$(DEST);export INST_DEST=$(INST_DEST); LD_CMD_ARGS="$(LD_CMD_ARGS) -lCrun"; . ./build_$(DEST)_svr.sh
			else
				DO_LD_CMD = CC=$(CXX); DEST=$(DEST); LD_CMD_ARGS="$(LD_CMD_ARGS) -lCrun"; . ./build_$(DEST)_svr.sh
			endif
		else
			ifneq "$(INST_DEST)" ""
				DO_LD_CMD = export CC=$(CXX); export DEST=$(DEST); export INST_DEST=$(INST_DEST); export LD_CMD_ARGS="$(LD_CMD_ARGS)"; . ./build_$(DEST)_svr.sh
			else
				DO_LD_CMD = export CC=$(CXX); export DEST=$(DEST); export LD_CMD_ARGS="$(LD_CMD_ARGS)"; . ./build_$(DEST)_svr.sh
			endif
		endif
	endif
endif


TARGET ?= $(SDL2CPP_GENERATED_SOURCES)

#add by dengyong for DLL版本管理
ifeq "$(VERSION_MAJOR)" ""
	VERSION_MAJOR = 0
endif
ifeq "$(VERSION_MINOR)" ""
	VERSION_MINOR = 0
endif
ifeq "$(VERSION_ADJUST)" ""
	VERSION_ADJUST = 0
endif
VERSION_NUM = .$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_ADJUST).$(VERSION_COMPILE)
VERSION_COMPILE ?= $(COMPILE_NUM_OF_YEAR)$(COMPILE_DAY_OF_YEAR)$(COMPILE_HOUR_DIV_THREE)
COMPILE_DAY_OF_YEAR = $(shell date +%m%d)
COMPILE_NUM_OF_YEAR = $(shell expr `date +%y` % 10)
COMPILE_HOUR_DIV_THREE = $(shell expr `date +%H` / 3)
	
# 解析依赖库，获取依赖库版本，检查APP_LIBRARIES\USER_LIBRARIES,检查路径依次
#为$(TOTAL_LD_PATH)值:(OB_LOCAL)/lib $(APP_LD_PATH) $(USER_LD_PATH) $(OB_REL)/lib

bind_fun = $(foreach i,$(1),$(wildcard $(addprefix $i/,lib$(2).$(DLLEXT))))
USE_LIBRARIES_PATH = $(foreach i,$(APP_LIBRARIES) $(USER_LIBRARIES),$(call bind_fun,$(TOTAL_LD_PATH),$i))
#readlink不通用，在HP_UNIX和sun平台上命令不存在，修改成从ls -l命令中提取,并且将USER_LIB_VERSION去掉路径信息
LABEL_STR = -> 
GET_SYMBOLIC_TAR = $(if $(findstring $(LABEL_STR),$(shell ls -l $1)),$(strip $(shell ls -l $1 | cut -d'>' -f2)),$2)
USER_LIB_VERSION = $(foreach i,$(USE_LIBRARIES_PATH),$(notdir $(call GET_SYMBOLIC_TAR,$i,$i)))

ifneq "$(INSTALL_PATH)" ""
	ifneq "$(INSTALL_NAME)" ""
		ifneq "$(wildcard $(INSTALL_PATH)$(INSTALL_NAME)$(notdir $(TARGET)))" ""
			DLL_NAME = $(call GET_SYMBOLIC_TAR,$(INSTALL_PATH)$(INSTALL_NAME)$(notdir $(TARGET)),)
		endif
	else
		ifneq "$(wildcard $(INSTALL_PATH)$(notdir $(TARGET)))" ""
			DLL_NAME = $(call GET_SYMBOLIC_TAR,$(INSTALL_PATH)$(notdir $(TARGET)),)
		endif
	endif
endif

ifneq "$(OB_LOCAL)" ""
	ifneq "$(INSTALL_NAME)" ""
		ifneq "$(wildcard $(INSTALL_LOCALPATH)$(INSTALL_NAME)$(notdir $(TARGET)))" ""
			DLL_NAME_LOCAL = $(call GET_SYMBOLIC_TAR,$(INSTALL_LOCALPATH)$(INSTALL_NAME)$(notdir $(TARGET)),)
		endif
	else
		ifneq "$(wildcard $(INSTALL_LOCALPATH)$(notdir $(TARGET)))" ""
			DLL_NAME_LOCAL = $(call GET_SYMBOLIC_TAR,$(INSTALL_LOCALPATH)$(notdir $(TARGET)),)
		endif
	endif
endif	
#add end

ifeq "$(NOT_USE_MODULE_DEFINE)" ""
	DEFS += MODULE_NAME=\"$(subst $(OB_SRC)/,,$(shell pwd))\"
endif

##########################################
# include AUTO_DEPENDED_SDL when clean_all, by SHIYM, 2012/11/08
# include AUTO_DEPENDED_SDL except AUTO_DEPENDED_SDL is null. shiym 2013/1/4
ifeq ($(MAKECMDGOALS),clean_all)
ifneq ("$(AUTO_DEPENDED_SDL)","")
        -include $(AUTO_DEPENDED_SDL)
endif
endif
#########################################

ifneq "$(NAMEDQUERY_SOURCES)" ""
	#强制加上_sql后缀
	NAMEDQUERY_SOURCES_1 = $(patsubst %.sql, %, $(NAMEDQUERY_SOURCES))
	NAMEDQUERY_SOURCES_2 = $(foreach i,$(NAMEDQUERY_SOURCES_1),$(i)_sql)
	#xxx_sql_ORACLE.cpp xxx_sql.h
	DEST_SOURCES += $(foreach i,$(NAMEDQUERY_SOURCES_2),$(i)_$(DB_TYPE).cpp)
	NAMEDQUERY_GENERATED_SOURCES = $(foreach i,$(NAMEDQUERY_SOURCES_2),$(i)_$(DB_TYPE).cpp) $(foreach i,$(NAMEDQUERY_SOURCES_2),$(i).h)
endif 

#业务可定制通用定义
include $(OB_REL)/etc/BizCommon.mk

#####################################################################
# Makefile 的规则
.PHONY: all checkenv clean clean_all rebuild depend install install_headers install_idl install_all make_install_all check_rule unittest

# 第一条规则
all: $(TARGET) cppcheck genunit $(UNITTEST_PROGRAM) $(VB_SVR) install_local
$(OUTPUT_DIR)%_sdl_c.o: %_sdl_c.cpp
	mkdir -p $(OUTPUT_DIR)$(dir $<)
	$(CCACHE_PREFIX) $(CXX) $(SDL_CXX_CMD_ARGS) -c $< -o $@
$(OUTPUT_DIR)%_imp.o: %_imp.cpp
	mkdir -p $(OUTPUT_DIR)$(dir $<)
	$(CCACHE_PREFIX) $(CXX) $(SDL_CXX_CMD_ARGS) -c $< -o $@
$(OUTPUT_DIR)test/%.o: test/%.cpp
	mkdir -p $(OUTPUT_DIR)$(dir $<)
	$(CXX) $(CXX_CMD_ARGS_NOGCOV) -c $< -o $@
$(OUTPUT_DIR)%.o: %.cpp
	mkdir -p $(OUTPUT_DIR)$(dir $<)
ifeq "$(NEED_COVERTEST)" "1"	
	rm -f $(OUTPUT_DIR)$*.gcda $(OUTPUT_DIR)$*.gcno
	cp -p $< $(OUTPUT_DIR)
	@if [ ! -f "$(OUTPUT_DIR)$<" ];then \
		cp -p $< $(OUTPUT_DIR)$(dir $<); \
	fi
endif
	$(CCACHE_PREFIX) $(CXX) $(CXX_CMD_ARGS) -c $< -o $@
$(OUTPUT_DIR)%.o: %.cc
	mkdir -p $(OUTPUT_DIR)$(dir $<)
	$(CCACHE_PREFIX) $(CXX) $(CXX_CMD_ARGS) -c $< -o $@
$(OUTPUT_DIR)%.o: %.c
	mkdir -p $(OUTPUT_DIR)$(dir $<)
	$(CCACHE_PREFIX) $(CC) $(CXX_CMD_ARGS) -c $< -o $@

#add by dengyong for rdl2cpp
ifeq "$(NEED_GEN_MAPREDUCE)" "1"
%_rdl.cpp %_mapreduce_rdl.cpp %_rdl.h: %.rdl
    ifeq "$(NEED_GEN_ASYN)" "0"
	rdl2cpp -g -m $<
    else
	rdl2cpp -g -m -a $<
    endif
else
%_rdl.cpp %_rdl.h: %.rdl
    ifeq "$(NEED_GEN_ASYN)" "0"
        ifeq "$(NEED_GEN_NORMALCLOUD)" "1"
	rdl2cpp -g -n $<
    	else
	rdl2cpp -g $<
        endif
    else
        ifeq "$(NEED_GEN_NORMALCLOUD)" "1"
	rdl2cpp -g -n -a $<
        else
	rdl2cpp -g -a $<
        endif
    endif
endif
#add end

ifneq "$(IMPL_XCD)" ""
ifeq "$(NEED_XC_SPLIT)" "1"
$(XC2CPP_GENERATED_SOURCES): $(IMPL_XCD)
else
%.cpp %.h: %.xcd
endif
	xc2code -i $< -C $(XC_CFG_PATH) -D $(XC_DBCONN) -T $(DB_TYPE)
endif

%_sdl_s.h %_sdl_s.cpp: %.sdl
	$(SDLCC_CMD_ARGS) -gs -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) $<

%_sdl_c.h %_sdl_c.cpp %_sdl_c.inc: %.sdl
  ifeq "$(SDLCHECK_NEED_FLAG)" "1"
    ifeq "$(SDLCHECK_BASE_TYPE)" "BASE_DIR"
			$(SDLCHECK_CMD_ARGS) -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) $< -b$(SDLCHECK_BASE_DIR)/$(notdir $<)
    else
      ifeq "$(SDLCHECK_BASE_TYPE)" "OLD_SUFF"
				$(SDLCHECK_CMD_ARGS) -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) $< -b$<.old
      else
				$(SDLCHECK_CMD_ARGS) -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) $< -b$(dir $<).svn/text-base/$(notdir $<).svn-base
      endif
    endif
  endif
ifeq "$(SDL_STRUCTMEM_PTRTYPE)" "1"
	$(SDLCC_CMD_ARGS) -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) -gc $<
else
	$(SDLCC_CMD_ARGS) -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) -gc -np $<
endif

#覆盖上面一行的生成规则
ifneq "$(SDL_CLIENT_NEED_NS)" "0"
$(GENED_FILE_WITHNS_4CLIENT):$(SDL_WITH_NS_4CLIENT)
	(for i in $(SDL_WITH_NS_4CLIENT); do $(SDLCC_CMD_ARGS_EXT) -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) -gc $$i; done;)
endif
	
%_imp.h %_imp.cpp: %.sdl
	$(SDLCC_CMD_ARGS) -gi -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) $<
### 增加_sdl_i.h/cpp的依赖规则 [2008-12-24]
%_sdl_i.h %_sdl_i.cpp: %.sdl
	$(SDLCC_CMD_ARGS) -gsi -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) $<

#增加生成_sdl_init.cpp和_sdl_init.h文件
%_sdl_init.h %_sdl_init.cpp: %.sdl
	$(SDLCC_CMD_ARGS) -ginit -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) $<

# unittest called_sdl support
test/%_sdl_c.h test/%_sdl_c.cpp test/%_sdl_c.inc: %.sdl
	$(SDLCC_CMD_ARGS_UNITTEST) -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) -gc -np $< -o./test

## 错误配置编译规则定义
ifeq "$(NEED_ERRCFG)" "1"
$(ERRCFG_DEF).cpp: $(ERRCFG_XML)
	efparser $(ERRCFG_XML) $(ERRCFG_DEF).cpp
endif

## cpp代码检查 [2011-06-03]
ifeq "$(NEED_CPPCHECK)" "1"
CPPCHECK_OPTION += $(addprefix -I,$(TOTAL_INC_PATH))
cppcheck:$(DEST_SOURCES_ORIGIN)
	@$(OB_REL)/bin/cppcheck $(CPPCHECK_OPTION) $(DEST_SOURCES_ORIGIN)
else
%_sql_$(DB_TYPE).cpp: %_$(DB_TYPE).sql
	@cat $*_$(DB_TYPE).sql | awk 'BEGIN{print "#ifndef _$*_SQL_H_\n#define _$*_SQL_H_\n#include \"common/baseplus/namedquery.h\""}{gsub("NQ_DEFINE", "NQ_DEFINE_HEAD");print $0}END{print "#endif"}' > $*_sql.h
	@cat $*_$(DB_TYPE).sql | awk 'BEGIN{print "#include \"$*_sql.h\""}{gsub("NQ_DEFINE", "NQ_DEFINE_BODY");print $0}END{print ""}' > $*_sql_$(DB_TYPE).cpp	
cppcheck:

endif

##单元测试代码框架
ifeq "$(NEED_UNITTEST)" "1"
ifneq "$(UNNEED_CPP2UNIT)" "1"
genunit:$(DEST_SOURCES_ORIGIN)
	$(foreach i,$(UNITTEST_CREATE_CODE), mkdir -p $(i);)
	$(OB_REL)/bin/cpp2unit -I$(DEST) $(UNCPP2UNIT_SOURCES2)
else
genunit:
endif
else
genunit:
endif

ifneq "$(TARGET_TYPE)" ""

$(TARGET): $(TOTAL_DEPENDENCIES)	
ifeq "$(TARGET_TYPE)" "EXE"
	$(CCACHE_PREFIX) $(DO_LD_CMD)
endif
ifeq "$(TARGET_TYPE)" "LIB"
	$(CCACHE_PREFIX) $(DO_AR_CMD)
endif
ifeq "$(TARGET_TYPE)" "DLL"
	$(CCACHE_PREFIX)  $(SHLD) $(TOTAL_OBJS) $(SHLD_CMD_ARGS) -o $@
endif
#删除3rd的代码，目标是不进行单元覆盖率统计
ifeq "$(NEED_COVERTEST)" "1"
	-@find build -name "*.cpp" | grep "\/3rd\/" | xargs rm -rf
endif
endif

$(UNITTEST_ORIGIN_LIB): $(TOTAL_DEPENDENCIES)
	$(CCACHE_PREFIX)  $(SHLD) $(TOTAL_OBJS) $(SHLD_CMD_ARGS) -o $(OUTPUT_DIR)lib$(DEST)$(DLLTAIL)

#added rules for pre compiled header file
ifeq "$(_USE_PCH)" "1"
ifeq "$(CXX)" "g++"
$(TOTAL_OBJS):$(PCH)
#$(PCH): $(PCH_H)
#	$(CCACHE_PREFIX) $(CXX) $(CXX_CMD_ARGS) -x c++-header $> $^
endif
endif
checkenv:
	@echo " 1.是否需要使用数据库 == " $(call CvtBool2Msg,$(NEED_DATABASE))
	@echo
	@echo " 2.是否需要将目标进行 install == " $(call CvtBool2Msg,$(NEED_INSTALL))
	@echo
	@echo " 3.是否需要生成 depend 文件 == " $(call CvtBool2Msg,$(NEED_MAKE_DEPEND))
	@echo
	@echo " 4.是否需要单元测试 == " $(call CvtBool2Msg,$(NEED_UNITTEST))
	@echo
	@echo " 5.源代码编译命令行"
	@echo "$(CXX) $(CXX_CMD_ARGS)"
	@echo
	@echo " 6.SDL 产生的源代码编译命令行:"
	@echo "$(CXX) $(SDL_CXX_CMD_ARGS)"
	@echo
	@echo " 7.动态库链接命令行"
	@echo "$(SHLD) $(SHLD_CMD_ARGS)"
	@echo
	@echo " 8.静态库链接命令行"
	@echo "$(DO_AR_CMD)"
	@echo
	@echo " 9.执行程序链接命令行"
	@echo "$(DO_LD_CMD)"
	@echo
	@echo " 10.SDL 文件编译命令行"
	@echo $(SDLCC_CMD_ARGS)
	@echo
	@echo " 11.编译目标类型 == " $(DEST_TYPE)
	@echo
	@echo " 12.目标安装路径"
	@echo $(INSTALL_PATH)
	@echo
	@echo " 13.目标文件名称"
	@echo $(TARGET)
	@echo
	@echo " 14.目标使用的 .o 文件"
	@echo $(TOTAL_OBJS)
	@echo
	@echo " 15.实现的 SDL 文件"
	@echo $(IMPL_SDL) $(IMPL_SDL_EXT)
	@echo
	@echo " 16.SDL 文件安装路径"
	@echo $(SDL_INSTALL_PATH)
	@echo
	@echo " 17.安装的 SDL 文件"
	@echo $(PURE_INSTALL_SDL) $(PURE_INSTALL_SDL_EXT)
	@echo
	@echo " 18.调用的 SDL 文件"
	@echo $(TOTAL_CALLED_SDL)
	@echo
	@echo " 19.头文件安装路径"
	@echo $(HEADER_INSTALL_PATH)
	@echo
	@echo " 20.安装的头文件"
	@echo $(TOTAL_HEADERS)
	@echo
	@echo " 21.自动生成的文件"
	@echo $(TOTAL_GENERATED_SOURCES) $(VER_SOURCES)
	@echo
	@echo " 22.目标的所有依赖"
	@echo $(TOTAL_DEPENDENCIES)
	@echo
	@echo " 23. 所有源代码路径"
	@echo $(SOURCE_PATH)
	@echo
	@echo " 24. os type"
	@echo $(OS_TYPE)
	@echo
clean:
	rm -rf $(TARGET) $(TOTAL_OBJS) $(CXXTMPOBJ) $(UNITTEST_PROGRAM) $(UNITTEST_OBJS) core
ifeq "$(NEED_COVERTEST)" "1"
	rm -rf $(UNITTEST_TMP_SOURCES) $(UNITTEST_TMP_DIR)
endif
ifeq "$(HAS_VB_SVR)" "1"
	rm -rf $(VB_SVR_DIR)
endif
ifeq "CLEAN_GCH" "1"
	rm -f $(SOURCE_PCH)
endif

clean_all:
ifeq "$(NEED_COVERTEST)" "1"
	rm -rf $(UNITTEST_TMP_SOURCES) $(UNITTEST_TMP_DIR)
endif
	rm -rf $(OUTPUT_DIR)
	rm -rf $(TARGET) $(TOTAL_OBJS) $(CXXTMPOBJ) $(TOTAL_GENERATED_SOURCES) $(VER_SOURCES) \
			$(UNITTEST_PROGRAM) $(UNITTEST_OBJS) $(UNITTEST_SDL2CPP_GENERATED_SOURCES)
	rm -rf $(VIDL2MW_GENERATED_FILES) $(AUTO_DEPENDED_FILE) $(AUTO_DEPENDED_SDL) $(MAKEVER_FILE) $(RDL2SDL_FILE) core
ifeq "CLEAN_GCH" "1"
	rm -f $(SOURCE_PCH)
endif

rebuild: clean_all all

install: all
ifneq "$(NEED_INSTALL)" "0"
  ifneq "$(INSTALL_PATH)" ""
    ifneq "$(NEED_DLOPEN_CHECK)" "0"
      ifneq "$(DEST_TYPE)" "BIN"
        ifeq "$(NOW_CHECK)" "0"
	$(DLLVER) sh $(TARGET)
        else
	$(DLLVER) sh -n $(TARGET)
        endif
      endif
    endif
    ifneq "$(INSTALL_NAME)" ""
	mkdir -p $(INSTALL_PATH)
      ifeq "$(NEED_VERSION_CTRL)" "1"
        ifneq "$(DLL_NAME)" ""
	$(DLLVER_SH) $(INSTALL_PATH)$(INSTALL_NAME)$(DLL_NAME) $(TARGET) $(INSTALL_PATH)$(INSTALL_NAME)$(notdir $(TARGET))$(VERSION_NUM) \
        $(notdir $(TARGET)$(VERSION_NUM) $(INSTALL_PATH)$(INSTALL_NAME)$(notdir $(TARGET) $(SAVE_HIS_LIBS)	
        else
	cp -rpf $(TARGET) $(INSTALL_PATH)$(INSTALL_NAME)$(notdir $(TARGET))$(VERSION_NUM)
	ln -s -f $(notdir $(TARGET)$(VERSION_NUM) $(INSTALL_PATH)$(INSTALL_NAME)$(notdir $(TARGET)
        endif
      else
	cp -rpf $(TARGET) $(INSTALL_PATH)$(INSTALL_NAME)
      endif
    else
	mkdir -p $(INSTALL_PATH)
      ifeq "$(NEED_VERSION_CTRL)" "1"
        ifneq "$(DLL_NAME)" ""
	$(DLLVER_SH) $(INSTALL_PATH)$(DLL_NAME) $(TARGET) $(INSTALL_PATH)$(notdir $(TARGET))$(VERSION_NUM) \
	$(notdir $(TARGET))$(VERSION_NUM) $(INSTALL_PATH)$(notdir $(TARGET)) $(SAVE_HIS_LIBS)
        else
	cp -rpf $(TARGET)  $(INSTALL_PATH)$(notdir $(TARGET))$(VERSION_NUM)
	ln -s -f $(notdir $(TARGET))$(VERSION_NUM) $(INSTALL_PATH)$(notdir $(TARGET))
        endif
      else
	cp -rpf $(TARGET)  $(INSTALL_PATH)
      endif
      ifneq "$(ADDTIONAL_INSTALL_CMD)" ""
	$(ADDTIONAL_INSTALL_CMD)
      endif
    endif
  endif
endif

ifneq "$(NEED_INSTALL)" "0"	
install_local:install_local_headers
ifneq "$(OB_LOCAL)" ""
ifneq "$(INSTALL_NAME)" ""
	mkdir -p $(INSTALL_LOCALPATH)
ifeq "$(NEED_VERSION_CTRL)" "1"
ifneq "$(DLL_NAME_LOCAL)" ""
	$(DLLVER_SH) $(INSTALL_LOCALPATH)$(INSTALL_NAME)$(DLL_NAME_LOCAL) $(TARGET) $(INSTALL_LOCALPATH)$(INSTALL_NAME)$(notdir $(TARGET))$(VERSION_NUM) \
	$(notdir $(TARGET))$(VERSION_NUM) $(INSTALL_LOCALPATH)$(INSTALL_NAME)$(notdir $(TARGET)) $(SAVE_HIS_LIBS)
else
	cp -rpf $(TARGET) $(INSTALL_LOCALPATH)$(INSTALL_NAME)$(notdir $(TARGET))$(VERSION_NUM)
	ln -s -f $(notdir $(TARGET))$(VERSION_NUM) $(INSTALL_LOCALPATH)$(INSTALL_NAME)$(notdir $(TARGET))
endif
else
	cp -rpf $(TARGET) $(INSTALL_LOCALPATH)$(INSTALL_NAME)
endif
else
	mkdir -p $(INSTALL_LOCALPATH)
ifeq "$(NEED_VERSION_CTRL)" "1"
ifneq "$(DLL_NAME_LOCAL)" ""
	$(DLLVER_SH) $(INSTALL_LOCALPATH)$(DLL_NAME_LOCAL) $(TARGET) $(INSTALL_LOCALPATH)$(notdir $(TARGET))$(VERSION_NUM) \
	$(notdir $(TARGET))$(VERSION_NUM) $(INSTALL_LOCALPATH)$(notdir $(TARGET)) $(SAVE_HIS_LIBS)
else
	cp -rpf $(TARGET) $(INSTALL_LOCALPATH)$(notdir $(TARGET))$(VERSION_NUM)
	ln -s -f $(notdir $(TARGET))$(VERSION_NUM) $(INSTALL_LOCALPATH)$(notdir $(TARGET))
endif
else
	cp -rpf $(TARGET)  $(INSTALL_LOCALPATH)
endif
endif
endif
else
install_local:
endif

BackUpGenSrc = $(foreach i,$(1),$(shell if [ -f $i ]; then \
	if [ ! -s $i ]; then \
	rm -rf $i;\
	else\
	mv $i .$i_bak; touch $i; \
	fi;\
	fi;))

CheckGenSrc = $(foreach i, $(1), $(shell xch=$i; xchbak="."$$xch"_bak";\
	if [ -f "$$xchbak" -a !	-s "$$xchbak" ]; then \
	rm -rf $$xchbak; \
	fi; \
	if [ -f "$$xch" -a !	-s "$$xch" ]; then \
	rm -rf $$xch; \
	fi; \
	if [ -f "$$xchbak" -a -f "$$xch" ]; then \
	diff $$xch $$xchbak | grep -v "Generated date" | wc -l | while read line; \
	do\
	if [ "$$line" = 0 -o "$$line" = 2 ]; then \
	rm -rf $$xch; mv $$xchbak $$xch;\
	fi; \
	done; \
	fi))

# 整个include目录需要安装时，可指定安装路径；安装路径默认为$(OB_REL)/include下两层目录
HEADERS_DIR_INSTALL_PATH?=$(OB_REL)/include/$(SUBSYSTEM)/$(MODULE_NAME)/

install_headers: regen_db_code gen_xc_src check_xc_head gen_db_sdl_src check_db_head $(TOTAL_HEADERS) $(TOTAL_GENERATED_SOURCES)
ifneq "$(NEED_INSTALL)" "0"
    ifneq "$(TOTAL_HEADERS)" ""
		mkdir -p $(HEADER_INSTALL_PATH) && cp -rpf $(TOTAL_HEADERS) $(HEADER_INSTALL_PATH)
    endif
    ifneq "$(HEADERS_DIR_NEED_INSTALL)" "" #  整个include目录需要安装
		mkdir -p $(HEADERS_DIR_INSTALL_PATH); cp -rpf $(shell pwd)/$(HEADERS_DIR_NEED_INSTALL)/* $(HEADERS_DIR_INSTALL_PATH)
    else
    ifneq "$(ADDTIONAL_INSTALL_HEADER_CMD)" ""
		$(ADDTIONAL_INSTALL_HEADER_CMD)
    endif
    endif
endif

gen_db_sdl_src:$(PURE_IMPL_DB_SDL)
ifneq "$(RE_GEN_DB_SDL)" "0"
ifneq "$(PURE_IMPL_DB_SDL)" ""
ifneq "$(PURE_IMPL_DB_SDL)" " "
	$(SDLCC_CMD_ARGS) -c$(OB_REL)/bin/sdl2cpp.cfg -C$(SDL_DBCONN) -gc -np $<
endif
endif
endif

check_db_head:
ifneq "$(RE_GEN_DB_SDL)" "0"
ifneq "$(PURE_IMPL_DB_SDL)" ""
ifneq "$(PURE_IMPL_DB_SDL)" " "
	$(call CheckGenSrc, $(SDL2CPP_GENERATED_DB_SOURCES))
endif
endif
endif

gen_xc_src:$(IMPL_XCD)
ifneq "$(RE_GEN_XC_CODE)" "0"
ifneq "$(IMPL_XCD)" ""
	xc2code -i $< -C $(XC_CFG_PATH) -D $(XC_DBCONN) -T $(DB_TYPE)
endif
endif

check_xc_head:
ifneq "$(RE_GEN_XC_CODE)" "0"
ifneq "$(IMPL_XCD)" ""
	$(call CheckGenSrc, $(XC2CPP_GENERATED_SOURCES))
endif
endif


install_local_headers: $(TOTAL_HEADERS)
ifneq "$(OB_LOCAL)" ""
ifneq "$(NEED_INSTALL)" "0"
    ifneq "$(TOTAL_HEADERS)" ""
		mkdir -p $(HEADER_INSTALL_LOCALPATH) && cp -rpf $(TOTAL_HEADERS) $(HEADER_INSTALL_LOCALPATH)
    endif
    ifneq "$(ADDTIONAL_INSTALL_HEADER_CMD)" ""
		$(ADDTIONAL_INSTALL_HEADER_CMD)
    endif
endif
endif

ifneq "$(SELFDEF_SDL_INSTALL_PATH)" ""
SDL_INSTALL_PATH = $(SELFDEF_SDL_INSTALL_PATH)
endif

install_idl: $(IMPL_SDL) $(IMPL_SDL_EXT)
ifneq "$(NEED_INSTALL)" "0"
ifneq "$(PURE_INSTALL_SDL)" ""
ifneq "$(PURE_INSTALL_SDL)" " "
		mkdir -p $(SDL_INSTALL_PATH) && cp -rpf $(PURE_INSTALL_SDL) $(SDL_INSTALL_PATH)
endif
endif
ifneq "$(PURE_INSTALL_SDL_EXT)" ""
	mkdir -p $(SDL_INSTALL_PATH) && cp -rpf $(PURE_INSTALL_SDL_EXT) $(SDL_INSTALL_PATH)
endif
ifeq "$(DEST_TYPE)" "JAVA"
  ifneq "$(PURE_DOWNLOAD_SDL)" ""
		mkdir -p $(SDL_DOWNLOAD_PATH) && cp -rpf $(PURE_DOWNLOAD_SDL) $(SDL_DOWNLOAD_PATH)	
  endif
endif
ifneq "$(ADDTIONAL_INSTALL_IDL_CMD)" ""
	$(ADDTIONAL_INSTALL_IDL_CMD)
endif
endif

gsi: $(PURE_INSTALL_SDL) $(PURE_INSTALL_SDL_EXT)
	(for i in $^; do $(SDLCC_CMD_ARGS) -gsi $$i; done; )

install_all:install_headers install install_idl

ifneq "$(NEED_FASTDEPEND)" "0"
#modifyed by wangqj5 2013/06/05: 原来查找依赖头文件并未使用TOTAL_INC_PATH全部路径来匹配导致很多依赖找不到
$(OUTPUT_DIR)%.d:%.cpp
	mkdir -p $(OUTPUT_DIR)
	$(MKDEP) $(EXCLUDE_FLAG) $(addprefix -I,$(TOTAL_INC_PATH)) $(addprefix -P,$(TOTAL_SDL_INC_PATH)) $< > $@

# BEGIN FOR FASTDEPEND SDL   by SHIYM, 2012/10/24
$(OUTPUT_DIR)%.s:%.sdl
	mkdir -p $(OUTPUT_DIR)
	$(MKDEP) $(EXCLUDE_FLAG) $(addprefix -I, $(APP_INC_PATH)) $(addprefix -P,$(USER_SDL_INC_PATH)) $< > $@
	#cp build/sample01.t $@	
# END

$(MAKEVER_FILE): $(filter-out %.h,$(TOTAL_GENERATED_SOURCES)) $(DEST_SOURCES)
	mkdir -p $(OUTPUT_DIR)
	$(MKDEP)  $(EXCLUDE_FLAG) -Ver $(addprefix -I,$(APP_INC_PATH)) $(addprefix -I,$(USER_INC_PATH)) $(addprefix -P,$(TOTAL_SDL_INC_PATH)) $^ > $(MAKEVER_FILE)
endif #end of NEED_FASTDEPEND
	
$(VER_NAME).cpp: $(MAKEVER_FILE)
	$(DLLVER) gen $(TARGET) -d $^ -o $@ -u $(USER_LIB_VERSION)
		
# 注意保留空白规则
ifneq "$(NEED_MAKE_DEPEND)" "0"
#  ifneq "$(wildcard *.d)" ""
    ifneq ($(MAKECMDGOALS),clean)
      ifneq ($(MAKECMDGOALS),clean_all)
        ifneq ($(MAKECMDGOALS),checkenv)
          ifneq ($(MAKECMDGOALS),install_idl)
            ifneq ($(MAKECMDGOALS),install_headers)
ifneq "$(AUTO_DEPENDED_FILE)" ""
              include $(AUTO_DEPENDED_FILE) 
endif

# BEGIN: The following statement is added for  including the sdl dependent files. By SHIYM, 2012/10/25
ifneq "$(AUTO_DEPENDED_SDL)" ""
              include $(AUTO_DEPENDED_SDL)
endif
#END
            endif
          endif
        endif
      endif
    endif
#  endif

# MODIFIED BY SHIYM, 2012/10/24
# ADD $(AUTO_DEPENDED_SDL)
depend: $(AUTO_DEPENDED_FILE) $(AUTO_DEPENDED_SDL)
	
else
depend:

endif

ADDTIONAL_TEST_LIB_PATH+= $(OUTPUT_DIR)

ifneq "$(UNITTEST_PROGRAM)" ""
$(UNITTEST_PROGRAM): $(UNITTEST_ORIGIN_LIB) $(UNITTEST_DEPENDENCIES)
	$(LD) $(UNITTEST_ORIGIN_LIB) $(UNITTEST_OBJS) $(LD_CMD_ARGS) $(addprefix -L,$(ADDTIONAL_TEST_LIB_PATH)) -l$(DLL_STEM_NAME) $(addprefix -l,$(ADDTIONAL_TEST_LIBS)) -o $@ $(UNITTEST_LIB_SET)
endif

check_rule:
    ifneq "$(filter %_sdl_c.cpp %_sdl_s.cpp, $(DEST_SOURCES))" ""
		@echo "错误：在 DEST_SOURCES 中包含了 *_sdl_c.cpp 或者 *_sdl_s.cpp 等自动生成的文件"
		@echo "提示：请在 IMPL_SDL 或者 CALLED_SDL 中写对应的 SDL 名称"
    endif
    ifneq "$(filter %_cvt.sdl %_db.sdl, $(TOTAL_CALLED_SDL))" ""
		@echo "错误：在 CALLED_SDL 中包含了 *_cvt.sdl 或者 *_db.sdl 的文件"
		@echo "提示：请在 CALLED_SDL 中去掉这些 SDL 名称，改为头文件依赖，只有在 IMPL_SDL 中才需要做 cvt"
    endif
	@echo "完成 Makefile 的规则检查！"
	
ifeq "$(UNITTEST_EXEC_TIME)" ""
  UNITTEST_EXEC_TIME := $(shell date +%Y%m%d_%H%M%S)
endif
unittest:
ifeq "$(NEED_UNITTEST)" "1"
	rm -rf $(OUTPUT_DIR)*.gcda $(OUTPUT_DIR)*.gcov
	-@$(UNITTEST_CREATE_REPORTDIR)
	-$(UNITTEST_PROGRAM) $(UNITTEST_OPTION) -t $(UNITTEST_EXEC_TIME)
ifeq "$(NEED_COVERTEST)" "1"
	-@$(OB_REL)/bin/createGcovReport $(UNITTEST_OPTION) -t $(UNITTEST_EXEC_TIME) -f "$(notdir $(DEST_SOURCES_ORIGIN))"
endif
else
ifneq "$(NEED_UNITTEST)" "-1"
#若设置了汇总目录，则未开启单元测试也要调用
ifneq "$(UNITTEST_REPORT_SUM_DIR)" ""
	-@$(OB_REL)/bin/createGcovReport $(UNITTEST_OPTION) -t $(UNITTEST_EXEC_TIME)
endif
endif
endif
regen_db_code:
ifneq "$(RE_GEN_DB_SDL)" "0"
ifneq "$(SDL2CPP_GENERATED_DB_SOURCES)" ""
	$(call BackUpGenSrc, $(SDL2CPP_GENERATED_DB_SOURCES))
endif
endif
ifneq "$(RE_GEN_XC_CODE)" "0"
ifneq "$(XC2CPP_GENERATED_SOURCES)" ""
	$(call BackUpGenSrc, $(XC2CPP_GENERATED_SOURCES))
endif
endif
